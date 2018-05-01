// Serial.cpp: implementation of the CSerial class.
//
//////////////////////////////////////////////////////////////////////
#include "Serial.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerial::CSerial( )
{
	time_out = 10;
}

CSerial::~CSerial()
{
	port->close();
}


void CSerial::SetValue( int iComNo, int iBaudRate, int iDataBite, int iTimeOut, int iStopBit, int  iOddEven , int iInterval)
{
#ifdef OS_WIN
	ComNo = QString("\\\\.\\COM%1").arg(iComNo);
#endif
#ifdef OS_UNIX
	ComNo = QString("/dev/ttySAC%1").arg(iComNo);
#endif
	settings.BaudRate = getBaudRate(iBaudRate);
	
	if(iDataBite == 5)
		settings.DataBits = DATA_5 ;
	else if(iDataBite == 6)
		settings.DataBits = DATA_6 ;
	else if(iDataBite == 7)
		settings.DataBits = DATA_7 ;
	else if(iDataBite == 8)
		settings.DataBits = DATA_8 ;

	if(iStopBit == 0)
		settings.StopBits = STOP_1 ;
	else if(iStopBit == 1)
		settings.StopBits = STOP_1_5 ;
	else if(iStopBit == 2)
		settings.StopBits = STOP_2 ;

	if(iOddEven == 0)
		settings.Parity = PAR_NONE;
	else if(iOddEven == 1)
		settings.Parity = PAR_EVEN;
	else if(iOddEven == 2)
		settings.Parity = PAR_ODD;
	else if(iOddEven == 3)
		settings.Parity = PAR_MARK;
	else if(iOddEven == 4)
		settings.Parity = PAR_SPACE;

	/* Ä¬ÈÏ×îÐ¡10ms */
	if (iTimeOut < 10)
	{
		iTimeOut = 10;
	}

	settings.Timeout_Millisec = iTimeOut ;

	time_out = iTimeOut;
}


BaudRateType CSerial::getBaudRate(int baudrate)
{
	BaudRateType rateType;
	switch(baudrate)
	{
	case 300:
		rateType = BAUD300;
		break;
	case 600:
		rateType = BAUD600;
		break;
	case 1200:
		rateType = BAUD1200;
		break;
	case 1800:
		rateType = BAUD1800;              //POSIX ONLY
		break;
	case 2400:
		rateType = BAUD2400;
		break;
	case 4800:
		rateType = BAUD4800;
		break;
	case 9600:
		rateType = BAUD9600;
		break;
	case 14400:
		rateType = BAUD14400;             //WINDOWS ONLY
		break;
	case 19200:
		rateType = BAUD19200;
		break;
	case 38400:
		rateType = BAUD38400;
		break;
	case 56000:
		rateType = BAUD56000;             //WINDOWS ONLY
		break;
	case 57600:
		rateType = BAUD57600;
		break;
	case 76800:
		rateType = BAUD76800;             //POSIX ONLY
		break;
	case 115200:
		rateType = BAUD115200;
		break;
	case 128000:
		rateType = BAUD128000;            //WINDOWS ONLY
		break;
	case 256000:
		rateType =BAUD256000;             //WINDOWS ONLY
		break;
	}
	return rateType;
}

bool CSerial::IsOpen()
{
	return port->isOpen();
}


bool CSerial::OpenCom(  )
{
#ifdef OS_WIN
	port = new Win_QextSerialPort( ComNo );	
#endif
#ifdef OS_UNIX
	port = new Posix_QextSerialPort( ComNo);
#endif
    port->setBaudRate(settings.BaudRate); 
    port->setFlowControl(FLOW_OFF);
	port->setParity(settings.Parity);
    port->setDataBits(settings.DataBits );
    port->setStopBits(settings.StopBits);
	port->setTimeout(0, settings.Timeout_Millisec);
	port->open();
	
	if(IsOpen())
		return 1;
	else 
		return 0;
}


void CSerial::CloseCom()
{
	port->close();
}

void CSerial::waitForMillisec(int millisec)
{
#ifdef OS_WIN
	Sleep(millisec);
#endif

#ifdef OS_UNIX
	usleep(millisec*1000);
#endif
}




/*int  CSerial::ReadCom1( unsigned char * lpBuf )
{
	int ReadCount = 0;
	int lent = 0 ;
	char temp[1024];
	printf("recv = ");
	for(int i=0 ; i < 100 ; i++)  
	{
		if(port->bytesWaiting() != -1)
		{
			lent= port->readBlock( temp,port->bytesWaiting());
			
			for (int j = 0; j < lent; j++)
			{
				printf("%.2x ", temp[j]);
			}
			memcpy((char *)lpBuf+ReadCount, temp, lent);
			ReadCount = ReadCount + lent ;
			waitForMillisec(200);			
			if (port->bytesWaiting() == -1){
				printf("\n");
				printf("len = %d", ReadCount);
				printf("\n");
				return ReadCount;
			}
		}
		else
			waitForMillisec( 10);
	}
	
	printf("\n");
	return ReadCount;
}*/


int CSerial::WriteCom( const void* lpBuf, int dwCount )
{
	int dwWrite = 0 ;
    dwWrite = port->writeBlock ((char *)lpBuf,dwCount);
	port->flush();
	return dwWrite;
}



int  CSerial::ReadCom( unsigned char * lpBuf, int dataLen )
{
	//int ReadCount = 0;
	//int lent = 0 ;
	//for(int i=0 ; i < 100 ; i++)  
	//{
	//	if (port->bytesWaiting() != -1)
	//	{
	//		lent = port->readBlock((char *)lpBuf + ReadCount,port->bytesWaiting());
	//		ReadCount = ReadCount + lent ;
	//		if ( ReadCount != dataLen )
	//		{
	//			waitForMillisec(10);
	//			continue;
	//		}
	//		else
	//		{
	//			return ReadCount;
	//		}
	//	}
	//	else
	//		waitForMillisec(10);
	//}
	//return ReadCount;


	/* modif by Gaoqiang 2015-01-28 */
	int ReadCount = 0;
	int len = 0 ;

	int temp_time_out = time_out;

	do 
	{
		if (port->bytesWaiting() != -1)
		{
			len = port->readBlock((char *)lpBuf + ReadCount,port->bytesWaiting());
			ReadCount = ReadCount + len;
			if ( ReadCount < dataLen )
			{
				waitForMillisec(10);
			}
			else
			{
				break ;
			}
		}
		else
		{
			waitForMillisec(10);
		}

		temp_time_out -= 10;

	} while (temp_time_out >= 0);

	return ReadCount;
}

int  CSerial::ReadCom1( unsigned char * lpBuf )
{
	int ByteCount,ReadCount;
	ByteCount = port->bytesWaiting();
	if(ByteCount)
		ReadCount = port->readBlock((char *)lpBuf ,ByteCount);
	else
		return 0 ;
	return ReadCount;
}

int  CSerial::ReadCom2( unsigned char * lpBuf )
{
	int ByteCount,ReadCount;
	ByteCount = port->bytesWaiting();
	if(ByteCount)
		ReadCount = port->readBlock((char *)lpBuf ,ByteCount);
	return ReadCount;
}


