#include "app.h"

using namespace std;

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
		cout << "\n\nPress any key to go back to the Admin Menu...";
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

	void adminMenu() {
		int menuChoice;
		asciiHeader();
		cout << "\n\n\tAdmin Menu\n\n";
		cout << "\t1. Add a Flight\n";
		cout << "\t2. View Flights\n";
		cout << "\t3. View Flight Manifest\n";
		cout << "\t4. View Bookings\n";
		cout << "\t5. View Pending Bookings\n";
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
			//viewFlightManifest(); 
			break;
		case 4:
			clearScreen();
			//viewBookings(); 
			break;
		case 5:
			clearScreen();
			//viewPendingBookings();
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
		departureCity = input;

		cout << "\tEnter Destination City: ";
		cin >> input;
		if (checkAndExitToUserMenu()) return;
		destinationCity = input;

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

	void userMenu() {
		int menuChoice;
		asciiHeader();
		cout << "\n\n\tUser Menu\n\n";
		cout << "\t1. Book a Flight\n";
		cout << "\t3. View Bookings\n";
		cout << "\t2. View Tickets\n";
		cout << "\t4. Logout\n\n";
		cout << "\tEnter Your Choice: ";
		cin >> menuChoice;

		switch (menuChoice) {
		case 1:
			clearScreen();
			bookFlight();
			break;
		case 2:
			clearScreen();
			break;
		case 3:
			break;
		case 4:
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
		if (loginUser(email, password)) {
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
		string userId, firstName, lastName, email, password, userType;
		asciiHeader();
		userId = getUserId();
		userType = "user";
		cout << "\n\n\tRegister\n\n";
		cout << "\tEnter First Name: ";
		cin >> firstName;
		cout << "\tEnter Last Name: ";
		cin >> lastName;
		cout << "\tEnter Email: ";
		cin >> email;
		cout << "\tEnter Password: ";
		cin >> password;
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
		int menuChoice;
		//system("color 1F");
		cout << setw(0);
		asciiHeader();
		cout << "\n\n\t\tWelcome to the Flight Management System\n\n";
		cout << "\t1. User Login\n";
		cout << "\t2. Register as a User\n";
		cout << "\t3. Employee login\n";
		cout << "\t4. Exit\n\n";
		cout << "\tEnter Your Choice: ";
		cin >> menuChoice;

		switch (menuChoice) {
		case 1:
			clearScreen();
			login();
			break;
		case 2:
			clearScreen();
			signUpUser();
			break;
		case 3:
			clearScreen();
			login();
			break;
		case 4:
			clearScreen();
			welcome("THANK YOU FOR CHOOSING SKY HIGH AIRLINES");
			break;
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

}