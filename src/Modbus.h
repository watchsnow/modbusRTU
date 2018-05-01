// Modbus.h: interface for the CModbus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined MODBUS_H
#define MODBUS_H


#include "comm.h"
#include "ramrt.h"
class QRamDrive ;
class CSerial ;

#define  LEN  1024


//modbus 类
class CModbus : public CCom
{
public:
	CModbus();
	virtual ~CModbus();

	unsigned short CRC16(unsigned char *puchMsg, unsigned short usDataLen); 
	
	void CreateFrame( DataReg  pdataReg ,int index);
	void Run();
	void Parse(DataReg  pdataReg,unsigned char *chInput, unsigned short iInputLen , unsigned short shCRC);
	int findWiteKcData( int wrindex, DataVar &writevar);

	int ExecCmd( DataVar execdata, char * chCmd );
	void ScanCmd();
	void SetDvStart( int dvStart ){ this->dvStart = dvStart; }

	//////完善解析
	
	// 移除接收串chCmd中的功能码
	void	getFirstString( char* szData );
	//移除接收串chCmd中的int型数如 设备地址 寄存器起始地址 寄存器个数 
    int		getFirstInt( char* szData );

	//将写入的多个DO取出存放数组
	void	getAnalyseDOCommand( const char* szData, int& nCommandNums, int Data[] );
	//将写入的多个AO取出存放数组
	void	getAnalyseAOCommand( const char* szData, int& nCommandNums, short Data[] );

	int		getDataNums( const QString& qstrCmdList ) const;
public:
//	unsigned char chReq[LEN] ;
//	unsigned char chBuf[LEN] ;
	int iLen ;
	int readDataLen;
	int exeNums;
	int iCommCount[1000] ;

	QRamRT* ramrt;
	bool  bRamRt;

	int nCurrentIndex;
};

#endif 
