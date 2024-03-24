#include "flightMgtSys.h"

// Global variables
vector<User> users;
User* currentSessionUser = nullptr;
vector<Flight> flights;
vector<Booking> bookings;

// Flight management
Flight* findFlightByID(const string& flightNumber) {
    for (Flight& flight : flights) {
        if (flight.getFlightNumber() == flightNumber) {
            return &flight;
        }
    }
    return nullptr;
}

void addFlight(const string& flightNumber, const string& airlineName, const string& origin,
    const string& destination, const string& departureTime, const string& arrivalTime,
    int totalRows, int seatsPerRow, int businessRows) {
    Flight newFlight(flightNumber, airlineName, origin, destination, departureTime, arrivalTime, totalRows, seatsPerRow, businessRows);
    flights.push_back(newFlight);
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

    // Generate booking ID based on current time
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    tm now_tm = {};
    localtime_s(&now_tm, &now_c);
    stringstream ss;
    ss << put_time(&now_tm, "%M%S");
    string bookingID = flightNumber.substr(0, 3) + ss.str();

    Booking booking(bookingID, userID, flightNumber, tickets, bookingDate, "Pending Confirmation");
    bookings.push_back(booking);

    return true;
}


// Authentication and session management
bool createAdmin(const string& userId, const string& firstName, const string& lastName, const string& email, const string& password, const string& adminRole) {
    User* user = findUserByEmail(email);
    if (user != nullptr) {
        return false;
    }
    users.push_back(FlightAdmin(userId, firstName, lastName, email, password, adminRole));
    return true;
}


bool registerUser(const string& userId, const string& firstName, const string& lastName, const string& email, const string& password, const string& userType) {
    User* user = findUserByEmail(email);
    if (user != nullptr) {
        return false;
    }
    users.push_back(User{ userId, firstName, lastName, email, password, userType });
    return true;
}

User* findUserByEmail(const string& email) {
    for (User& user : users) {
        if (user.get_email() == email) {
            return &user;
        }
    }
    return nullptr;
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