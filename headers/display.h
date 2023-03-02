// HASSICI Rayan Zakara

#include "helper.h"                   // Header containing some helper functions
#include "titles.h"                  // Header containing the Window titles 

/*************************************************/
/** This File Contains the Screens and Windows  **/
/**             Used in the Program             **/
/*************************************************/


// Function Prototypes

void addPatient( User* user );
bool changeStatusMenu(int role, User* user);
void monitoring(int role, User* user);
void monitorPatient(int role, User* user) ;
void monitorPatientMenu(int role, User* user);
void printPatientHistory(int role, User* user);
void success();
void color();
int options2();

/*
    Print the Loading Screen
*/
void printIntro()
{
    intensiveCareUnit();
    move(0, 0);         // set the cursor away from text
    refresh();          // print the content of the screen before the delay in loading
    loading();
}

/*
    Function to display and prompt user to enter his role
    @return the index referring to the user's selection
*/
roles roleSelect()
{
    clear();    // Clear screen

    // Print title
    selectRole();

    WINDOW* menu = drawBox(23, COLS/2 - 12, 8, 25, CONTAINER);      // Create a Container for Menu


    keypad(stdscr, TRUE);           // Enable using arrow keys
    
    const int NUM_OF_ROLES = 3;
    std::string opts[NUM_OF_ROLES] = { "  Director   ", "   Doctor    ", "   Nurse     "};    // List of options


    int c;              // Input character
    int selection = 0;  // Highlighted Option


    while ( true )
    {
        for ( int i = 0 ; i < NUM_OF_ROLES ; i++)  
        {
            mvwwritew(menu, 2 * i + 1, 3, "   ");       // Spacing
           
            if ( i == selection )                       // If highlited
            {
                wattron(menu, A_REVERSE);               // Reverse Colors foreground to background Vice versa
                mvwwritew(menu, 2 * i + 1, 3, " > ");
            }
            mvwwritew(menu, 2 * i + 1, 6, opts[i]);
            wattroff(menu, A_REVERSE );                 // Untoggle the Reverse
            move(0, 0);                                 // set the cursir away from text
        }

        c = getch();                                    // Read Input
        
        moveCursor(c, selection, NUM_OF_ROLES);         // Move according to the input

        if (c == 10)                                    // If the user pressed ENTER 
            break;
    }
    keypad(stdscr, FALSE);           // Disabable using arrow keys

    return (roles) selection;     // Keep track of the user input 
}

/*
    Function to display the authentification screen and returns user input by refernce                                          FINISHED
    @param name: Reference to the name of the user (Director, Doctor or nurse)
    @param id: Reference to the Identification number of the user
    @param password: User's password
    @param role: User's role
    @param u: Pointer to initialize the user at
    @return 
    true: for reselection
    , false: otherweise
*/
bool auth( User*& user, roles userRole )
{
    /**********************************************************************************/
    /********************* Declaring / Initialzing variables   ************************/
    /**********************************************************************************/
    int userId = 0;                   // User's Id   
    string userName = "";             // User's name    
    string userPassword = "";         // User's Password    
    user = new User(); 
    /**********************************************************************************/

    // Display title
    clear();
    login();

    // indicates whether the 
    // credentials are correct or not
    bool ch;     
    do    // Keep Prompting for Details Untill correct info is given
    {
        /*******************************   DISPLAY   **************************************/
        WINDOW* menu = drawBox(15, COLS / 2 - 30, 21, 60, 2);       // Menu Container

        mvwwritew(menu, 4, 1, "Full Name:", 3);                     // Display Name Prompt 
        WINDOW* fname = drawBox(18, COLS / 2 - 26, 2, 52, 4);

        mvwwritew(menu, 4, 8, "ID Number:", 3);                     // Display Id Prompt
        WINDOW* Id = drawBox(25, COLS / 2 - 26, 2, 52, 4);

        mvwwritew(menu, 4, 15, "Password:", 3);                     // Display Password Prompt
        WINDOW* pswd = drawBox(32, COLS / 2 - 26, 2, 52, 4);
        /***********************************************************************************/
        
        // Receiving Inputs
        getInput(fname, userName);                                      
        getInput(Id, userId);
        getPassword(pswd, userPassword);

        ch = user->check( userName, userId, userPassword, userRole );        // Check the credentials
        
        if ( ch )  // Patient exists
            break; // go back to main and execute next procedures
        
        // Display authentificatrion error message
        authErr();

        // take user input
        int c = getch();    

        // Make an option to go back to role selection menu
        keypad(stdscr, true);
        if ( c == KEY_BACKSPACE )
        {
            keypad(stdscr, false);        
            return true;
        }
         keypad(stdscr, false);

    } while ( !ch );   

    return false;
}

/*
    * Display services and receive Director's choice
    * Options:
    * - Critical
    * - Cardiology
    * - Neurology
    * - Genicology
    * - Pneumology
*/
void chooseService(User*& user)
{
    int selection = options2();
    // Update the service member of the Director
    user->setService( ( services ) selection );   
    return;
}   


/*
    *Show the following Options:
    *1. Monitor a Patient
    *2. Add a Patient
    *3. Log out
    *4. Choose an other service (Director only)
    @return selection | -1 == NONE ( if nothing selected within 3 seconds)
*/
int options1( int role )
{
     /******************************************* DISPLAY ****************************************/
        // clear();
        wattron(stdscr, A_BOLD);
        mainTitle();
        WINDOW* menu = drawBox(23, COLS * 0.1 - 12, 8, 40, CONTAINER);      // Create a Container for Menu
        wattron(stdscr, A_REVERSE);
        mvprintw(20, COLS - 40 , "    PATIENT'S MONITOR:    "); 
        mvprintw( 20, COLS * 0.1  , "        OPTIONS:          "); 
        wattroff(stdscr, A_BOLD);
        wattroff(stdscr, A_REVERSE);
        /**********************************************************************************************/

    const int NUM_OF_OPTIONS = 4;
    const int DIRECTOR_ONLY_OPTION = 3;
   
    std::string opts[NUM_OF_OPTIONS] = { "  Monitor a Patient          ", "  Add a patient              ", "  Log out                    ", "  Choose an other Service    "};
    int c;              // User input charachter
    static int selection = 0;  // Highlighted Option
    keypad(stdscr, true);
    while ( true )
    {
        for ( int i = 0 ; i < NUM_OF_OPTIONS ; i++)  
        {
            if ( i == DIRECTOR_ONLY_OPTION && role != DIRECTOR )
                 continue;
            mvwwritew(menu, 2 * i + 1, 3, "   ");
            if ( i == selection )                       // If highlited
            {
                wattron(menu, A_REVERSE);               // Reverse Colors foreground to background Vice versa
                mvwwritew(menu, 2 * i + 1, 4, " > ");
            }
            mvwwritew(menu, 2 * i + 1, 6, opts[i]);
            wattroff(menu, A_REVERSE );                 // Untoggle the Reverse
            move(0, 0);                                 // set the cursor away from text
        }
        timeout(3000);
        c = getch();  
        timeout(-3);
        if ( c == ERR )
            return -1;
                                          // Read Input
        moveCursor(c, selection, (role != DIRECTOR) ? NUM_OF_OPTIONS - 1 : NUM_OF_OPTIONS  );                     // Move according to the input
        if (c == 10)                           // 10 -> ENTER key
        {
            keypad( stdscr, false );
            break;
        }
    }
    keypad( stdscr, false );
    return selection;
}


/*
    *Show the Service Options:
    *1. Critical
    *2. Cardiology
    *3. Neurology
    *4. Genicology
    *5. Pneumology
    *@return Director's service choice
*/
int options2()
{
    /******************************************* DISPLAY ****************************************/
        // Display title
    chooseYourService();
    WINDOW* menu = drawBox(23, COLS * 0.5 - 12, 12, 25, CONTAINER);      // Create a Container for Menu
    /********************************************************************************************/

    const int NUM_OF_SERVICES = 5;
    std::string opts[NUM_OF_SERVICES] = { "  Critical    ", "  Cardiology  ", "  Neurology   ", "  Genicology  ", "  Pneumology   "};
    
    int c;              // User's input charachter
    int selection = 0;  // Highlighted Option

    keypad(stdscr, true);   // Enable arrow keys

    while ( true )
    {
        for ( int i = 0 ; i < NUM_OF_SERVICES ; i++)  
        {
            mvwwritew(menu, 2 * i + 1, 3, "   ");
            if ( i == selection )                       // If highlited
            {
                wattron(menu, A_REVERSE);               // Reverse Colors foregrounf to background Vice versa
                mvwwritew(menu, 2 * i + 1, 3, " > ");
            }
            mvwwritew(menu, 2 * i + 1, 6, opts[i]);
            wattroff(menu, A_REVERSE );                 // Untoggle the Reverse
            move(0, 0);                                 // set the cursir away from text
        }
        c = getch();                                    // Read Input
        moveCursor(c, selection, NUM_OF_SERVICES);                    // Move according to the input

        if (c == 10)                         // If Pressed ENTER
        {
            keypad(stdscr, FALSE);           // Disable using arrow keys
            // Keep showing the menu untill
            // The user clicks enter
            break;
        }
    }
    clear();
    return selection;
}

/*
    Display a visual Prompt to enter the name 
    and Id of a new Patient to be Inserted
*/
void addPatient( User* user )
{
    bool ch;
    do
    {
        int id;             // Patent's Id
        std::string name;   // Patent's Name
        clear();

    /**********************************  DISPLAY '*******************************************/
        WINDOW* menu = drawBox(15, COLS / 2 - 30, 21, 60, 2);       // Menu Container
        mvwwritew(menu, 4, 1, "Full Name:", PLACE_HOLDER);                     // Display Name Prompt 
        WINDOW* fname = drawBox(18, COLS / 2 - 26, 2, 52, 4);
        WINDOW* goBack = drawBox(25, COLS / 2 - 20, 3, 40, PLACE_HOLDER);
        mvwwritew(goBack, 20 - 17, 1, "Press BACKSPACE ( <- ) to go back", PLACE_HOLDER);  
        refresh();
    /***************************************************************************************/
        keypad(stdscr, true);
        int c = getch();
        if ( c == KEY_BACKSPACE )
        {
            keypad(stdscr, false);
            return ;
        }
        keypad(stdscr, false);
        // Get Input
        getInput(fname, name);                                      

         

        if( name != "" )   // Check for Patient validity
        {
            user->addPatient( name);       // add patient
            break; 
        }
        else
            // Print error message
            if ( Err() )  
                return;

    } while( true );    // Keep prompting untill the patient is added
    

}


/*
    Display a prompt for Id
    and check validity of Patient
*/
void monitorPatient(int role, User* user) 
 { 
    clear();

    bool ch;    
    string id;     

    do{
    /*********************************  DISPLAY   ***********************************/
        WINDOW* menu = drawBox(15, COLS / 2 - 30, 21, 60, CONTAINER);   
        
        mvwwritew(menu, 4, 8, "Patient name or ID Number:", PLACE_HOLDER);              // Display Id Prompt
        WINDOW* Id = drawBox(25, COLS / 2 - 26, 2, 52, IN);
    /********************************************************************************/
    
        // read both id or Name
        if ( getInput_template(Id, id) )        // if Input is string
            ch = user->checkPatientByName( id );
        else 
            ch = user->checkPatientById( stoi(id) );

        if(!ch) // If wrong Id
        {
            // display error
            if ( incorrectERR() ) 
                break;
        }
        else
        {
            monitoring(role, user);  
            return;   
        }

    } while(!ch);
}


/*
    Prints Current Info about Patient and the Monitoring Menu
*/
void monitoring(int role, User* user)
{
    clear();
    monitorPatientMenu(role, user); 
}

/*
 *Display the following Options:
 *- History
 *- Return Back
 *- Change Statis (for Doctor and director only)
*/
void monitorPatientMenu(int role, User* user)
{
    // Create a Container for Menu options
    WINDOW* menu = drawBox(23, 5 , 8, 25, 2);      

    //  receive arrow keys as input
    keypad(stdscr, TRUE);
    
    const int NUM_OF_OPTIONS = 3;
    const int NOT_NURSE_OPTION = 2;

    // enum options{ HIST, CHANGE_STATUS, }
    std::string opts[NUM_OF_OPTIONS] = { "    History      ", "  Return back    ", " Change Status   "  };    // List of options

    int c;              // Input charachter
    int selection = 0;  // Highlighted Option

    // Keep showing the menu untill
    // The user selects return back
    while( true ) { 
        while ( true )
        {
            // Display tilte
            monitoringTitle();
            user->printCurrentPatientInfo();
            refresh();    

/****************** Displaying the selection Boxes *****************/
            
            for ( int i = 0 ; i < NUM_OF_OPTIONS ; i++)  
            {
                if ( i == NOT_NURSE_OPTION && role == NURSE )
                    continue;

                mvwwritew(menu, 2 * i + 1, 3, "   ");
                if ( i == selection )                       // If highlited
                {
                    wattron(menu, A_REVERSE);               // Reverse Colors foregrounf to background Vice versa
                    mvwwritew(menu, 2 * i + 1, 3, " > ");
                }
                mvwwritew(menu, 2 * i + 1, 6, opts[i]);
                wattroff(menu, A_REVERSE );                 // Untoggle the Reverse
                move(0, 0);                                 // set the cursir away from text
            }

            // Read Input
            c = getch();                                    

            moveCursor(c, selection, ( role == NURSE )? NUM_OF_OPTIONS - 1 : NUM_OF_OPTIONS );                    // Move according to the input

            // 10 -> ENTER key
            if (c == 10)                                    
                break;
        }

/********************** and receiving input ************************/

        if( selection == 0 ) // History
        {
            printPatientHistory(role , user);
            refresh();
        }
        else if ( selection == 2 ) // Change Status
        {
            if ( !changeStatusMenu(role, user) )
                return;
            refresh();
        }
        else if ( selection == 1 )  // return Back
        {
           return;
        }
    }
 }

/*
* @return false if the User moved a patient to critical
*/
bool changeStatusMenu(int role, User* user)
{
    clear();
    // Create a Container for Menu options
    WINDOW* menu = drawBox(23, COLS/2 - 12, 8, 25, 2);      

    keypad(stdscr, TRUE);
    
    const int NUM_OF_OPTIONS = 4;
    std::string opts[NUM_OF_OPTIONS] = { "Under Treatment   ", "    Released      ", "  Passed Away     ",  "    Critical      "};    // List of options


    int c;              // Input charachter
    int selection = 0;  // Highlighted Option

    
    while ( true )
    {
        for ( int i = 0 ; i < NUM_OF_OPTIONS ; i++)  
        {
            mvwwritew(menu, 2 * i + 1, 3, "   ");
            if ( i == selection )                       // If highlited
            {
                wattron(menu, A_REVERSE);               // Reverse Colors foregrounf to background Vice versa
                mvwwritew(menu, 2 * i + 1, 3, " > ");
            }
            mvwwritew(menu, 2 * i + 1, 6, opts[i]);
            wattroff(menu, A_REVERSE );                 // Untoggle the Reverse
            move(0, 0);                                 // set the cursor away from text
        }

        
        c = getch();                                    // Read Input
        
        //// Move according to the input
        moveCursor(c, selection, NUM_OF_OPTIONS );                    

        if (c == 10)            // 10 -> ENTER key
            break;
    }

    switch ( selection )
    {
        case 3: // Change Status
            user->changeStatus(CRITICAL);
            if ( user->getService() == "Critical" )
                break;
            success();
            return false;
        case 0:
            user->changeStatus(UNDERTEAT);
            break;
        case 1:
            user->changeStatus(RELEASED);
            break;
        case 2:
            user->changeStatus(PASSEDAWAY);;
            break;
    }
    clear();
    return true;
}


/*
* Prints History of the current Patient
*/
void printPatientHistory(int role, User* user)
{
    clear();
    historyTitle( );
    refresh( );
    user->printCurrentPatientHistory();
    getch();
    clear();
}