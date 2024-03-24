#include "user.h"

User::User(const string& userId, const string& first_name, const string& last_name, const string& email, const string& password, const string& user_type)
    : userId(userId), first_name(first_name), last_name(last_name), email(email), password(password), user_type(user_type) {}

string User::get_first_name() {
    return first_name;
}

string User::get_last_name() {
    return last_name;
}

string User::get_password() {
    return password;
}

string User::get_email() {
    return email;
}

string User::get_user_type() {
    return user_type;
}

void User::set_password(string new_password) {
    password = new_password;
}

void User::set_email(string new_email) {
    email = new_email;
}