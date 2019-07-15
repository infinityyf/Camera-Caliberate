#include "CameraCaliberation.h"

#include <iostream>
CameraCaliberation::CameraCaliberation(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//mainwindow 将窗口的各个区域进行封装
	init();
}

void CameraCaliberation::help() {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	QString content = Codec->toUnicode("实现通过张正友相机标定法对相机内参进行标定，接受多张标定棋盘格的照片，输出相机内参数据。");
	QMessageBox::information(NULL, Codec->toUnicode("工具说明"), content);
}

void CameraCaliberation::openDir() {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	QFileDialog* fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(Codec->toUnicode("选择标定图片"));
	fileDialog->setDirectory(QDir::currentPath());
	fileDialog->setFileMode(QFileDialog::ExistingFiles);//允许选择多个文件
	if (fileDialog->exec() == QDialog::Accepted) {//如果点击确认
		SelectedFiles = fileDialog->selectedFiles();//返回所选择的图片,包含多个图片
	}
	for (QString file : SelectedFiles)
	{
		//定义QListWidgetItem对象
		QListWidgetItem* imageItem = new QListWidgetItem;
		//为单元项设置属性
		imageItem->setIcon(QIcon(file));
		//重新设置单元项图片的宽度和高度
		imageItem->setSizeHint(QSize(100, 120));

		//将单元项添加到QListWidget中
		imageList->addItem(imageItem);
	}
	//显示QListWidget
	imageList->show();
}

void CameraCaliberation::process() {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	QString content = Codec->toUnicode("请选择图片");
	if (SelectedFiles.size() == 0) {
		QMessageBox::information(NULL, Codec->toUnicode("无法标定"), content);
		return;
	}


	caliberation = new Caliberation(SelectedFiles,9,6,28);
	caliberation->run();//标定线程启动

	
	
	QMessageBox::information(NULL, QString("done"), QString("done"));
}

void CameraCaliberation::save() {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	QFileDialog* saveDialog = new QFileDialog(this);
	QString fileName = saveDialog->getSaveFileName(this, tr("Open File"), QDir::currentPath(), tr("Text File(*.txt)"));
	//获得保存的文件路径
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, tr("错误"), tr("打开文件失败"));
		return;
	}
	else
	{
		std::ofstream fout(fileName.toStdString());//保存标定结果的文件
		fout << "camera:" << std::endl;
		fout << *(caliberation->cameraMatrix) << std::endl;
	}
}

void CameraCaliberation::init() {
	cameraMatrix = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0));

	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	//首先定义菜单栏
	//QMenuBar* MyMenuBar = new QMenuBar();
	//this->setMenuBar(MyMenuBar);
	//QMenuBar* MyMenuBar = this->menuBar;

	//定义菜单项
	QMenu* PicPath = new QMenu(Codec->toUnicode("文件"));
	QMenu* Start = new QMenu(Codec->toUnicode("标定"));
	QMenu* Doc = new QMenu(Codec->toUnicode("帮助"));
	menuBar()->addMenu(PicPath);
	menuBar()->addMenu(Start);
	menuBar()->addMenu(Doc);

	QAction* ToHelp = Doc->addAction(Codec->toUnicode("工具说明"), this, SLOT(help()));//注意这样仅仅对槽函数进行定义就可以，不需要定义信号量
	//ToHelp->setCheckable(true); 该行表示是否需要在前面打勾
	QAction* StartCali = Start->addAction(Codec->toUnicode("张正友标定"), this, SLOT(process()));
	QAction* OpenDir = PicPath->addAction(Codec->toUnicode("标定照片路径"), this, SLOT(openDir()));
	QAction* Save = PicPath->addAction(Codec->toUnicode("保存内参"), this, SLOT(save()));

	//设置中央区域
	//QTextEdit* edit = new QTextEdit(this);
	//this->setCentralWidget(edit);

	imageList = new QListWidget();

	//设置QListWidget的显示模式
	imageList->setViewMode(QListView::IconMode);

	//设置QListWidget中单元项的图片大小
	imageList->setIconSize(QSize(100, 100));

	//设置QListWidget中单元项的间距
	imageList->setSpacing(10);

	//设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
	imageList->setResizeMode(QListWidget::Adjust);

	//设置不能移动
	imageList->setMovement(QListWidget::Static);

	//将list放入window
	this->setCentralWidget(imageList);

	statusBar()->showMessage(Codec->toUnicode("请选择图片"));

	ready = false;
}