#pragma once

#include <string>
#include <vector>
#include "booking.h"
using namespace std;

class User
{
private:
	string userId;
	string first_name;
	string last_name;
	string email;
	string password;
	string user_type;
	vector<Booking> bookings;


public:
	User(const string& userId, const string& first_name, const string& last_name, const string& email, const string& password, const string& user_type);
	string get_first_name();
	string get_last_name();
	string get_password();
	string get_email();
	string get_user_type();
	void set_password(string password);
	void set_email(string email);
};