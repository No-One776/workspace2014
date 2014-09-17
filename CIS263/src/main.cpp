//
//  main.cpp
//  Justin Rohr
//

#include <iostream>
#include "Coin.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{

#ifdef WITH_GVSU_NAMESPACE
    cout << "Hello from GVSU" << endl;
#endif

    /* use the current time as the seed of the random generator */
    srand ((unsigned int) time(NULL));

    /* C++ does not require explicit instantiation
     for the following declaration */
#ifdef WITH_GVSU_NAMESPACE
    gvsu::Coin myCoin;    // = new Coin();
#else
    Coin myCoin;    // = new Coin();
#endif

    myCoin.flip();

    /* require explicit call to toString() */
    cout << myCoin.toString() << endl;

/*    if (myCoin.isHeads())
        printf ("You Win.\n");
    else
        printf ("Better luck next time\n");

    return 0; */
}
