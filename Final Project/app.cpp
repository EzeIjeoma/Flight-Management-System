#include "app.h"

void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void landingPage() {
    int menuChoice;
    system("color 1F");
    cout << setw(0);
    cout << "\n\t ==========================================" << endl;
    cout << "\t||           SKY HIGH AIRLINES            ||" << endl;
    cout << "\t ==========================================" << endl;
    cout << "\n\n\t\tWelcome to the Flight Management System\n\n";
    cout << "\t1. User Login\n";
    cout << "\t2. Register as a User\n";
    cout << "\t3. Employee login\n";
    cout << "\t4. Exit\n\n";
    cout << "\tEnter Your Choice: ";
    cin >> menuChoice;

    switch (menuChoice) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        system("cls");
        welcome("THANK YOU FOR CHOOSING SKY HIGH AIRLINES");
        break;
    default:
        cout << "\n\tInvalid Input! Please Try Again.";
        delay(2000);
        system("cls");
        landingPage();
    }
}


void welcome(string message) {
    const vector<string> airplaneLines = {
        " -.                 `|.",
        " |:\\-,              .| \\.",
        " |: `.------------------------------------.",
        " / /   o o o o o o o o o o o o o.-.o o   (_`.",
        "/_ \\_              .     .=     |'|         `)",
        "     ``\"\"\"\"\"\"\"\"\"\"\"\"\"//    /  \"\"\"\"\" `\"\"\"------\"'"
    };

    const int totalWidth = 50;
    const int airplaneWidth = airplaneLines[2].length();
    const int startPosition = -airplaneWidth;
    const int endPosition = totalWidth;

    for (int position = startPosition; position < endPosition; ++position) {
        clearScreen();
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
        for (const auto& line : airplaneLines) {
            cout << setw(position) << "" << line << endl;
        }
        delay(10);
    }

    clearScreen();
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n" << right << setw((totalWidth / 2) + (message.length() / 2)) << message;
    delay(3500); 
    clearScreen();
}