#include "app.h"
#include "flightMgtSys.h"
#include <iostream>
#include "util.h"

#include <cassert>

using namespace std;
void loadData();

int main() {
    //welcome("SKY HIGH FLIGHT BOOKING SERVICES");
	//app::viewFlightManifest();
	//loginUser("jd", "1234");
	//app::processCancellation();
	 app::readFromCSV();
	//loginUser("danalex@gmail.com", "1234");
	//app::viewBookingsTripDetails();
     app::landingPage();
	//app::bookFlight();
}

//int main() {
//	importUsersFromCSV("./db/users.csv");
//	importFlightsFromCSV("./db/flights.csv");
//	importBookingsFromCSV("./db/bookings.csv", "./db/tickets.csv");
//	//loadData();
//	app::landingPage();
//	exportUsersToCSV("./db/users.csv");
//	exportFlightsToCSV("./db/flights.csv");
//	exportBookingsToCSV("./db/bookings.csv", "./db/tickets.csv");
//}



//int main() {
//	// Create some sample flights
//
//	addFlight("FL001", "Delta", "2023-04-01", "NYC", "LAX", "06:00", "09:00", 30, 6, 2, 300.00, 150.00, 5.5);
//	addFlight("FL002", "United", "2023-04-15", "NYC", "CHI", "07:00", "10:00", 30, 6, 2, 320.00, 160.00, 2.0);
//	addFlight("FL003", "American", "2023-04-25", "NYC", "MIA", "08:00", "11:00", 30, 6, 2, 340.00, 170.00, 3.0);
//
//
//	// Create some bookings
//	std::vector<Booking> bookings = {
//		Booking("B001", "U100", "FL001", vector<Ticket>(), "2023-04-01", "Confirmed"),
//		Booking("B003", "U100", "FL004", vector<Ticket>(), "2023-04-19", "Confirmed"),
//		Booking("B002", "U101", "FL002", vector<Ticket>(), "2023-04-15", "Pending"),
//		Booking("B004", "U102", "FL003", vector<Ticket>(), "2023-04-25", "Pending")
//	};
//
//	vector<Booking> results = searchBookingsByUser(bookings, "U100");
//
//	// Output the results and perform assertions
//	std::cout << "Bookings for user U100:" << std::endl;
//	for (const Booking& booking : results) {
//		std::cout << "Booking ID: " << booking.getBookingID() << std::endl;
//	}
//
//	// Asserts to ensure the function works as expected
//	assert(results.size() == 2);  // Expect to find 2 bookings for user U100
//	assert(results[0].getBookingID() == "B001" && results[1].getBookingID() == "B003");
//
//	std::cout << "All tests passed." << std::endl;
//
//	return 0;
//}

//int main() {
//	// Create some sample flights
//
//	addFlight("FL001", "Delta", "2023-04-01", "NYC", "LAX", "06:00", "09:00", 30, 6, 2, 300.00, 150.00, 5.5);
//	addFlight("FL002", "United", "2023-04-15", "NYC", "CHI", "07:00", "10:00", 30, 6, 2, 320.00, 160.00, 2.0);
//	addFlight("FL003", "American", "2023-04-25", "NYC", "MIA", "08:00", "11:00", 30, 6, 2, 340.00, 170.00, 3.0);
//
//
//	// Create some bookings
//	std::vector<Booking> bookings = {
//		Booking("B001", "U100", "FL001", vector<Ticket>(), "2023-04-01", "Confirmed"),
//		Booking("B002", "U101", "FL002", vector<Ticket>(), "2023-04-15", "Pending"),
//		Booking("B003", "U102", "FL003", vector<Ticket>(), "2023-04-25", "Pending")
//	};
//
//	// Testing for bookings before a specific date
//	std::vector<Booking> results = searchBookingsByFlightDate(bookings, "2023-04-20", true);
//	std::cout << "Test for bookings before 2023-04-20:" << std::endl;
//	for (const Booking& b : results) {
//		std::cout << "Booking ID: " << b.getBookingID() << std::endl;
//	}
//
//	// Assertions to validate the functionality
//	assert(results.size() == 2);  // Expect to find 2 bookings before April 20, 2023
//	assert(results[0].getBookingID() == "B001" && results[1].getBookingID() == "B002");
//
//	return 0;
//}



// This is a function that loads dummy data to pre-populate the system
void loadData() {
	//// We are creating admin users here
	//createAdmin(getUserId(), "Ijun", "Adams", "ij", "1234", "Manager");
	//createAdmin(getUserId(), "Daniel", "Johnson", "dan@skyhigh.com", "1234", "Flight Adminstrator");
	//createAdmin(getUserId(), "Paul", "Smith", "paul@skyhigh.com", "1234", "Booking Attendant");
	//
	//// We are creating flights here
	//addFlight("AA123", "American Airlines", "2024-12-01", "New York", "Los Angeles", "08:00", "12:00", 10, 6, 2, 500.0, 250.0, 4.0);
	//addFlight("DL456", "Delta Airlines", "2024-12-02", "Los Angeles", "New York", "10:00", "14:00", 10, 6, 2, 500.0, 250.0, 4.0);
	//addFlight("UA789", "United Airlines", "2024-12-03", "Chicago", "Miami", "12:00", "16:00", 10, 6, 2, 500.0, 250.0, 4.0);
	//addFlight("SW101", "Southwest Airlines", "2024-12-04", "Miami", "Chicago", "14:00", "18:00", 10, 6, 2, 500.0, 250.0, 4.0);
	//addFlight("BA234", "British Airways", "2024-12-01", "New York", "Los Angeles", "09:00", "13:00", 12, 6, 3, 550.0, 300.0, 5.0);
	//addFlight("AF345", "Air France", "2024-12-02", "Los Angeles", "New York", "11:00", "15:00", 12, 6, 3, 550.0, 300.0, 5.0);
	//addFlight("LH456", "Lufthansa", "2024-12-03", "Chicago", "Miami", "13:00", "17:00", 12, 6, 3, 550.0, 300.0, 5.0);
	//addFlight("QR567", "Qatar Airways", "2024-12-04", "Miami", "Chicago", "15:00", "19:00", 12, 6, 3, 550.0, 300.0, 5.0);
	//addFlight("EK678", "Emirates", "2024-12-05", "New York", "Los Angeles", "07:00", "11:00", 14, 7, 4, 600.0, 350.0, 6.0);
	//addFlight("SQ789", "Singapore Airlines", "2024-12-06", "Los Angeles", "New York", "09:30", "13:30", 14, 7, 4, 600.0, 350.0, 6.0);
	//addFlight("CX890", "Cathay Pacific", "2021-12-07", "Chicago", "Miami", "12:30", "16:30", 14, 7, 4, 600.0, 350.0, 6.0);
	//addFlight("NH901", "ANA", "2024-12-08", "Miami", "Chicago", "14:30", "18:30", 14, 7, 4, 600.0, 350.0, 6.0);
	//addFlight("AA002", "American Airlines", "2024-12-01", "New York", "Los Angeles", "11:00", "15:00", 10, 6, 2, 520.0, 270.0, 4.5);
	//addFlight("DL003", "Delta Airlines", "2024-12-02", "Los Angeles", "New York", "13:00", "17:00", 10, 6, 2, 520.0, 270.0, 4.5);
	//addFlight("UA004", "United Airlines", "2024-12-03", "Chicago", "Miami", "15:00", "19:00", 10, 6, 2, 520.0, 270.0, 4.5);
	//addFlight("SW005", "Southwest Airlines", "2024-12-04", "Miami", "Chicago", "17:00", "21:00", 10, 6, 2, 520.0, 270.0, 4.5);
	//addFlight("BA006", "British Airways", "2024-12-05", "New York", "Los Angeles", "16:00", "20:00", 12, 6, 3, 560.0, 310.0, 5.5);
	//addFlight("AF007", "Air France", "2024-04-18", "Los Angeles", "New York", "18:00", "22:00", 12, 6, 3, 560.0, 310.0, 5.5);
	//addFlight("LH008", "Lufthansa", "2024-12-07", "Chicago", "Miami", "20:00", "00:00", 12, 6, 3, 560.0, 310.0, 5.5);
	//addFlight("QR009", "Qatar Airways", "2024-12-08", "Miami", "Chicago", "22:00", "02:00", 12, 6, 3, 560.0, 310.0, 5.5);
	//addFlight("BA123", "British Airways", "2024-12-10", "Lagos", "Houston", "06:00", "16:00", 12, 6, 3, 1100.0, 800.0, 14.0);
	//addFlight("DL234", "Delta Airlines", "2024-12-10", "Lagos", "Houston", "08:30", "18:30", 10, 6, 2, 1150.0, 850.0, 14.0);
	//addFlight("UA345", "United Airlines", "2024-12-10", "Lagos", "Houston", "11:00", "21:00", 14, 7, 4, 1200.0, 900.0, 14.0);
	//addFlight("QR456", "Qatar Airways", "2024-12-10", "Lagos", "Houston", "13:30", "23:30", 12, 6, 3, 1250.0, 950.0, 14.0);
	//addFlight("EK567", "Emirates", "2024-12-10", "Lagos", "Houston", "16:00", "02:00", 14, 7, 4, 1300.0, 1000.0, 14.0);
	//addFlight("KLM678", "KLM Royal Dutch Airlines", "2024-12-10", "Lagos", "Houston", "18:30", "04:30", 12, 6, 3, 1050.0, 750.0, 14.0);
	//addFlight("LH789", "Lufthansa", "2024-04-17", "Lagos", "Houston", "20:00", "06:00", 10, 6, 2, 1350.0, 1050.0, 14.0);
	//addFlight("AF890", "Air France", "2024-12-10", "Lagos", "Houston", "22:30", "08:30", 14, 7, 4, 1400.0, 1100.0, 14.0);
	//addFlight("AA901", "American Airlines", "2024-12-10", "Lagos", "Houston", "00:00", "10:00", 12, 6, 3, 1450.0, 1150.0, 14.0);
	//addFlight("SW012", "Southwest Airlines", "2024-12-10", "Lagos", "Houston", "02:30", "12:30", 10, 6, 2, 1500.0, 1200.0, 14.0);

	//registerUser("100", "John", "Doe", "jd", "1234", "user");
	Passenger passenger3("John Doe", "P123456", "USA");
	Passenger passenger4("Dele Momo", "P123456", "USA");
	map<string, Passenger> seatToPassengerMap3;
	seatToPassengerMap3["1A"] = passenger3;
	seatToPassengerMap3["1B"] = passenger4;
	bookFlight("100", "AF007", "Business", "2024-04-14", seatToPassengerMap3);

	//registerUser("180", "Tim", "Cook", "tim@gmail.com", "1234", "user");
	Passenger passenger("John Doe", "P123456", "USA");
	map<string, Passenger> seatToPassengerMap;
	seatToPassengerMap["7A"] = passenger;
	bookFlight("100", "LH789", "Economy", "2024-04-14", seatToPassengerMap);


	//registerUser("181", "Dele", "Amodu", "del@mail.com", "1234", "user");
	Passenger passenger1("John Doe", "P123456", "USA");
	map<string, Passenger> seatToPassengerMap1;
	seatToPassengerMap1["1A"] = passenger1; 
	bookFlight("100", "AA123", "Business", "2024-11-30", seatToPassengerMap1);


	//registerUser("182", "Ade", "Bola", "bola@gmail.com", "1234", "user");
	Passenger passenger2("Jane Doe", "P654321", "Canada");
	map<string, Passenger> seatToPassengerMap2;
	seatToPassengerMap2["6B"] = passenger2;
	bookFlight("100", "DL456", "Economy", "2024-11-30", seatToPassengerMap2);

	Passenger passenger6("Adeola Okeke", "P123456", "USA");
	Passenger passenger8("Chinedu Ifeanyi", "P123456", "USA");
	Passenger passenger10("Oluchi Amadi", "P123456", "USA");
	Passenger passenger5("Oliver Smith", "P123456", "USA");
	Passenger passenger7("Harry Johnson", "P123456", "USA");
	Passenger passenger9("Ella Brown", "P123456", "USA");
	map<string, Passenger> seatToPassengerMap4;
	seatToPassengerMap4["5A"] = passenger5;
	seatToPassengerMap4["5B"] = passenger6;
	seatToPassengerMap4["5C"] = passenger7;
	seatToPassengerMap4["6A"] = passenger8;
	seatToPassengerMap4["6B"] = passenger9;
	seatToPassengerMap4["6C"] = passenger10;
	bookFlight("182", "AF007", "Business", "2024-11-19", seatToPassengerMap4);
}