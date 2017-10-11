#ifndef SOCKSERVER_H
#define SOCKSERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

class SockServer
{
	SockServer();

public:
	static SockServer *GetInst();

};

#endif // SOCKSERVER_H
