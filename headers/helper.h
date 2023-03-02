// HASSIC Rayan Zakaria

#include <unistd.h>       // functions: sleep

// Library for I/O manipulation in terminal
#include <ncurses.h>     
#include <string>
#include <fstream>                      
#include <iostream>                // functions: cout, cin 
#include <nlohmann/json.hpp>       // nlohmann::json
#include <vector>   

#include "user.h"
#include "director.h"
#include "doctor.h"
#include "nurse.h"

using std::vector;



/*************************************/
/**  This file contains some helper **/
/** functions That help with Th UI  **/
/*************************************/


// Global Color Pallet
enum colors {MAIN = 1, CONTAINER = 2, PLACE_HOLDER = 3, IN = 4 , ACTIVE = 5, CAUTION = 6};

/*
    Check if the User exists
*/
bool check (string name, int id, string password, int role, User*& user)
{
    string roleName;
    if ( role == DIRECTOR )
        roleName = "Director";
    else if (role == DOCTOR )
        roleName = "Doctor";
    else if ( role == NURSE )
        roleName = "Nurse";
    

    std::fstream f("../Data/Users.json");
    json j = json::parse(f);
    static vector<User> users;
    users = j[roleName];

    // Intialize it as static so that the object won't 
    // be destructed at the end of the function and 
    // the pointer will still be valid
    static vector<User>::iterator itr;    

    for(  itr = users.begin() ; itr != users.end() ; itr++)
    {
        if (itr->getName() == name && itr->getID() == id && itr->getPasswd() == password)
        {
            user = &(*itr);         // returning the address of the object pointed to by the itrator  

            return true;
        }
    }
    user = nullptr;

    return false;
}

/*
    Returns an object of the specified role 
*/
User* newUser(int role, User* u)
{
    if ( role == DOCTOR )
    {
        return new Doctor(u->getName(), u->getID(), u->getPasswd(), u->getService());
    }
    else if (role == NURSE )
    {
        
        return new Nurse(u->getName(), u->getID(), u->getPasswd(), u->getService());
    }
    else if (role == DIRECTOR)
    {
        return new Director(u->getName(), u->getID(), u->getPasswd(), u->getService());
    }
    else 
        throw -1;
}

/*
    Function to draw Boxes Given their color and the top left corner coordinates
    @param y: y coordinate of the top left corner
    @param x: x coordinate of the top left corner
    @param height: the height of the box
    @param width: the width of the box
    @param color: The index of the color pair defined in void colors()
*/
WINDOW* drawBox(int y, int x, int height, int width, int color)
{
    WINDOW* Box = newwin( height, width, y, x);     // Create a Windoe object (from ncurses) 
    wbkgd(Box, COLOR_PAIR(color));                  // set the Background of the Box
    refresh();                                      // Update the Screen
    wrefresh(Box);                                  // display the box
    return Box;
}

/*
    Write on specific coordinates inside of a window (box) with style
    @param box: The Window we want to write inside
    @param y: The y coordinate of the position we want to print in
    @param x: The x coordinate of the position we want to print in
    @param text: The content we want to write
*/
void mvwwritew(WINDOW* box, int y, int x, std::string text)
{
    wattron(box, A_BOLD);
    wattron(box, COLOR_PAIR(PLACE_HOLDER));
    mvwprintw(box, y, x, text.c_str());
    wattroff(box, COLOR_PAIR(PLACE_HOLDER));
    wattroff(box, A_BOLD);
    wrefresh(box);
}

/*
  Overload for mvwritew
    @param color: specified color pallet for text
*/
void mvwwritew(WINDOW* box, int x, int y, std::string text, int color)
{
    wattron(box, COLOR_PAIR(color));
    wattron(box, A_BOLD);
    mvwprintw(box, y, x, text.c_str());
    wattroff(box, COLOR_PAIR(color));
    wattroff(box, A_BOLD);
    wrefresh(box);
}


/*
    Helper function to Read text Input
    @param bar: The Window representing the Input bar  
    @param in: Reference to variable that will store the input  
*/
void getInput(WINDOW* bar, std::string& in)
{
    in = "";
    keypad(stdscr, true);
    char s[30];                       // Initalize the output

    wmove(bar, 1, 1);               // Move to (1, 1) with repect to the window "bar"
    wbkgd(bar, COLOR_PAIR(ACTIVE));   // Change the background of the input bar
    echo();                         // Allow User to type in terminal and show his Input

    wattron(bar, COLOR_PAIR(ACTIVE)); // Toggle Color attribute for text   
    mvwgetstr(bar, 0, 1, s);         // Move the cursor to the specified position and read input
    wattroff(bar, COLOR_PAIR(ACTIVE));// Untoggle Color attribute

    in = s;                         // Assign the char * value to our string

    wbkgd(bar, COLOR_PAIR(IN));     // Change the background color back to Normal Input
    wrefresh(bar);                  // Print the window 
    noecho();                       // Hide User Input from terminal
}
/*
    Helper function to Read Number Input
    @param bar: The Window representing the Input bar  
    @param in: Reference to variable that will store the input  
*/
void getInput(WINDOW* bar, int& in)
{
    in = 0;
    keypad(stdscr, true);
    char s[30];                       // Initalize the output

    wmove(bar, 1, 1);               // Move to (1, 1) with repect to the window "bar"
    wbkgd(bar, COLOR_PAIR(ACTIVE));   // Change the background of the input bar
    echo();                         // Allow User to type in terminal and show his Input

    wattron(bar, COLOR_PAIR(ACTIVE)); // Toggle Color attribute for text   
    mvwgetstr(bar, 0, 1, s);         // Move the cursor to the specified position and read input
    wattroff(bar, COLOR_PAIR(ACTIVE));// Untoggle Color attribute

    try
    {
        in = std::stoi(s);                         // Assign the char * value to our string
    } catch(...)
    {
        in = 0;
    }
    wbkgd(bar, COLOR_PAIR(IN));     // Change the background color back to Normal Input
    wrefresh(bar);                  // Print the window 
    noecho();                       // Hide User Input from terminal
}

/*
    * 
    *@return true: if input is string
    *@return false: if inpit is int
*/
bool getInput_template(WINDOW* bar, string& in)
{
    getInput(bar, in);
    try
    {
        stoi(in);
    }
    catch(const std::exception& e)
    {
        return true;
    }
    return false;
}

/*
    Helper function to Read Password Input
    @param pswd: The Window representing the password bar  
    @param buff: Reference to variable that will store the input  
*/
void getPassword(WINDOW* pswd, std::string& buff)
{
    std::string stars="";           // Needed later for printing starts
    buff = "";
    move(32, COLS / 2 - 25);        

    int size = 0;     // size of the input buffer 
    int c = 0;        // Input charactIVEers (int on purpous)
    
    
    wbkgd(pswd, COLOR_PAIR(ACTIVE));   // Change Password Bar background active
    wrefresh(pswd);                 // Display the changes


    while ( true )       
    {

        if ( size > 20 )            // set max password charachters to 25
        {
            size = 20;
            buff.pop_back();
            continue;
        }
        c = getch();

        if ( c == KEY_ENTER || c == 10)   // 10 is enter ASCII code
            break;

        if (c == KEY_BACKSPACE )          // In case of deletion              
        {
            if ( buff.empty() )           // If output already empty do nothing            
                continue;

            size--;                       
            buff.pop_back();            

            wattron(stdscr, COLOR_PAIR(ACTIVE));
            printw("\b \b");                    // Move the cursor one strp back and replace the * with ' '
            stars.pop_back();
            wattroff(stdscr, COLOR_PAIR(ACTIVE));
        }
        else    // If normal input
        {
            buff.push_back(c);                  
            wattron(stdscr, COLOR_PAIR(ACTIVE));
            printw("*");            
            stars += "*";
            wattroff(stdscr, COLOR_PAIR(ACTIVE));
            size++; 
        }
    }

    mvwprintw(pswd, 0, 1, stars.c_str());   // move to non active password position and output the exact number of *
    wbkgd(pswd, COLOR_PAIR(IN));            // Change the backgrounf back to inactive
    wrefresh(pswd);                         // Display the changes
}

/*
    Print an error message saying that the name
    or Id of the patient are incorrect
    * @return true if the user wants to go back
    * @return false if the user wants to re enter a name or id
*/
bool incorrectERR()
{
    WINDOW* err = drawBox( 39, COLS / 2 - 20, 4, 40, CAUTION);    // Error conainer
    wattron(err, A_BLINK);
    wattron(err, A_BOLD);
    mvwwritew(err, 20 - 14, 1, "Name or ID Number incorrect!", CAUTION);
    wattroff(err, A_BLINK);
    mvwwritew(err, 20 - 14, 3, "Press BACKSPACE to go back", CAUTION);
    wattroff(err, A_BOLD);
    move(0, 0);

    // Oprtion to go back to mainMenu
    keypad(stdscr, true);
    int c = getch();
    if ( c == KEY_BACKSPACE )
    {
        keypad(stdscr, false);
        return true;
    }
    keypad(stdscr, false);
    return false;
}


/*
    Display error message for authentification failure
*/
void authErr()
{
    WINDOW* err = drawBox( 39, COLS / 2 - 20, 6, 40, CAUTION);    // Error conainer
    wattron(err, A_BLINK);
    wattron(err, A_BOLD);
    mvwwritew(err, 20 - 12, 1, "Authentification Error!", CAUTION);
    mvwwritew(err, 20 - 19, 2, "Check your Credentials then try again.", CAUTION);
    wattroff(err, A_BLINK);
    mvwwritew(err, 2, 4, "Press BACKSPACE (<-) to reselect Role", CAUTION);
    wattroff(err, A_BOLD);
    move(0, 0);
}
/*
    Display error message when inserting a Patient
*/
bool Err()
{
   WINDOW* err = drawBox( 39, COLS / 2 - 20, 3, 40, CAUTION);    // Error conainer
            wattron(err, A_BLINK);
            wattron(err, A_BOLD);
            mvwwritew(err, 20 - 13, 1, "Please Enter a valid Name", CAUTION);
            wattroff(err, A_BLINK);
            wattroff(err, A_BOLD);
            move(0, 0);
            
            timeout(3000);
            int c = getch();
            timeout(-3); 
            
            return c == KEY_BACKSPACE;
}

/*
    Display error message when inserting invalid ID
*/
void Err1()
{
   WINDOW* err = drawBox( 39, COLS / 2 - 20, 3, 40, CAUTION);    // Error conainer
            wattron(err, A_BLINK);
            wattron(err, A_BOLD);
            mvwwritew(err, 20 - 5, 1, "Invalid Id", CAUTION);
            wattroff(err, A_BLINK);
            wattroff(err, A_BOLD);
            move(0, 0);
            
            timeout(3000);
            getch();
            timeout(-3); 
}


/*
    Helper function for The Selection Menu
    This funcions moves the cursor to the next position
    according to the input and previous state
    @param c: reference to the input charachter
    @param selectioon: reference to the current Highlited option
    @param nOps: The Number of options
*/
void moveCursor(int& c, int& selection, int nOpts)
{
    switch (c)
        {
        case 'w':
            selection--;        // Move upward
            if (selection < 0)
                selection = 0;  // Stay static
            break;
        case KEY_UP:
            selection--;        // Move upward
            if (selection < 0)
                selection = 0;  // Stay static
            break;
        case 's':
            selection++;
            if (selection > nOpts - 1)
                selection = nOpts - 1;  // Stay static
            break;
        case KEY_DOWN:
            selection++;
            if (selection > nOpts - 1)
                selection = nOpts - 1;
            break;
        
        default:
            break;
        }
}


/*
    Display "Patient Moved Successefully!"
*/
void success()
{    
    clear();
    WINDOW* msg = drawBox( LINES/ 2, COLS / 2 - 20, 3, 40, CAUTION);    // msg for conainer
    wattron(msg, A_BLINK);
    wattron(msg, A_BOLD);
    mvwwritew(msg, 20 - 14, 1, "Patient moved Successfully!", PLACE_HOLDER);
    wattroff(msg, A_BLINK);
    wattroff(msg, A_BOLD);
    move(0, 0);
    timeout(3000);
    getch();
    timeout(-3); 
}


