/* Justin Rohr */
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string greetings = "Hello World";
    /* in the following loop, ch is an iterator (a pointer to each
     * character of the string) */
    for (auto ch = greetings.begin();
              ch != greetings.end();
              ++ch)
    {
        // Use C/C++ dereference operator (*) to access the corresponding
        // character from the iterator
        cout <<  *ch  << '-';
    }
    cout << endl;   // print a new line (end-of-line)

    return 0;
}
