// C++ program to demonstrate the
// solution of above drawback
// C++ program to hide the password
// using *(asterik)
#include <conio.h>
#include <iostream>
using namespace std;

// Enumerator
enum IN
{

    // 13 is ASCII for carriage
    // return
    IN_BACK = 8,
    IN_RET = 13

};

// Function that accepts the password
string takePasswdFromUser(
    char sp = '*')
{
    // Stores the password
    string passwd = "";
    char ch_ipt;

    // Until condition is true
    while (true)
    {

        ch_ipt = getch();

        // if the ch_ipt
        if (ch_ipt == IN::IN_RET)
        {
            cout << endl;
            return passwd;
        }
        else if (ch_ipt == IN::IN_BACK && passwd.length() != 0)
        {
            passwd.pop_back();

            // Cout statement is very
            // important as it will erase
            // previously printed character
            cout << "\b \b";

            continue;
        }

        // Without using this, program
        // will crash as \b can't be
        // print in beginning of line
        else if (ch_ipt == IN::IN_BACK && passwd.length() == 0)
        {
            continue;
        }

        passwd.push_back(ch_ipt);
        cout << sp;
    }
}

// Driver Code
int main()
{
    string input;
    cout << "@root>>> ";

    // Function call
    input = takePasswdFromUser();
    cout << input << endl;
}
