#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <stdlib.h>
#include "flightMgtSys.h"
#include "util.h"
#include <conio.h>
#include <cctype>

using namespace std;

//void welcome(string message);
//void landingPage();
//void delay(int milliseconds);
//void clearScreen();
//void asciiHeader();
//void login();
//void userMenu();
//void adminMenu();
//void signUpUser();
//void logout();
//void addAFlight();
//void viewFlights();

namespace app {

    void welcome(std::string message);
    void landingPage();
    void delay(int milliseconds);
    void clearScreen();
    void asciiHeader();
    void login();
    void userMenu();
    void adminMenu();
    void signUpUser();
    void logout();
    void addAFlight();
    void viewFlights();
    void bookFlight();
}

