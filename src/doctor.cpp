// HASSIC Rayan Zakaria

#include "../headers/doctor.h"


Doctor::Doctor(string doctorName , int doctorID, string doctorPassword, string doctorService)
: Nurse( doctorName, doctorID, doctorPassword, doctorService)
{
} 
/*
    Allow's Doctor to change the Patient's Status
*/
void Doctor::changeStatus(Status patientStatus)
{
    Nurse::service->SetStatus( patientStatus );
    if ( patientStatus == CRITICAL && service->getServiceName() != "Critical" )
        Nurse::service->movePatient();
    Nurse::service->updatePatientsFile();
}

Doctor::~Doctor()
{
    // Update the Patient's 
    // file before destruction
    Nurse::service->updatePatientsFile();
    delete service;
}