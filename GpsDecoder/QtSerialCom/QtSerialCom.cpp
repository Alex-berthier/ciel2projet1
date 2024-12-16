#include "QtSerialCom.h"
#include <QSerialPortInfo>

QtSerialCom::QtSerialCom(QWidget* parent)
    : QMainWindow(parent), port(nullptr)
{
    ui.setupUi(this);

    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& info : availablePorts)
    {
        ui.comboBox->addItem(info.portName(), QVariant(info.portName()));
    }
}

QtSerialCom::~QtSerialCom()
{
    if (port && port->isOpen())
        port->close();
    delete port;
}

void QtSerialCom::OpenPort()
{
    if (ui.comboBox->currentIndex() >= 0)
    {
        if (port)
        {
            if (port->isOpen())
                port->close();
            delete port;
        }

        port = new QSerialPort(ui.comboBox->currentText(), this);
        QObject::connect(port, &QSerialPort::readyRead, this, &QtSerialCom::onSerialPortReadyRead);

        port->setBaudRate(QSerialPort::Baud9600);
        port->setDataBits(QSerialPort::Data8);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);
        port->setFlowControl(QSerialPort::NoFlowControl);

        if (port->open(QIODevice::ReadWrite))
        {
            ui.PortStatus->setText("Status port : Ouvert");
        }
        else
        {
            ui.PortStatus->setText("Status port : �chec d'ouverture");
            delete port;
            port = nullptr;
        }
    }
}

/* ////////////////////////////////////////////////////////////////////////////////////////////////////////
Le serial ready read va lire sur 510 byte le port s�rie par capture et lecture
Il va ensuite d�couper les data re�u pour ne garder qu'une trame GPGPA et l'envoyer vers la fonction d�code pour ne r�cup�rer que la partie qui contient les coordon�es
La fonction decode va ensuite envoyer vers convertData les donn�es pour les convertir en double et les envoyer vers la fonction sendToBdd pour les envoyer dans la base de donn�es
*/

//Lecture du port s�rie sur 510 bytes et envoie vers la fonction decode une trame d�coup� correctement qui va de GPGPA jusqu'� la fin de la trame
//Une partie de la fonction va chercher un d�but de trame GPGPA parmi ce qui est lu et va chercher si cette trame GPGPA a une fin et donc ne garder que la trame si elle est compl�te
void QtSerialCom::onSerialPortReadyRead()
{
  //Lecture du port s�rie sur 510 bytes
  if (port->bytesAvailable() >= 510)
  {
      QByteArray data = port->readAll();
      QString dataString(data);
      //Cherche une trame GPGPA compl�te dans la data
      if (dataString.contains("GPGGA"))
      {
          //D�coupe la trame pour ne garder que la partie GPGGA jusqu'� la fin de la trame
          QString dataString = dataString.mid(dataString.indexOf("GPGGA"), dataString.indexOf("\r\n"));
          //Envoie la trame vers la fonction decode pour ne garder que les coordon�es
          decode(dataString);
      }
  }
}
// D�code le Qstring de la trame pour ne garder que les coordon�es en brute et appel de la fonction convertData avec la trame brut d�cod� en param�tre
void QtSerialCom::decode(QString data)
{
    //R�cup�re uniquement la partie longitude et lattitude d'une trame compl�te et la stocke dans un Qstring pour l'envoyer vers convertData
    QString dataString = data.mid(data.indexOf("$GPGGA"), data.indexOf("\r\n"));
    //envoie vers convertData
    convertData(dataString);
}

//Converti les donn�es brut des coordon�es Qstring vers un double et envoie ce ses fonction vers la BDD avec la fonction sendtoBDD
void QtSerialCom::convertData(QString data)
{
    //Convertie les valeurs re�u en Qstring vers 2 double contenant la lattitude et la longitude
    double lattitude;
    double longitude;
    //Conversion de la lattitude du Qstring vers le double
    lattitude = data.mid(data.indexOf("$GPGGA"), data.indexOf(",")).toDouble();
    //Conversion de la longitude du Qstring vers le double
    longitude = data.mid(data.indexOf("$GPGGA"), data.indexOf(",")).toDouble();
    //Envoie les donn�es vers la fonction sendToBdd

    ui.TextBox->appendPlainText(QString::number( longitude , lattitude));
}
