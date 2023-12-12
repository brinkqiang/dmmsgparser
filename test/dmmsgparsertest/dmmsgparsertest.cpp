
#include "dmmsgparser.h"
#include <memory>
#include "person.msg.h"

class CPlayer : public CDMMsgParserSession
    , public CDMDispatcher_db
{
public:
    CPlayer(){ }
    virtual ~CPlayer(){}
    virtual MSG_STYLE GetMsgStyle(){ return MSG_STYLE_DMSTYLE;}
    virtual void DMAPI OnMessage(uint16_t msgID, void* data, int size)
    {
        NetCall(msgID, data, size, this);
    }
    virtual bool DMAPI Send(const char* data, int size)
    {
        return 0 == OnRecv(data, size);
    }
    virtual int Ontb_Person(::google::protobuf::Message& msg, int nLen, const void* pObject)
    {
        ::db::tb_Person* pData = dynamic_cast<::db::tb_Person*>(&msg);
        fmt::print(pData->Utf8DebugString());
        return 0;
    }
public:
    template<class T>
    bool DMAPI SendMsg(T& msg)
    {
        return CDMMsgParserSession::SendMsg(GetMsgID<T>(), msg);
    }

};

int main(int argc, char* argv[]) {

    CPlayer oPlayer;

    if (!oPlayer.SessionInit())
    {
        return -1;
    }

    db::tb_Person tb;

    tb.set_uuid(1);
    tb.set_job(2);

    tb.set_name("tom");
    tb.set_number(1366532956);
    tb.set_email("tom@163.com");
    tb.set_phonetype(db::PhoneType::MOBILE);
    tb.set_money(10000);
    tb.set_cash(10000);

    oPlayer.SendMsg(tb);

    return 0;
}
