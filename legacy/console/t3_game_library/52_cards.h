#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Thêm thư viện này để dùng srand
#include <ctime>   // Thêm thư viện này để dùng time
#include <algorithm> // Thêm thư viện này để dùng random_shuffle
#include <map>

//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================

//Mô tả: Thư viện này bao gồm các hàm liên quan đến việc khởi tạo và sử dụng bộ bài 52 lá

//Hướng dẫn sử dụng: 
    //Để sử dụng các hàm trong thư viện này, bạn cần include thư viện này vào file của mình bằng cách thêm dòng lệnh sau:
    //#include "52_cards.h"

//Thư viện này bao gồm các hàm:

    //Hàm tạo và trả về bộ bài 52 lá
    std::vector<std::string> return_pack ();
    
    //Hàm sắp xếp lá bài của các người chơi
    void rank_player_cards(std::vector<std::vector<std::string>>& player_cards, int number_player, int ranks[], int suits[]);

    //Hàm xào bài ngẫu nhiên
    std::vector<std::string> return_shuffled_pack (std::vector<std::string> shuffled_pack);

    // Hàm chia bài cho n người chơi
    std::vector<std::vector<std::string>> deal_cards(const std::vector<std::string>& shuffled_pack, int number_player);

    // Hàm chia bài cho n người chơi chế độ Single Card Duel
    std::vector<std::vector<std::string>> deal_cards_Single_Card_Duel(const std::vector<std::string>& shuffled_pack, int number_player);

    // Hàm lấy giá trị thứ hạng từ chuỗi
    int get_rank(const std::string& card);

    // Hàm lấy chất từ chuỗi
    int get_suit(const std::string& card);

    /*
    // Hàm chia bài cho n người chơi chế độ Three Card Poker
    std::vector<std::vector<std::string>> deal_cards_Three_Card_Poker(const std::vector<std::string>& shuffled_pack, int number_player);
    */

   //Hàm phát bài trong chế độ Three Card Poker và sắp xếp các lá bài theo thứ hạng
    std::vector<std::vector<std::string>> deal_cards_Three_Card_Poker(const std::vector<std::string>& shuffled_pack, int number_player);




//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================



//tạo và trả về bộ bài 52 lá
 std::vector<std::string> return_pack ()
 {
    std::vector<std::string> pack;
    for(int i = 1; i <= 52; i++){
        switch (i % 13 ) 
        {
            case 10: pack.push_back("10");
                break;
            case 11: pack.push_back("J");
                break;
            case 12: pack.push_back("Q");
                break;
            case 0: pack.push_back("K");
                break;
            case 1: pack.push_back("A");
                break;
            default: 
                std::string s;
                s = (char)(i % 13 + 48 );
                pack.push_back(s); 
                break;
        }
        if (i >= 1 && i <= 13){
            pack[pack.size() - 1] += " spade";
        }
        if (i >= 14 && i <= 26){
            pack[pack.size() - 1] += " club";
        }
        if (i >= 27 && i <= 39){
            pack[pack.size() - 1] += " diamond";
        }
        if (i >= 40 && i <= 52){
            pack[pack.size() - 1] += " heart";
        }
    }
    return pack;
 }

// Sắp xếp lá bài của các người chơi
void rank_player_cards(std::vector<std::vector<std::string>>& player_cards, int number_player, int ranks[], int suits[]) {
    for (int player_index = 0; player_index < number_player; player_index++) {
        for (int i = 0; i < 5; i++) {
            ranks[player_index * 5 + i] = get_rank(player_cards[player_index][i]);
            suits[player_index * 5 + i] = get_suit(player_cards[player_index][i]);
        }

        // Sắp xếp các lá bài theo thứ tự tăng dần
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 5; j++) {
                if (ranks[player_index * 5 + i] > ranks[player_index * 5 + j]) {
                    std::swap(player_cards[player_index][i], player_cards[player_index][j]);
                    std::swap(ranks[player_index * 5 + i], ranks[player_index * 5 + j]);
                }
            }
        }
    }
}


//xào bài
std::vector<std::string> return_shuffled_pack (std::vector<std::string> shuffled_pack)
{
    // Nhận một số ngẫu nhiên khác nhau mỗi lần chương trình chạy
    //tham khảo ở https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    srand(time(0));
    //xáo bài tham khảo ở https://www.w3schools.com/cpp/ref_algorithm_random_shuffle.asp
    std::random_shuffle(shuffled_pack.begin(), shuffled_pack.end());
    return shuffled_pack;
}


// Chia bài 
std::vector<std::vector<std::string>> deal_cards(const std::vector<std::string>& shuffled_pack, int number_player) 
{
    std::vector<std::vector<std::string>> player_cards(number_player); // Mỗi người chơi sẽ có một vector riêng
    for (int i = 0; i < number_player * 5; i++) 
    {
        player_cards[i % number_player].push_back(shuffled_pack[i]);
    }
    return player_cards;
}


// Tách giá trị thứ hạng từ chuỗi
int get_rank(const std::string& card) { 
    std::string rank_str = card.substr(0, card.find(" ")); 
    std::map<std::string, int> rank_map = {{"2", 1}, {"3", 2}, {"4", 3}, 
                                            {"5", 4}, {"6", 5}, {"7", 6}, 
                                            {"8", 7}, {"9", 8}, {"10", 9}, 
                                            {"J", 10}, {"Q", 11}, {"K", 12}, {"A", 13}}; 
    return rank_map[rank_str]; // Trả về giá trị thứ hạng của lá bài }
}

// Tách chất từ chuỗi (giả sử chất nằm sau khoảng trắng)
int get_suit(const std::string& card) {
    std::string suit_str = card.substr(card.find(" ") + 1);
    std::map<std::string, int> suit_map = {{"spade", 0}, {"heart", 1}, {"diamond", 2}, {"club", 3}};
    return suit_map[suit_str];
}

// Hàm chia bài cho n người chơi chế độ Single Card Duel
std::vector<std::vector<std::string>> deal_cards_Single_Card_Duel(const std::vector<std::string>& shuffled_pack, int number_player) 
{
    std::vector<std::vector<std::string>> player_cards(number_player); // Mỗi người chơi sẽ có một vector riêng
    for (int i = 0; i < number_player; i++) {
        player_cards[i].push_back(shuffled_pack[i]); // Mỗi người chơi nhận 1 lá bài
    }
    return player_cards;
}

// Lấy giá trị điểm của lá bài (chỉ tính chữ số hàng đơn vị)
int get_card_value(const std::string& card) {
    int rank = get_rank(card);  // Lấy giá trị thứ hạng của lá bài

    // Cộng điểm và chỉ lấy chữ số hàng đơn vị (mod 10)
    return rank > 10 ? 10 : rank;  // Các lá bài lớn hơn 10 (J, Q, K) có giá trị là 10
}

