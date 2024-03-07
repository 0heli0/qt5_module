#include "crc16util.h"

CRC16Util::CRC16Util()
{

}

QString CRC16Util::ByteArryToHexString(QByteArray ascii)
{

}

quint16 CRC16Util::CRC16(quint8 *pchMsg, quint16 wDataLen)
{
    quint8 chCRCHi = 0xFF; // 高CRC字节初始化
    quint8 chCRCLo = 0xFF; // 低CRC字节初始化
    quint16 wIndex; // CRC循环中的索引

    while (wDataLen--)
    {
    // 计算CRC
    wIndex = chCRCLo ^ *(pchMsg++ );
    chCRCLo = chCRCHi ^ chCRCHTalbe[wIndex];
    chCRCHi = chCRCLTalbe[wIndex] ;
    }

    return ((chCRCHi << 8) | chCRCLo) ;
}
