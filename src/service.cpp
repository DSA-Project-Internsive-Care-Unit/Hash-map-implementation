// HASSIC Rayan Zakaria

#include "../headers/service.h"
#include <vector>
#include <fstream>
#include <string>
#include <ncurses.h>
// Initialize critical Service as global variable
Service* critical = new Service("Critical");



Service::Service(const string& serviceName)
{
  this->serviceName = serviceName;
  // Read Patients file
  std::ifstream f ("Data/Patients.json", std::ios::in);
  // Parse the Patients file
  json j = json::parse(f);
  f.close();
  
  patients = j.at(serviceName);
  current = patients.begin();
}

//copy Constructor
Service::Service(const Service & serve)
{
    serviceName = serve.serviceName;
    patients = serve.patients;
    current = patients.begin();
}

string Service::getServiceName() const
{
  return serviceName;
}

Service& Service::operator=(const Service & serve)
{
    Service copy = serve;
      swap( *this,copy );
        return *this;
}
 
void Service::addPatient(const Patient & p)
{
  // Insert the patient Id as key and the patient as object
  patients.insert(std::pair<int, Patient>( p.getID() , std::move(p)) );
}

/*
  * Change Patient status to one of the options:
  * - Under Treatment
  * - Passed Away
  * or if in critical case move to Critical service
  * Only the director or Doctor can change Patient's status
*/
void Service::SetStatus(Status s)
{
  current->second.setStatus(s); 
}

/*
* Add a new test measurement
*/
void Service::patientUpdate ( )
{
  // Variable to indicate on which iteration
  // We will update the Patient 
  static int now = 0;
  now++;  
  if ( now % PATIENT_UPDATE_RATE != 0)
    return;
  for ( auto& patient: patients)
      patient.second.setLatest();
  updatePatientsFile();
}

/*
* Prints current patient and keeps 
* track of the next patient to print
*/
void Service::printNextPatient() const
{
  static auto current = patients.begin();
  if ( patients.size() == 0)
  {
    mvprintw( LINES / 2 - 3, COLS - 40, "      Service is Empty");
    return;
  }
  if ( current == patients.end())
    current = patients.begin();
  current->second.PrintInfo();
  current++;
}
/*
  Helper function to move patient to critical service
*/
void Service::movePatient()
{
  critical->addPatient( current->second );
  // Update the critical service in the Patients file
  critical->updatePatientsFile();
  // Remove the patient from the current service
  patients.erase( current->second.getID() );
  
  // Reset the current patient
  current = patients.end() ;
}

/*
  Search for Patient By Name
  * This function is less optimised than the one
  By Id since it will search linearly through the patients
*/
Patient* Service::getPatientByName(const string& patientName)
{

  auto itr = patients.begin();
  for (; itr != patients.end() ; itr++)
  {
    if (itr->second.getName() == patientName )
    {
      current = itr;
      // Returns the pointer to the 
      // Patient Stored in current
      return &(current->second);    
    }
  }
  current = patients.end();
  // If the Patient does not exist
  return nullptr;
}

/*
  Search for Patient By Id
  * This function is more optimised than the one
  By name since it will search by key 
*/
Patient* Service::getPatientById( int patientID )
{
  // find the Id int the hashmap
  current = patients.find( patientID );
  if ( current == patients.end() )  // if not found
    return nullptr;
  return &(current->second);

}

/*
  Returns the current Patient
*/
Patient Service::getCurrentPatient() const
{
    return current->second;
}


/*
 * return the list of patients
 */
unordered_map<int, Patient> Service::getPatients() const
{
  return patients;
}



void Service::updatePatientsFile()
{
  std::fstream p("Data/Patients.json");
  json j = json::parse(p);
  p.close();
  j[serviceName] = patients; 
  
  std::ofstream out("Data/Patients.json");
  out << std::setw(4) << j;
  out.close();
}



/*
  Set the behavior for assigning json objects to Service object
*/
void from_json(const json& j, Service& s)
{
  s.patients = j.at(s.serviceName);
}


/*
    * Hash function to get a Id 
    * with maximum load factor of 0.1
*/
size_t hash1(string key )
{
  int hashVal = 0;
  for ( char ch  : key )
  {
    hashVal = (37 * hashVal + ch); 
  }
  hashVal = ( hashVal < 0) ? -hashVal : hashVal;
  return hashVal  % (PATIENT_CAPACITY * 10); 
}


int isPrime( int x )
{
  if ( x == 1 )
    return false;
  for ( int i = 2; i * i <= x ; i++)
  {
    if ( x % i == 0)
      return false;
  }
        return true;
}

size_t previousPrime( size_t n )
{
  if ( n < 2 )
  throw -1;
  if ( isPrime( n ) )
    return n;
  return previousPrime( n - 1 );
}


/*
    * Hash function to get a Id 
    * with maximum load factor of 0.1
*/
size_t hash2(string key )
{
  size_t previous = previousPrime( PATIENT_CAPACITY * 10 );
  size_t hashVal = 0;
  for ( char ch  : key )
  {
    hashVal = 24 * hashVal + ch ; 
  }
  hashVal = (hashVal < 0) ? -hashVal : hashVal; // handle the case of overflow
  return previous - ( hashVal  % previous ); 
}

// Creates a Unique ID for new Patient
size_t Service::getNewID( const string& name )
{
  // Getting current time
  time_t _tm = std::time(NULL);
  struct tm * curtime = localtime ( &_tm );
  
  string time = asctime(curtime);
  string key = name + time;

  size_t index1 = hash1( key );
  size_t index2 = hash2( key );
  size_t id = index1;

  int offset = 1;
  while ( getPatientById( id ) )
  {
    id +=  index2;
    id %=  PATIENT_CAPACITY * 10;
    offset++;
  }
  return id;
}

/*
  @return returns the number of patients enrolled in the service
*/
int Service::getNumberOfPatients() const
{
  return patients.size();
}