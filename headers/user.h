// HASSIC Rayan Zakaria

#ifndef USER_H
#define USER_H


#include "service.h"


// Enumration of All possible roles
enum roles { DIRECTOR, DOCTOR, NURSE };


/**
 * Standard class, used similar to an abstract data
 * class of the Doctor, Nurse and Director classes
 * Uses polymorphism and dynamic binding of member
 * functions
*/
class User
{    
    // Function overload to deserialize a
    // json object into a user object
    friend void from_json(const json&, User& );     

    private:
        string serviceName;     // The service in which the user works
        string name;            // User's name
        int id;                 // User's id
        string password;        // User's Password
        
    public:
        User() = default;
        User( const string& userName, int userID, const string& userPassword, const string& userService);
        // Getters
        string getName() const;
        int getID() const;
        string getPasswd() const;
        string getService() const;
        
        // Check for validity of a user
        // In the User.json file
        bool check( string name, int id, string password, roles role );

        // function overrides
        //  for nurse class:
        
        virtual bool checkPatientById ( int ) { return false; }
        virtual bool checkPatientByName ( string ) { return false; }
        // Printing Info about the patient
        virtual void printCurrentPatientInfo()    {}
        virtual void printNextPatient( )  {}
         //Print Info of the current Patient while keepin track of the next
        virtual void printCurrentPatientHistory() {}
        // @return A unique Id for a new Patient
        virtual size_t getNewId( const string& ) const { return -1; }
        // add Patient by his name and id
        virtual void addPatient(string ) {}
        // Overrides for Doctor Class
        virtual void changeStatus( Status ) {}
        // Override for Director Class
        virtual void setService( services ) {}
        
};

#endif
