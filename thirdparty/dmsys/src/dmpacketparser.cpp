
#include "dmpacketparser.h"
#include <memory.h>

int32_t DMAPI HPacketParser::ParsePacket(const char* pBuf, int32_t nLen)
{
    if (nLen < GetPacketHeaderSize())
    {
        return 0;
    }

    SPacketHeader* pHeader = (SPacketHeader*)pBuf;

    int32_t nPacketLen = CheckPacketHeader(pHeader);

    if (nPacketLen < 0)
    {
        return nPacketLen;
    }

    if (nPacketLen <= nLen)
    {
        return nPacketLen;
    }

    return 0;
}

int32_t DMAPI HPacketParser::GetPacketHeaderSize()
{
    return sizeof(SPacketHeader);
}

int32_t DMAPI HPacketParser::BuildPacketHeader(void* pHeader, int32_t nDataLen,
        uint16_t wMsgID)
{
    SPacketHeader* poHeader = (SPacketHeader*)pHeader;
    poHeader->wDataLen = htons(nDataLen);
    poHeader->wMsgID = htons(wMsgID);
    return sizeof(*poHeader);
}

int32_t DMAPI HPacketParser::CheckPacketHeader(void* pHeader)
{
    SPacketHeader* poHeader = (SPacketHeader*)pHeader;
    uint16_t wDataLen = ntohs(poHeader->wDataLen);
    uint16_t wMsgID = ntohs(poHeader->wMsgID);

    return sizeof(*poHeader) + wDataLen;
}

uint16_t DMAPI HPacketParser::GetMsgID(void* pHeader)
{
    SPacketHeader* poHeader = (SPacketHeader*)pHeader;

    return ntohs(poHeader->wMsgID);
}

int32_t DMAPI HDMPacketParser::ParsePacket(const char* pBuf, int32_t nLen)
{
    if (nLen < GetPacketHeaderSize())
    {
        return 0;
    }

    SDMPacketHeader* pHeader = (SDMPacketHeader*)pBuf;

    int32_t nPacketLen = CheckPacketHeader(pHeader);

    if (nPacketLen < 0)
    {
        return nPacketLen;
    }

    if (nPacketLen <= nLen)
    {
        return nPacketLen;
    }

    return 0;
}

int32_t DMAPI HDMPacketParser::GetPacketHeaderSize()
{
    return sizeof(SDMPacketHeader);
}

int32_t HDMPacketParser::BuildPacketHeader(void* pHeader,
        int32_t nDataLen, uint16_t wMsgID)
{
    SDMPacketHeader* poHeader = (SDMPacketHeader*)pHeader;
    poHeader->wMark = PACKET_MARK;
    poHeader->nDataLen = nDataLen;
    poHeader->wCheckSum = ((nDataLen ^ PACKET_CHECKSUM1) & PACKET_CHECKSUM2);

    poHeader->wMark = htons(poHeader->wMark);
    poHeader->nDataLen = htonl(poHeader->nDataLen);
    poHeader->wCheckSum = htons(poHeader->wCheckSum);
    poHeader->wMsgID = htons(wMsgID);
    return sizeof(*poHeader);
}

int32_t HDMPacketParser::CheckPacketHeader(void* pHeader)
{
    SDMPacketHeader* poHeader = (SDMPacketHeader*)pHeader;
    uint16_t wMark = ntohs(poHeader->wMark);
    int32_t nDataLen = ntohl(poHeader->nDataLen);
    uint16_t wCheckSum = ntohs(poHeader->wCheckSum);

    if (PACKET_MARK != wMark)
    {
        return PACKET_MARK_ERROR;
    }

    uint16_t wCheckSum2 = ((nDataLen ^ PACKET_CHECKSUM1) &
                           PACKET_CHECKSUM2);

    if (wCheckSum2 != wCheckSum)
    {
        return PACKET_CHECKSUM_ERROR;
    }

    return sizeof(*poHeader) + nDataLen;
}

uint16_t DMAPI HDMPacketParser::GetMsgID(void* pHeader)
{
    SDMPacketHeader* poHeader = (SDMPacketHeader*)pHeader;

    return ntohs(poHeader->wMsgID);
}
