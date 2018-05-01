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

//实时数据库与图
//该类
//即所有的驱动程序共享内存
//如要增加,使得增加
//共享
//本类版本号为1.1

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
#define STATION_SIZE		200000		//一个站点所占用的大小200000 bytes 未使用的空间作为备用
#endif

#ifdef OS_UNIX
#define SHMDBKEYRTRAM_RT 	1829503351	//811047
#define STATION_SIZE		70000
#endif

struct StructData
{
	double dValue ;
	char chState ;				//实时量状态值
	bool	bAlarm ;			
	bool bChangeState ;
	bool bVisible;
};

struct StructKcData
{
	int kcNo;
	char dataKC[200];
};

//单台机组的实时数据库
struct StructStation	
{
	int iVersion;
	StructData  DataValue[ MAX_NUM ];			
	int DataKCFlag;                             //开出命令标识
	StructKcData DataKC;                        //开出结构
	int StructNum;								//告警结构标识
	char chStruct[MAX_STRUCT][200];             //告警结构串
	int StructUpNum ;							//上传结构标识
	char chStructUp[MAX_STRUCT_UP][200] ;		//上传结构串
	int StructDownNum;                          //下传结构标识
	int StructDownProg;                         //驱动id
	char chStructDown[MAX_STRUCT_DOWN][200];    //下传结构串
};

//系统内存使用-1编号
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
