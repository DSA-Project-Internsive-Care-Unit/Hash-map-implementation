// HASSIC Rayan Zakaria

#ifndef PATIENT_H
#define PATIENT_H


// Implementing a stack
// using std::list
// #define list<Patient::info> list<Patient::info>
// #define top begin
// #define push push_front


#include <nlohmann/json.hpp>
#include <list>
#include <iostream>
#include <string>
#include <ctime>

using std::string;
using std::list;   // alias for std::list

using json = nlohmann::json; 

// Enumartion of different Patient States
enum Status { CRITICAL, PASSEDAWAY, RELEASED, UNDERTEAT };

// Set rate in which the patient's 
// Info gets updated ( Each time it is 
// shown in the patient's monitor)
const int PATIENT_UPDATE_RATE = 10; 


class Patient
{
  private:
    // Struct to store medical Information
    struct info {
      int bloodPleasure;
      int heartRate;
      string time;       // the time the tests where taken
      info() = default;
      info(int bP, int hR, string time): bloodPleasure(bP), heartRate(hR), time(time) {}
    };

    // Stack Implementation of Patient's 
    // measurment history using std::list
    list<Patient::info> history;   
    string patientName;
    int patientID;
    Status patientStatus;
    
    // Helper function to Check if 
    // the medical information are unstable
    bool urgent( list<Patient::info>::const_iterator ) const;
    // helper function to return Current time
    string getCurrentTime() const;
    // helper function to get Latest Measuremnt check
    list<Patient::info>::const_iterator getLatest() const; 
    // helper function to print patient status
    void printStatus() const;
    
public:
    Patient() = default;
    Patient(string pName , int pID);  

  // Getters
    string getName() const;
    int getID() const;
    int getStatus() const; 

    void getHistory() const;          // print The History
    void PrintInfo() const;
    void setLatest();           // Set latest Info
    void setStatus( Status );   // Set patient Status

  // Function overloads to Serialize / Deserialize Json objects into Patient and info objects 
  friend void from_json(const json& j, Patient&);
  friend void from_json(const json& j, Patient::info&);
  friend void to_json (json & j, const Patient& p);
  friend void to_json (json & j, const Patient::info& i);

};
#endif

