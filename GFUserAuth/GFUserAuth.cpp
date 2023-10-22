// GFUserAuth.cpp : Source file for your target.
//

#include "GFUserAuth.h"


int main()
{

    gfuser::GFUserServer test{};
    test.init();
    test.run();
    test.shutdown();
}
