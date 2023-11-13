#include "Reader.h"

Reader::Reader()
{
  key = new BYTE[6];
  memset(key, 0xff, 6);
}

Reader::~Reader()
{
  delete key;
}

int gethexvalue(char p)
{
  switch (p)
  {
  case '0':
    return 0;
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 4;
  case '5':
    return 5;
  case '6':
    return 6;
  case '7':
    return 7;
  case '8':
    return 8;
  case '9':
    return 9;
  case 'a':
    return 10;
  case 'A':
    return 10;
  case 'b':
    return 11;
  case 'B':
    return 11;
  case 'c':
    return 12;
  case 'C':
    return 12;
  case 'd':
    return 13;
  case 'D':
    return 13;
  case 'e':
    return 14;
  case 'E':
    return 14;
  case 'f':
    return 15;
  case 'F':
    return 15;
  };
  return -1;
}

void Reader::SetKey(std::string str)
{
  int i = 0;
  int len = str.length();
  const char *p = str.c_str();
  for (i = 0; i < 16; i++)
  {
    int value = 0;
    value = gethexvalue(p[i * 2]) * 16;
    value += gethexvalue(p[i * 2 + 1]);
    if (value < 0)
    {
      lastError = 2;
      return;
    }
    key[i] = value;
  }
}

void Reader::SetKey(BYTE *nKey)
{
  delete key;
  key = nKey;
}

BYTE *Reader::GetKey()
{
  return key;
}

int Reader::GetLastError()
{
  return lastError;
}

std::vector<char> Reader::Read(AddInNative *comp, int sector, int block, int count, bool skip)
{
  auto out = new std::vector<char>();
  int blocksCount = count;
  int currentSector = sector;
  int currentBlock = block;
  while (blocksCount > 0)
  {
    int sectorSize = 4;
    int offset = currentSector * sectorSize + currentBlock;
    int blocksToRead = (skip ? sectorSize - 1 : sectorSize) - currentBlock;
    if (currentSector >= 32)
    {
      sectorSize = 16;
      offset = 32 * 4 + (currentSector - 32) * sectorSize + currentBlock;
      // blocksToRead = sectorSize - 2 - currentBlock;
      blocksToRead = (skip ? sectorSize - 1 : sectorSize) - currentBlock;
    }
    if (blocksToRead > blocksCount)
    {
      blocksToRead = blocksCount;
    }
    if (blocksToRead > 14)
    {
      // currentSector += 1;
      currentBlock = 14;
      blocksToRead = 14;
    }
    else
    {
      currentSector += 1;
      currentBlock = 0;
    }
    auto bufferLength = blocksToRead * 16;
    BYTE *buffer = new BYTE[bufferLength];
    lastError = API_PCDRead(0, 0, 0, offset, blocksToRead, key, buffer);
    if (lastError != 0)
    {
      return *out;
    }
    auto row = new std::vector<char>((char *)buffer, (char *)buffer + bufferLength);
    out->insert(out->end(), row->begin(), row->end());
    // std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    // std::string des;
    // des += std::to_string(offset);
    // des += " ";
    // des += std::to_string(blocksToRead);
    // comp->AddError(convert.from_bytes(des));

    blocksCount -= blocksToRead;
    // currentSector += 1;
    // currentBlock = 0;
  }
  return *out;
}

void Reader::Write(AddInNative *comp, int sector, int block, int count, bool skip, std::vector<char> *data)
{
  int blocksCount = count;
  // int currentSector = sector;
  int offset = sector * 4 + block;
  if (sector >= 32)
  {
    int offset = sector * 16 + block;
  }
  // int currentBlock = block;
  int dataOffset = 0;
  int blocksToWrite = 1;
  while (blocksCount > 0)
  {
    // int sectorSize = 4;
    // int offset = currentSector * sectorSize + currentBlock;
    // int blocksToWrite = (skip ? sectorSize - 1 : sectorSize) - currentBlock;
    // if (currentSector >= 32)
    //{
    // sectorSize = 16;
    // offset = 32 * 4 + (currentSector - 32) * sectorSize + currentBlock;
    // blocksToWrite = sectorSize - 2 - currentBlock;
    // blocksToWrite = (skip ? sectorSize - 1 : sectorSize) - currentBlock;
    //}
    // if (blocksToWrite > blocksCount)
    //{
    //	blocksToWrite = blocksCount;
    //}
    // if (blocksToWrite > 14) {
    //	//currentSector += 1;
    //	currentBlock = 14;
    //	blocksToWrite = 14;
    //}
    // else {
    //	currentSector += 1;
    //	currentBlock = 0;
    //}
    if (skip)
    {
      if (((offset < 128) && (offset % 4 == 3)) || ((offset >= 128) && (offset % 16 == 15)))
      {
        offset++;
        continue;
      }
    }
    auto bufferLength = blocksToWrite * 16;
    auto row = new std::vector<char>(data->begin() + dataOffset * 16, data->begin() + dataOffset * 16 + bufferLength);
    auto key = new BYTE[6];
    memset(key, 0xff, 6);
    BYTE *buf = (BYTE *)&row->front();
    lastError = API_PCDWrite(0, 0, 0, offset, blocksToWrite, key, buf);
    if (lastError != 0)
    {
      return;
    }
    // std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    // std::string des;
    // des += std::to_string(offset);
    // des += " ";
    // des += std::to_string(blocksToWrite);
    // comp->AddError(convert.from_bytes(des));
    dataOffset += blocksToWrite;
    blocksCount -= blocksToWrite;
    // currentSector += 1;
    // currentBlock = 0;
    offset++;
  }
}

std::string Reader::GetCardSnr()
{
  BYTE *buf = new BYTE[128];
  BYTE snr[16];
  lastError = GET_SNR(0, 0, 0x26, 0x00, snr, buf);
  std::string cardSnr = std::format("%02x%02x%02x%02x", buf[0], buf[1], buf[2], buf[3]);
  delete buf;
  return cardSnr;
}

std::string Reader::GetReaderSnr()
{
  BYTE *buf = new BYTE[128];
  lastError = GetReaderVersion(buf);
  std::string readerSnr = std::format("%02x %02x %02x %02x %02x %02x %02x %02x",
                                      buf[1], buf[2], buf[3],
                                      buf[4], buf[5], buf[6], buf[7], buf[8]);
  delete buf;
  return readerSnr;
}
