#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ofstream myfile;
    myfile.open("example.txt");
    myfile << "Hello" << endl;
    myfile << "World\nAmjad\nHaider" << endl;
    myfile.close();

    vector<string> lines;
    string line;
    ifstream myfile2("example.txt");
    while (getline(myfile2, line)) {
        lines.push_back(line);
    }
    myfile2.close();

    if (lines.size() >= 3) {
        cout << "3rd index data : " << lines[2] << endl;
    } else {
        cout << "3rd index not available as file has less data" << endl;
    }
    return 0;
}
