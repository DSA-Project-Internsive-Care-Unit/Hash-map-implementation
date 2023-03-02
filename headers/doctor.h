// HASSIC Rayan Zakaria

#ifndef DOCTOR_H
#define DOCTOR_H

#include "nurse.h"
#include <iostream>


/*
* Derivation of class Nurse
* adds a functionality to change Patient Status
*/
class Doctor : public Nurse
{
    public:
        Doctor() = default;
        Doctor(string doctorName , int doctorID, string doctorPassword, string doctorService); 
        ~Doctor();
        
        // Allows Doctor  to change Patient Status
        void changeStatus( Status patientStatus ) override;    
};


#endif