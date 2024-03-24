#include "flightAdmin.h"

FlightAdmin::FlightAdmin(const string& userID, const string& first_name, const string& last_name, const string& email, const string& password, const string& adminRole)
    : User(userID, first_name, last_name, email, password, "Admin"), adminRole(adminRole) {}

string FlightAdmin::get_adminRole() {
    return adminRole;
}
