#include <iostream>
#include <unistd.h> // for sleep()
using namespace std;

int main() {
    for (int i = 0; i < 80; i++) {
        // Clear the console
        system("cls");
        // Draw the bus
        cout << string(i, ' ');

        cout << "      _____" << endl;
        cout << string(i, ' ');
        cout << "     |     |" << endl;
        cout << string(i, ' ');
        cout << "     |  o  |" << endl;
        cout << string(i, ' ');
        cout << "_____|_____|_____" << endl;
        // Move the bus to the right
        // Wait for a moment
        sleep(0.9);
    }
    
    return 0;
}
