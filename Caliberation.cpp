#include "Caliberation.h"
#include <iostream>

Caliberation::Caliberation(QStringList selectedfiles,int width,int height,float size) {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	for (QString str : selectedfiles) {
		this->files.push_back(str.toStdString());
	}
	this->width = width;
	this->height = height;
	this->size = size;
}

void Caliberation::run() {

	//首先获得标定板内角点的世界坐标，这里把标定板所在平面作为Z轴
	//提取角点，得到像素坐标
	cv::Size chessSize(9, 6);
	cv::Size imageSize;

	//获得角点的世界坐标
	std::vector<std::vector<cv::Point3f>> objectPoints;
	std::vector<cv::Point3f> eachPoints;
	//获得每张图片角点的像素位置
	std::vector<std::vector<cv::Point2f>> imagePoints;
	std::vector<cv::Point2f> corners;

	for (int k = 0; k < files.size();k++) {
		eachPoints.clear();
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				eachPoints.push_back(cv::Point3f(i * size, j * size, 0.0));
			}
		}
		objectPoints.push_back(eachPoints);
		cv::Mat pic = cv::imread(files[k], cv::IMREAD_COLOR);
		

		bool result = cv::findChessboardCorners(pic, chessSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
		//如果寻找角点失败
		if (!result) {
			cv::Mat gray;
			cv::cvtColor(pic,gray,cv::COLOR_RGB2GRAY);
			cv::find4QuadCornerSubpix(gray, corners, chessSize);
		}
		cv::drawChessboardCorners(pic, chessSize, corners, true);
		imageSize.width = pic.cols;
		imageSize.height = pic.rows;
		imagePoints.push_back(corners);
		proc = ((float)k / files.size())*0.9;
	}
	//定义内参矩阵
	cameraMatrix = new cv::Mat(3,3,CV_32FC1,cv::Scalar::all(0.0));
	//cv::Mat cameraMatrix2 = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0.0));

	//定义畸变系数
	cv::Mat distCoeffs = cv::Mat(1, 5, CV_32FC1, cv::Scalar::all(0.0));

	//定义旋转向量（之后通过罗德里格公式转换成举证）,位移矩阵
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
	cv::calibrateCamera(objectPoints,imagePoints,imageSize,*cameraMatrix,distCoeffs,rvecs,tvecs);

	proc = 1.0;

	//exec();

	
}