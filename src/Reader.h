#include "mireader.h"
#include <vector>
//#include <codecvt>
#include "AddInNative.h"

typedef unsigned char BYTE;

class Reader
{
  int lastError;
  BYTE *key;

public:
  Reader();
  ~Reader();
  void SetKey(std::string);
  void SetKey(BYTE *);
  BYTE *GetKey();
  int GetLastError();
  std::vector<char> Read(AddInNative *, int, int, int, bool);
  void Write(AddInNative *, int, int, int, bool, std::vector<char> *);
};