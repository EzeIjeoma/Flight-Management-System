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

vector<Booking> searchBookingsByDate(const std::vector<Booking>& bookings, const std::string& date, bool searchBefore) {
    std::vector<Booking> result;
    for (const Booking& booking : bookings) {
        Flight* flight = findFlightByID(booking.getFlightNumber());
        if (searchBefore) {
            if (flight->getDateOfFlight() < date) {
                result.push_back(booking);
            }
        }
        else {
            if (flight->getDateOfFlight() > date) {
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

vector<Booking> searchBookingsByBookingID(const vector<Booking>& bookings, string& bookingID) {
 vector<Booking> matchedBookings;
    for (const Booking& booking : bookings) {
        if (toUpper(booking.getBookingID()) == toUpper(bookingID)) {
			matchedBookings.push_back(booking);
		}
	}
	return matchedBookings;
}

vector<Booking> searchBookingsByBookingDate(const std::vector<Booking>& bookings, std::string& date) {
	std::vector<Booking> matchedBookings;
    for (const Booking& booking : bookings) {
        if (toUpper(booking.getBookingDate()) == toUpper(date)) {
			matchedBookings.push_back(booking);
		}
	}
	return matchedBookings;
}

vector<Booking> searchBookingsByFlightNumber(const std::vector<Booking>& bookings, std::string& flightNumber) {
	std::vector<Booking> matchedBookings;
    for (const Booking& booking : bookings) {
        if (toUpper(booking.getFlightNumber()) == toUpper(flightNumber)) {
			matchedBookings.push_back(booking);
		}
	}
	return matchedBookings;
}

vector<Booking> searchBookingsByUser(const vector<Booking>& bookings, string& userId) {
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

bool bookFlight(const string& userID, const string& flightNumber, const string& ticketType, const string& bookingDate, const map<string, Passenger>& seatToPassengerMap, const string& bookingID) {
    Flight* flight = findFlightByID(flightNumber);
    if (!flight) {
        cout << "\tFlight not found." << endl;
        return false;
    }

    vector<Ticket> tickets;

    for (const auto& seatAndPassenger : seatToPassengerMap) {
        const string& seatNumber = seatAndPassenger.first;
        const Passenger& passenger = seatAndPassenger.second;

        //if (!flight->bookSeat(seatNumber)) {
        //    cout << "Seat " << seatNumber << " could not be booked." << endl;
        //    continue;
        //}

        string ticketID = toUpper(flightNumber.substr(0, 3) + passenger.get_name().substr(0, 2) + passenger.get_passportNumber().substr(passenger.get_passportNumber().length() - 3));
        double price = flight->getSeatPrice(seatNumber);
        string seatClass = flight->getSeatClass(seatNumber);

        tickets.push_back(Ticket(ticketID, passenger, flightNumber, ticketType, seatNumber, price));
    }

    if (bookingID == "") {
		auto now = chrono::system_clock::now();
		auto now_c = chrono::system_clock::to_time_t(now);
		tm now_tm = {};
		localtime_s(&now_tm, &now_c);
		stringstream ss;
		ss << put_time(&now_tm, "%M%S");
		string bookID = flightNumber.substr(0, 3) + ss.str();
        bookings.emplace_back(bookID, userID, flightNumber, tickets, bookingDate, "Scheduled");
    }
    else {
		bookings.emplace_back(bookingID, userID, flightNumber, tickets, bookingDate, "Scheduled");
	}

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
        if (toLower(flight.getOrigin()) == origin && toLower(flight.getDestination()) == destination) {
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
    catch (std::runtime_error&) {
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

string toLower(string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
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
    formatted += "\"";
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


// Read and write data to files
void exportUsersToCSV(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        return;
    }
    vector<User*> userList = users.traverse();
    outFile << "Type,UserID,FirstName,LastName,Email,Password,UserType,AdminRole\n";
    for (User* user : userList) {
        FlightAdmin* admin = dynamic_cast<FlightAdmin*>(user);
        if (admin) {
            outFile << "Admin," << admin->get_userId() << "," << admin->get_first_name() << ","
                << admin->get_last_name() << "," << admin->get_email() << "," << admin->get_password() << ","
                << admin->get_user_type() << "," << admin->get_adminRole() << "\n";
        }
        else {
            outFile << "User," << user->get_userId() << "," << user->get_first_name() << ","
                << user->get_last_name() << "," << user->get_email() << "," << user->get_password() << "," << user->get_user_type() << ",\n";
        }
    }
    outFile.close();
}

void importUsersFromCSV(const string& filename) {
    ifstream inFile(filename);
    string line;
    if (!inFile.is_open()) {
        return;
    }
    getline(inFile, line);
    while (getline(inFile, line)) {
        stringstream ss(line);
        string type, userId, firstName, lastName, email, password, userType, adminRole;
        getline(ss, type, ',');
        getline(ss, userId, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, userType, ',');
        getline(ss, adminRole);

        if (type == "Admin") {
            createAdmin(userId, firstName, lastName, email, password, adminRole);
        }
        else if (type == "User") {
            registerUser(userId, firstName, lastName, email, password, userType);
            getUserId();
        }
    }
    inFile.close();
}

void exportFlightsToCSV(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        return;
    }
    outFile << "FlightNumber,AirlineName,DateOfFlight,Origin,Destination,DepartureTime,ArrivalTime,TotalRows,SeatsPerRow,BusinessRows,BusinessPrice,RegularPrice,FlightDuration\n";
    for (const Flight& flight : flights) {
        outFile << flight.getFlightNumber() << "," << flight.getAirlineName() << ","
            << flight.getDateOfFlight() << "," << flight.getOrigin() << ","
            << flight.getDestination() << "," << flight.getDepartureTime() << ","
            << flight.getArrivalTime() << "," << flight.getTotalRows() << ","
            << flight.getSeatsPerRow() << "," << flight.getBusinessRows() << ","
            << flight.getBusinessPrice() << "," << flight.getRegularPrice() << ","
            << flight.getFlightDuration() << "\n";
    }

    outFile.close();
}

void importFlightsFromCSV(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        return;
    }
    string line;
    getline(inFile, line);
    while (getline(inFile, line)) {
        stringstream ss(line);
        string flightNumber, airlineName, dateOfFlight, origin, destination, departureTime, arrivalTime;
        int totalRows, seatsPerRow, businessRows;
        double businessPrice, regularPrice, flightDuration;
        getline(ss, flightNumber, ',');
        getline(ss, airlineName, ',');
        getline(ss, dateOfFlight, ',');
        getline(ss, origin, ',');
        getline(ss, destination, ',');
        getline(ss, departureTime, ',');
        getline(ss, arrivalTime, ',');
        ss >> totalRows;
        ss.ignore(1, ',');
        ss >> seatsPerRow;
        ss.ignore(1, ',');
        ss >> businessRows;
        ss.ignore(1, ',');
        ss >> businessPrice;
        ss.ignore(1, ',');
        ss >> regularPrice;
        ss.ignore(1, ',');
        ss >> flightDuration;

        addFlight(flightNumber, airlineName, dateOfFlight, origin, destination, departureTime, arrivalTime,
            totalRows, seatsPerRow, businessRows, businessPrice, regularPrice, flightDuration);
    }
    inFile.close();
}

void exportBookingsToCSV(const string& bookingsFilename, const string& ticketsFilename) {
    ofstream bookingsFile(bookingsFilename);
    ofstream ticketsFile(ticketsFilename);

    if (!bookingsFile.is_open() || !ticketsFile.is_open()) {
        cerr << "Error opening one or more files." << endl;
        return;
    }

    bookingsFile << "BookingID,UserID,FlightNumber,BookingDate,Status,CheckInStatus\n";
    ticketsFile << "BookingID,TicketID,PassengerName,PassportNumber,PassportIssueCountry,FlightNumber,TicketType,SeatNumber,Price\n";

    for (const Booking& booking : bookings) {
        bookingsFile << booking.getBookingID() << "," << booking.getUserID() << ","
            << booking.getFlightNumber() << "," << booking.getBookingDate() << ","
            << booking.getStatus() << "," << (booking.getCheckInStatus() ? "Checked In" : "Not Checked In") << "\n";
        for (const Ticket& ticket : booking.getTickets()) {
            const Passenger& passenger = ticket.getPassenger();
            ticketsFile << booking.getBookingID() << "," << ticket.getTicketID() << "," << passenger.get_name() << ","
                << passenger.get_passportNumber() << "," << passenger.get_passportIssueCountry() << ","
                << ticket.getFlightNumber() << "," << ticket.getTicketType() << ","
                << ticket.getSeatNumber() << "," << ticket.getPrice() << "\n";
        }
    }
    bookingsFile.close();
    ticketsFile.close();
}

void importBookingsFromCSV(const string& bookingsFilename, const string& ticketsFilename) {
    ifstream bookingsFile(bookingsFilename);
    ifstream ticketsFile(ticketsFilename);
    map<string, vector<Ticket>> ticketMap;
    if (!bookingsFile.is_open() || !ticketsFile.is_open()) {
        cerr << "Error opening one or more files." << endl;
        return;
    }
    string line;
    getline(ticketsFile, line);
    while (getline(ticketsFile, line)) {
        stringstream ss(line);
        string bookingID, ticketID, passengerName, passportNumber, passportIssueCountry, flightNumber, ticketType, seatNumber, priceStr;
        getline(ss, bookingID, ',');
        getline(ss, ticketID, ',');
        getline(ss, passengerName, ',');
        getline(ss, passportNumber, ',');
        getline(ss, passportIssueCountry, ',');
        getline(ss, flightNumber, ',');
        getline(ss, ticketType, ',');
        getline(ss, seatNumber, ',');
        getline(ss, priceStr);
        double price = stod(priceStr);
        Passenger passenger(passengerName, passportNumber, passportIssueCountry);
        Ticket newTicket(ticketID, passenger, flightNumber, ticketType, seatNumber, price);
        ticketMap[bookingID].push_back(newTicket);
    }

    getline(bookingsFile, line);
    while (getline(bookingsFile, line)) {
        stringstream ss(line);
        string bookingID, userID, flightNumber, bookingDate, status, checkInStatus;
        getline(ss, bookingID, ',');
        getline(ss, userID, ',');
        getline(ss, flightNumber, ',');
        getline(ss, bookingDate, ',');
        getline(ss, status, ',');
        getline(ss, checkInStatus);

        bool checkIn = (checkInStatus == "Checked In");
        vector<Ticket>& tickets = ticketMap[bookingID];
        Booking* newBooking = new Booking(bookingID, userID, flightNumber, tickets, bookingDate, status);
        newBooking->setCheckInStatus(checkIn);
        bookings.push_back(*newBooking);

        // Enqueue if status is "Pending Cancellation"
        if (status == "Pending Cancellation") {
            cancelledBookingsQueue.enqueue(newBooking);
        }

    }

    bookingsFile.close();
    ticketsFile.close();
}