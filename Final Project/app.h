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
    void viewBookingsTripDetails();
    void tripDetails(string bookingID);
    void viewFlightManifest();
    void checkInBoardingPass();
    void processCancellation();
}

