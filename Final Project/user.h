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


public:
	User(const string& userId, const string& first_name, const string& last_name, const string& email, const string& password, const string& user_type);
	string get_first_name() const;
	string get_last_name() const;
	string get_password() const;
	string get_email() const;
	string get_user_type() const;
	void set_password(string password);
	void set_email(string email);
};