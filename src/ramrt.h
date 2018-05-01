// RamRT.h: interface for the CRamRT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(RAMRT_H)
#define RAMRT_H

#include <qstring.h>
#include "os.h"

#ifdef OS_WIN
#include <windows.h>
#include <stdio.h>
#endif

#ifdef OS_UNIX
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#define SHM_MODE (SHM_R | SHM_W | IPC_CREAT) /*user read/write/create*/
#endif

//ʵʱ���ݿ���ͼ
//����
//�����е������������ڴ�
//��Ҫ����,ʹ������
//����
//����汾��Ϊ1.1

#ifdef OS_WIN
#define MAX_NUM				12000
#endif

#ifdef OS_UNIX
#define MAX_NUM				4000
#endif

#define MAX_SYSITEM			200
#define MAX_STRUCT          5
#define MAX_STRUCT_DOWN     5
#define MAX_STRUCT_UP		5

#ifdef OS_WIN
#define STATION_SIZE		200000		//һ��վ����ռ�õĴ�С200000 bytes δʹ�õĿռ���Ϊ����
#endif

#ifdef OS_UNIX
#define SHMDBKEYRTRAM_RT 	1829503351	//811047
#define STATION_SIZE		70000
#endif

struct StructData
{
	double dValue ;
	char chState ;				//ʵʱ��״ֵ̬
	bool	bAlarm ;			
	bool bChangeState ;
	bool bVisible;
};

struct StructKcData
{
	int kcNo;
	char dataKC[200];
};

//��̨�����ʵʱ���ݿ�
struct StructStation	
{
	int iVersion;
	StructData  DataValue[ MAX_NUM ];			
	int DataKCFlag;                             //���������ʶ
	StructKcData DataKC;                        //�����ṹ
	int StructNum;								//�澯�ṹ��ʶ
	char chStruct[MAX_STRUCT][200];             //�澯�ṹ��
	int StructUpNum ;							//�ϴ��ṹ��ʶ
	char chStructUp[MAX_STRUCT_UP][200] ;		//�ϴ��ṹ��
	int StructDownNum;                          //�´��ṹ��ʶ
	int StructDownProg;                         //����id
	char chStructDown[MAX_STRUCT_DOWN][200];    //�´��ṹ��
};

//ϵͳ�ڴ�ʹ��-1���
class QRamRT
{
public:
	QRamRT( );
	virtual ~QRamRT(  );

#ifdef OS_WIN
	HANDLE hMapFile;		
	LPVOID  lpMapAddress;
#endif

#ifdef OS_UNIX
	int shmid ;
#endif
	bool bRam ;
	bool bEmbed ;
	bool CreateRam( int iStationNum );

	double GetItemValue( int iStationid,  int id ) ;
	bool GetItemChangeState( int iStationid,  int id ) ;
	void  SetItemValue( int iStationid ,  int id , double dValue ) ;
	StructKcData * GetKcData(int iStationid);
	int GetKcFlag(int iStationid);
	StructData* GetItem(int iStationid,int id);
	
	double GetSysItem( int id ) { return *( pSysItem + id ) ; }
	char * GetStruct(int iNum);
	int GetStructNum();
	char * GetStructDown(int iNum);
	int GetStructDownNum();
	int GetStructDownProgId();
	int GetStructUpNum();
	char * GetStructUp(int iNum);

	void  SetDataState(int iStationid, int id , bool bAlarm ,  bool bChangeState);
	void  SetSysItem( int id , double dValue) { *( pSysItem + id ) = dValue ; }

	void  SetStruct(int iNum, char *chMsg);
	void  SetStructNum(int iStructNum);
	void  SetStructDown(int iNum, char *chMsg);
	void  SetStructDownNum(int iProg ,int iNum);
	void  SetStructUpNum(int iStructNum);
	void  SetStructUp(int iNum,char *chMsg);
	void  SetKcFlag(int iStationid,int flag);
	void  SetKcData(int iStationid, int no,QString data);
	void  SetKcClear(int iStationid,int flag);

private:
	StructStation * pStation ;
	double * pSysItem;
	
};
#endif
