#pragma once
#include <limits>
#include <iostream>
#include <iomanip>
#include <vector>
#include "game_database.h"
#include <windows.h>
//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
// Description: This library includes functions related to the game interface such as input, output, and display of information.

// Usage instructions: 
    // To use the functions in this library, you need to include this library in your file by adding the following line:
    //#include "poker_desk.h"

// This library includes the following functions:
//..................................................................................................................................
    // Input and information checking functions

        // Function to input the number of players
        int input_number_of_players();

        // Ask the user to input Yes or No 
        bool check_Yes_No_Input();

        // Ask the player if they want to choose the game mode again
        bool ask_to_choose_mode_again();

        // Function to ask the player if they want to continue playing
        bool ask_to_continue();

        // Function to select the difficulty level of the game
        int selectGameLevel();
//..................................................................................................................................
    // Information output functions

        // Function to print the player's cards
        void print_player_cards(std::vector<std::string> player_cards);

        // Function to print all players' cards
        void print_all_player_cards(const std::vector<std::vector<std::string>>& player_cards, int number_player);

        // Function to print player information
        void print_player_info(const Player& player);

        // Function to print PvE mode information
        void print_pve_info(const Player& player, bool check_bot, int level_bot);

        // Function to print the leaderboard (PvE) ranking players based on win rate
        void leaderboard_pve(const std::vector<Player>& players, int level_bot);

        // Function to print the final leaderboard (PvE) ranking players based on win rate
        void final_leaderboard_pve(const std::vector<Player>& players, int level_bot);

        // Function to print the leaderboard ranking players
        void leaderboard(const std::vector<Player>& players);
        
        // Function to print the final leaderboard ranking players
        void final_leaderboard(const std::vector<Player>& players);

        // Function to print the PvP mode guide
        void printPvPGuide();
        
        // Function to print the PvE mode guide
        void printPvEGuide();

        // Print ASCII Art Poker
        void printASCIIPoker();

        // Print ASCII Art
        void printASCIIArt();

        // Print the Single Card Duel mode guide
        void printSingleCardDuelGuide();

        // Print the Three Card Poker mode guide
        void printThreeCardPokerGuide();

        // Function to set text color
        void setTextColor(int color);


//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================


// Function to input the number of players
int input_number_of_players() 
{
    int number_player;
    setTextColor(3); // Set color to Green
    std::cout << "Enter number of players(between 2 and 10): ";
    setTextColor(0); // Reset color
    while (!(std::cin >> number_player) || number_player < 2 || number_player >= 10) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        setTextColor(2); // Set color to Red
        std::cout << "Enter again: ";
        setTextColor(0); // Reset color
    }
    setTextColor(3); // Set color to Green
    printASCIIArt();
    setTextColor(0); // Reset color
    return number_player;
}

// Function to print the player's cards
void print_player_cards(std::vector<std::string> player_cards)
{
    for (const std::string& card : player_cards)
    {
        setTextColor(4); // Set color to Blue
        std::cout << card << std::endl; // Print each card on a new line
        setTextColor(0); // Reset color
    }
    std::cout << std::endl; 
    // New line after printing the player's cards
}

// Function to print all players' cards
void print_all_player_cards(const std::vector<std::vector<std::string>>& player_cards, int number_player) 
{
    // Print each player's cards on a new line
    for (int i = 0; i < number_player; i++) {
        setTextColor(5); // Set color to Magenta
        std::cout << "Cards of player " << i + 1 << ":" << std::endl;
        setTextColor(0); // Reset color

        for (const std::string& card : player_cards[i]) {
            setTextColor(4); // Set color to Blue
            std::cout << card << std::endl; // Print each card on a new line
            setTextColor(0); // Reset color
        }

        std::cout << std::endl; // New line after printing the player's cards
    }
}

// Function to print player information
void print_player_info(const Player& player) {
    // Print basic player information
    setTextColor(6); // Set color to Cyan
    std::cout << "Player " << player.number << ":\n" << "Username: " << player.username << "\n";
    std::cout << "Total games played: " << player.total_games << "\n";
    std::cout << "Total wins: " << player.wins << "\n";
    
    // Print win rate, rounded to 2 decimal places
    std::cout << "Win rate: " << std::fixed << std::setprecision(2) << player.win_rate << "%\n";
    
    // Print winning situations
    std::cout << "Winning situations:\n";
    if (player.win_situations.empty()) {
        std::cout << "No winning situations recorded.\n";
    } else {
        for (const auto& situation : player.win_situations) {
            std::cout << "- " << situation.first << ": " << situation.second << " wins\n";
        }
    }
    setTextColor(0); // Reset color
    std::cout << std::endl;
}


// Function to print PvE mode information
void print_pve_info(const Player& player, bool check_bot, int level_bot) {
    if (check_bot) 
    {
    // Print basic player information
    setTextColor(5); // Set color to Magenta
    std::cout << "Bot("<< (level_bot == 1 ? "Normal" : level_bot == 2 ? "Challenge" : "Legendary") <<" version)\n";
    std::cout << "Total games played: " << player.total_games << "\n";
    std::cout << "Total wins: " << player.wins << "\n";
    
    // Print win rate, rounded to 2 decimal places
    std::cout << "Win rate: " << std::fixed << std::setprecision(2) << player.win_rate << "%\n";
    
    // Print winning situations
    std::cout << "Winning situations:\n";
    if (player.win_situations.empty()) {
        std::cout << "No winning situations recorded.\n";
    } else {
        for (const auto& situation : player.win_situations) {
            std::cout << "- " << situation.first << ": " << situation.second << " wins\n";
        }
    }
    setTextColor(0); // Reset color
    std::cout << std::endl;
    }
    else
    {
        // Print basic player information
        setTextColor(6); // Set color to Cyan
        std::cout << "Player:\n";
        std::cout << "Total games played: " << player.total_games << "\n";
        std::cout << "Total wins: " << player.wins << "\n";
        
        // Print win rate, rounded to 2 decimal places
        std::cout << "Win rate: " << std::fixed << std::setprecision(2) << player.win_rate << "%\n";
        
        // Print winning situations
        std::cout << "Winning situations:\n";
        if (player.win_situations.empty()) {
            std::cout << "No winning situations recorded.\n";
        } else {
            for (const auto& situation : player.win_situations) {
                std::cout << "- " << situation.first << ": " << situation.second << " wins\n";
            }
        }
        setTextColor(0); // Reset color
        std::cout << std::endl;
    }

}

int selectGameLevel() {
    int level;
    bool isValid = false;

    // Loop until the user enters a valid level
    while (!isValid) {
        setTextColor(3); // Set color to Green
        std::cout << "Select the Bot difficulty level:\n";
        std::cout << "1. Lv1 - Normal\n";
        std::cout << "2. Lv2 - Challenge\n";
        std::cout << "3. Lv3 - Legendary\n";
        std::cout << "Enter your choice (1-3): ";
        setTextColor(0); // Reset color

        // Check if the user entered the wrong data type
        if (std::cin >> level) {
            // Validate the user's input
            if (level >= 1 && level <= 3) {
                isValid = true; // Exit the loop if valid input is provided
                setTextColor(3); // Set color to Green
                switch (level) {
                    case 1:
                        std::cout << "You have selected Lv1 - Normal.\n";
                        break;
                    case 2:
                        std::cout << "You have selected Lv2 - Challenge.\n";
                        break;
                    case 3:
                        std::cout << "You have selected Lv3 - Legendary.\n";
                        break;
                }
                setTextColor(0); // Reset color
            } else {
                // Error message when the user selects the wrong level
                setTextColor(2); // Set color to Red
                std::cout << "Invalid choice! Please select a number between 1 and 3.\n\n";
                setTextColor(0); // Reset color
            }
        } else {
            // Handle when the user enters a non-numeric value
            setTextColor(2); // Set color to Red
            std::cout << "Invalid input! Please enter a valid number between 1 and 3.\n";
            setTextColor(0); // Reset color
            std::cin.clear();  // Clear the error state of cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Remove remaining characters in the input buffer
        }
    }
    printASCIIArt();
    return level;
}

// Ask the user to input Yes or No 
bool check_Yes_No_Input() {
    char input;
    while (true) {
        setTextColor(3); // Set color to Green
        std::cout << "Please enter Y (Yes) or N (No): ";
        setTextColor(0); // Reset color
        std::cin >> input;

        if (input == 'y' || input == 'Y') {
            return true; // User entered Y
        } else if (input == 'n'|| input == 'N') {
            return false; // User entered N
        } else {
            setTextColor(2); // Set color to Red
            std::cout << "Invalid input. "; // Error message for invalid input
            setTextColor(0); // Reset color
        }
    }
}


// Function to print the leaderboard (PvE) ranking players based on win rate
void leaderboard_pve(const std::vector<Player>& players, int level_bot) 
{
    // Create a copy of the player list to sort
    std::vector<Player> sorted_players = players;

    // Sort by win rate in descending order
    sort(sorted_players.begin(), sorted_players.end(), [](const Player& a, const Player& b) {
        return a.win_rate > b.win_rate;
    });

    // Print the leaderboard
    setTextColor(3); // Set color to Green
    std::cout << "\n================= LEADERBOARD PVE ("<< (level_bot == 1 ? "Normal" : level_bot == 2 ? "Challenge" : "Legendary") <<" version) ==================\n";
    std::cout << std::left << std::setw(10) << "Rank" 
         << std::setw(15) << "Participant" 
         << std::setw(15) << "Games Played" 
         << std::setw(10) << "Wins" 
         << std::setw(12) << "Win Rate (%)" << std::endl;

    for (size_t i = 0; i < sorted_players.size(); ++i) {
        const Player& player = sorted_players[i];
        setTextColor(4); // Set color to Blue
        std::cout << std::left << std::setw(10) << (i + 1) 
             << std::setw(15) << (player.number == 2 ? "Bot" : "Player")
             << std::setw(15) << player.total_games 
             << std::setw(10) << player.wins 
             << std::setw(12) << std::fixed << std::setprecision(2) << player.win_rate << std::endl;
        setTextColor(0); // Reset color
    }
    setTextColor(3); // Set color to Green
    std::cout << "================================================================\n";
    setTextColor(0); // Reset color
}

// Function to print the final leaderboard (PvE) ranking players based on win rate
void final_leaderboard_pve(const std::vector<Player>& players, int level_bot) 
{
    // Create a copy of the player list to sort
    std::vector<Player> sorted_players = players;

    // Sort by win rate in descending order
    sort(sorted_players.begin(), sorted_players.end(), [](const Player& a, const Player& b) {
        return a.win_rate > b.win_rate;
    });

    // Print the leaderboard
    setTextColor(3); // Set color to Green
    std::cout << "\n============== FINAL LEADERBOARD ("<< (level_bot == 1 ? "Normal" : level_bot == 2 ? "Challenge" : "Legendary") <<" version) ===============\n";
    std::cout << std::left << std::setw(10) << "Rank" 
         << std::setw(15) << "Participant" 
         << std::setw(15) << "Games Played" 
         << std::setw(10) << "Wins" 
         << std::setw(12) << "Win Rate (%)" << std::endl;

    for (size_t i = 0; i < sorted_players.size(); ++i) {
        const Player& player = sorted_players[i];
        setTextColor(4); // Set color to Blue
        std::cout << std::left << std::setw(10) << (i + 1) 
             << std::setw(15) << (player.number == 2 ? "Bot" : "Player")
             << std::setw(15) << player.total_games 
             << std::setw(10) << player.wins 
             << std::setw(12) << std::fixed << std::setprecision(2) << player.win_rate << std::endl;
        setTextColor(0); // Reset color
    }
    setTextColor(3); // Set color to Green
    std::cout << "=======================================================================\n";
    setTextColor(0); // Reset color
}


// Function to print the leaderboard ranking players based on win rate
void leaderboard(const std::vector<Player>& players) 
{
    // Create a copy of the player list to sort
    std::vector<Player> sorted_players = players;

    // Sort by win rate in descending order
    sort(sorted_players.begin(), sorted_players.end(), [](const Player& a, const Player& b) {
        return a.win_rate > b.win_rate;
    });

    // Print the leaderboard
    setTextColor(3); // Set color to Green
    std::cout << "\n=================================== LEADERBOARD ======================================\n";
    std::cout << std::left 
              << std::setw(10) << "Rank" 
              << std::setw(15) << "Player No." 
              << std::setw(20) << "Username" 
              << std::setw(15) << "Games Played" 
              << std::setw(10) << "Wins" 
              << std::setw(12) << "Win Rate (%)" << std::endl;

    for (size_t i = 0; i < sorted_players.size(); ++i) {
        const Player& player = sorted_players[i];
        setTextColor(4); // Set color to Blue
        std::cout << std::left 
                  << std::setw(10) << (i + 1) 
                  << std::setw(15) << player.number 
                  << std::setw(20) << player.username 
                  << std::setw(15) << player.total_games 
                  << std::setw(10) << player.wins 
                  << std::setw(12) << std::fixed << std::setprecision(2) << player.win_rate << std::endl;
        setTextColor(0); // Reset color
    }
    setTextColor(3); // Set color to Green
    std::cout << "=======================================================================================\n";
    setTextColor(0); // Reset color
}

// Function to print the final leaderboard ranking players based on win rate
void final_leaderboard(const std::vector<Player>& players) 
{
    // Create a copy of the player list to sort
    std::vector<Player> sorted_players = players;

    // Sort by win rate in descending order
    sort(sorted_players.begin(), sorted_players.end(), [](const Player& a, const Player& b) {
        return a.win_rate > b.win_rate;
    });

    // Print the leaderboard
    setTextColor(3); // Set color to Green
    std::cout << "\n================================= FINAL LEADERBOARD ===================================\n";
    std::cout << std::left 
              << std::setw(10) << "Rank" 
              << std::setw(15) << "Player No." 
              << std::setw(20) << "Username" 
              << std::setw(15) << "Games Played" 
              << std::setw(10) << "Wins" 
              << std::setw(12) << "Win Rate (%)" << std::endl;

    for (size_t i = 0; i < sorted_players.size(); ++i) {
        const Player& player = sorted_players[i];
        setTextColor(4); // Set color to Blue
        std::cout << std::left 
                  << std::setw(10) << (i + 1) 
                  << std::setw(15) << player.number 
                  << std::setw(20) << player.username 
                  << std::setw(15) << player.total_games 
                  << std::setw(10) << player.wins 
                  << std::setw(12) << std::fixed << std::setprecision(2) << player.win_rate << std::endl;
        setTextColor(0); // Reset color
    }
    setTextColor(3); // Set color to Green
    std::cout << "========================================================================================\n";
}

// Ask the player if they want to choose the game mode again
bool ask_to_choose_mode_again() {
    std::string user_input;
    setTextColor(3); // Set color to Green
    std::cout << "Do you want to choose the game mode again (yes/no): ";
    setTextColor(0); // Reset color
    std::cin >> user_input;

    // Check if the player entered "yes" or "no"
    if (user_input == "yes" || user_input == "y" || user_input == "Y") {
        return true;  // Player wants to choose the mode again
    } else if (user_input == "no" || user_input == "n" || user_input == "N") {
        return false;  // Player does not want to choose the mode again
    } else {
        setTextColor(2); // Set color to Red
        std::cout << "Invalid input! Please enter 'yes' or 'no'.\n";
        setTextColor(0); // Reset color
        return ask_to_choose_mode_again();  // If input is invalid, ask again
    }
}


// Function to ask the player if they want to continue playing
bool ask_to_continue() {
    char choice;
    setTextColor(3); // Set color to Green
    std::cout << "Do you want to continue playing? (Y/N): ";
    setTextColor(0); // Reset color
    std::cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

// Function to print the PvP mode guide
void printPvPGuide() {
    setTextColor(6); // Set color to Cyan
    std::cout << "=== PvP (Player vs. Player) Poker Mode ===\n\n";

    std::cout << "Description:\n";
    std::cout << "  + The PvP mode allows two players to compete directly against each other. Each player will take turns during their play.\n\n";

    std::cout << "Instructions:\n";
    std::cout << "  + When entering PvP mode, input the number of players participating (from 2 to 10).\n";
    std::cout << "  + Enter the usernames of the players.\n";
    std::cout << "  + The computer will randomly deal cards to each player.\n";
    std::cout << "  + The computer will automatically evaluate and determine the strongest hand for each player and display it on the screen.\n";
    std::cout << "  + The computer will automatically determine the winner.\n";
    std::cout << "  + Players who have or share the strongest hand will win and receive 1 point.\n";
    std::cout << "  + The computer will automatically update player information.\n";
    std::cout << "  + The computer will display the current round Leaderboard, sorted by win rate.\n";
    std::cout << "  + The game does not limit the number of rounds.\n";
    std::cout << "  + The game ends when the participants decide to stop playing.\n";
    std::cout << "  + The computer will display the final Leaderboard on the screen.\n";
    std::cout << "  + The computer will save the match data, including player information and the final Leaderboard, into the file Data_Game.txt.\n\n";

    std::cout << "Rules for Determining Hands:\n";
    std::cout << "  1. The program will randomly deal 5 cards to each participant.\n\n";

    std::cout << "  2. The card rankings are as follows:\n";
    std::cout << "     2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < J < Q < K < A.\n\n";

    std::cout << "  3. The program evaluates the participants’ hands in the following order, from highest to lowest:\n\n";

    std::cout << "     | Rank | Hand Type         | Description                                   |\n";
    std::cout << "     |------|-------------------|-----------------------------------------------|\n";
    std::cout << "     | 1    | Straight Flush    | 5 consecutive cards of the same suit.        |\n";
    std::cout << "     | 2    | Four of a Kind    | 4 cards of the same rank.                    |\n";
    std::cout << "     | 3    | Full House        | 3 cards of the same rank and a pair.         |\n";
    std::cout << "     | 4    | Flush             | 5 cards of the same suit but not consecutive.|\n";
    std::cout << "     | 5    | Straight          | 5 consecutive cards, not necessarily suited. |\n";
    std::cout << "     | 6    | Three of a Kind   | 3 cards of the same rank.                    |\n";
    std::cout << "     | 7    | Two Pairs         | Two pairs of cards with different ranks.     |\n";
    std::cout << "     | 8    | One Pair          | A single pair of cards with the same rank.   |\n";
    std::cout << "     | 9    | High Card         | The highest-value card in the hand.          |\n\n";

    std::cout << "  4. Suits are not considered (only the rank of the cards matters).\n\n";

    std::cout << "  5. The player with the highest-ranked hand wins the match.\n";
    setTextColor(0); // Reset color
}

// Function to print the PvE mode guide
void printPvEGuide() {
    setTextColor(6); // Set color to Cyan
    std::cout << "=== PvE (Player vs. T3 Super AI) Poker Mode ===\n\n";

    std::cout << "Description:\n";
    std::cout << "  + PvE mode allows players to face off against a computer (AI/Bot) designed by the Triple_Star team.\n";
    std::cout << "  + This is a great way to practice or have fun when no real opponent is available.\n\n";

    std::cout << "Instructions:\n";
    std::cout << "  + When entering PvE mode, the player will be prompted to choose the bot difficulty level:\n";
    std::cout << "      Lv1 - Normal: Basic difficulty, the bot plays like a regular player (Bot's win rate: ~60%).\n";
    std::cout << "      Lv2 - Challenge: Challenging difficulty, the bot plays at the level of an expert (Bot's win rate: ~70%).\n";
    std::cout << "      Lv3 - Legendary: Very high difficulty, the bot plays like a poker champion (Bot's win rate: ~80%).\n";
    std::cout << "  + The computer will randomly deal the cards.\n";
    std::cout << "  + The computer will automatically calculate and determine the strongest hand for both the Bot and the player, then display it on the screen.\n";
    std::cout << "  + The computer will automatically determine the winner.\n";
    std::cout << "  + The winner, or those who tie with the strongest hand, will earn 1 point.\n";
    std::cout << "  + The computer will automatically update player and Bot information.\n";
    std::cout << "  + The computer will display the current round's Leaderboard, sorted by win rate.\n";
    std::cout << "  + The game does not limit the number of rounds.\n";
    std::cout << "  + The game ends when the participant decides to stop playing.\n";
    std::cout << "  + The computer will display the final Leaderboard on the screen.\n";
    std::cout << "  + The computer will save match data, including player information and the final Leaderboard, to the file Data_Game.txt.\n\n";

    std::cout << "Rules for Determining Hands:\n";
    std::cout << "  1. The program will randomly deal 5 cards to each participant.\n\n";

    std::cout << "  2. The card rankings are as follows:\n";
    std::cout << "     2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < J < Q < K < A.\n\n";

    std::cout << "  3. The program evaluates the participants’ hands in the following order, from highest to lowest:\n\n";

    std::cout << "     | Rank | Hand Type         | Description                                   |\n";
    std::cout << "     |------|-------------------|-----------------------------------------------|\n";
    std::cout << "     | 1    | Straight Flush    | 5 consecutive cards of the same suit.        |\n";
    std::cout << "     | 2    | Four of a Kind    | 4 cards of the same rank.                    |\n";
    std::cout << "     | 3    | Full House        | 3 cards of the same rank and a pair.         |\n";
    std::cout << "     | 4    | Flush             | 5 cards of the same suit but not consecutive.|\n";
    std::cout << "     | 5    | Straight          | 5 consecutive cards, not necessarily suited. |\n";
    std::cout << "     | 6    | Three of a Kind   | 3 cards of the same rank.                    |\n";
    std::cout << "     | 7    | Two Pairs         | Two pairs of cards with different ranks.     |\n";
    std::cout << "     | 8    | One Pair          | A single pair of cards with the same rank.   |\n";
    std::cout << "     | 9    | High Card         | The highest-value card in the hand.          |\n\n";

    std::cout << "  4. Suits are not considered (only the rank of the cards matters).\n\n";

    std::cout << "  5. The player with the highest-ranked hand wins the match.\n";
    setTextColor(0); // reset color
}

// Print ASCII Art Poker
    void printASCIIPoker() {
    setTextColor(4); // Set color to Blue
    std::cout << "  _____      _             \n";
    std::cout << " |  __ \\    | |            \n";
    std::cout << " | |__) |__ | | _____ _ __ \n";
    std::cout << " |  ___/ _ \\| |/ / _ \\ '__|\n";
    std::cout << " | |  | (_) |   <  __/ |   \n";
    std::cout << " |_|   \\___/|_|\\_\\___|_|   \n";
    std::cout << "                           \n";
    std::cout << "                           \n";
    setTextColor(0); // Reset color
}

// Print ASCII Art
void printASCIIArt() {
    setTextColor(3); // Set color to Green
    std::cout << "                                              %######%\n";
    std::cout << "                                           %*+=+++++++==+#%%%%%%*+*%\n";
    std::cout << "                                         %*-=**=---==++**++++++==#==%\n";
    std::cout << "                                       %%+-#*::=**+===-::-++*++#%#%:*%\n";
    std::cout << "                                     %#+==#*:*%%+=+*++=++==::-*#-*#:#%\n";
    std::cout << "                                    %+-+*+%*#%%*#%#*+*****####*+#%-+%\n";
    std::cout << "                                   %+:#+.-#%%%##%#*%%###%%%##%%%%+:%\n";
    std::cout << "                                   %-+#.*##%%%#%%%@%#%@%%#%%%%%=-%-+%\n";
    std::cout << "                                   %-+#*#%%*===::=++++-:.  :#%#*=%-=%\n";
    std::cout << "                                   %==%+#%#--=.              #%++%:*%\n";
    std::cout << "                                   %*:#*%%*---               #@*#*:#%\n";
    std::cout << "                                    %:=%%%+-==.         ...  =@%%-=%\n";
    std::cout << "                                   %+-+%%#-*#####+   .*###**- %%#+-*%\n";
    std::cout << "                                  %+:%+:*#=++*%%*+.  .:+%#=.: %=:**:#%\n";
    std::cout << "                                  %==%=#%#--:=@%:      =@%-  .%#*+%:*%\n";
    std::cout << "                                  %*:%*=#%=:  ..        .    :%*=#*:#%\n";
    std::cout << "                                   %=-%*+%=: .    .       .  -%+##:*%\n";
    std::cout << "                                    %+-+*%+=#- :*%%##%#+..+* +%*=-*%\n";
    std::cout << "                                      %*:*#=%##@@@@@@@@@%#%+ %=-*%\n";
    std::cout << "                                       %+-%*=*#*#*+--+*#**: *#:*%\n";
    std::cout << "                                     %%#*-+@#=:   :--.    .*%--#%%\n";
    std::cout << "                                  %##*+--#*%#%*-.       .=#%%#*-=+*##%\n";
    std::cout << "                             %%#*+===+*#%--%.+@%#+-:::-*%@--%:+%*++===+*#\n";
    std::cout << "                          %#*+=-+**+=--%::*%. *@@@@%%%@@%+ -%+.+%-=+***=-=+*#%\n";
    std::cout << "                         #==+**#@::--*#-.+*%-:.-*%%%%%#+:  -%++.*#*:=.=@***===#\n";
    std::cout << "                        #=-*#+:..%-=%*@+.+++%#***+-=**--=++*#%++=.#%*@-=# .-*#+-=#\n";
    std::cout << "                      #-=%+.    #**##%.=+++%-:--=#*++##=--:+%+++:=%*%+#*    .+%=-#\n";
    std::cout << "                     #-=%-      *#*%#%##*+*%-==+#%--:+%#+=-=%*+*##%*%*%=      -%=-#\n";
    std::cout << "                    #-=%:       +%*%*%%#=-*%+-=**%*++#%**=-*%+-+%#%*%*%-       :%==#\n";
    std::cout << "                   #==%-       :+%*%#%--=++#%++*#%####%#*++%#++-:+%#%*%=:       -%-+#\n";
    std::cout << "                  #+-%=      .::+%*%#%*+++++*%#*+-::::=+*%%*+++++#%*%#%=:::      +%-+#\n";
    std::cout << "                 #+-#+      ::::+%*%*%%*+++++%+..  *=  .:##+++++#%%*%#%=::::      ##-*#\n";
    std::cout << "                #*-*#      :::::=%*%#%#%*++++#*   #+  .%*++++#%%*%*%##=*-:::::     .%+-#\n";
    std::cout << "                #-+%.     ::::-:=%#%###%%*++++*%+  ..  ##++++#%#%*%*%#%%%-=#=::----=-:.=#-+#\n";
    std::cout << "               #==%-     .::::-*+%#%###%%%*+++*%*:-#%+++#%%#%*%*%#%%%-=#=::----=-:.=#-+#\n";
    std::cout << "             #==*=.:-------:-**-#%%######%#%%*++*%*:-#%+++#%%#%*%*%#%%%-=#=::----=-:.=#-+#\n";
    std::cout << "            #+-%*=++=-.:-==-=*%*%%%######%###%%%#*++%#**%%%%##*%*%*%#%%%**%+=##*++++=-:-+%+-*#\n";
    std::cout << "           #+-*#=--==+++++*#+=%**%%######%###%%%#*+%#**%%%%##*%*%*%#%%%**%+=##*++++=-:-+%+-*#\n";
    std::cout << "          %*:#+:=*+-...-=++*%%%-=%%%#%###%###%#%%%%%%%%%%#%#%*%*%#%#%%%=-%%%#++=-..:-+*-:#+-#\n";
    std::cout << "          %*-%*#-     :--===+*%=-%%%%%#%#%###%%%%%%%%%%%%#%#%#%#%%%%%%%+%%*+===--.  . .+##*-%\n";
    std::cout << "          %+-%*..:. .=*#+===+*%%+%%%%%%%#%#%%#+==+++++++=#%%%#%#%%%%%%%+%%*+===+**-..:. :#*-#\n";
    std::cout << "          %-*%::=-.-#%+.      .-+##%%%%%%%%%====-:-=====. -#%%%%%%%@%#*=:.       +%*:.+=:=%-+%\n";
    std::cout << "          %+=%+*#-:##=-.          =%+-*##%#%*-.:=+=-:::-:   -#%##+-+#:          .-=%*:+#=*#-#%\n";
    std::cout << "           %+=*%%--%+-==-:.      +*.-+-++: **+#+:..-++=:..    :++-*::#-      .--==-#%:=%#+=*%\n";
    std::cout << "            *=-+%*-##+=--===--:.=# -*:#-    .-***##*#%+%*::     =*:#::%-::--===--=+%+-##--+*\n";
    std::cout << "           +****%%%#%%%#*+======%+:%-*+    .::-=-:#+.+*=%+:::    *==#:##----==+*#%%%#%%##*+\n";
    setTextColor(0); // Reset color
}


void printSingleCardDuelGuide()
{   
    setTextColor(6); // Set color to Cyan
    std::cout << "=== Single Card Duel Mode ===\n\n";

    std::cout << "Description:\n";
    std::cout << "  + Single Card Duel mode allows multiple players to compete directly.\n";
    std::cout << "  + Each player is dealt one card.\n";
    std::cout << "  + A simple and quick gameplay mode.\n\n";

    std::cout << "Instructions:\n";
    std::cout << "  + Enter the number of players:\n";
    std::cout << "    - At the start of the mode, players input the number of participants (from 2 to 10).\n";
    std::cout << "  + Random card dealing:\n";
    std::cout << "    - The computer will randomly deal one card to each player.\n";
    std::cout << "  + Scoring and winner determination:\n";
    std::cout << "    - After the cards are dealt, the computer determines the maximum score for each player and displays the results.\n";
    std::cout << "    - The player with the highest score wins the round and earns 1 point.\n";
    std::cout << "    - If multiple players have the same highest score, all of them earn 1 point.\n";
    std::cout << "  + Automatic updates:\n";
    std::cout << "    - The computer automatically updates the players' scores after each round.\n";
    std::cout << "  + Leaderboard:\n";
    std::cout << "    - A temporary leaderboard sorted by win rate is displayed for players to track progress.\n";
    std::cout << "  + Unlimited rounds:\n";
    std::cout << "    - The game does not limit the number of rounds.\n";
    std::cout << "  + End of game:\n";
    std::cout << "    - When the game ends, the computer prints the final leaderboard, showing the results of the entire match.\n\n";

    std::cout << "Rules for Determining the Winning Card:\n";
    std::cout << "  1. Ranks (values) are ordered from 2 (lowest) to A (highest):\n";
    std::cout << "     2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < J < Q < K < A.\n";
    std::cout << "  2. Suits are ranked as follows:\n";
    std::cout << "     Hearts > Diamonds > Clubs > Spades.\n";
    std::cout << "  3. Winner determination:\n";
    std::cout << "     - The player with the card of the highest rank wins.\n";
    std::cout << "     - If two or more players have cards of the same rank, the suit is considered to break the tie:\n";
    std::cout << "       The card with the higher suit wins.\n\n";
    setTextColor(0); // Reset color
}

// Print the Three Card Poker mode guide
void printThreeCardPokerGuide() {
    setTextColor(6); // Set color to Cyan
       std::cout << "=== Three Card Poker Mode ===\n\n";

    std::cout << "Description:\n";
    std::cout << "  + Three Card Poker mode allows multiple players to compete directly.\n";
    std::cout << "  + Each player is dealt three cards.\n";
    std::cout << "  + Players with the strongest hand will win.\n\n";

    std::cout << "Instructions:\n";
    std::cout << "  + Enter the number of players:\n";
    std::cout << "    - At the start of the mode, players input the number of participants (from 2 to 10).\n";
    std::cout << "  + Random card dealing:\n";
    std::cout << "    - The computer will randomly deal three cards to each player.\n";
    std::cout << "  + Scoring and winner determination:\n";
    std::cout << "    - After the cards are dealt, the computer calculates the maximum score for each player and displays the results.\n";
    std::cout << "    - The player with the highest score wins the round and earns 1 point.\n";
    std::cout << "    - If multiple players have the same highest score, all of them earn 1 point.\n";
    std::cout << "  + Automatic updates:\n";
    std::cout << "    - The computer automatically updates the players' scores after each round.\n";
    std::cout << "  + Leaderboard:\n";
    std::cout << "    - A temporary leaderboard sorted by win rate is displayed for players to track progress.\n";
    std::cout << "  + Unlimited rounds:\n";
    std::cout << "    - The game does not limit the number of rounds.\n";
    std::cout << "  + End of game:\n";
    std::cout << "    - When the game ends, the computer prints the final leaderboard, showing the results of the entire match.\n\n";

    std::cout << "Rules for Scoring Hands:\n";
    std::cout << "  1. Standard 52-card deck is used.\n";
    std::cout << "  2. Card values:\n";
    std::cout << "     - A (Ace) = 1 point.\n";
    std::cout << "     - Cards 2 to 9 retain their face value.\n";
    std::cout << "     - 10, J, Q, K are worth 10 points.\n";
    std::cout << "  3. Total points of three cards:\n";
    std::cout << "     - Only the unit digit of the total is considered.\n";
    std::cout << "       For example: If the total is 18, the actual score is 8.\n";
    std::cout << "  4. Maximum score is 9.\n\n";
    setTextColor(0); // Reset color
}

// Function to set text color
void setTextColor(int color) {
    switch (color) {
        case 0: std::cout << "\033[0m"; break; // Reset
        case 1: std::cout << "\033[30m"; break; // Black
        case 2: std::cout << "\033[31m"; break; // Red
        case 3: std::cout << "\033[32m"; break; // Green
        case 4: std::cout << "\033[33m"; break; // Yellow
        case 5: std::cout << "\033[34m"; break; // Blue
        case 6: std::cout << "\033[35m"; break; // Magenta
        case 7: std::cout << "\033[36m"; break; // Cyan
        case 8: std::cout << "\033[37m"; break; // White
        case 9: std::cout << "\033[90m"; break; // Bright Black (Gray)
        case 10: std::cout << "\033[91m"; break; // Bright Red
        case 11: std::cout << "\033[92m"; break; // Bright Green
        case 12: std::cout << "\033[93m"; break; // Bright Yellow
        case 13: std::cout << "\033[94m"; break; // Bright Blue
        case 14: std::cout << "\033[95m"; break; // Bright Magenta
        case 15: std::cout << "\033[96m"; break; // Bright Cyan
        case 16: std::cout << "\033[97m"; break; // Bright White
        default: std::cout << "\033[0m"; break; // Reset
    }
}
