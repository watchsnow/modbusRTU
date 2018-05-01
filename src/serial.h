// Serial.h: interface for the CSerial class.
//
//////////////////////////////////////////////////////////////////////
#if !defined SERIAL_H
#define SERIAL_H

#include "os.h"

#ifdef OS_WIN
#include "win_qextserialport.h"
#endif

#ifdef OS_UNIX
#include "posix_qextserialport.h"
#endif

class CSerial
{
public:
	CSerial();
	virtual ~CSerial();
	
	void SetValue( int iComNo, int iBaudRate, int iDataBite, int iTimeOut, int iStopBit, int  iOddEven , int iInterval);

	bool OpenCom( );
	void CloseCom( );

	int  ReadCom( unsigned char * lpBuf , int dataLen);
	int WriteCom( const void* lpBuf, int dwCount );
	bool IsOpen(  );
	BaudRateType getBaudRate(int baudrate);
	void waitForMillisec(int millisec);
	int  ReadCom1( unsigned char * lpBuf );		//�����ڷ���1
	int  ReadCom2( unsigned char * lpBuf );		//�����ڷ���2


private:
	PortSettings settings;
	QString	ComNo;								//���ں�

	int time_out;

#ifdef OS_UNIX
	Posix_QextSerialPort	*port	;			//���
#endif

#ifdef OS_WIN
	Win_QextSerialPort	*port	;				//���
#endif
};

#endif 
