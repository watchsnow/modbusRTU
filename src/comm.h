// DL103.h: interface for the CCom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined COMM_H
#define COMM_H

//#include "ramdrive.h"
#include "domparser.h"
#include "serial.h"
#include "ctsocket.h"

#define MSG_DISPLAY_COM  		1		®¹
#define MSG_DISPLAY_STATE  		2		

#define MSG_COMM_INPUT  		3
#define MSG_COMM_OUTPUT  		4
#define MSG_DISPLAY  			5

#define WM_SHOWDATA				6

#define  BUFLEN  1024

typedef struct Buf
{
	unsigned char pBuf[BUFLEN] ;
	int iLen;
	unsigned char type;			
} Buf ;

typedef struct StructOpenInfo
{
	unsigned char comNo ;
	unsigned char bandRateLo ;
	unsigned char bandRateHi ;
	unsigned char dataBit ;
	unsigned char verifyBit ;
	unsigned char stopBit ;
	unsigned char frameLen ;
	unsigned char cycTimeLo ;
	unsigned char cycTimeHi ;
	unsigned char bResult ;
} OpenInfo ;


class CCom 
{
public:
	CCom();
	virtual ~CCom();

	void display( int iDisplayType );
	void DisplayTxt( char*  strTxt );
	void ReadXmlFile(QString path ,QString fileName);
	virtual void Run();
	void quitDrives();

protected:
	virtual unsigned char CheckSum( unsigned char * chBuf, int iLen );
	virtual void ParseFrame( unsigned char * chBuf, int iLen );

public:
	CSerial * pSerial;			
	int cycTime;
	QString rdyType;
	int dvStart;
	OpenInfo openinfo ;
	int frameLen;
	int querynum;
	int rmtPort;
		
	QDomParser domparser;
	Buf  buffer ;	
	
	unsigned char chInput[BUFLEN]/*, chOutput[BUFLEN]*/;
	unsigned char *chOutput;
	int iOutputLen, iInputLen ;	
};

#endif 
