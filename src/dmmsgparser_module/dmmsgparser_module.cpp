
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

CDMMsgParser_module::CDMMsgParser_module()
    : m_poPacketParser(NULL), m_poMsgSession(NULL)
{
    m_oNetBuffer.Init(65535);
}

CDMMsgParser_module::~CDMMsgParser_module()
{

}

void DMAPI CDMMsgParser_module::Release(void)
{
    delete this;
}

void DMAPI CDMMsgParser_module::Test(void)
{
    std::cout << "PROJECT_NAME = dmmsg" << std::endl;
    std::cout << "PROJECT_NAME_UP = DMMSG" << std::endl;
    std::cout << "PROJECT_NAME_LO = dmmsg" << std::endl;
}

int DMAPI CDMMsgParser_module::OnRecv(const char* data, int size)
{
    if (!m_oNetBuffer.PushBack(data, size))
    {
        return -1;
    }

    for (;;)
    {
        if (!m_oNetBuffer.Peek((char*)&m_vecBuff[0], m_vecBuff.size()))
        {
            return 0;
        }

        int nUsed = m_poPacketParser->ParsePacket((const char*)&m_vecBuff[0],
                    m_oNetBuffer.GetSize());

        if (0 == nUsed)
        {
            break;
        }

        if (nUsed < 0)
        {
            if (!m_oNetBuffer.DiscardFront(1))
            {
                DoClose(fmt::format("ParserPacket failed2 error:{}", nUsed));
                return -2;
            }

            continue;
        }

        std::string strHead;

        if (!m_oNetBuffer.PopFront(&strHead, m_vecBuff.size()))
        {
            DoClose("ParserPacket failed");
            return -3;
        }

        std::string strData;

        if (!m_oNetBuffer.PopFront(&strData, nUsed - m_vecBuff.size()))
        {
            DoClose("ParserPacket failed2");
            return -4;
        }

        uint16_t wMsgID = m_poPacketParser->GetMsgID((void*)&m_vecBuff[0]);

        m_poMsgSession->OnMessageInline(wMsgID, strHead, strData);
    }

    return 0;
}

void DMAPI CDMMsgParser_module::DoClose(const std::string& strError)
{

}

bool DMAPI CDMMsgParser_module::SendMsg(uint16_t msgID,
                                        ::google::protobuf::Message& msg)
{
    std::string strMsg = msg.SerializeAsString();
    int size = strMsg.size();

    std::string strHeader;
    strHeader.resize(m_poPacketParser->GetPacketHeaderSize());
    int build = m_poPacketParser->BuildPacketHeader(&strHeader.front(), size,
                msgID);

    std::string strData;
    strData.append(strHeader);
    strData.append(strMsg);

    return m_poMsgSession->Send(strData.data(), strData.size());
}

void DMAPI CDMMsgParser_module::SetPacketParser(IDMPacketParser* sink)
{
    m_poPacketParser = sink;

    m_vecBuff.resize(m_poPacketParser->GetPacketHeaderSize());
}

void DMAPI CDMMsgParser_module::SetMsgSession(IDMMsgParserSession* sink)
{
    m_poMsgSession = sink;
}

IDMMsgParserModule* DMAPI DMMsgParserGetModule(MSG_STYLE eMsg)
{
    IDMMsgParserModule* poModule = new CDMMsgParser_module();

    if (NULL == poModule)
    {
        return nullptr;
    }

    switch (eMsg)
    {
    case MSG_STYLE_LIGHT:
        poModule->SetPacketParser(HPacketParser::Instance());
        break;

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
