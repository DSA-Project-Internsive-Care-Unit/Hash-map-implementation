/********************************************/
/* Team Leader's Name: HASSIC Rayan Zakaria */
/* --- --- --- --- --- --- --- --- --- --- -*/
/** Please Check the DocStrings for Better **/
/**            Understanding               **/
/********************************************/


#include "../headers/display.h"         

// Function prototypes

bool mainMenu( User* user, roles role );

int main()
{
/***************************    Initializing Display   ****************************/
    initscr(); // initialze screen
    if (COLS < 100 || LINES < 44)              // Set Minimum Screen size
    {
        endwin();
       std::cout << "\v \t\tSize of the Window is too small\n\t       Please Resize your screen Then try again.\v\n";
       return 1;
    }
    
    start_color();                              // Prepare for displaying colors
    wbkgd(stdscr, COLOR_PAIR(MAIN));            // Setting the background and text colors
    raw();                                      // Process each character on input without waiting for end of line
    noecho();                                   // No writing in terminal
    colors();                                   // initialize the color pallet
    refresh();

/**********************************************************************************/

/************************* Initializing variables *************************/
    User* user = nullptr;       // Pointer to the user ( Doctor, Director or Nurse )
    roles userRole;             // User's role    
/*************************************************************************/
    
    // Print the Splash screen
    printIntro();                               
        // Boolean to tell if the Director 
        // wants to reselect role or not
        bool reselect;                              
        do {
            // Prompt the user to enter his role
            userRole = roleSelect();
            reselect = auth( user , userRole );   
            clear();
        // Does not exit until the credentials are correct
        } while( reselect );                        


        // Use polymorphism to instantiate the
        // object corresponding to the user role
        user = newUser( userRole, user );
        if ( userRole == DIRECTOR )
        {
            // Variable to tell if the user wants 
            // to change service or not 
            bool change;                            
            do 
            {
                chooseService( user );
                 // Main menu returns if the Director 
                 // wants to change service or not
                change = mainMenu( user, DIRECTOR );
            
            // Loop until the Director doesn't want to change service
            } while ( change );
        }
        else 
         // Display the mainMenu 
         // according to the role
           mainMenu( user , userRole );           

    // Clear the window
    endwin();
}


/*
    * DashBoard for the user that cyclically displays 
    the service's patient's Info
    * as well as the following options:
    *- Monitor a patient
    *- Add a patient
    *- log out
    *- Choose a service (  director only )
    *Returns: 
    *true if the user wants to log out
    *false if the director wants to change service
*/
bool mainMenu( User* user, roles role )
{
    do
    {
        // Print Info of the first 
        // Patient in the Service
        user->printNextPatient();
        enum options { MONITOR, ADD, LOGOUT, CHOOSE_OTHER_SERVICE , NONE = -1 };
        
        int selection = options1( role );
        
        if ( selection == LOGOUT )
        {
            delete user;
            user = nullptr;
            return false;                    // Indicate that the user wants to log out
        }
        else if ( selection == MONITOR )
        {
            monitorPatient(role, user);      // Displays
            clear();
        }
        else if ( selection == ADD )
        {
            addPatient( user );
            clear();
        }
        else if ( selection == CHOOSE_OTHER_SERVICE )   
             //  indicate that the director 
             // wants to change service 
            return true;    
        
        
    // Keep showing the menu until the 
    // user logs out or changes service
    } while (true);  
}