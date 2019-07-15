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

	//���Ȼ�ñ궨���ڽǵ���������꣬����ѱ궨������ƽ����ΪZ��
	//��ȡ�ǵ㣬�õ���������
	cv::Size chessSize(9, 6);
	cv::Size imageSize;

	//��ýǵ����������
	std::vector<std::vector<cv::Point3f>> objectPoints;
	std::vector<cv::Point3f> eachPoints;
	//���ÿ��ͼƬ�ǵ������λ��
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
		//���Ѱ�ҽǵ�ʧ��
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
	//�����ڲξ���
	cameraMatrix = new cv::Mat(3,3,CV_32FC1,cv::Scalar::all(0.0));
	//cv::Mat cameraMatrix2 = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0.0));

	//�������ϵ��
	cv::Mat distCoeffs = cv::Mat(1, 5, CV_32FC1, cv::Scalar::all(0.0));

	//������ת������֮��ͨ���޵����ʽת���ɾ�֤��,λ�ƾ���
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
	cv::calibrateCamera(objectPoints,imagePoints,imageSize,*cameraMatrix,distCoeffs,rvecs,tvecs);

	proc = 1.0;

	//exec();

	
}