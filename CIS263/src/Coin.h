//
//  Coin.h
//  Justin Rohr
//

#ifndef __CoinExample__Coin__
#define __CoinExample__Coin__

#include <iostream>
#include <string>

using namespace std;
#ifdef WITH_GVSU_NAMESPACE
namespace gvsu {
#endif

class Coin {
private:
    const int HEADS = 0;
    const int TAILS = 1;

    int face;

public:
    Coin();  // prototype only !!!!
    void flip();
    bool isHeads();
    string toString();

};

#ifdef WITH_GVSU_NAMESPACE
}
#endif

#endif /* defined(__CoinExample__Coin__) */
