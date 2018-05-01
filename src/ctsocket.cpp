/****************************************************************************
** $Id: qt/server.cpp   3.2.1   edited May 13 09:08 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/
#include "ctsocket.h"
#include "ctdrive.h"

#include <math.h>
#include <stdlib.h>


ClientSocket::ClientSocket( int sock, QObject *parent=0, const char *name=0 ) 
	:QSocket( parent, name )
{
	connect( this, SIGNAL(readyRead()),
		SLOT(readClient()) );

	setSocket( sock );
}

ClientSocket::~ClientSocket()
{
	
}


void ClientSocket::readClient()
{
  
}


SimpleServer::SimpleServer( Q_UINT16 port , QObject* parent=0 ) :QServerSocket( port, 1, parent )
{
	if ( !ok() ) {
		qWarning("Failed to bind to port ");
	}
}

SimpleServer::~SimpleServer()
{
}

void SimpleServer::newConnection( int socket )
{
	ClientSocket *s = new ClientSocket( socket, this );
	emit newConnect( s );
}

