// HASSICI Rayan Zakaria

#include "../headers/director.h"

Director::Director(string directorName , int directorID, string directorPassword, string directorService)
: Doctor( directorName, directorID, directorPassword, directorService )
{     
} 
/*
    Update Patient's File on destruction
*/
Director::~Director()
{
    Nurse::service->updatePatientsFile();
    delete service;
}

/*
    Initalizes the service for the director
*/
void Director::setService( services s )
{
    Service* temp;
    switch (s)
    {
        case CRITIC:
        {
            temp = new Service("Critical");
            break;
        }
        
        case CARDIO:
        { 
            temp = new Service("Cardiology");
            break;
        }

        case NEURO:
        {
            temp = new Service("Neurology");
            break;
        }

        case GENICO:
        {
            temp = new Service("Genicology");
            break;
        }

        case PNEUMO:
        {
            temp = new Service("Pneumology");
            break;
        }

        default:
            break;
    }
    
    service = new Service(*temp);
}