#include <iostream>
using namespace std;
int main()
{
    // single word input using either c-string/cpp string
    // cin
    char str[100];
    // cout << "Enter a string: ";
    // cin >> str;
    // cout << "You entered: " << str << endl;
    // cout << "\nEnter another string: ";
    // cin >> str;
    // cout << "You entered: "<<str<<endl;

    
    // sentence input using character array(c string)
    // cin.getline // cin.get keeps the \n character
    cout << "Enter a string: ";
    cin.getline(str, 100); // if cin has been used before then you cannot use cin.getline
    cin.getline(str, 100);
    cout << "You entered: " << str << endl;
    
    // for cpp string
    // string str;
    // cout << "Enter a string: ";
    // getline(cin, str);

}
