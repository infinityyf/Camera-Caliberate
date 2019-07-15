#include "CameraCaliberation.h"

#include <iostream>
CameraCaliberation::CameraCaliberation(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//mainwindow �����ڵĸ���������з�װ
	init();
}

void CameraCaliberation::help() {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	QString content = Codec->toUnicode("ʵ��ͨ������������궨��������ڲν��б궨�����ܶ��ű궨���̸����Ƭ���������ڲ����ݡ�");
	QMessageBox::information(NULL, Codec->toUnicode("����˵��"), content);
}

void CameraCaliberation::openDir() {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	QFileDialog* fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(Codec->toUnicode("ѡ��궨ͼƬ"));
	fileDialog->setDirectory(QDir::currentPath());
	fileDialog->setFileMode(QFileDialog::ExistingFiles);//����ѡ�����ļ�
	if (fileDialog->exec() == QDialog::Accepted) {//������ȷ��
		SelectedFiles = fileDialog->selectedFiles();//������ѡ���ͼƬ,�������ͼƬ
	}
	for (QString file : SelectedFiles)
	{
		//����QListWidgetItem����
		QListWidgetItem* imageItem = new QListWidgetItem;
		//Ϊ��Ԫ����������
		imageItem->setIcon(QIcon(file));
		//�������õ�Ԫ��ͼƬ�Ŀ�Ⱥ͸߶�
		imageItem->setSizeHint(QSize(100, 120));

		//����Ԫ����ӵ�QListWidget��
		imageList->addItem(imageItem);
	}
	//��ʾQListWidget
	imageList->show();
}

void CameraCaliberation::process() {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	QString content = Codec->toUnicode("��ѡ��ͼƬ");
	if (SelectedFiles.size() == 0) {
		QMessageBox::information(NULL, Codec->toUnicode("�޷��궨"), content);
		return;
	}


	caliberation = new Caliberation(SelectedFiles,9,6,28);
	caliberation->run();//�궨�߳�����

	
	
	QMessageBox::information(NULL, QString("done"), QString("done"));
}

void CameraCaliberation::save() {
	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	QFileDialog* saveDialog = new QFileDialog(this);
	QString fileName = saveDialog->getSaveFileName(this, tr("Open File"), QDir::currentPath(), tr("Text File(*.txt)"));
	//��ñ�����ļ�·��
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, tr("����"), tr("���ļ�ʧ��"));
		return;
	}
	else
	{
		std::ofstream fout(fileName.toStdString());//����궨������ļ�
		fout << "camera:" << std::endl;
		fout << *(caliberation->cameraMatrix) << std::endl;
	}
}

void CameraCaliberation::init() {
	cameraMatrix = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0));

	QTextCodec* Codec = QTextCodec::codecForName("GBK");
	//���ȶ���˵���
	//QMenuBar* MyMenuBar = new QMenuBar();
	//this->setMenuBar(MyMenuBar);
	//QMenuBar* MyMenuBar = this->menuBar;

	//����˵���
	QMenu* PicPath = new QMenu(Codec->toUnicode("�ļ�"));
	QMenu* Start = new QMenu(Codec->toUnicode("�궨"));
	QMenu* Doc = new QMenu(Codec->toUnicode("����"));
	menuBar()->addMenu(PicPath);
	menuBar()->addMenu(Start);
	menuBar()->addMenu(Doc);

	QAction* ToHelp = Doc->addAction(Codec->toUnicode("����˵��"), this, SLOT(help()));//ע�����������Բۺ������ж���Ϳ��ԣ�����Ҫ�����ź���
	//ToHelp->setCheckable(true); ���б�ʾ�Ƿ���Ҫ��ǰ���
	QAction* StartCali = Start->addAction(Codec->toUnicode("�����ѱ궨"), this, SLOT(process()));
	QAction* OpenDir = PicPath->addAction(Codec->toUnicode("�궨��Ƭ·��"), this, SLOT(openDir()));
	QAction* Save = PicPath->addAction(Codec->toUnicode("�����ڲ�"), this, SLOT(save()));

	//������������
	//QTextEdit* edit = new QTextEdit(this);
	//this->setCentralWidget(edit);

	imageList = new QListWidget();

	//����QListWidget����ʾģʽ
	imageList->setViewMode(QListView::IconMode);

	//����QListWidget�е�Ԫ���ͼƬ��С
	imageList->setIconSize(QSize(100, 100));

	//����QListWidget�е�Ԫ��ļ��
	imageList->setSpacing(10);

	//�����Զ���Ӧ���ֵ�����Adjust��Ӧ��Fixed����Ӧ����Ĭ�ϲ���Ӧ
	imageList->setResizeMode(QListWidget::Adjust);

	//���ò����ƶ�
	imageList->setMovement(QListWidget::Static);

	//��list����window
	this->setCentralWidget(imageList);

	statusBar()->showMessage(Codec->toUnicode("��ѡ��ͼƬ"));

	ready = false;
}