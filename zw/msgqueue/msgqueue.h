#ifndef MSGQUEUE_H
#define MSGQUEUE_H
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
///消息队列类型
#define MQ_TYPE         77
///消息队列缓冲区大小
#define MQ_DATA_SIZE    2048

using namespace std;

///一个消息的大小
typedef struct _msgbuff
{
    long m_type;
    char mdata[MQ_DATA_SIZE];
}msg_t;

class MsgQueue
{
    msg_t m_msg;
    int m_msgid;
public:
	MsgQueue();
    bool Init(unsigned int msgid = 128);
    ssize_t GetMsgWithType(msg_t *&pmsg, long type, int flg = 0);
    int SendMsgWithType(void **sendbuff, size_t &bufflen, long type, int flg = 0);
};

#endif // MSGQUEUE_H
