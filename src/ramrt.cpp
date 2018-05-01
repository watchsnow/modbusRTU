// RamRT.cpp: implementation of the CRamRT class.
//
//////////////////////////////////////////////////////////////////////

#include "ramrt.h"

#include <stdio.h>
#include <qapplication.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QRamRT::QRamRT()
{
	pStation = NULL;
	//qDebug( "station size %d", sizeof( StructStation ) );
	if( sizeof( StructStation ) > STATION_SIZE )
		printf( "数组定义越过规定大小 size = %d \n", sizeof( StructStation ));
#ifdef OS_WIN
	lpMapAddress = NULL ;
	hMapFile = NULL ;
#endif
	bEmbed = true ;
}

QRamRT::~QRamRT( )
{
#ifdef OS_WIN
    if (lpMapAddress)  UnmapViewOfFile(lpMapAddress);
    if (hMapFile) CloseHandle(hMapFile);
#endif

#ifdef OS_UNIX
	//close share memory
	int iResult;
	iResult = shmctl(shmid, IPC_RMID, 0 ) ;

	//if( iResult  < 0 )
	  //qDebug( "close share memory" );
#endif

}

bool QRamRT::CreateRam( int iStationNum )
{
	//qDebug( "createram %d", iStationNum );
#ifdef OS_WIN    
	char chRamName[30] ; 
	strcpy( chRamName, "RAMRT" );

    if ( lpMapAddress ) UnmapViewOfFile( lpMapAddress );
    if ( hMapFile ) CloseHandle( hMapFile );

    HANDLE hFile = (HANDLE) 0xFFFFFFFF ;

	int iSize1 , iSize2 ;
	iSize1 = iStationNum * STATION_SIZE ;
	iSize2 = iStationNum * sizeof( StructStation) + MAX_SYSITEM * sizeof( double ) ;
	//qDebug( "size ok ! %d", iSize1 >  iSize2 );

    hMapFile = CreateFileMapping( hFile, NULL, PAGE_READWRITE, 0, iStationNum * STATION_SIZE , (LPCTSTR)chRamName );
	if ( hMapFile == NULL ){
		char chMsg[100];
		strcpy( chMsg, "共享内存申请错误，请与程序供应商联系" );
		::MessageBox( NULL, (LPCTSTR)chMsg , NULL, MB_OK );
		lpMapAddress = NULL;
		return false;
	}
    lpMapAddress = MapViewOfFile( hMapFile,FILE_MAP_ALL_ACCESS,0,0,0 );
	pSysItem = ( double * )lpMapAddress ; 
	pStation = ( StructStation * )( ( double * )lpMapAddress + MAX_SYSITEM )  ;
#endif

#ifdef  OS_UNIX
	int shmid ;
	void *shmptr ;

	if((shmid = shmget( SHMDBKEYRTRAM_RT , iStationNum * STATION_SIZE , SHM_MODE ) ) < 0 ){
		qDebug("shmget error");
		bRam = false ;
		return false ;
	}
	shmptr = shmat( shmid, 0, 0 ) ;
	//qDebug("shmat %d", shmptr );
	
	if ( shmptr == (void*) -1 ) {
		//qDebug( "shmat error" );
		bRam = false ;
		return false ;
	}
	//qDebug ( "shared memory attached" );
	pSysItem = ( double * )shmptr ; 
	pStation = ( StructStation * )( ( double * )shmptr + MAX_SYSITEM );

#endif
	pStation->iVersion = 1 ;
	bRam = true ;
	return true;
}

double QRamRT::GetItemValue( int iStationid ,  int id )
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	if ( id >= MAX_NUM )
		return 0;
	else
		return pStation1->DataValue[ id ].dValue ;
}


StructData* QRamRT::GetItem(int iStationid,int id)
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	if ( id >= MAX_NUM )
		return 0;
	else
		return &pStation1->DataValue[ id ] ;
}



bool QRamRT::GetItemChangeState( int iStationid, int id )
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	if ( id >= MAX_NUM )
		return 0;
	else
		return pStation1->DataValue[ id ].bChangeState ;
}

void  QRamRT::SetItemValue( int iStationid ,  int id , double dValue )
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	if ( id >= MAX_NUM ) return ;

	pStation1->DataValue[id].dValue  = dValue ;
}


StructKcData *QRamRT::GetKcData( int iStationid )
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation  + iStationid ;

	return  &pStation1->DataKC;
}

int QRamRT::GetKcFlag( int iStationid )
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation  + iStationid ;

	return pStation1->DataKCFlag;
}


	
void QRamRT::SetDataState(int iStationid, int id, bool bAlarm ,  bool bChangeState)
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	if ( id >= MAX_NUM ) return ;

	pStation1->DataValue[id].bAlarm = bAlarm ;
	pStation1->DataValue[id].bChangeState = bChangeState ;
}
	

//设置控制命令标志
void  QRamRT::SetKcFlag(int iStationid, int flag)
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	pStation1->DataKCFlag = flag;
}

//设置控制串 no为开出串的序号，也可以是ramid号，addstr为附加字符串
void  QRamRT::SetKcData(int iStationid, int no , QString data)
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	pStation1->DataKC.kcNo = no;
	strcpy(pStation1->DataKC.dataKC,data);
}


//清除控制数据
void  QRamRT::SetKcClear(int iStationid,int flag)
{
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	if(!flag){
		char data[200] = {0} ;
		pStation1->DataKCFlag = flag ;
		strcpy(pStation1->DataKC.dataKC,data);
	}
}


void QRamRT::SetStruct(int iNum,char *chMsg)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	strcpy(pStation1->chStruct[iNum],chMsg);
}

void QRamRT::SetStructNum(int iStructNum)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	pStation1->StructNum = iStructNum;
}


void QRamRT::SetStructUp(int iNum,char *chMsg)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	strcpy(pStation1->chStructUp[iNum],chMsg);
}


void QRamRT::SetStructUpNum(int iStructNum)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	pStation1->StructUpNum = iStructNum;
}


void QRamRT::SetStructDown(int iNum, char *chMsg)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	strcpy(pStation1->chStructDown[iNum],chMsg);
}

void QRamRT::SetStructDownNum(int iProg ,int iNum)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;
	
	pStation1->StructDownProg = iProg;
	pStation1->StructDownNum = iNum;
}


char * QRamRT::GetStruct(int iNum)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	return pStation1->chStruct[iNum];
}

int QRamRT::GetStructNum()
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	return pStation1->StructNum;
}

char * QRamRT::GetStructUp(int iNum)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	return pStation1->chStructUp[iNum];
}

int QRamRT::GetStructUpNum()
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	return pStation1->StructUpNum;
}

char * QRamRT::GetStructDown(int iNum)
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	return pStation1->chStructDown[iNum];
}

int QRamRT::GetStructDownNum()
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	return pStation1->StructDownNum;
}

int QRamRT::GetStructDownProgId()
{
	int iStationid = 0 ;
	if( bEmbed ) iStationid = 0 ;
	StructStation *  pStation1 ;
	pStation1 = pStation + iStationid;

	return pStation1->StructDownProg;
}