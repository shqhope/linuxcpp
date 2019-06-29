#include "msgqueue.h"

MsgQueue::MsgQueue()
{

}

bool MsgQueue::Init(unsigned int msgid /*= 128*/)
{
    bool iRetVal = true;
    m_msgid = msgget(msgid, IPC_CREAT);
    if (m_msgid < 0)
    {
        cout<<"open seq:"<<msgid<<" failed"<<endl;
        iRetVal = false;
    }
    else
    {
        cout<<"succeed"<<endl;
    }
    return iRetVal;
}

ssize_t MsgQueue::GetMsgWithType(msg_t *&pmsg, long type, int flg /*= 0*/)
{
    pmsg = &m_msg;
    return msgrcv(m_msgid, &m_msg, sizeof(msg_t), type, flg);
}

int MsgQueue::SendMsgWithType(void **sendbuff, size_t &bufflen, long type, int flg /*= 0*/)
{
    if (bufflen >= sizeof(msg_t))
    {
        return -1;
    }
    m_msg.m_type = type;
    memcpy(m_msg.mdata, sendbuff, bufflen);
    m_msg.mdata[bufflen] = '\0';
    return msgsnd(m_msgid, &m_msg, sizeof(msg_t), flg);
}
