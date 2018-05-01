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


//modbus ��
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

	//////���ƽ���
	
	// �Ƴ����մ�chCmd�еĹ�����
	void	getFirstString( char* szData );
	//�Ƴ����մ�chCmd�е�int������ �豸��ַ �Ĵ�����ʼ��ַ �Ĵ������� 
    int		getFirstInt( char* szData );

	//��д��Ķ��DOȡ���������
	void	getAnalyseDOCommand( const char* szData, int& nCommandNums, int Data[] );
	//��д��Ķ��AOȡ���������
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
