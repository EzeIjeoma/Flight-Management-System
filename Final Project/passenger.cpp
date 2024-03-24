#include "passenger.h"

Passenger::Passenger() : name(""), passportNumber(""), passportIssueCountry("") {}

Passenger::Passenger(const string& name, const string& passportNumber, const string& passportIssueCountry)
    : name(name), passportNumber(passportNumber), passportIssueCountry(passportIssueCountry) {}

string Passenger::get_name() const {
    return name;
}

string Passenger::get_passportNumber() const {
    return passportNumber;
}

string Passenger::get_passportIssueCountry() const {
    return passportIssueCountry;
}
