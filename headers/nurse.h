// HASSIC Rayan Zakaria

#ifndef NURSE_H
#define NURSE_H

#include "user.h"


/*
* ADT for All Types of Users that contains all the general 
* functionelities that the nurse has 
*/
class Nurse : public User
{    
    friend class Doctor;        
    friend class Director;
    
    private:
        Service* service;
    public:
        Nurse() = default;
        Nurse( const string& nurseName , int nurseID, const string& nursePassword, const string& nurseService );
        Nurse( string&& nurseName , int nurseID, string && nursePassword, string && nurseService );
        ~Nurse();        

        // Look for a patient by Id number . complexity O(1) on average
        bool checkPatientById( int ) override;
        // Look for a patient by Name. complexity O(n) 
        bool checkPatientByName( string ) override;
        // Prints the Info of the current Patient
        void printCurrentPatientInfo() override;
        void printCurrentPatientHistory() override;
        //Print Info of the current while keepin track of the next
        void printNextPatient()  override;
        // generate a new ID number for a new Patient
        size_t getNewId( const string& ) const override;
        // Add a new Patient to the service
        void addPatient(string ) override;
        void addPatientWithoutWriting(string );
};

#endif

