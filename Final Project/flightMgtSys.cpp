#include "flightMgtSys.h"

// Global variables
util::BinarySearchTree<User*, std::string> users;
util::Queue<Booking*> bookingsQueue;
User* currentSessionUser = nullptr;
vector<Flight> flights;
vector<Booking> bookings;
int userId = 0;

// Flight management
Flight* findFlightByID(const string& flightNumber) {
    for (Flight& flight : flights) {
        if (flight.getFlightNumber() == flightNumber) {
            return &flight;
        }
    }
    return nullptr;
}

void addFlight(const string& flightNumber, const string& airlineName, const string& dateOfFlight, const string& origin,
    const string& destination, const string& departureTime, const string& arrivalTime,
    int totalRows, int seatsPerRow, int businessRows,
    double businessPrice, double regularPrice, double flightDuration) {
    flights.emplace_back(flightNumber, airlineName, dateOfFlight, origin, destination, departureTime, arrivalTime,
        totalRows, seatsPerRow, businessRows, businessPrice, regularPrice, flightDuration);
}

void displayFlightDetails(const string& flightNumber) {
	Flight* flight = findFlightByID(flightNumber);
    if (!flight) {
		cout << "Flight not found." << endl;
		return;
	}

	cout << "Flight Number: " << flight->getFlightNumber() << endl;
	cout << "Airline: " << flight->getAirlineName() << endl;
	cout << "Origin: " << flight->getOrigin() << endl;
	cout << "Destination: " << flight->getDestination() << endl;
	cout << "Departure Time: " << flight->getDepartureTime() << endl;
	cout << "Arrival Time: " << flight->getArrivalTime() << endl;

	const map<string, SeatInfo>* seats = flight->getSeats();
    for (const auto& seat : *seats) {
		cout << "Seat: " << seat.first << " | Class: " << seat.second.seatClass << " | Price: " << seat.second.price << " | Booked: " << (seat.second.isBooked ? "Yes" : "No") << endl;
	}
}

vector<Flight> sortFlightsByCriteria(const string& criterion, bool ascending) {
    vector<Flight> sortedFlights = flights;

    if (criterion == "businessPrice") {
        util::insertionSort(sortedFlights, &Flight::getBusinessPrice, ascending);
    }
    else if (criterion == "regularPrice") {
        util::insertionSort(sortedFlights, &Flight::getRegularPrice, ascending);
    }
    else if (criterion == "flightDuration") {
        util::insertionSort(sortedFlights, &Flight::getFlightDuration, ascending);
    }
    else if (criterion == "airlineName") {
		util::insertionSort(sortedFlights, &Flight::getAirlineName, ascending);
	}
    else if (criterion == "dateOfFlight") {
		util::insertionSort(sortedFlights, &Flight::getDateOfFlight, ascending);
	}
    else {
        cerr << "Invalid sorting criterion: " << criterion << std::endl;
    }

    return sortedFlights;
}

vector<Flight> searchFlightsByOriginAndDestination(const string& origin, const string& destination) {
	vector<Flight> matchingFlights;
    for (Flight& flight : flights) {
        if (flight.getOrigin() == origin && flight.getDestination() == destination) {
			matchingFlights.push_back(flight);
		}
	}
	return matchingFlights;
}

vector<Flight> searchFlightsByDate(const string& date) {
	vector<Flight> matchingFlights;
    for (Flight& flight : flights) {
        if (flight.getDateOfFlight() == date) {
			matchingFlights.push_back(flight);
		}
	}
	return matchingFlights;
}

bool bookFlight(const string& userID, const string& flightNumber, const string& ticketType, const string& bookingDate, const map<string, Passenger>& seatToPassengerMap) {
    Flight* flight = findFlightByID(flightNumber);
    if (!flight) {
        cout << "Flight not found." << endl;
        return false;
    }

    vector<Ticket> tickets;

    for (const auto& seatAndPassenger : seatToPassengerMap) {
        const string& seatNumber = seatAndPassenger.first;
        const Passenger& passenger = seatAndPassenger.second;

        if (!flight->bookSeat(seatNumber)) {
            cout << "Seat " << seatNumber << " could not be booked." << endl;
            continue;
        }

        string ticketID = flightNumber.substr(0, 3) + passenger.get_name().substr(0, 2) + passenger.get_passportNumber().substr(passenger.get_passportNumber().length() - 3);
        double price = flight->getSeatPrice(seatNumber);
        string seatClass = flight->getSeatClass(seatNumber);

        tickets.push_back(Ticket(ticketID, passenger, flightNumber, ticketType, seatNumber, price));
    }

    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    tm now_tm = {};
    localtime_s(&now_tm, &now_c);
    stringstream ss;
    ss << put_time(&now_tm, "%M%S");
    string bookingID = flightNumber.substr(0, 3) + ss.str();

    bookings.emplace_back(bookingID, userID, flightNumber, tickets, bookingDate, "Pending Confirmation");
    Booking& addedBooking = bookings.back();
    bookingsQueue.enqueue(&addedBooking);

    return true;
}

Booking* getRecentBooking() {
    if (bookingsQueue.empty()) {
        cout << "Booking stack is empty." << std::endl;
        return nullptr;
    }

    Booking* topBooking = bookingsQueue.front();
    bookingsQueue.dequeue();
    return topBooking;
}

const vector<Booking>& getBookings() {
    return bookings;
}


// Authentication and session management
bool createAdmin(const string& userId, const string& firstName, const string& lastName, const string& email, const string& password, const string& adminRole) {
    if (findUserByEmail(email) != nullptr) {
        return false;
    }
    users.addItem(new FlightAdmin(userId, firstName, lastName, email, password, adminRole), email);
    return true;
}

bool registerUser(const string& userId, const string& firstName, const string& lastName, const string& email, const string& password, const string& userType) {
    if (findUserByEmail(email) != nullptr) {
        return false;
    }
    users.addItem(new User(userId, firstName, lastName, email, password, userType), email);
    return true;
}

User* findUserByEmail(const string& email) {
    try {
        User* user = users.searchByKey(email);
        return user;
    }
    catch (std::runtime_error& e) {
        return nullptr;
    }
}

bool loginUser(const string& email, const string& password) {
    User* user = findUserByEmail(email);
    if (user != nullptr && user->get_password() == password) {
        currentSessionUser = user;
        return true;
    }
    return false;
}

void logoutUser() {
    currentSessionUser = nullptr;
}

User* getCurrentSessionUser() {
    return currentSessionUser;
}