#include "CameraCaliberation.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CameraCaliberation w;
	w.show();
	return a.exec();
}
