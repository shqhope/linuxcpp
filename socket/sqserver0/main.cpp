#include <iostream>
#include <string>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define FLG_START "#$$START"
#define FLG_END	"#$#END"
#define SAVEPATH "/home/sdzw/testsocket"

using namespace std;


typedef struct recallfun
{
	const char *ptype;
	void *(*pfun)(void *);
}RECall;

RECall g_recall[] =
{
	"str", NULL,
	"file", NULL
};

int g_irecalllen = sizeof(g_recall)/sizeof(RECall);

class Scaner
{
private:
	int m_cfd;
	int m_sfd;
public:
	Scaner(int icfd, int isfd):m_cfd(icfd),m_sfd(isfd){}
	void run()
	{
		pthread_t thread0;
	//	int iRet = pthread_create(&thread0, NULL, Handler, this);
		int iRet = pthread_create(&thread0, NULL, HandlerFileTransport, this);
		if (iRet != 0)
		{
			cout<<"create scaner thread failed"<<endl;
		}
		else
		{
			cout<<"create thread success, client fd:"<< m_cfd <<endl;
		}
	}

	static void *HandlerCommon(void *p)
	{
		Scaner *para = (Scaner *)p;
		char buff[BUFSIZ] = {0};
		int len = 0;
		for (;;)
		{
			len = recv(para->m_cfd, buff, sizeof(buff), 0);
			if (len > 0)
			{
				for (int i = 0; i < g_irecalllen; ++i)
				{
					if (strcasecmp(buff, g_recall[i].ptype) == 0)
					{
						(g_recall[i].pfun)(para);
					}
				}
			}
		}
		return p;
	}

	static void *Handler(void *p)
	{
		Scaner *para = (Scaner *)p;
		char buf[BUFSIZ] = {0};
		int len = 0;
		for(;;)
		{
			len = recv(para->m_cfd ,buf,sizeof(buf),0);

			if (strcasecmp(buf, "#$#") == 0)
			{
				cout<<"recv end flags"<<endl;
				close(para->m_cfd);
				break;
			}

			if(len <= 0)
			{
				cout<<"recv len less than 0"<<endl;
				close(para->m_cfd);
			//	shutdown(para->m_cfd, SHUT_RDWR);
				break;
			}
			cout <<"\n读到数据了\n" <<endl;
			cout << buf <<endl;
			send(para->m_cfd,buf,strlen(buf),0);
			memset(buf,0,sizeof(buf));
		}
		return p;
	}

	static void *HandlerFileTransport(void *p)
	{
		Scaner *para = (Scaner *)p;
		char buf[BUFSIZ] = {0};
		char buffline[2048];
		int len = 0;
		char buffDestname[1024];
		int ifile = -1;
		int iseq = 0;
		int isize = 0;
		for(;;)
		{
			len = recv(para->m_cfd ,buf,sizeof(buf),0);

			if (len <= 0)
			{
				cout<<"close client"<<endl;
				close(para->m_cfd);
				return NULL;
			}

			if (strncasecmp(buf, FLG_START, strlen(FLG_START)) == 0)
			{
				cout<<"recv start flags"<<endl;
				cout<<"start to receive data"<<endl;
				sprintf(buffDestname, "%s/recv_%010d_%03d.bak", SAVEPATH, time(0), iseq++);
				ifile = open(buffDestname, O_RDWR|O_CREAT);
				if (ifile < 0)
				{
					cout<<"open file error:"<<buffDestname<<endl;
					return NULL;
				}
				else
				{
					while ((len = recv(para->m_cfd ,buffline,2000,0)) > 0)
					{
						if (memcmp(buffline,  FLG_END, sizeof(FLG_END)) == 0)
						{
							cout<<"recv end flags2"<<endl;
							close(ifile);
							cout<<"recv file:"<<buf<<" file len:"<<isize<<endl;
							break;
						}
						write(ifile, buffline, len);
						cout<<"buffline:==="<<buffline<<"==="<<endl;
						isize += len;
						memset(buffline,0,sizeof(buffline));
					}
				}
			}

		}
		return p;
	}
};

class Server
{
private:
	int port; //端口号
	int sfd;  //监听套接字
	int cfd;  //客户端套接字
	struct sockaddr_in server_addr; //服务端ip
	struct sockaddr_in client_addr; //客户端ip
	socklen_t c_len;
public:
	//有参构造函数
	Server(int port=8888):port(port),sfd(-1),cfd(-1)
	{
		sfd = socket(AF_INET,SOCK_STREAM,0);
		if(-1 == sfd)
		{
			throw("创建套接字失败\n");
		}
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		int on = 1;
		setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

		bind(sfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
		listen(sfd,128);
	}
	//函数运行
	void run()
	{
		if(sfd >= 0)
		{
			cfd = accept(sfd,(struct sockaddr*)&client_addr,&c_len);
			char buf[BUFSIZ] = {0};
			int len = 0;
			int opt = 1;
			setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
			while(1)
			{
				len = recv(cfd,buf,sizeof(buf),0);
				if(len <= 0)
				{
					break;
				}
				cout <<"\n读到数据了\n" <<endl;
				cout << buf <<endl;
				send(cfd,buf,strlen(buf),0);
				memset(buf,0,sizeof(buf));
			}
		}
	}

	void ScanAccept()
	{
		for (;;)
		{
			int icfd = accept(sfd,(struct sockaddr*)&client_addr,&c_len);

			unsigned int chOpt=1;
			int nErr=setsockopt(icfd, SOL_SOCKET, SO_KEEPALIVE, &chOpt, sizeof(unsigned int));//使用KEEPALIVE;
			if(nErr==-1)
			{
				cout<<"set tcpnodealy failed0:"<<errno<<" str:"<<strerror(errno)<<endl;
			}
			nErr=setsockopt(icfd, IPPROTO_TCP, TCP_NODELAY, &chOpt, sizeof(unsigned int));//禁用NAGLE算法
			if(nErr==-1)
			{
				cout<<"set tcpnodealy failed1:"<<errno<<" str:"<<strerror(errno)<<endl;
			}
			Scaner *tmpScaner = new Scaner(icfd, sfd);
			tmpScaner->run();
		}
	}

/**
tcp        0      0 0.0.0.0:8888            0.0.0.0:*               LISTEN      8800/sqserver0
tcp        0      0 127.0.0.1:8888          127.0.0.1:40648         ESTABLISHED 8800/sqserver0
tcp        0      0 127.0.0.1:8888          127.0.0.1:40644         CLOSE_WAIT  8800/sqserver0
tcp        0      0 127.0.0.1:8888          127.0.0.1:40646         CLOSE_WAIT  8800/sqserver0
tcp        0      0 127.0.0.1:40648         127.0.0.1:8888          ESTABLISHED 8835/sqclient0
*/

	~Server()
	{
		cout <<"析构" <<endl;;//析构
		if(-1 != sfd)
			shutdown(sfd,SHUT_RDWR);
		if(-1 != cfd)
			shutdown(cfd,SHUT_RDWR);
	}

};

int main(int argc, char *argv[])
{
	Server *s = NULL;
	try
	{
		s = new Server;
		//s->run();
		s->ScanAccept();
	}
	catch(char const*str)
	{
		cout << str <<endl;
	}
	catch(...)
	{
		cout<<"万能捕获"<<endl;
	}
	delete s;
	return 0;
}
