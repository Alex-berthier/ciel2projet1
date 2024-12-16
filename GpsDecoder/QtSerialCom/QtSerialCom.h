#pragma once

#include <QtWidgets/QMainWindow>
#include "Ui_QtSerialCom.h"
#include <qserialport.h>



class QtSerialCom : public QMainWindow
{
    Q_OBJECT

public:
    QtSerialCom(QWidget *parent = nullptr);
    ~QtSerialCom();

 

    

private:
   Ui::QtSerialComClass ui;
    QSerialPort* port;

public slots:
    
   //Slots d'ouverture du port
   void OpenPort();
   //Slots de lecture du port série
   void onSerialPortReadyRead();
   //Slot de découpage de la trames
   void decode(QString data);
   //Slot d'envoi de la trame en bdd
;
   //Slot de conversion des data de la trame vers des double
   void convertData(QString data);

};
