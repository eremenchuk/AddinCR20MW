#ifndef __TESTCOMPONENT_H__
#define __TESTCOMPONENT_H__

#include "AddInNative.h"
#include "Reader.h"
#include <sstream>
#include <algorithm>

class CR20MW : public AddInNative
{
private:
    static std::vector<std::u16string> names;
    Reader *reader;
    CR20MW();
};
#endif //__TESTCOMPONENT_H__