#pragma once

//����궨�࣬��ʹ�䵥����Ϊһ���߳̽�������

#ifndef CALIBERATION_H
#define CALIBERATION_H
#include "qthread.h"
#include "qstring.h"
#include <string>
#include <vector>

#include <opencv2\calib3d\calib3d.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <QtWidgets/QMainWindow>
#include "qtextcodec.h"
#include "qprogressdialog.h"
#include "qmessagebox.h"

class Caliberation{
public:
	Caliberation(QStringList, int , int , float );
	float proc;
	cv::Mat* cameraMatrix;
	//virtual void run();
	void run();
	
private:
	std::vector<std::string> files;
	int width;
	int height;
	float size;//�궨����
	
};

#endif 