// HASSIC Rayan Zakaria

#include "../headers/nurse.h"         
#include <chrono>
#include <unistd.h>
#include <fstream>
using namespace std::chrono_literals;

/********************************************************************
// Testing Insertion time for Different sizes of Patients          //
// -- for this test we removed the ability to update patient file  //
// The steps are:                                                  //
// -- keep changing the number of Patients in a service            //
// -- for eacg number of Patient test the insertion time           //
/*******************************************************************/


const int NUMBER_OF_EXPERIMENTS = 5;
int main()
{
    std::fstream f ("Hash-running-time.csv", std::ios::out );
    f << "Size, time\n";
    for ( int i = 1 ; i < PATIENT_CAPACITY ; i += 100)
    {
        Nurse test("test", 0, "test", "test");
        for ( int k = 0 ; k < i ; k++)
            test.addPatientWithoutWriting( std::to_string(k));
        
        std::chrono::nanoseconds average = 0ns;
        for ( int j = 0 ; j < NUMBER_OF_EXPERIMENTS ; j++ )
        {
            auto begin = std::chrono::high_resolution_clock::now();
            test.addPatientWithoutWriting( std::to_string(j + i * 6 ) );
            auto end = std::chrono::high_resolution_clock::now();
            average += std::chrono::duration_cast<std::chrono::microseconds>( end - begin);
        }
        f << i <<", " << average.count() / NUMBER_OF_EXPERIMENTS << "\n";
    }
    f.close();
}


