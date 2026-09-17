#include "t3_game_library/t3_library.h"

// Define ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

int main() 
{
    
    // Clear the content of DataTable.txt
    clear_file();

    // Initialize seed for random function
    std::srand(std::time(0));  
    
    // Print ASCII Art Poker with color  
    printASCIIPoker();
    
    std::cout << "Welcome to Triple Star's Poker Game!" << std::endl;

    std::cout << std::endl;

    // Initialize the list of players
    std::vector<Player> players;

    bool continue_game = true;
    bool first_game = true;

    // Proceed with game rounds until the player wants to stop
    while (continue_game) {

        // Check if it's the first game
        if (first_game) {
            select_game_mode(players);
            first_game = false;
        } 
        
        else {
            // Ask the player if they want to choose the mode again
            if (ask_to_choose_mode_again()) {
                select_game_mode(players);
            } else {
                // If not, ask the player if they want to continue playing
                continue_game = ask_to_continue();
            }
        }
    }

    std::cout << YELLOW << "Thanks for playing! See you next time." << RESET << std::endl;

    return 0;
}


