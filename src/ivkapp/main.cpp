#include <iostream>

#include <QApplication>
#include <QDesktopWidget>

#include "MainWindow.h"

int main(int argc, char* argv[]) 
{
	QApplication app(argc, argv);
	MainWindow mainWin;
	
	QDesktopWidget desktop;
    QRect screenRect = desktop.screenGeometry( desktop.primaryScreen() );

    mainWin.move((screenRect.width() - mainWin.width()) / 2, 50);
	mainWin.show();
	mainWin.parseCommandLine(argc, argv);
	
	return app.exec();
}
