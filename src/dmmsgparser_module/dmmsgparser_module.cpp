
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

#include "dmmsgparser_module.h"

CDMMsg_module::CDMMsg_module()
: m_poPacketParser(NULL), m_poMsgSession(NULL)
{
    m_oNetBuffer.Init(65535);
}

CDMMsg_module::~CDMMsg_module()
{

}

void DMAPI CDMMsg_module::Release(void)
{
    delete this;
}

void DMAPI CDMMsg_module::Test(void)
{
    std::cout << "PROJECT_NAME = dmmsg" << std::endl;
    std::cout << "PROJECT_NAME_UP = DMMSG" << std::endl;
    std::cout << "PROJECT_NAME_LO = dmmsg" << std::endl;
}

void DMAPI CDMMsg_module::OnRecv(const char* data, int size)
{
    if (!m_oNetBuffer.PushBack(data, size, m_poPacketParser->GetPacketHeaderSize())) {
        return;
    }

    for (;;) {
        std::vector<char> vecBuff(m_poPacketParser->GetPacketHeaderSize());
        if (!m_oNetBuffer.Peek((char*)&m_vecBuff[0], m_vecBuff.size()))
        {
            return;
        }

        int nUsed = m_poPacketParser->ParsePacket((const char*)&m_vecBuff[0], m_oNetBuffer.GetSize());

        if (0 == nUsed) {
            break;
        }

        if (nUsed < 0) {
            DoClose("ParserPacket failed");
            return;
        }

        std::string strData;
        if (!m_oNetBuffer.PopFront(&strData, nUsed))
        {
            DoClose("ParserPacket failed2");
            return;
        }

        uint16_t wMsgID = m_poPacketParser->GetMsgID((void*)&m_vecBuff[0]);

        m_poMsgSession->OnMessage(wMsgID, strData.data() + m_poPacketParser->GetPacketHeaderSize(), strData.size() - m_poPacketParser->GetPacketHeaderSize());
    }
}

void DMAPI CDMMsg_module::DoClose(const std::string& strError)
{

}

bool DMAPI CDMMsg_module::SendMsg(uint16_t msgID, ::google::protobuf::Message& msg)
{
    std::string strMsg =  msg.SerializeAsString();
    int size = strMsg.size();

    std::string strHeader;
    strHeader.resize(m_poPacketParser->GetPacketHeaderSize());
    int build = m_poPacketParser->BuildPacketHeader(&strHeader.front(), size, msgID);

    std::string strData;
    strData.append(strHeader);
    strData.append(strMsg);

    return m_poMsgSession->Send(strData.data(), strData.size());
}

void DMAPI CDMMsg_module::SetPacketParser(IDMPacketParser* sink)
{
    m_poPacketParser = sink;

    m_vecBuff.resize(m_poPacketParser->GetPacketHeaderSize());
}

void DMAPI CDMMsg_module::SetMsgSession(IDMMsgSession* sink)
{
    m_poMsgSession = sink;
}

IDMMsgModule* DMAPI DMMsgGetModule(MSG_STYLE eMsg)
{
    IDMMsgModule* poModule = new CDMMsg_module();
    if (NULL == poModule)
    {
        return nullptr;
    }
    switch (eMsg)
    {
    case MSG_STYLE_NC:
        poModule->SetPacketParser(HNCParser::Instance());
        break;
    case MSG_STYLE_DMSTYLE:
        poModule->SetPacketParser(HDMPacketParser::Instance());
        break;
    default:
        // user define
        return nullptr;
    }
    return poModule;
}
