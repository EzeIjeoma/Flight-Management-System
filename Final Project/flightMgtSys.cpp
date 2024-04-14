#include "flightMgtSys.h"

// Global variables
util::BinarySearchTree<User*, std::string> users;
util::Queue<Booking*> bookingsQueue;
User* currentSessionUser = nullptr;
vector<Flight> flights;
vector<Booking> bookings;
int userId = 0;


// Booking Management
vector<Booking> searchBookingsByStatus(const std::vector<Booking>& bookings, const std::string& status) {
    std::vector<Booking> result;
    for (const Booking& booking : bookings) {
        if (booking.getStatus() == status) {
            result.push_back(booking);
        }
    }
    return result;
}

std::vector<Booking> searchBookingsByDate(const std::vector<Booking>& bookings, const std::string& date, bool searchBefore) {
    std::vector<Booking> result;
    for (const Booking& booking : bookings) {
        if (searchBefore) {
            if (booking.getBookingDate() < date) {
                result.push_back(booking);
            }
        }
        else {
            if (booking.getBookingDate() > date) {
                result.push_back(booking);
            }
        }
    }
    return result;
}

Booking* findBookingByID(const string& bookingID) {
    for (Booking& booking : bookings) {
        if (booking.getBookingID() == bookingID) {
            return &booking;
        }
    }
    return nullptr;
}

vector<Booking> searchBookingsByFlightDate(const vector<Booking>& bookings, const string& date, bool searchBefore) {
    vector<Booking> filteredBookings;
    for (const Booking& booking : bookings) {
        Flight* flight = findFlightByID(booking.getFlightNumber());
        if (flight != nullptr) {
            string flightDate = flight->getDateOfFlight();

            // Check the date condition based on the searchBefore parameter
            if (searchBefore) {
                if (flightDate < date) {
                    filteredBookings.push_back(booking);
                }
            }
            else {
                if (flightDate > date) {
                    filteredBookings.push_back(booking);
                }
            }
        }
    }
    return filteredBookings;
}

vector<Booking> searchBookingsByUser(const std::vector<Booking>& bookings, const std::string& userId) {
    std::vector<Booking> matchedBookings;
    for (const Booking& booking : bookings) {
        if (booking.getUserID() == userId) {
            matchedBookings.push_back(booking);
        }
    }
    return matchedBookings;
}

void sortBookingsByCriteria(vector<Booking>& bookingList, const string& criterion, bool ascending) {
    if (criterion == "bookingDate") {
        util::insertionSort(bookingList, &Booking::getBookingDate, ascending);
    }
    else if (criterion == "userID") {
        util::insertionSort(bookingList, &Booking::getUserID, ascending);
    }
    else if (criterion == "status") {
        util::insertionSort(bookingList, &Booking::getStatus, ascending);
    }
    else {
        cerr << "Invalid sorting criterion: " << criterion << endl;
    }
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

vector<Booking>& getBookings() {
    return bookings;
}


// Flight management
Flight* findFlightByID(const string& flightNumber) {
    for (Flight& flight : flights) {
        if (flight.getFlightNumber() == flightNumber) {
            return &flight;
        }
    }
    return nullptr;
}

vector<Flight> getFlights() {
	return flights;
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

void sortFlightsByCriteria(vector<Flight>& flightList, const string& criterion, bool ascending) {
    if (criterion == "businessPrice") {
        util::insertionSort(flightList, &Flight::getBusinessPrice, ascending);
    }
    else if (criterion == "regularPrice") {
        util::insertionSort(flightList, &Flight::getRegularPrice, ascending);
    }
    else if (criterion == "flightDuration") {
        util::insertionSort(flightList, &Flight::getFlightDuration, ascending);
    }
    else if (criterion == "airlineName") {
        util::insertionSort(flightList, &Flight::getAirlineName, ascending);
    }
    else if (criterion == "dateOfFlight") {
        util::insertionSort(flightList, &Flight::getDateOfFlight, ascending);
    }
    else {
        cerr << "Invalid sorting criterion: " << criterion << endl;
    }
}

vector<Flight> searchFlightsByOriginAndDestination(const vector<Flight>& flightList, const string& origin, const string& destination) {
    vector<Flight> matchingFlights;
    for (const Flight& flight : flightList) {
        if (flight.getOrigin() == origin && flight.getDestination() == destination) {
            matchingFlights.push_back(flight);
        }
    }
    return matchingFlights;
}

vector<Flight> searchFlightsByDate(const vector<Flight>& flightList, const string& date) {
    vector<Flight> matchingFlights;
    for (const Flight& flight : flightList) {
        if (flight.getDateOfFlight() == date) {
            matchingFlights.push_back(flight);
        }
    }
    return matchingFlights;
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

std::string getUserId() {
    userId += 1;
    stringstream ss;
    ss << setw(3) << setfill('0') << userId;
    return ss.str();
}

// Helper functions
string currentDate() {
	auto now = chrono::system_clock::now();
	auto now_c = chrono::system_clock::to_time_t(now);
	tm now_tm = {};
	localtime_s(&now_tm, &now_c);
	stringstream ss;
	ss << put_time(&now_tm, "%Y-%m-%d");
	return ss.str();
}

string getCurrentDate() {
	auto now = chrono::system_clock::now();
	auto now_c = chrono::system_clock::to_time_t(now);
	tm now_tm = {};
	localtime_s(&now_tm, &now_c);
	stringstream ss;
	ss << put_time(&now_tm, "%Y-%m-%d");
	return ss.str();
}