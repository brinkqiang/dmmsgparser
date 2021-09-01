# dmmsgparser

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![dmmsgparser](https://img.shields.io/badge/brinkqiang-dmmsgparser-blue.svg?style=flat-square)](https://github.com/brinkqiang/dmmsgparser)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/dmmsgparser/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/dmmsgparser.svg?label=Stars)](https://github.com/brinkqiang/dmmsgparser) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/dmmsgparser.svg?label=Fork)](https://github.com/brinkqiang/dmmsgparser)

## Build status
| [Linux][lin-link] | [Mac][mac-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![mac-badge]       | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/dmmsgparser/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/dmmsgparser/actions/workflows/linux.yml "linux build status"
[mac-badge]: https://github.com/brinkqiang/dmmsgparser/workflows/mac/badge.svg "mac build status"
[mac-link]:  https://github.com/brinkqiang/dmmsgparser/actions/workflows/mac.yml "mac build status"
[win-badge]: https://github.com/brinkqiang/dmmsgparser/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/dmmsgparser/actions/workflows/win.yml "win build status"

## Intro
dmmsgparser
```cpp

#include "dmmsgparser.h"
#include <memory>
#include "person.msg.h"

class CPlayer : public CDMMsgParserSession
    , public CDMDispatcher_db
{
public:
    CPlayer()
    {
        CDMDispatcher_db::Init();
    }

    virtual ~CPlayer()
    {
    }

    virtual MSG_STYLE GetMsgStyle()
    {
        return MSG_STYLE_DMSTYLE;
    }

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

using namespace std;

int main( int argc, char* argv[] ) {

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
```
## Contacts
[![Join the chat](https://badges.gitter.im/brinkqiang/dmmsgparser/Lobby.svg)](https://gitter.im/brinkqiang/dmmsgparser)

## Thanks
