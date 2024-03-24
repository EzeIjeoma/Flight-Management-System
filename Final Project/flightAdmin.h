#pragma once

#include "user.h"
#include <string>
#include <vector>

using namespace std;

class FlightAdmin : public User {
private:
    string adminRole;

public:
    FlightAdmin(const string& userID, const string& first_name, const string& last_name, const string& email, const string& password, const string& adminRole);
    string get_adminRole();
};
