#pragma once
#include <map>
#include <string>
     
//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
//Mô tả: Thư viện này bao gồm các hàm liên quan đến việc xây dựng Database cho trò chơi

//Hướng dẫn sử dụng: 
    //Để sử dụng các hàm trong thư viện này, bạn cần include thư viện này vào file của mình bằng cách thêm dòng lệnh sau:
    //#include "game_database.h"

//Thư viện này bao gồm:

    //Phân loại các mức bài
    enum Hand_Rank {
        HIGH_CARD = 0,
        PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        STRAIGHT,
        FLUSH,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        STRAIGHT_FLUSH
    };

    //Cấu trúc dữ liệu người chơi
    struct Player {
        int number;  
        std::string username;
        int total_games = 0;  
        int wins = 0;  
        float win_rate = 0.0;  
        std::map<std::string, int> win_situations; 
    };

// Hàm khởi tạo người chơi
Player create_player(int player_number) {
    Player p;
    p.number = player_number;

    // Nhập tên người chơi
    std::cout << "Please input Username: (Player " << player_number << "): ";
    std::getline(std::cin, p.username);

    // Các thông tin mặc định
    p.total_games = 0;
    p.wins = 0;
    p.win_rate = 0.0;

    // Trả về người chơi
    return p;
}

    // Hàm khởi tạo người chơi trong chế độ Poker PvE
    Player create_player_Poker_PvE_mode(int player_number) {
        Player p;
        p.number = player_number;
        p.total_games = 0;
        p.wins = 0;
        p.win_rate = 0.0;
        // Khởi tạo thêm các giá trị khác nếu cần
        return p;
    }

    // Enum để lưu chất của lá bài
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    // Struct for representing a card
    struct Card 
    {
        int value;  //lưu giá trị của lá bài
        Suit suit;  //lưu chất của lá bài
    };
    

    // Hàm lưu dữ liệu trò chơi vào file
    void save_game_data_to_file(const std::string& mode, const std::vector<Player>& players);
    
//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
