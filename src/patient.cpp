// HASSIC Rayan Zakaria

#include "../headers/patient.h"
#include <string>
#include <ncurses.h>

Patient::Patient(string pName, int pID)
{
    patientName = pName;  
    patientID = pID;
    setLatest(); //set the first messure of heart rate and blood pressure of the patient 
    patientStatus = UNDERTEAT;
}

//function to print the patient information
void Patient::printStatus() const
{
  int s;
  s = getStatus();
  switch (s)
  {
  case 0:
    mvprintw( LINES / 2 + 1, COLS - 40,"Critical        ");
    break;
  case 1:
    mvprintw( LINES / 2 + 1, COLS - 40,"Passed away     ");
    break;
  case 2:
    mvprintw( LINES / 2 + 1, COLS - 40,"Released        ");
    break;
  case 3:
    mvprintw( LINES / 2 + 1, COLS - 40,"Under treatement");
    break;
  }
}
void Patient::PrintInfo( ) const
{
  init_pair( 6 , COLOR_RED, COLOR_BLACK);   // Set Color Palet for Urgent

  wattron( stdscr, A_BOLD);
  if ( urgent( getLatest() ) )  // check if urgent Case
  { 
        wattron(stdscr, COLOR_PAIR( 6 ));
        beep();
  }
  
  mvprintw(LINES / 2 - 3, COLS - 40 , "Name: %s\n", getName().c_str());
  mvprintw(LINES / 2 - 2, COLS - 40 , "ID: %d\n", getID());
  mvprintw(LINES / 2 - 1, COLS - 40 , "Latest blood Pressure: %d \n", getLatest()->bloodPleasure );
  mvprintw(LINES / 2 , COLS - 40 , "Latest heart rate: %d\n", getLatest()->heartRate );
  printStatus();
  wattroff( stdscr, COLOR_PAIR( 6 ) );
  wattroff( stdscr, A_BOLD);
}

  //function to get the latest messurment of the patient 

  list<Patient::info>::const_iterator Patient::getLatest() const
  {
    // retutns the top of the stack
    return history.begin(); 
  }

  //funtion to set both blood pressure and heart rate and push them into the history

  void Patient::setLatest()
  {
    info temp;
    temp.time = getCurrentTime();
    temp.bloodPleasure = 90 + rand() % 30 + ( random() % 60 - 30) ;
    temp.heartRate = 60 + rand() % 40 + ( random() % 40 - 20);
    
    history.push_front(temp);
  }


  string Patient::getName() const
  {
    return patientName;
  }
  
  int Patient::getID() const
  {
    return patientID;
  }

  // function to display the patient history from the latest to the oldest
void Patient::getHistory()  const
{
  list<Patient::info>::const_iterator iter;
  int i = 14;
  for ( iter = history.begin() ; iter != history.end() ; iter++)
  {
    wattron( stdscr, A_BOLD );
    if ( urgent( iter ) )  // check if urgent Case
    { 
          wattron(stdscr, COLOR_PAIR( 6 ));
          beep();
    }

    mvprintw( i + 1, COLS / 2 - 12 - 30, "> : %s               \n", iter->time.c_str() );
    mvprintw( i + 1, COLS / 2 - 12, " Blood Pressure: %d\n", iter->bloodPleasure );
    mvprintw( i + 2, COLS / 2 - 12, " Heart Rate: %d \n", iter->heartRate );
    
    i += 4;

    wattroff( stdscr, A_BOLD );
    wattroff( stdscr, COLOR_PAIR( 6 ));
  }
    
}


// function to get the actual time for the measurement day month h:m:s
string Patient::getCurrentTime() const
{
  time_t now = std::time(NULL);
  struct tm * curtime = localtime ( &now );
   return asctime(curtime);
}
/*
  * @return true: If urgent
*/
bool Patient::urgent( list<Patient::info>::const_iterator itr ) const
{
  return itr->bloodPleasure > 140 || itr->bloodPleasure < 90 || itr->heartRate > 100  || itr->heartRate < 60 ;
}

/*
 * get Patient Status
 */
int Patient::getStatus() const
{
   return patientStatus;
}

/*
 * Change Patient Status
 */
void Patient::setStatus(Status s)
{
  patientStatus = s;
}

 
void from_json(const json& j, Patient::info& i)
{
  j.at("time").get_to(i.time);
  j.at("Blood pressure").get_to(i.bloodPleasure);
  j.at("Heart rate").get_to(i.heartRate);
}
void from_json(const json& j, Patient& p)
{
  j.at("ID").get_to(p.patientID);
  j.at("Name").get_to(p.patientName );
  j.at("Status").get_to(p.patientStatus);
  j.at("Info").get_to(p.history);
}

void to_json(json & j, const Patient& p)
{
  j = json { {"Name", p.patientName }, { "ID" , p.patientID }, { "Status" , p.patientStatus}, {"Info", p.history }};
}

void to_json (json & j, const Patient::info& i)
{
  j = json { {"time", i.time }, { "Blood pressure" , i.bloodPleasure }, { "Heart rate" , i.heartRate }};
}
