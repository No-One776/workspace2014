//
//  Coin.cpp
//  Justin Rohr
//

#include "Coin.h"
#include "time.h"

#ifdef WITH_GVSU_NAMESPACE
namespace gvsu {
#endif

Coin::Coin()
{
    flip();
}

void Coin::flip()
{
	//rand = srand(time(NULL))
    //face = rand() % 2;
}

bool Coin::isHeads() {
    return face == HEADS;
}

string Coin::toString() {
    if (face == HEADS) {
        return "Heads";
    }
    else
        return "Tails";
}

#ifdef WITH_GVSU_NAMESPACE
}
#endif
