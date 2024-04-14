#include "flightMgtSys.h"

// Global variables
util::BinarySearchTree<User*, std::string> users;
util::Queue<Booking*> cancelledBookingsQueue;
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
    else if (criterion == "checkInStatus") {
		util::insertionSort(bookingList, &Booking::getCheckInStatus, ascending);
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

    bookings.emplace_back(bookingID, userID, flightNumber, tickets, bookingDate, "Scheduled");

    return true;
}

bool adminCancelBooking(const string bookingID) {
	Booking* booking = findBookingByID(bookingID);
    if (!booking) {
		return false;
	}

    for (const Ticket& ticket : booking->getTickets()) {
		Flight* flight = findFlightByID(booking->getFlightNumber());
        if (flight) {
			flight->cancelSeat(ticket.getSeatNumber());
		}
	}

	booking->setStatus("Cancelled");
    return true;
}

bool keepCancellationRequest(const string bookingID) {
	Booking* booking = findBookingByID(bookingID);
    if (!booking) {
		return false;
	}

	booking->setStatus("Pending Cancellation");
    cancelledBookingsQueue.enqueue(booking);
	return true;
}

bool requestBookingCancellation(const string bookingID) {
	Booking* booking = findBookingByID(bookingID);
    if (!booking) {
		return false;
	}

	booking->setStatus("Pending Cancellation");
	cancelledBookingsQueue.enqueue(booking);
    return true;
}

Booking* getCancelledBooking() {
    if (cancelledBookingsQueue.empty()) {
        return nullptr;
    }

    Booking* topBooking = cancelledBookingsQueue.front();
    cancelledBookingsQueue.dequeue();
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

util::TwoDArrayADT<string> getFlightManifest(const string& flightNumber) {
	Flight* flight = findFlightByID(flightNumber);
    if (!flight) {
        return util::TwoDArrayADT<string>(0,0,"");
	}
	return flight->getManifest(flightNumber, bookings);
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

string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

bool writeCSVToFile(const string& fileName, string& csvData, string& filePath) {
    char* userProfilePath = nullptr;
    size_t size = 0;
    errno_t err = _dupenv_s(&userProfilePath, &size, "USERPROFILE");

    if (err || userProfilePath == nullptr) {
        cerr << "Error: Unable to find user profile directory." << endl;
        return false;
    }
    filePath = string(userProfilePath) + "\\Downloads\\" + fileName;
    ofstream outFile(filePath);
    if (!outFile.is_open()) {
        cerr << "Failed to open file at " << fileName << endl;
        return false;
    }
    outFile << csvData;
    outFile.close();
    return true; 
}

string formatCSVContent(const string& content) {
    string formatted = "\"";
    for (char c : content) {
        if (c == '\"') {
            formatted += "\"\"";
        }
        else {
            formatted += c;
        }
    }
    formatted += "\""; // End with a quote
    return formatted;
}

bool openExcel(const string& filePath) {
    string command = "start excel \"" + filePath + "\"";
    if (system(command.c_str()) != 0) {
        cerr << "Failed to open Excel." << endl;
        return false;
    }
    return true;
}

int days_between_dates(const string& date1, const string& date2) {
    tm tm1 = {};
    tm tm2 = {};
    istringstream ss1(date1);
    istringstream ss2(date2);

    ss1 >> get_time(&tm1, "%Y-%m-%d"); 
    ss2 >> get_time(&tm2, "%Y-%m-%d"); 

    auto tp1 = system_clock::from_time_t(mktime(&tm1));
    auto tp2 = system_clock::from_time_t(mktime(&tm2));

    auto duration = tp1 - tp2;
    auto durationInHours = duration_cast<hours>(duration).count();
    return (durationInHours / 24);
}