// HASSICI Rayan Zakaria

#include <string>   
#include <fstream> 
#include <nlohmann/json.hpp>
#include <vector>
#include "../headers/user.h"

using std::vector;

User::User(const string& userName, int userID, const string& userPassword, const string& userService): name(userName), id(userID), password(userPassword), serviceName(userService)
{
}

string User::getName() const
{
    return name;
}
int User::getID() const
{
    return id;
}
string User::getPasswd() const
{
    return password;
}
string User::getService() const
{
    return serviceName;
}

/*
    *
    *Checks if the User with the given credentials exists
    *@param name: User's Name
    *@param id: User's Id
    *@param password: User's Password
    *@param role: User's role ( Director, Nurse or Doctor) 
*/
bool User::check( string name, int id, string password, roles role )
{
    string roleName;
    if ( role == DIRECTOR )
        roleName = "Director";
    else if (role == DOCTOR )
        roleName = "Doctor";
    else if ( role == NURSE )
        roleName = "Nurse";

    // parse the User's file
    std::fstream f("Data/Users.json");
    json j = json::parse(f);
    f.close();
    // put the users in an array
    vector<User> users = j[roleName];
    
    // Intialize a static iterator so that it won't
    // be destructed at the end of the function
    static vector<User>::iterator itr;    

    for(  itr = users.begin() ; itr != users.end() ; itr++)
    {
        if (itr->getName() == name && itr->getID() == id && itr->getPasswd() == password)
        {
            *this = *itr;
            return true;
        }
    }
    return false;
}

// /*
//     Set service from Pointer
// */
// void User::setService(Service* service )
// {
//     if ( service == nullptr)
//     {
//         this->service = service;
//         return;
//     }
//     // Initialize an object
//     if ( this->service == nullptr )
//         this->service = new Service();
//     setService(*service);
// }

/*
    Deserialize json object into User object
*/        
void from_json(const json& j, User& u)
{    
    u.name = j.at("Name");
    u.id = j.at("Id");
    u.password = j.at("Password");
    u.serviceName = j.at("Service");
}
