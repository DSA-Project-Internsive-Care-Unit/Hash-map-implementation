// HASSIC Rayan Zakaria

#include "../headers/nurse.h"

/*
* Construct a Service object inside the nurse
*/
Nurse::Nurse(const string& nurseName , int nurseID, const string& nursePassword, const string& nurseService)
             : User(nurseName, nurseID, nursePassword, nurseService)
{
    // nurseService == "" <=> user is Direcor
    // Do not initialize the service yet
    service = ( nurseService.empty() ) ? nullptr : new Service(nurseService);
}

/*
* Construct a Service object inside the nurse
*/
Nurse::Nurse(string && nurseName , int nurseID, string&& nursePassword, string&& nurseService)
             : User(nurseName, nurseID, nursePassword, nurseService)
{
    // nurseService == "" <=> user is Direcor
    // Do not initialize the service yet
    service = ( nurseService.empty() ) ? nullptr : new Service(nurseService);
}


/*
    Print Info of the current Patient
*/
void Nurse::printCurrentPatientInfo( )
{
    service->getCurrentPatient().PrintInfo(); 
}

/*
    Print the history of the current Patient
*/
void Nurse::printCurrentPatientHistory ()
{
    service->getCurrentPatient().getHistory();
}

/*
* Prints the next patient
*/
void Nurse::printNextPatient()
{
    service->printNextPatient();
    service->patientUpdate( );
}

/*
    Add a key( id ) value ( Patient ) pair to the Patient's map 
*/
void Nurse::addPatient(string patientName)
{
    // Do not allow adding more 
    // patients than the service capacity
    if ( service->getNumberOfPatients() + 1 > PATIENT_CAPACITY )
        return; 
    // Initialize a new patient object
    Patient p(patientName, getNewId( patientName ));
   
    service->addPatient(p);
   // Write changes to the Json file
    service->updatePatientsFile();
}

/*
    Add a key( id ) value ( Patient ) pair to the Patient's map 
*/
void Nurse::addPatientWithoutWriting(string patientName)
{
    // Do not allow adding more 
    // patients than the service capacity
    if ( service->getNumberOfPatients() + 1 > PATIENT_CAPACITY )
        return; 
    // Initialize a new patient object
    Patient p(patientName, getNewId( patientName ));
   
    service->addPatient(p);
   // Write changes to the Json file
    // service->updatePatientsFile();
}



/*
    * Checks if a patient is in the service using id
    * complexity O(1) on average
*/
bool Nurse::checkPatientById( int id )
{
    if( service->getPatientById(id) == nullptr)
        return false;
    return true;
}

/*
    * Checks if a patient is in the service using name
    *complexity O(n)
*/
bool Nurse::checkPatientByName( string name )
{
    if( service->getPatientByName( name ) == nullptr)
        return false;
    return true;
}

/*
    * Create a unique Id for a new patient
    * Each ID is prefixed by a one
    * digit number that indicates which service
    * the patient initially belongs to
*/
size_t Nurse::getNewId( const string& name ) const
{
   size_t prefix;
   if ( service->getServiceName() == "Critical" )
       prefix = CRITICAL_PREF;      // prefix = 10000
   else if ( service->getServiceName() == "Cardiology" )
       prefix = CARDIOLOGY_PREF;    // prefix = 20000
   else if ( service->getServiceName() == "Gynecology" )
       prefix = GENICO_PREF;        // prefix = 30000
   else if ( service->getServiceName() == "Neurology" )
       prefix = NEURO_PREF;         // prefix = 40000
   else if ( service->getServiceName() == "Pneumology" )
       prefix = PNEUMO_PREF;        // prefix = 50000
   return service->getNewID( name ) + prefix ;
}

/*
    Update the Patient's file right before destruction
*/
Nurse::~Nurse()
{
    service->updatePatientsFile();
    delete service;
}