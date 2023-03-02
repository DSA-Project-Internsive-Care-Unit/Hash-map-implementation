// HASSIC Rayan Zakaria

#ifndef SERVICE_H
#define SERVICE_H

#include <vector>
#include "patient.h"
#include <unordered_map>    // Hash Map library

// setting an alias for unordered map
// #define unordered_map<int, Patient> unordered_map<int, Patient>

using std::swap;
using std::unordered_map;

// The Maximum capacity that 
// the service can handle
const int PATIENT_CAPACITY = 10000;

// Prefixes to be used in the creating of Patient IDs
enum service_id_prefixes { CRITICAL_PREF = 100000, CARDIOLOGY_PREF = 200000, NEURO_PREF = 300000, GENICO_PREF = 400000, PNEUMO_PREF = 500000 };

 // enumerate different services
enum services { CRITIC , CARDIO , NEURO, GENICO, PNEUMO };



/*
  *This Class is the representation of The hospital's
  *Service.
  *Each service Stores Information of it's Own Patients
  *For each member function, Check the docString For Explanation
*/
class Service
{
  // Access move `patient()`
  friend class Doctor; 
  // Convert Json into a service object
  friend void from_json(const json& j, Service& s);

private:
    string serviceName;
    unordered_map<int, Patient> patients;               
    // Keeps track of the last 
    // Patient checked
    unordered_map<int, Patient>::iterator current;
   
    void SetStatus(Status);
    void movePatient();     

public:

    Service() = default;
    Service(const string& serviceName);
    Service(const Service &);

    int getNumberOfPatients() const;
    string getServiceName() const;
    Patient getCurrentPatient() const;
    unordered_map<int, Patient> getPatients() const;

    Service& operator=(const Service &);
    Patient* getPatientByName(const string& patientName);
    Patient* getPatientById(int patientID); 
    
    void addPatient(const Patient &);
    void updatePatientsFile();
    void printNextPatient() const;
    void patientUpdate( );
    size_t getNewID( const string& );

};

#endif