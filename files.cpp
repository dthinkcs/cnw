#include <bits/stdc++.h>
#include <fstream>
using namespace std;

int main() {
    fstream file;
    file.open("sample.txt");
    string total = "";
    string s;
    while  (file >> s) {
        total += s;
    }
    stringstream ss;
    ss.str(total);
    while (ss >> s) {
        cout << s << endl;
    }
    file.close();

    fstream fwrite;
    fwrite.open("another.txt", fstream::out);
    fwrite << "GOOGLE " << endl;
    fwrite.close();
}