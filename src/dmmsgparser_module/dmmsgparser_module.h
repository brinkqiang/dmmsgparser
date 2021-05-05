
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "dmmsgparser.h"
#include "dmnetbuffer.h"
#include "msgdispatcher.sys.h"

class CDMMsgParser_module :
    public IDMMsgParserModule
{
public:
    CDMMsgParser_module();
    
    virtual ~CDMMsgParser_module();

    virtual void DMAPI Release(void);

    virtual void DMAPI Test(void);

    virtual int DMAPI OnRecv(const char* data, int size);

    virtual void DMAPI DoClose(const std::string& strError);

    virtual bool DMAPI SendMsg(uint16_t msgID, ::google::protobuf::Message& msg);

    virtual void DMAPI SetPacketParser(IDMPacketParser* sink);

    virtual void DMAPI SetMsgSession(IDMMsgParserSession* sink);

	template<typename T>
	uint16_t GetMSGID()
	{
		return GetMsgID<T>();
	}

private:
    IDMPacketParser* m_poPacketParser;
    IDMMsgParserSession* m_poMsgSession;
    DMMESSAGE_QUEUE m_WriteMsgs;
    CDMNetBuffer m_oNetBuffer;

    std::vector<char> m_vecBuff;
};
