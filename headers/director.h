// HASSIC Rayan Zakaria
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "doctor.h"

/*
* Inherits from Nurse and Doctor
* Has the same abilities as Doctor
* Has a feature to change service
*/
class Director : public Doctor
{
public:
    Director() = default;
    Director(string directorName , int directorID, string directorPassword, string directorService);
    ~Director();
    
    //Initalizes the service for the director
    void setService( services s) override;
};



#endif

