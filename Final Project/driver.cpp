#include "app.h"
#include "flightMgtSys.h"
#include <iostream>
#include "util.h"

using namespace std;
void loadData();

int main() {
	loadData();
    //welcome("SKY HIGH FLIGHT BOOKING SERVICES");
    app::landingPage();
	//app::bookFlight();
}



// This is a function that loads dummy data to pre-populate the system
void loadData() {
	// We are creating admin users here
	createAdmin(getUserId(), "Ijun", "Adams", "ij", "1234", "Manager");
	createAdmin(getUserId(), "Daniel", "Johnson", "dan@skyhigh.com", "1234", "Flight Adminstrator");
	createAdmin(getUserId(), "Paul", "Smith", "paul@skyhigh.com", "1234", "Booking Attendant");
	
	// We are creating flights here
	addFlight("AA123", "American Airlines", "2024-12-01", "New York", "Los Angeles", "08:00", "12:00", 10, 6, 2, 500.0, 250.0, 4.0);
	addFlight("DL456", "Delta Airlines", "2024-12-02", "Los Angeles", "New York", "10:00", "14:00", 10, 6, 2, 500.0, 250.0, 4.0);
	addFlight("UA789", "United Airlines", "2024-12-03", "Chicago", "Miami", "12:00", "16:00", 10, 6, 2, 500.0, 250.0, 4.0);
	addFlight("SW101", "Southwest Airlines", "2024-12-04", "Miami", "Chicago", "14:00", "18:00", 10, 6, 2, 500.0, 250.0, 4.0);
	addFlight("BA234", "British Airways", "2024-12-01", "New York", "Los Angeles", "09:00", "13:00", 12, 6, 3, 550.0, 300.0, 5.0);
	addFlight("AF345", "Air France", "2024-12-02", "Los Angeles", "New York", "11:00", "15:00", 12, 6, 3, 550.0, 300.0, 5.0);
	addFlight("LH456", "Lufthansa", "2024-12-03", "Chicago", "Miami", "13:00", "17:00", 12, 6, 3, 550.0, 300.0, 5.0);
	addFlight("QR567", "Qatar Airways", "2024-12-04", "Miami", "Chicago", "15:00", "19:00", 12, 6, 3, 550.0, 300.0, 5.0);
	addFlight("EK678", "Emirates", "2024-12-05", "New York", "Los Angeles", "07:00", "11:00", 14, 7, 4, 600.0, 350.0, 6.0);
	addFlight("SQ789", "Singapore Airlines", "2024-12-06", "Los Angeles", "New York", "09:30", "13:30", 14, 7, 4, 600.0, 350.0, 6.0);
	addFlight("CX890", "Cathay Pacific", "2021-12-07", "Chicago", "Miami", "12:30", "16:30", 14, 7, 4, 600.0, 350.0, 6.0);
	addFlight("NH901", "ANA", "2024-12-08", "Miami", "Chicago", "14:30", "18:30", 14, 7, 4, 600.0, 350.0, 6.0);
	addFlight("AA002", "American Airlines", "2024-12-01", "New York", "Los Angeles", "11:00", "15:00", 10, 6, 2, 520.0, 270.0, 4.5);
	addFlight("DL003", "Delta Airlines", "2024-12-02", "Los Angeles", "New York", "13:00", "17:00", 10, 6, 2, 520.0, 270.0, 4.5);
	addFlight("UA004", "United Airlines", "2024-12-03", "Chicago", "Miami", "15:00", "19:00", 10, 6, 2, 520.0, 270.0, 4.5);
	addFlight("SW005", "Southwest Airlines", "2024-12-04", "Miami", "Chicago", "17:00", "21:00", 10, 6, 2, 520.0, 270.0, 4.5);
	addFlight("BA006", "British Airways", "2024-12-05", "New York", "Los Angeles", "16:00", "20:00", 12, 6, 3, 560.0, 310.0, 5.5);
	addFlight("AF007", "Air France", "2024-12-06", "Los Angeles", "New York", "18:00", "22:00", 12, 6, 3, 560.0, 310.0, 5.5);
	addFlight("LH008", "Lufthansa", "2024-12-07", "Chicago", "Miami", "20:00", "00:00", 12, 6, 3, 560.0, 310.0, 5.5);
	addFlight("QR009", "Qatar Airways", "2024-12-08", "Miami", "Chicago", "22:00", "02:00", 12, 6, 3, 560.0, 310.0, 5.5);
	addFlight("BA123", "British Airways", "2024-12-10", "Lagos", "Houston", "06:00", "16:00", 12, 6, 3, 1100.0, 800.0, 14.0);
	addFlight("DL234", "Delta Airlines", "2024-12-10", "Lagos", "Houston", "08:30", "18:30", 10, 6, 2, 1150.0, 850.0, 14.0);
	addFlight("UA345", "United Airlines", "2024-12-10", "Lagos", "Houston", "11:00", "21:00", 14, 7, 4, 1200.0, 900.0, 14.0);
	addFlight("QR456", "Qatar Airways", "2024-12-10", "Lagos", "Houston", "13:30", "23:30", 12, 6, 3, 1250.0, 950.0, 14.0);
	addFlight("EK567", "Emirates", "2024-12-10", "Lagos", "Houston", "16:00", "02:00", 14, 7, 4, 1300.0, 1000.0, 14.0);
	addFlight("KLM678", "KLM Royal Dutch Airlines", "2024-12-10", "Lagos", "Houston", "18:30", "04:30", 12, 6, 3, 1050.0, 750.0, 14.0);
	addFlight("LH789", "Lufthansa", "2024-12-10", "Lagos", "Houston", "20:00", "06:00", 10, 6, 2, 1350.0, 1050.0, 14.0);
	addFlight("AF890", "Air France", "2024-12-10", "Lagos", "Houston", "22:30", "08:30", 14, 7, 4, 1400.0, 1100.0, 14.0);
	addFlight("AA901", "American Airlines", "2024-12-10", "Lagos", "Houston", "00:00", "10:00", 12, 6, 3, 1450.0, 1150.0, 14.0);
	addFlight("SW012", "Southwest Airlines", "2024-12-10", "Lagos", "Houston", "02:30", "12:30", 10, 6, 2, 1500.0, 1200.0, 14.0);

	registerUser("100", "John", "Doe", "jd", "1234", "user");

	registerUser("180", "Tim", "Cook", "tim@gmail.com", "1234", "user");
	Passenger passenger("John Doe", "P123456", "USA");
	map<string, Passenger> seatToPassengerMap;
	seatToPassengerMap["7A"] = passenger;
	bookFlight("180", "AA123", "Economy", "2024-11-30", seatToPassengerMap);


	registerUser("181", "Dele", "Amodu", "del@mail.com", "1234", "user");
	Passenger passenger1("John Doe", "P123456", "USA");
	map<string, Passenger> seatToPassengerMap1;
	seatToPassengerMap1["1A"] = passenger1; 
	bookFlight("181", "AA123", "Business", "2024-11-30", seatToPassengerMap1);


	registerUser("182", "Ade", "Bola", "bola@gmail.com", "1234", "user");
	Passenger passenger2("Jane Doe", "P654321", "Canada");
	map<string, Passenger> seatToPassengerMap2;
	seatToPassengerMap2["6B"] = passenger2;
	bookFlight("182", "DL456", "Economy", "2024-11-30", seatToPassengerMap2);
}