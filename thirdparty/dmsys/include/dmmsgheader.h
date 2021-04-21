
#ifndef __DMMSGHEADER_H_INCLUDE__
#define __DMMSGHEADER_H_INCLUDE__

#include "dmtypes.h"

#pragma pack(push,1)

#define PACKET_CHECKSUM1 0xBBCC
#define PACKET_CHECKSUM2 0x88AA
#define PACKET_MARK 0xAAEE

#define PACKET_MARK_ERROR       (-1000)
#define PACKET_CHECKSUM_ERROR   (-1001)
typedef struct tagPacketHeader {
    uint16_t wMark;

    uint16_t wDataLen;
    uint16_t wCheckSum;

    uint8_t  byFlags;
    uint8_t  byOptLen;
} SPacketHeader;

typedef struct tagDMPacketHeader {
    uint16_t wMark;
    uint16_t wCheckSum;
    int32_t nDataLen;
    uint16_t wMsgID;
} SDMPacketHeader;

#define MAX_NET_BUF_SIZE (512 * 1024)

#define DMNET_TEST_PORT 8345

#define DMMSG_HEADER_LEN (sizeof(SDMPacketHeader))

#pragma pack(pop)

#endif
