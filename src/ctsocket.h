#ifndef CTSOCKET_H
#define CTSOCKET_H

#include <qsocket.h>
#include <qserversocket.h>
#include <qtextstream.h>
#include <qdatastream.h>
#include <qserversocket.h> 

class ClientSocket : public QSocket
{
    Q_OBJECT
public:
    ClientSocket( int sock, QObject *parent, const char *name ) ;
    ~ClientSocket();

public slots:
    void readClient();

};


class SimpleServer : public QServerSocket
{
    Q_OBJECT
public:
    SimpleServer( Q_UINT16 port , QObject* parent ) ;
    ~SimpleServer();

    void newConnection( int socket );

signals:
    void newConnect( ClientSocket* );
};


#endif