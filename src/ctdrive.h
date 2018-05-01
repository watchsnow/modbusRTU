#ifndef CTRTDB_H
#define CTRTDB_H

#include <qapplication.h>
#include <qstring.h>
#include <qtimer.h>

#include "ctsocket.h"
#include "Modbus.h"

class QApplication;


class QCtDrive:public QApplication
{
	Q_OBJECT

public:
    //QCtDrive(int argc,char **argv);//2016.11.18
	#ifdef OS_WIN 
	QCtDrive(int argc,char **argv); 
	#else 
	QCtDrive(int argc,char **argv, Type type); 
    #endif 
	~QCtDrive();
	
	void setExistFile(QString file);
	void freshDisplay(Buf buf);
	void quitApplication();
public:
	QTimer *freshTimer;
	SimpleServer *server;
	CModbus protocol;
	QSocket *client ;
	QString fileName;
	QString filePath;

protected slots:
	void freshRun();
	void newConnect(ClientSocket*) ;
};

#endif
