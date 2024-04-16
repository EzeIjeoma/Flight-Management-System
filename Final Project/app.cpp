#include "app.h"
#include "flightMgtSys.h"

// using namespace std;

namespace app {
	void viewFlights() {
		string flightNumber;
		vector<Flight> flights = getFlights();
		sortFlightsByCriteria(flights, "airlineName");
		asciiHeader();
		cout << "\n\n\tShowing All Flights Details\n\n";

		util::ConsoleTable table;
		vector<string> headers = { "Flight No.", "Airline", "Date", "Origin", "Destination", "Departure", "Arrival", "Business Price", "Economy Price" };
		table.addHeaders(headers);

		for (const auto& flight : flights) {
			stringstream businessPriceStream, regularPriceStream;

			businessPriceStream << fixed << setprecision(2) << flight.getBusinessPrice();
			string businessPrice = "$" + (businessPriceStream.str().find(".00") != string::npos ? businessPriceStream.str().substr(0, businessPriceStream.str().length() - 3) : businessPriceStream.str());

			regularPriceStream << fixed << setprecision(2) << flight.getRegularPrice();
			string regularPrice = "$" + (regularPriceStream.str().find(".00") != string::npos ? regularPriceStream.str().substr(0, regularPriceStream.str().length() - 3) : regularPriceStream.str());

			table.addRow({ flight.getFlightNumber(), flight.getAirlineName(), flight.getDateOfFlight(),
						   flight.getOrigin(), flight.getDestination(), flight.getDepartureTime(),
						   flight.getArrivalTime(), businessPrice, regularPrice });
		}

		table.printTable();
		cout << "\n\n\tPress any key to go back to the Admin Menu...";
		_getch();

		clearScreen();
		adminMenu();
	}

	void addAFlight() {
		string input;
		string flightNumber, airlineName, dateOfFlight, origin, destination, departureTime, arrivalTime;
		int totalRows, seatsPerRow, businessRows;
		double businessPrice, regularPrice, flightDuration;

		auto checkAndExit = [&]() -> bool {
			if (input == "exit") {
				clearScreen();
				adminMenu();
				return true;
			}
			return false;
			};

		asciiHeader();
		cout << "\n\n\tAdd a Flight\n\n";
		cout << "\n\n\tEnter exit at any time to return back to Admin Menu\n\n";

		cout << "\tEnter Flight Number: ";
		cin >> input;
		if (checkAndExit()) return;
		flightNumber = input;

		cout << "\tEnter Airline Name: ";
		cin.ignore();
		getline(cin, input);
		if (checkAndExit()) return;
		airlineName = input;

		cout << "\tEnter Date of Flight (YYYY-MM-DD): ";
		cin >> input;
		if (checkAndExit()) return;
		dateOfFlight = input;

		cout << "\tEnter Origin: ";
		cin.ignore();
		getline(cin, input);
		if (checkAndExit()) return;
		origin = input;

		cout << "\tEnter Destination: ";
		getline(cin, input);
		if (checkAndExit()) return;
		destination = input;

		cout << "\tEnter Departure Time (HH:MM): ";
		cin >> input;
		if (checkAndExit()) return;
		departureTime = input;

		cout << "\tEnter Arrival Time (HH:MM): ";
		cin >> input;
		if (checkAndExit()) return;
		arrivalTime = input;

		cout << "\tEnter Total Rows: ";
		cin >> input;
		if (checkAndExit()) return;
		totalRows = stoi(input);

		cout << "\tEnter Seats per Row: ";
		cin >> input;
		if (checkAndExit()) return;
		seatsPerRow = stoi(input);

		cout << "\tEnter Total Business Rows: ";
		cin >> input;
		if (checkAndExit()) return;
		businessRows = stoi(input);

		cout << "\tEnter Business Price: ";
		cin >> input;
		if (checkAndExit()) return;
		businessPrice = stod(input);

		cout << "\tEnter Regular Price: ";
		cin >> input;
		if (checkAndExit()) return;
		regularPrice = stod(input);

		cout << "\tEnter Flight Duration (ex. 40): ";
		cin >> input;
		if (checkAndExit()) return;
		flightDuration = stod(input);

		addFlight(flightNumber, airlineName, dateOfFlight, origin, destination, departureTime, arrivalTime, totalRows, seatsPerRow, businessRows, businessPrice, regularPrice, flightDuration);
		cout << "\n\tFlight Added Successfully!";
		delay(2000);
		clearScreen();
		adminMenu();
	}

	void viewFlightManifest() {
		string flightNumber;

		auto checkAndExit = [&]() -> bool {
			if (flightNumber == "exit") {
				clearScreen();
				adminMenu();
				return true;
			}
			return false;
		};

		asciiHeader();
		cout << "\n\n\tFlight Manifest\n\n";
		cout << "\tEnter Flight Number (or 'exit' to go to admin menu): ";
		cin >> flightNumber;
		if (checkAndExit()) return;
		flightNumber = toUpper(flightNumber);

		Flight* flight = findFlightByID(flightNumber);
		if (!flight) {
			cout << "\n\tFlight not found! Please Try Again.";
			delay(2000);
			clearScreen();
			adminMenu();
			return;
		}

		util::TwoDArrayADT<string> manifest = flight->getManifest(flightNumber, getBookings());
		if (manifest.getLength() == 0) {
			cout << "\n\tNo Bookings Found for this Flight!";
			delay(3000);
			clearScreen();
			adminMenu();
			return;
		}

		// Display the manifest
		clearScreen();
		asciiHeader();
		string csvData;
		//cout << "\n\n\tFlight Manifest\n\n";
		cout << "\tFlight Number: " << flightNumber << endl;
		cout << "\tAirline: " << flight->getAirlineName() << endl;
		cout << "\tDate: " << flight->getDateOfFlight() << endl;
		cout << "\tOrigin: " << flight->getOrigin() << endl;
		cout << "\tDestination: " << flight->getDestination() << endl;
		cout << "\tDeparture Time: " << flight->getDepartureTime() << endl;
		cout << "\tArrival Time: " << flight->getArrivalTime() << endl;
		cout << "\tFlight Duration: " << flight->getFlightDuration() << " hours" << endl;
		cout << "\tNumber of Passengers: " << manifest.getLength() << endl << endl;

		csvData += "Flight Number:," + flightNumber + "\n";
		csvData += "Airline:," + flight->getAirlineName() + "\n";
		csvData += "Date:," + flight->getDateOfFlight() + "\n";
		csvData += "Origin:," + flight->getOrigin() + "\n";
		csvData += "Destination:," + flight->getDestination() + "\n";
		csvData += "Departure Time:," + flight->getDepartureTime() + "\n";
		csvData += "Arrival Time:," + flight->getArrivalTime() + "\n";
		csvData += "Flight Duration:," + to_string(flight->getFlightDuration()) + " hours\n";
		csvData += "Number of Passengers:," + to_string(manifest.getLength()) + "\n\n";
		csvData += "Seat Number,Passenger Name,Passport Number,Passport Issue Country,Ticket Type\n";

		util::ConsoleTable table;
		vector<string> headers = { "Seat Number", "Passenger Name", "Passport Number", "Passport Issue Country", "Ticket Type" };
		table.addHeaders(headers);

		for (int i = 0; i < manifest.getLength(); i++) {
			table.addRow({ manifest.getItem(i, 3), manifest.getItem(i, 1), manifest.getItem(i, 0), manifest.getItem(i, 2), manifest.getItem(i, 4) });
			csvData += manifest.getItem(i, 3) + "," + manifest.getItem(i, 1) + "," + manifest.getItem(i, 0) + "," + manifest.getItem(i, 2) + "," + manifest.getItem(i, 4) + "\n";
		}
		table.printTable();

		cout << "\n\n\t1. Download Manifest as CSV\n";
		cout << "\t2. Go Back to Admin Menu\n";
		cout << "\tEnter Your Choice: ";
		string input;
		cin >> input;
		if (input == "1") {
			formatCSVContent(csvData);
			string fileName = "FlightManifest_" + flightNumber + ".csv";
			string filePath;
			if (writeCSVToFile(fileName, csvData, filePath)) {
				clearScreen();
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tDownloading"; 
				delay(1500);
				cout << ".";
				delay(1000);
				cout << "."; 
				delay(1000);				
				cout << "."; 
				delay(500);
				cout << "." << endl;
				clearScreen();
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tManifest Downloaded Successfully!";
				delay(2500);
				openExcel(filePath);
				clearScreen();
				adminMenu();
			}
			else {
				cout << "\n\tManifest Download Failed! Please Try Again.";
				delay(2000);
				clearScreen();
				viewFlightManifest();
			}
		}
		else {
			clearScreen();
			adminMenu();
		}
	}

	void processCancellation() {
		string bookingID;
		
		Booking* cancelledBooking = getCancelledBooking();
		while (cancelledBooking) {
			asciiHeader();
			cout << "\n\n\tProcess Booking Cancellation\n\n";
			vector<Ticket> ticket = cancelledBooking->getTickets();
			// calculate total refund amount
			double totalRefund = 0.0;
			for (const auto& t : ticket) {
				if (t.getTicketType() == "Business") {
					totalRefund += 0.8 * findFlightByID(cancelledBooking->getFlightNumber())->getBusinessPrice();
				}
				else {
					totalRefund += 0.8 * findFlightByID(cancelledBooking->getFlightNumber())->getRegularPrice();
				}
			}

			cout << "\tBooking ID: " << cancelledBooking->getBookingID();
			cout << "\n\tFlight Number: " << cancelledBooking->getFlightNumber();
			cout << "\n\tBooking Date: " << cancelledBooking->getBookingDate();
			cout << "\n\tStatus: " << cancelledBooking->getStatus();
			cout << "\n\tTotal Refund Amount: $" << fixed << setprecision(2) << totalRefund << endl;
			cout << "\n\n\t1. Approve cancellation & intiate refund: \n";
			cout << "\t2. Leave cancellation and refund on pending: \n";
			cout << "\t3. Go Back to Admin Menu\n";
			cout << "\tEnter Your Choice: ";
			string input;
			cin >> input;

			if (input == "1") {
				adminCancelBooking(cancelledBooking->getBookingID());
				cout << "\n\tBooking Cancelled. Refund Approved!";
				delay(2000);
				clearScreen();
			}
			else if (input == "2") {
				keepCancellationRequest(cancelledBooking->getBookingID());
				cout << "\n\tBooking refund not yet approved!";
				delay(2000);
				clearScreen();
				break;
			}
			else {
				keepCancellationRequest(cancelledBooking->getBookingID());
				break;
			}

			cancelledBooking = getCancelledBooking();
		}

		if (!cancelledBooking) {
			clearScreen();
			asciiHeader();
			cout << "\n\n\tProcess Booking Cancellation\n\n";
			cout << "\n\tNo Booking Cancellation Requests Found!";
			delay(2500);
			clearScreen();
			adminMenu();
		}
		else {
			clearScreen();
			adminMenu();
		}

	}

	void adminMenu() {
		 writeToCSV();
		int menuChoice;
		asciiHeader();
		cout << "\n\n\tAdmin Menu\n\n";
		cout << "\t1. Add a Flight\n";
		cout << "\t2. View Flights\n";
		cout << "\t3. View Flight Manifest\n";
		cout << "\t4. View Bookings\n";
		cout << "\t5. Process Booking Cancellation\n";
		cout << "\t6. Logout\n\n";
		cout << "\tEnter Your Choice: ";
		cin >> menuChoice;

		switch (menuChoice) {
		case 1:
			clearScreen();
			addAFlight();
			break;
		case 2:
			clearScreen();
			viewFlights();
			break;
		case 3:
			clearScreen();
			viewFlightManifest(); 
			break;
		case 4:
			clearScreen();
			//viewBookings(); 
			break;
		case 5:
			clearScreen();
			processCancellation();
			break;
		case 6:
			logout();
			break;
		default:
			cout << "\n\tInvalid Input! Please Try Again.\n";
			delay(2000);
			adminMenu();
		}
	}


	void bookFlight() {
		string input;
		string departureCity, destinationCity, flightDate;
		int sortCriteria;

		auto checkAndExitToUserMenu = [&input]() -> bool {
			if (input == "exit") {
				clearScreen();
				userMenu();
				return true;
			}
			return false;
			};

		asciiHeader();
		cout << "\n\n\tBook a Flight - Search flights\n";
		cout << "\tEnter exit at any time to return back to User Menu\n\n";

		cout << "\tEnter Departure City: ";
		cin >> input;
		if (checkAndExitToUserMenu()) return;
		departureCity = toLower(input);

		cout << "\tEnter Destination City: ";
		cin >> input;
		if (checkAndExitToUserMenu()) return;
		destinationCity = toLower(input);

		cout << "\tEnter Flight Date (YYYY-MM-DD): ";
		cin >> input;
		if (checkAndExitToUserMenu()) return;
		flightDate = input;

		clearScreen();
		asciiHeader();
		cout << "\n\n\tBook a Flight - Search flights\n";
		cout << "\tEnter exit at any time to return back to User Menu\n\n";
		cout << "\tSort Flights By:\n";
		cout << "\t1.Price (Cheapest to Highest)\n";
		cout << "\t2.Flight Duration\n";
		cout << "\tEnter Your Choice: ";
		cin >> input;
		if (checkAndExitToUserMenu()) return;
		sortCriteria = stoi(input);

		vector<Flight> allFlights = getFlights();
		vector<Flight> filteredByOriginDestination = searchFlightsByOriginAndDestination(allFlights, departureCity, destinationCity);
		vector<Flight> finalFilteredFlights = searchFlightsByDate(filteredByOriginDestination, flightDate);

		if (finalFilteredFlights.empty()) {
			cout << "\n\tNo Flights Found! Please Try Again.";
			delay(2000);
			clearScreen();
			userMenu();
			return;
		}

		clearScreen();
		asciiHeader();
		cout << "\n\n\tAvailable Flights Details\n\n";
		sortFlightsByCriteria(finalFilteredFlights, sortCriteria == 1 ? "regularPrice" : "flightDuration");
		util::ConsoleTable table;
		vector<string> headers = { "Flight No.", "Airline", "Date", "Origin", "Destination", "Departure", "Arrival", "Business Price", "Economy Price" };
		table.addHeaders(headers);
		for (const auto& flight : finalFilteredFlights) {
			stringstream businessPriceStream, regularPriceStream;
			businessPriceStream << fixed << setprecision(2) << flight.getBusinessPrice();
			string businessPrice = "$" + businessPriceStream.str();
			regularPriceStream << fixed << setprecision(2) << flight.getRegularPrice();
			string regularPrice = "$" + regularPriceStream.str();
			table.addRow({ flight.getFlightNumber(), flight.getAirlineName(), flight.getDateOfFlight(),
						  flight.getOrigin(), flight.getDestination(), flight.getDepartureTime(),
						  flight.getArrivalTime(), businessPrice, regularPrice });
		}
		table.printTable();

		cout << "\n\n\tEnter Flight Number to Book: ";
		cin >> input;
		if (checkAndExitToUserMenu()) return;
		Flight* flight = findFlightByID(input);
		if (!flight) {
			cout << "\n\tFlight not found! Please Try Again.";
			delay(2000);
			clearScreen();
			bookFlight();
			return;
		}

		// Flight Details Section
		clearScreen();
		asciiHeader();
		cout << "\n\n\tBook a Flight - Enter Flight Details\n";
		cout << "\tEnter exit at any time to return back to User Menu\n\n";
		string bookingDate, ticketType, seatNumber, passengerName, passportNumber, passportIssueCountry;
		int numOfPassenger;
		map<string, Passenger> seatToPassengerMap;
		bookingDate = currentDate();
		cout << "\tEnter Number of Passengers: ";
		cin >> input;
		if (checkAndExitToUserMenu()) return;
		numOfPassenger = stoi(input);

		for (int i = 0; i < numOfPassenger; i++) {
			cout << "\n\n\tPassenger " << i + 1 << " Details\n";

			if (i == 0) {
				cout << "\tIs the first passenger same as the account owner? (Y/N): ";
				cin >> input;
				if (checkAndExitToUserMenu()) return;
				if (input == "Y" || input == "y") {
					User* user = getCurrentSessionUser();
					passengerName = user->get_first_name() + " " + user->get_last_name();
				}
			}
			else {
				cout << "\tEnter Passenger Name: ";
				cin.ignore();
				getline(cin, input);
				if (checkAndExitToUserMenu()) return;
				passengerName = input;
			}

			cout << "\tEnter Passport Number: ";
			cin >> input;
			if (checkAndExitToUserMenu()) return;
			passportNumber = input;

			cout << "\tEnter Passport Issue Country: ";
			cin.ignore();
			getline(cin, input);
			if (checkAndExitToUserMenu()) return;
			passportIssueCountry = input;

			cout << "\tEnter Ticket Type:\n\t1. Business\n\t2. Economy\n\tEnter Your Choice: ";
			cin >> input;
			if (checkAndExitToUserMenu()) return;
			int choice = stoi(input);
			string ticketType = (choice == 1) ? "Business" : "Economy";

			cout << "\tAvailable Seats: \n";
			vector<string> availableSeats = flight->getAvailableSeats(ticketType);
			for (const auto& seat : availableSeats) {
				cout << "\t" << seat << " ";
			}
			cout << "\n\tEnter Seat Number: ";
			cin >> input;
			if (checkAndExitToUserMenu()) return;
			string seatNumber = input;

			if (seatNumber.length() > 1) {
				seatNumber[1] = toupper(seatNumber[1]);
			}
			seatToPassengerMap[seatNumber] = Passenger(passengerName, passportNumber, passportIssueCountry);
		}

		string confirm;
		cout << "\n\n\tConfirm Booking? (Y/N): ";
		cin >> input;
		if (checkAndExitToUserMenu()) return;
		if (input == "Y" || input == "y") {
			if (bookFlight(getCurrentSessionUser()->get_userId(), flight->getFlightNumber(), ticketType, bookingDate, seatToPassengerMap)) {
				cout << "\n\tBooking Successful!";
				delay(2000);
				clearScreen();
				userMenu();
			}
			else {
				cout << "\n\tBooking Failed! Please Try Again.";
				delay(2000);
				clearScreen();
				bookFlight();
			}
		}
		else {
			cout << "\n\tBooking Cancelled!";
			delay(2000);
			clearScreen();
			userMenu();
		}
	}


	void viewBookingsTripDetails() {
		// Get current session user ID
		User* currentUser = getCurrentSessionUser();
		string userId = currentUser->get_userId();

		// Filter bookings by the current user's ID
		vector<Booking> userBookings = searchBookingsByUser(getBookings(), userId);

		string currentDate = getCurrentDate();
		vector<Booking> confirmedBookings;
		confirmedBookings = searchBookingsByStatus(userBookings, "Scheduled");
		confirmedBookings = searchBookingsByDate(confirmedBookings, currentDate, false);

		vector<Booking> pendingCancelBookings;
		pendingCancelBookings = searchBookingsByStatus(userBookings, "Pending Cancellation");
		pendingCancelBookings = searchBookingsByDate(pendingCancelBookings, currentDate, false);

		vector<Booking> expiredBookings;
		expiredBookings = searchBookingsByStatus(userBookings, "Scheduled");
		expiredBookings = searchBookingsByFlightDate(expiredBookings, currentDate, true);
		
		vector<Booking> cancelledBookings;
		cancelledBookings = searchBookingsByStatus(userBookings, "Cancelled");
		cancelledBookings = searchBookingsByDate(cancelledBookings, currentDate, true);


		asciiHeader();
		cout << "\n\n\tBooking Details\n\n";

		util::ConsoleTable table;
		vector<string> headers = { "Booking ID", "Booking Date", "Origin", "Destination", "Flight Date", "Status"};

		int countOfTablesWithData = 0;
		// Table for confirmed bookings
		table.addHeaders(headers);

		sortBookingsByCriteria(confirmedBookings, "bookingDate", false);
		for (const auto& booking : confirmedBookings) {
			Flight* flight = findFlightByID(booking.getFlightNumber());
			table.addRow({ booking.getBookingID(), booking.getBookingDate(), flight->getOrigin(), flight->getDestination(), flight->getDateOfFlight(), booking.getStatus() });
		}
		cout << "\n\tScheduled Bookings\n";
		if (!confirmedBookings.empty()) {
			countOfTablesWithData++;
			cout << endl;
			table.printTable();
		}
		else {
			cout << "\t--------------------------------\n";
			cout << "\tNo Active Scheduled Bookings Found!\n";
		}

		// Reset the table for pending cancellation bookings
		table.clear();
		table.addHeaders(headers);
		sortBookingsByCriteria(pendingCancelBookings, "bookingDate", false);
		for (const auto& booking : pendingCancelBookings) {
			Flight* flight = findFlightByID(booking.getFlightNumber());
			table.addRow({ booking.getBookingID(), booking.getBookingDate(), flight->getOrigin(), flight->getDestination(), flight->getDateOfFlight(), booking.getStatus() });
			}
		cout << "\n\tPending Cancellation Bookings\n";
		if (!pendingCancelBookings.empty()) {
			countOfTablesWithData++;
			cout << endl;
			table.printTable();
		}
		else {
			cout << "\t--------------------------------\n";
			cout << "\tNo Pending Cancellation Bookings Found!\n";
		}

		// Reset the table for expired bookings
		table.clear();
		table.addHeaders(headers);
		sortBookingsByCriteria(expiredBookings, "bookingDate", false);
		for (const auto& booking : expiredBookings) {
			Flight* flight = findFlightByID(booking.getFlightNumber());
			table.addRow({ booking.getBookingID(), booking.getBookingDate(), flight->getOrigin(), flight->getDestination(), flight->getDateOfFlight(), booking.getStatus() });
		}
		cout << "\n\tExpired Bookings\n";
		if (!expiredBookings.empty()) {
			countOfTablesWithData++;
			cout << endl;
			table.printTable();
		}
		else {
			cout << "\t--------------------------------\n";
			cout << "\tNo Expired Bookings Found!\n";
		}

		// Reset the table for cancelled bookings
		table.clear();
		table.addHeaders(headers);
		sortBookingsByCriteria(cancelledBookings, "bookingDate", false);
		for (const auto& booking : cancelledBookings) {
			Flight* flight = findFlightByID(booking.getFlightNumber());
			table.addRow({ booking.getBookingID(), booking.getBookingDate(), flight->getOrigin(), flight->getDestination(), flight->getDateOfFlight(), booking.getStatus() });
		}
		cout << "\n\tCancelled Bookings\n";
		if (!cancelledBookings.empty()) {
			countOfTablesWithData++;
			cout << endl;
			table.printTable();
		}
		else {
			cout << "\t--------------------------------\n";
			cout << "\tNo Cancelled Bookings Found!\n";
		}

		if (countOfTablesWithData > 0) {
			string bookingID;
			cout << "\n\n\tEnter Booking ID to view Trip Details (or 'exit' to go to user menu): ";
			cin >> bookingID;
			bookingID = toUpper(bookingID);
			if (bookingID == "EXIT") {
				clearScreen();
				userMenu();
			}
			tripDetails(bookingID);
		}
		else {
			cout << "\n\tPress any key to go back to the User Menu...";
			_getch();
		}

		clearScreen();
		userMenu();
	}

	void tripDetails(string bookingID) {
		clearScreen();
		asciiHeader();
		Booking* booking = findBookingByID(bookingID);
		if (!booking) {
			cout << "\n\tBooking not found! Please Try Again.";
			delay(2000);
			clearScreen();
			viewBookingsTripDetails();
			return;
		}

		Flight* flight = findFlightByID(booking->getFlightNumber());
		vector<Ticket> tickets = booking->getTickets();
		vector<string> headers = { "Ticket ID", "Passenger Name", "Passport Number", "Passport Issue Country", "Seat Number", "Ticket Type" };

		cout << "\n\n\tTrip Details -" << booking->getBookingID() << endl << endl;
		cout << "\tFlight Info\n";
		cout << "\t---------------------\n";

		cout << "\tFlight Number: " << flight->getFlightNumber() << endl;
		cout << "\tAirline: " << flight->getAirlineName() << endl;
		cout << "\tDate: " << flight->getDateOfFlight() << endl;
		cout << "\tOrigin: " << flight->getOrigin() << endl;
		cout << "\tDestination: " << flight->getDestination() << endl;
		cout << "\tDeparture Time: " << flight->getDepartureTime() << endl;
		cout << "\tArrival Time: " << flight->getArrivalTime() << endl;
		cout << "\tFlight Duration: " << flight->getFlightDuration() << " hours" << endl;

		cout << "\t---------------------\n";
		cout << "\n\tPassenger Info\n";
		cout << "\t---------------------\n";
		util::ConsoleTable table;
		table.addHeaders(headers);
		for (const auto& ticket : tickets) {
			table.addRow({ ticket.getTicketID(), ticket.getPassenger().get_name(), ticket.getPassenger().get_passportNumber(), ticket.getPassenger().get_passportIssueCountry(), ticket.getSeatNumber(), ticket.getTicketType() });
		}
		table.printTable();

		int count = 1;
		if (booking->getStatus() == "Pending Cancellation") {
			count = 0;
		}

		if (count == 1)
			cout << "\n\n\t" << count << ". Cancel Booking\n";
		else
			cout << endl;
		cout << "\t" << count + 1 <<". Go Back to User Menu\n";
		cout << "\tEnter Your Choice: ";
		string input;
		cin >> input;
		if (input == "1" && count == 1) {
			string confirm;
			cout << "\n\tConfirm Cancellation? (Y/N): ";
			cin >> confirm;
			if (confirm == "Y" || confirm == "y") {
				requestBookingCancellation(bookingID);
				cout << "\n\tBooking Cancellation Requested";
				delay(2000);
				clearScreen();
				viewBookingsTripDetails();
			}
			else {
				clearScreen();
				viewBookingsTripDetails();
			}
		}
		else {
			clearScreen();
			userMenu();
		}
	}

	void checkInBoardingPass() {
		// Get current session user ID
		User* currentUser = getCurrentSessionUser();
		string userId = currentUser->get_userId();

		// Filter bookings by the current user's ID
		vector<Booking> userBookings = searchBookingsByUser(getBookings(), userId);

		// Filter bookings by upcoming flights
		string currentDate = getCurrentDate();
		vector<Booking> upcomingBookings;
		for (const auto& booking : userBookings) {
			if (booking.getStatus() == "Scheduled") {
				Flight* flight = findFlightByID(booking.getFlightNumber());
				int days_between = days_between_dates(flight->getDateOfFlight(), currentDate);
				if (days_between <= 4 && days_between >= 0) {
					upcomingBookings.emplace_back(booking);
				}
			}
		}
		// sort upcoming bookings by check-in status
		sortBookingsByCriteria(upcomingBookings, "checkInStatus", false);

		asciiHeader();
		cout << "\n\n\tCheck In/Boarding Pass\n\n";

		util::ConsoleTable table;
		vector<string> headers = { "Booking ID", "Flight Number", "Origin", "Destination", "Flight Date", "Check-In Status" };
		table.addHeaders(headers);

		for (const auto& booking : upcomingBookings) {
			Flight* flight = findFlightByID(booking.getFlightNumber());
			string checkInStatus = booking.getCheckInStatus() ? "Checked In" : "Not Checked In";
			table.addRow({ booking.getBookingID(), booking.getFlightNumber(), flight->getOrigin(), flight->getDestination(), flight->getDateOfFlight(), checkInStatus });
		}
		if (!upcomingBookings.empty()) {
			table.printTable();
			cout << "\n\n\tEnter Booking ID to Check In/Get Boarding Pass (or 'exit' to go to user menu): ";
			string bookingID;
			cin >> bookingID;
			bookingID = toUpper(bookingID);
			if (bookingID == "EXIT") {
				clearScreen();
				userMenu();
			}

			clearScreen();
			asciiHeader();
			int count = 0;
			cout << "\n\n\tCheck In/Boarding Pass\n\n";
			for (auto& booking : upcomingBookings) {
				if (booking.getBookingID() == bookingID) {
					if (booking.getCheckInStatus()) {
						cout << "\n\tAlready Checked In!\n";
					}
					else {
						string confirm;
						cout << "\n\tWould you like to Check In? (Y/N): ";
						cin >> confirm;
						if (confirm == "Y" || confirm == "y") {
							Booking* bookingToUpdate = findBookingByID(bookingID);
							bookingToUpdate->setCheckInStatus(true);
							clearScreen();
							asciiHeader();
							cout << "\n\tChecked In Successfully!\n\n";
							break;
						}
						else {
							cout << "\n\tCheck In Cancelled!";
							delay(2000);
							clearScreen();
							userMenu();
						}
					}
				}
				else if (count == upcomingBookings.size() - 1) {
					cout << "\n\tBooking not found! Please Try Again.";
					delay(2000);
					clearScreen();
					checkInBoardingPass();
				}
				count++;
			}

			cout << "\t--------------------------------\n";
			cout << "\tBoarding Pass\n";	
			cout << "\t--------------------------------\n";
			Booking* booking = findBookingByID(bookingID);
			Flight* flight = findFlightByID(booking->getFlightNumber());
			vector<Ticket> tickets = booking->getTickets();
			cout << "\tBooking ID: " << booking->getBookingID() << endl;
			cout << "\tFlight Number: " << flight->getFlightNumber() << endl;
			cout << "\tAirline: " << flight->getAirlineName() << endl;
			cout << "\tDate: " << flight->getDateOfFlight() << endl;
			cout << "\tOrigin: " << flight->getOrigin() << endl;
			cout << "\tDestination: " << flight->getDestination() << endl;
			cout << "\tDeparture Time: " << flight->getDepartureTime() << endl;
			cout << "\tArrival Time: " << flight->getArrivalTime() << endl;
			cout << "\tFlight Duration: " << flight->getFlightDuration() << " hours" << endl;

			cout << "\t--------------------------------\n";
			cout << "\tPassenger Info\n";
			cout << "\t--------------------------------\n";
			for (const auto& ticket : tickets) {
				cout << "\tTicket ID: " << toUpper(ticket.getTicketID()) << endl;
				cout << "\tPassenger Name: " << ticket.getPassenger().get_name() << endl;
				cout << "\tPassport Number: " << ticket.getPassenger().get_passportNumber() << endl;
				cout << "\tPassport Issue Country: " << ticket.getPassenger().get_passportIssueCountry() << endl;
				cout << "\tSeat Number: " << ticket.getSeatNumber() << endl;
				cout << "\tTicket Type: " << ticket.getTicketType() << endl;
				cout << "\t--------------------------------\n";
			}

		}
		else {
			cout << "\n\tNo Available CheckIns Found!";
			delay(2000);
			clearScreen();
			userMenu();
		}
		
		cout << "\n\n\tPress any key to go back to the User Menu...";
		_getch();
		clearScreen();
		userMenu();
	}


	void userMenu() {
		writeToCSV();
		string input;
		char menuChoice;
		asciiHeader();
		cout << "\n\n\tUser Menu\n\n";
		cout << "\t1. Book a Flight\n";
		cout << "\t2. My Bookings/Trip Details\n";
		cout << "\t3. Check In/Boarding Pass\n";
		cout << "\t4. Logout\n\n";
		cout << "\tEnter Your Choice: ";
		cin >> input;
		menuChoice = input[0];

		switch (menuChoice) {
		case '1':
			clearScreen();
			bookFlight();
			break;
		case '2':
			clearScreen();
			viewBookingsTripDetails();
			break;
		case '3':
			clearScreen();
			checkInBoardingPass();
			break;
		case '4':
			logout();
			break;
		default:
			cout << "\n\tInvalid Input! Please Try Again.";
			delay(2000);
			clearScreen();
			userMenu();
		}
	}

	void logout() {
		logoutUser();
		clearScreen();
		landingPage();
	}

	void login() {
		string email, password;
		asciiHeader();
		cout << "\n\n\tLogin\n\n";
		cout << "\n\n\tEnter Email: ";
		cin >> email;
		cout << "\tEnter Password: ";
		cin >> password;
		if (loginUser(toLower(email), password)) {
			User* user = getCurrentSessionUser();
			if (user->get_user_type() == "Admin") {
				clearScreen();
				adminMenu();
			}
			else {
				clearScreen();
				userMenu();
			}
		}
		else {
			cout << "\n\tInvalid Username or Password! Please Try Again.";
			delay(2000);
			clearScreen();
			landingPage();
		}
	}

	void signUpUser() {

		auto checkAndExit = [](string& input) -> bool {
			if (input == "exit") {
				clearScreen();
				landingPage();
				return true;
			}
			return false;
		};


		string userId, firstName, lastName, email, password, userType, input;
		asciiHeader();
		cout << "\n\n\tRegister\n\n";
		
		userId = getUserId();
		userType = "user";

		cout << "\tEnter First Name: ";
		cin >> input;
		if (checkAndExit(input)) return;
		firstName = input;

		cout << "\tEnter Last Name: ";
		cin >> input;
		if (checkAndExit(input)) return;
		lastName = input;

		cout << "\tEnter Email: ";
		cin >> input;
		if (checkAndExit(input)) return;
		email = toLower(input);
		
		cout << "\tEnter Password: ";
		cin >> input;
		if (checkAndExit(input)) return;
		password = input;

		if (registerUser(userId, firstName, lastName, email, password, userType)) {
			cout << "\n\tUser Registered Successfully!";
			delay(2000);
			clearScreen();
			landingPage();
		}
		else {
			cout << "\n\tUser Registration Failed! Please Try Again.";
			delay(2000);
			clearScreen();
			landingPage();
		}
	}

	void landingPage() {
		writeToCSV();
		char menuChoice;
		string input;
		cout << setw(0);
		asciiHeader();
		cout << "\n\n\t\tWelcome to the Flight Management System\n\n";
		cout << "\t1. User Login\n";
		cout << "\t2. Register as a User\n";
		cout << "\t3. Employee login\n";
		cout << "\t4. Exit\n\n";
		cout << "\tEnter Your Choice: ";
		cin >> input;
		menuChoice = input[0];

		switch (menuChoice) {
		case '1':
			clearScreen();
			login();
			break;
		case '2':
			clearScreen();
			signUpUser();
			break;
		case '3':
			clearScreen();
			login();
			break;
		case '4':
			clearScreen();
			writeToCSV();
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tTHANK YOU FOR CHOOSING SKY HIGH AIRLINES\n\n";
			exit(EXIT_SUCCESS);
		default:
			cout << "\n\tInvalid Input! Please Try Again.";
			delay(2000);
			clearScreen();
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
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t" << right << setw((totalWidth / 2) + (message.length() / 2)) << message;
		delay(3500);
		clearScreen();
	}



	// helper functions
	void asciiHeader() {
		cout << "\n\n\n\t\t __               ___  __         _    ___  __    ___     _   _   _     ___       __    \n";
		cout << "\t\t(_  |/ \\_/    |_|  |  /__ |_|    |_ |   |  /__ |_| |     |_) / \\ / \\ |/  |  |\\ | /__    \n";
		cout << "\t\t__) |\\  |     | | _|_ \\_| | |    |  |_ _|_ \\_| | | |     |_) \\_/ \\_/ |\\ _|_ | \\| \\_|    \n";
		cout << "\n\n";
	}

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

	void readFromCSV() {
		importUsersFromCSV("./db/users.csv");
		importFlightsFromCSV("./db/flights.csv");
		importBookingsFromCSV("./db/bookings.csv", "./db/tickets.csv");
	}

	void writeToCSV() {
		exportUsersToCSV("./db/users.csv");
		exportFlightsToCSV("./db/flights.csv");
		exportBookingsToCSV("./db/bookings.csv", "./db/tickets.csv");
	}

}