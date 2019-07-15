/********************************************************************************
** Form generated from reading UI file 'CameraCaliberation.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERACALIBERATION_H
#define UI_CAMERACALIBERATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraCaliberationClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CameraCaliberationClass)
    {
        if (CameraCaliberationClass->objectName().isEmpty())
            CameraCaliberationClass->setObjectName(QString::fromUtf8("CameraCaliberationClass"));
        CameraCaliberationClass->resize(600, 400);
        menuBar = new QMenuBar(CameraCaliberationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        CameraCaliberationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CameraCaliberationClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CameraCaliberationClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CameraCaliberationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        CameraCaliberationClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CameraCaliberationClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CameraCaliberationClass->setStatusBar(statusBar);

        retranslateUi(CameraCaliberationClass);

        QMetaObject::connectSlotsByName(CameraCaliberationClass);
    } // setupUi

    void retranslateUi(QMainWindow *CameraCaliberationClass)
    {
        CameraCaliberationClass->setWindowTitle(QApplication::translate("CameraCaliberationClass", "CameraCaliberation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraCaliberationClass: public Ui_CameraCaliberationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERACALIBERATION_H
