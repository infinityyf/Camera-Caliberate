#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CameraCaliberation.h"
#include "qtextcodec.h"
#include "qmessagebox.h"
#include "qdir.h"
#include "qfiledialog.h"
#include "qdebug.h"
#include "qlabel.h"
#include "qtextedit.h"
#include "qlistwidget.h"
#include "qpushbutton.h"
#include "qprogressdialog.h"
#include "qlineedit.h"
#include "Caliberation.h"	//±Í∂®¿‡
#include <fstream>
#include <iostream>
#include <vector>

class CameraCaliberation : public QMainWindow
{
	Q_OBJECT

public slots:
	void help();
	void openDir();
	void process();
	void save();

public:
	CameraCaliberation(QWidget *parent = Q_NULLPTR);
	QStringList SelectedFiles;
	QListWidget* imageList;
	Caliberation* caliberation;
	cv::Mat cameraMatrix;
	bool ready;
	void init();

private:
	Ui::CameraCaliberationClass ui;
};
