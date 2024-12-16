/********************************************************************************
** Form generated from reading UI file 'QtSerialCom.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSERIALCOM_H
#define UI_QTSERIALCOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtSerialComClass
{
public:
    QWidget *centralWidget;
    QComboBox *comboBox;
    QLabel *Port;
    QLabel *PortStatus;
    QPushButton *OpenPortButton;
    QPlainTextEdit *TextBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtSerialComClass)
    {
        if (QtSerialComClass->objectName().isEmpty())
            QtSerialComClass->setObjectName(QString::fromUtf8("QtSerialComClass"));
        QtSerialComClass->resize(198, 377);
        centralWidget = new QWidget(QtSerialComClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(50, 10, 131, 20));
        Port = new QLabel(centralWidget);
        Port->setObjectName(QString::fromUtf8("Port"));
        Port->setGeometry(QRect(10, 0, 61, 31));
        PortStatus = new QLabel(centralWidget);
        PortStatus->setObjectName(QString::fromUtf8("PortStatus"));
        PortStatus->setGeometry(QRect(210, 30, 181, 20));
        OpenPortButton = new QPushButton(centralWidget);
        OpenPortButton->setObjectName(QString::fromUtf8("OpenPortButton"));
        OpenPortButton->setGeometry(QRect(50, 40, 131, 21));
        TextBox = new QPlainTextEdit(centralWidget);
        TextBox->setObjectName(QString::fromUtf8("TextBox"));
        TextBox->setGeometry(QRect(10, 69, 181, 241));
        QtSerialComClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtSerialComClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 198, 20));
        QtSerialComClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtSerialComClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtSerialComClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtSerialComClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtSerialComClass->setStatusBar(statusBar);

        retranslateUi(QtSerialComClass);
        QObject::connect(OpenPortButton, SIGNAL(clicked()), QtSerialComClass, SLOT(OpenPort()));

        QMetaObject::connectSlotsByName(QtSerialComClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtSerialComClass)
    {
        QtSerialComClass->setWindowTitle(QCoreApplication::translate("QtSerialComClass", "QtSerialCom", nullptr));
        Port->setText(QCoreApplication::translate("QtSerialComClass", "Port :", nullptr));
        PortStatus->setText(QString());
        OpenPortButton->setText(QCoreApplication::translate("QtSerialComClass", "Ouvrir le port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtSerialComClass: public Ui_QtSerialComClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSERIALCOM_H
