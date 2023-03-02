// HASSIC Rayan Zakaria

#include <string>       // std::string
#include <unistd.h>     // sleep



/*********************************************/
/**      This file contains some helper     **/
/** functions That print the window titles  **/
/*********************************************/


// Function Prototypes

WINDOW* drawBox(int y, int x, int height, int width, int color);
void mvwwritew(WINDOW* box, int x, int y, std::string text, int color);



// Setting up custom color
#define COLOR_DARK_BLUE init_color(COLOR_CYAN, 16, 134, 222)

// Setup the Global color pallet
void colors()
{
    init_pair(MAIN, COLOR_BLUE, COLOR_DARK_BLUE);              // The Main Color pair
    init_pair(CONTAINER, COLOR_DARK_BLUE, COLOR_DARK_BLUE);    // Contaners
    init_pair(PLACE_HOLDER, COLOR_BLUE, COLOR_DARK_BLUE);      // Place holder    
    init_pair(IN, COLOR_WHITE, COLOR_CYAN);                    // Input Box
    init_pair(ACTIVE, COLOR_DARK_BLUE, COLOR_MAGENTA);         // Active Input
    init_pair(CAUTION, COLOR_BLACK, COLOR_RED);                // Caution
}


/**********************************************************************************************\
|***************************              SCREEN TITLES             ***************************|
\**********************************************************************************************/

/*
    Print the Title
*/
void intensiveCareUnit()
{
    attron(A_BOLD);
    attron(COLOR_PAIR(MAIN));
        // COPY PASTED FROM THE OUTPUT OF THE SCRIPT
    mvprintw(1, COLS / 2 - 45, "$$$$$$\\            $$\\                                   $$\\                      "); 
    mvprintw(2, COLS / 2 - 45, "\\_$$  _|           $$ |                                  \\__|                     "); 
    mvprintw(3, COLS / 2 - 45, "  $$ |  $$$$$$$\\ $$$$$$\\    $$$$$$\\  $$$$$$$\\   $$$$$$$\\ $$\\ $$\\    $$\\  $$$$$$\\  "); 
    mvprintw(4, COLS / 2 - 45, "  $$ |  $$  __$$\\\\_$$  _|  $$  __$$\\ $$  __$$\\ $$  _____|$$ |\\$$\\  $$  |$$  __$$\\ "); 
    mvprintw(5, COLS / 2 - 45, "  $$ |  $$ |  $$ | $$ |    $$$$$$$$ |$$ |  $$ |\\$$$$$$\\  $$ | \\$$\\$$  / $$$$$$$$ |"); 
    mvprintw(6, COLS / 2 - 45, "  $$ |  $$ |  $$ | $$ |$$\\ $$   ____|$$ |  $$ | \\____$$\\ $$ |  \\$$$  /  $$   ____|"); 
    mvprintw(7, COLS / 2 - 45, "$$$$$$\\ $$ |  $$ | \\$$$$  |\\$$$$$$$\\ $$ |  $$ |$$$$$$$  |$$ |   \\$  /   \\$$$$$$$\\ "); 
    mvprintw(8, COLS / 2 - 45, "\\______|\\__|  \\__|  \\____/  \\_______|\\__|  \\__|\\_______/ \\__|    \\_/     \\_______|"); 
   
    mvprintw(10, COLS / 2 - 45 + 1, " $$$$$$\\                                      $$\\   $$\\           $$\\   $$\\     "); 
    mvprintw(11, COLS / 2 - 45 + 1, "$$  __$$\\                                     $$ |  $$ |          \\__|  $$ |    "); 
    mvprintw(12, COLS / 2 - 45 + 1, "$$ /  \\__| $$$$$$\\   $$$$$$\\   $$$$$$\\        $$ |  $$ |$$$$$$$\\  $$\\ $$$$$$\\   "); 
    mvprintw(13, COLS / 2 - 45 + 1, "$$ |       \\____$$\\ $$  __$$\\ $$  __$$\\       $$ |  $$ |$$  __$$\\ $$ |\\_$$  _|  "); 
    mvprintw(14, COLS / 2 - 45 + 1, "$$ |       $$$$$$$ |$$ |  \\__|$$$$$$$$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |    "); 
    mvprintw(15, COLS / 2 - 45 + 1, "$$ |  $$\\ $$  __$$ |$$ |      $$   ____|      $$ |  $$ |$$ |  $$ |$$ |  $$ |$$\\ "); 
    mvprintw(16, COLS / 2 - 45 + 1, "\\$$$$$$  |\\$$$$$$$ |$$ |      \\$$$$$$$\\       \\$$$$$$  |$$ |  $$ |$$ |  \\$$$$  |"); 
    mvprintw(17, COLS / 2 - 45 + 1, " \\______/  \\_______|\\__|       \\_______|       \\______/ \\__|  \\__|\\__|   \\____/ "); 
    mvprintw(18, COLS / 2 - 45 + 1, "                                                                                "); 
    mvprintw(19, COLS / 2 - 45 + 1, "                                                                                "); 
    mvprintw(20, COLS / 2 - 45 + 1, "                                                                               "); 
    attroff(A_BOLD);
    attroff(COLOR_PAIR(MAIN));
}


// Function to display the loading progess bar with a little delay to feel realistic
void loading()
{
    attron(COLOR_PAIR(MAIN));      // Toggle Changing The color
    attron(A_BOLD);                // Toggle Font to bold
    sleep(1);                      // Set 1 second delay
    // Print loading... in the lower 10% and the middle of the screen 
    mvprintw( LINES - LINES * 0.1 , COLS / 2 - 5, "LOADING...", COLS);  
    move(0, 0);                     // set cursor postion away from text
    refresh();
    sleep(1);                       
    attroff(A_BOLD);               // Untoggle Changing The color
    attroff(COLOR_PAIR(MAIN));        // Untoggle Font to bold 
}   

// Display Select Menu Title
void selectRole()
{
        attron(A_BOLD);
    mvprintw(1, COLS / 2 - 49, " $$$$$$\\            $$\\                       $$\\           $$\\     $$\\                                   "); 
    mvprintw(2, COLS / 2 - 49, "$$  __$$\\           $$ |                      $$ |          \\$$\\   $$  |                                  "); 
    mvprintw(3, COLS / 2 - 49, "$$ /  \\__| $$$$$$\\  $$ | $$$$$$\\   $$$$$$$\\ $$$$$$\\          \\$$\\ $$  /$$$$$$\\  $$\\   $$\\  $$$$$$\\        "); 
    mvprintw(4, COLS / 2 - 49, "\\$$$$$$\\  $$  __$$\\ $$ |$$  __$$\\ $$  _____|\\_$$  _|          \\$$$$  /$$  __$$\\ $$ |  $$ |$$  __$$\\       "); 
    mvprintw(5, COLS / 2 - 49, " \\____$$\\ $$$$$$$$ |$$ |$$$$$$$$ |$$ /        $$ |             \\$$  / $$ /  $$ |$$ |  $$ |$$ |  \\__|      "); 
    mvprintw(6, COLS / 2 - 49, "$$\\   $$ |$$   ____|$$ |$$   ____|$$ |        $$ |$$\\           $$ |  $$ |  $$ |$$ |  $$ |$$ |            "); 
    mvprintw(7, COLS / 2 - 49, "\\$$$$$$  |\\$$$$$$$\\ $$ |\\$$$$$$$\\ \\$$$$$$$\\   \\$$$$  |          $$ |  \\$$$$$$  |\\$$$$$$  |$$ |            "); 
    mvprintw(8, COLS / 2 - 49, " \\______/  \\_______|\\__| \\_______| \\_______|   \\____/           \\__|   \\______/  \\______/ \\__|            "); 
    mvprintw(9, COLS / 2 - 49, "                                                                                                          "); 
    mvprintw(10, COLS / 2 -49, "                                                                                                          "); 
    mvprintw(11, COLS / 2 -49, "                                                                                                         "); 

    mvprintw(11, COLS / 2 - 45 + 25, "$$$$$$$\\            $$\\               "); 
    mvprintw(12, COLS / 2 - 45 + 25, "$$  __$$\\           $$ |              "); 
    mvprintw(13, COLS / 2 - 45 + 25, "$$ |  $$ | $$$$$$\\  $$ | $$$$$$\\  $$\\ "); 
    mvprintw(14, COLS / 2 - 45 + 25, "$$$$$$$  |$$  __$$\\ $$ |$$  __$$\\ \\__|"); 
    mvprintw(15, COLS / 2 - 45 + 25, "$$  __$$< $$ /  $$ |$$ |$$$$$$$$ |    "); 
    mvprintw(16, COLS / 2 - 45 + 25, "$$ |  $$ |$$ |  $$ |$$ |$$   ____|$$\\ "); 
    mvprintw(17, COLS / 2 - 45 + 25, "$$ |  $$ |\\$$$$$$  |$$ |\\$$$$$$$\\ \\__|"); 
    mvprintw(18, COLS / 2 - 45 + 25, "\\__|  \\__| \\______/ \\__| \\_______|    "); 
    mvprintw(19, COLS / 2 - 45 + 25, "                                      "); 
    mvprintw(20, COLS / 2 - 45 + 25, "                                      "); 
    mvprintw(21, COLS / 2 - 45 + 25, "                                     "); 
    attroff(A_BOLD);

}

// Display Login title
void login()
{
    attron(A_BOLD);
    mvprintw(1,  COLS / 2 - 25, "$$\\                               $$$$$$\\          "); 
    mvprintw(2,  COLS / 2 - 25, "$$ |                              \\_$$  _|         "); 
    mvprintw(3,  COLS / 2 - 25, "$$ |     $$$$$$\\   $$$$$$\\          $$ | $$$$$$$\\  "); 
    mvprintw(4,  COLS / 2 - 25, "$$ |    $$  __$$\\ $$  __$$\\         $$ | $$  __$$\\ "); 
    mvprintw(5,  COLS / 2 - 25, "$$ |    $$ /  $$ |$$ /  $$ |        $$ | $$ |  $$ |"); 
    mvprintw(6,  COLS / 2 - 25, "$$ |    $$ |  $$ |$$ |  $$ |        $$ | $$ |  $$ |"); 
    mvprintw(7,  COLS / 2 - 25, "$$$$$$$$\\$$$$$$  |\\$$$$$$$ |      $$$$$$\\$$ |  $$ |"); 
    mvprintw(8,  COLS / 2 - 25, "\\________\\______/  \\____$$ |      \\______\\__|  \\__|"); 
    mvprintw(9,  COLS / 2 - 25, "                  $$\\   $$ |                       "); 
    mvprintw(10, COLS / 2 - 25, "                  \\$$$$$$  |                       "); 
    mvprintw(11, COLS / 2 - 25, "                   \\______/                       "); 

}


// Display choose Your
void chooseYourService()
{
    clear();
        mvprintw(1, COLS / 2 - 40, " $$$$$$\\  $$\\                                                               "); 
        mvprintw(2, COLS / 2 - 40, "$$  __$$\\ $$ |                                                              "); 
        mvprintw(3, COLS / 2 - 40, "$$ /  \\__|$$$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$$\\  $$$$$$\\         $$$$$$\\  "); 
        mvprintw(4, COLS / 2 - 40, "$$ |      $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\        \\____$$\\ "); 
        mvprintw(5, COLS / 2 - 40, "$$ |      $$ |  $$ |$$ /  $$ |$$ /  $$ |\\$$$$$$\\  $$$$$$$$ |       $$$$$$$ |"); 
        mvprintw(6, COLS / 2 - 40, "$$ |  $$\\ $$ |  $$ |$$ |  $$ |$$ |  $$ | \\____$$\\ $$   ____|      $$  __$$ |"); 
        mvprintw(7, COLS / 2 - 40, "\\$$$$$$  |$$ |  $$ |\\$$$$$$  |\\$$$$$$  |$$$$$$$  |\\$$$$$$$\\       \\$$$$$$$ |"); 
        mvprintw(8, COLS / 2 - 40, " \\______/ \\__|  \\__| \\______/  \\______/ \\_______/  \\_______|       \\_______|"); 
        mvprintw(9, COLS / 2 - 40, "                                                                            "); 
    
        mvprintw(10, COLS / 2 - 31, " $$$$$$\\                               $$\\                     "); 
        mvprintw(11, COLS / 2 - 31, "$$  __$$\\                              \\__|                    "); 
        mvprintw(12, COLS / 2 - 31, "$$ /  \\__| $$$$$$\\   $$$$$$\\$$\\    $$\\ $$\\  $$$$$$$\\  $$$$$$\\  "); 
        mvprintw(13, COLS / 2 - 31, "\\$$$$$$\\  $$  __$$\\ $$  __$$\\$$\\  $$  |$$ |$$  _____|$$  __$$\\ "); 
        mvprintw(14, COLS / 2 - 31, " \\____$$\\ $$$$$$$$ |$$ |  \\__\\$$\\$$  / $$ |$$ /      $$$$$$$$ |"); 
        mvprintw(15, COLS / 2 - 31, "$$\\   $$ |$$   ____|$$ |      \\$$$  /  $$ |$$ |      $$   ____|"); 
        mvprintw(16, COLS / 2 - 31, "\\$$$$$$  |\\$$$$$$$\\ $$ |       \\$  /   $$ |\\$$$$$$$\\ \\$$$$$$$\\ "); 
        mvprintw(17, COLS / 2 - 31, " \\______/  \\_______|\\__|        \\_/    \\__| \\_______| \\_______|"); 
        mvprintw(18, COLS / 2 - 31, "                                                               "); 
        mvprintw(19, COLS / 2 - 31, "                                                               "); 
        mvprintw(20, COLS / 2 - 31, "                                                              "); 
}

// Display Main Menu Title
void mainTitle()
{
    mvprintw(1, COLS / 2 - 42, "$$\\      $$\\           $$\\                 $$\\      $$\\                               "); 
    mvprintw(2, COLS / 2 - 42, "$$$\\    $$$ |          \\__|                $$$\\    $$$ |                              "); 
    mvprintw(3, COLS / 2 - 42, "$$$$\\  $$$$ | $$$$$$\\  $$\\ $$$$$$$\\        $$$$\\  $$$$ | $$$$$$\\  $$$$$$$\\  $$\\   $$\\ "); 
    mvprintw(4, COLS / 2 - 42, "$$\\$$\\$$ $$ | \\____$$\\ $$ |$$  __$$\\       $$\\$$\\$$ $$ |$$  __$$\\ $$  __$$\\ $$ |  $$ |"); 
    mvprintw(5, COLS / 2 - 42, "$$ \\$$$  $$ | $$$$$$$ |$$ |$$ |  $$ |      $$ \\$$$  $$ |$$$$$$$$ |$$ |  $$ |$$ |  $$ |"); 
    mvprintw(6, COLS / 2 - 42, "$$ |\\$  /$$ |$$  __$$ |$$ |$$ |  $$ |      $$ |\\$  /$$ |$$   ____|$$ |  $$ |$$ |  $$ |"); 
    mvprintw(7, COLS / 2 - 42, "$$ | \\_/ $$ |\\$$$$$$$ |$$ |$$ |  $$ |      $$ | \\_/ $$ |\\$$$$$$$\\ $$ |  $$ |\\$$$$$$  |"); 
    mvprintw(8, COLS / 2 - 42, "\\__|     \\__| \\_______|\\__|\\__|  \\__|      \\__|     \\__| \\_______|\\__|  \\__| \\______/ "); 
    mvprintw(9, COLS / 2 - 42, "                                                                                      "); 
    mvprintw(10, COLS / 2 - 45, "                                                                                      "); 
    mvprintw(11, COLS / 2 - 45, "                                                                                     "); 
}

void monitoringTitle()
{
    clear();
    wattron( stdscr, A_BOLD);
    mvprintw(1, COLS / 2 - 45, "$$\\      $$\\                     $$\\  $$\\                        $$\\                     "); 
    mvprintw(2, COLS / 2 - 45, "$$$\\    $$$ |                    \\__| $$ |                       \\__|                    "); 
    mvprintw(3, COLS / 2 - 45, "$$$$\\  $$$$ | $$$$$$\\  $$$$$$$\\  $$\\$$$$$$\\   $$$$$$\\   $$$$$$\\  $$\\ $$$$$$$\\   $$$$$$\\  "); 
    mvprintw(4, COLS / 2 - 45, "$$\\$$\\$$ $$ |$$  __$$\\ $$  __$$\\ $$ \\_$$  _| $$  __$$\\ $$  __$$\\ $$ |$$  __$$\\ $$  __$$\\ "); 
    mvprintw(5, COLS / 2 - 45, "$$ \\$$$  $$ |$$ /  $$ |$$ |  $$ |$$ | $$ |   $$ /  $$ |$$ |  \\__|$$ |$$ |  $$ |$$ /  $$ |"); 
    mvprintw(6, COLS / 2 - 45, "$$ |\\$  /$$ |$$ |  $$ |$$ |  $$ |$$ | $$ |$$\\$$ |  $$ |$$ |      $$ |$$ |  $$ |$$ |  $$ |"); 
    mvprintw(7, COLS / 2 - 45, "$$ | \\_/ $$ |\\$$$$$$  |$$ |  $$ |$$ | \\$$$$  \\$$$$$$  |$$ |      $$ |$$ |  $$ |\\$$$$$$$ |"); 
    mvprintw(8, COLS / 2 - 45, "\\__|     \\__| \\______/ \\__|  \\__|\\__|  \\____/ \\______/ \\__|      \\__|\\__|  \\__| \\____$$ |"); 
    mvprintw(9, COLS / 2 - 45, "                                                                               $$\\   $$ |"); 
    mvprintw(10, COLS / 2 - 45, "                                                                               \\$$$$$$  |"); 
    mvprintw(11, COLS / 2 - 45, "                                                                                \\______/"); 
    wattroff( stdscr, A_BOLD);

}

/*
    Prints the `History` windw title
*/
void historyTitle( )
{
    wattron( stdscr, A_BOLD);

    mvprintw(1, COLS / 2 - 25, "$$\\   $$\\ $$\\            $$\\                                  "); 
    mvprintw(2, COLS / 2 - 25, "$$ |  $$ |\\__|           $$ |                                 "); 
    mvprintw(3, COLS / 2 - 25, "$$ |  $$ |$$\\  $$$$$$$\\$$$$$$\\   $$$$$$\\   $$$$$$\\  $$\\   $$\\ "); 
    mvprintw(4, COLS / 2 - 25, "$$$$$$$$ |$$ |$$  _____\\_$$  _| $$  __$$\\ $$  __$$\\ $$ |  $$ |"); 
    mvprintw(5, COLS / 2 - 25, "$$  __$$ |$$ |\\$$$$$$\\   $$ |   $$ /  $$ |$$ |  \\__|$$ |  $$ |"); 
    mvprintw(6, COLS / 2 - 25, "$$ |  $$ |$$ | \\____$$\\  $$ |$$\\$$ |  $$ |$$ |      $$ |  $$ |"); 
    mvprintw(7, COLS / 2 - 25, "$$ |  $$ |$$ |$$$$$$$  | \\$$$$  \\$$$$$$  |$$ |      \\$$$$$$$ |"); 
    mvprintw(8, COLS / 2 - 25, "\\__|  \\__|\\__|\\_______/   \\____/ \\______/ \\__|       \\____$$ |"); 
    mvprintw(9, COLS / 2 - 25, "                                                    $$\\   $$ |"); 
    mvprintw(10, COLS / 2 - 25, "                                                    \\$$$$$$  |"); 
    mvprintw(11, COLS / 2 - 25, "                                                     \\______/"); 



    wattroff( stdscr, A_BOLD);
}

/**********************************************************************************************/
