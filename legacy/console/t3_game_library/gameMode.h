
#pragma once
#include "t3_library.h"

//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================

//Mô tả: Thư viện này bao gồm các hàm liên quan đến việc khởi tạo và thực thi các chế độ game

//Hướng dẫn sử dụng: 
    //Để sử dụng các hàm trong thư viện này, bạn cần include thư viện này vào file của mình bằng cách thêm dòng lệnh sau:
    //#include "gameMode.h"

//Thư viện này bao gồm các hàm:

    // Hàm chọn chế độ chơi
    void select_game_mode(std::vector<Player>& players);

//...................................................................................................................................................................................................................................................................................................
//Chế độ PvP_Poker

    // Khởi tạo và thực thi chế độ chơi PVP
    void run_poker_pvp_mode();

    // Tính điểm cho từng người chơi
        // + Tại tham số bool check_print: true hoặc 1 nếu muốn in và false hoặc 0 nếu không muốn in
        // + Tại tham số bool pve_mode: false hoặc 0
    void calculate_player_points(int number_player, const std::vector<std::vector<std::string>>& player_cards, int ranks[], int suits[], std::vector<int> &player_value_card_points, std::vector<int> &player_rank_points, bool check_print, bool pve_mode);

    // Xác định người chiến thắng
    void determine_winner(int number_player, std::vector<int>& player_value_card_points, std::vector<int>& player_rank_points, std::vector<Player>& players);
//...................................................................................................................................................................................................................................................................................................
//Chế độ PvE

    // Khởi tạo và thực thi chế độ chơi PVE
    void run_poker_pve_mode();

    //hàm tạo sô ngẫu nhiên từ 1 đến 10
    int return_random_number();

    // Tính điểm cho từng người chơi
        // + Tại tham số bool check_print: true hoặc 1 nếu muốn in và false hoặc 0 nếu không muốn in
        // + Tại tham số bool pve_mode: true hoặc 1
    void calculate_player_points(int number_player, const std::vector<std::vector<std::string>>& player_cards, int ranks[], int suits[], std::vector<int> &player_value_card_points, std::vector<int> &player_rank_points, bool check_print, bool pve_mode);

    // Xác định người chiến thắng trong chế độ PvE
    void determine_winner_pve(int number_player, std::vector<int>& player_value_card_points, std::vector<int>& player_rank_points, std::vector<Player>& players);

//...................................................................................................................................................................................................................................................................................................
//Chế độ Single Card Duel

    //Khởi tạo và thực thi chế độ chơi Single Card Duel
    void run_Single_Card_Duel();    

    // Tính điểm cho từng người chơi trong chế độ Single Card Duel
    void calculate_player_points_Single_Card_Duel(int number_player, const std::vector<std::vector<std::string>>& player_cards, int ranks[], int suits[], std::vector<int> &player_value_card_points, std::vector<int> &player_rank_points, bool check_print, bool pve_mode);
    
    // Xác định người chiến thắng
    void determine_winner_Single_Card_Duel(int number_player, std::vector<int>& player_value_card_points, std::vector<int>& player_rank_points, std::vector<Player>& players);

    // Hàm kiểm tra giữa 2 lá bài lá nào mạnh hơn
    bool is_stronger_between_2_cards (const Card& a, const Card& b);

//...................................................................................................................................................................................................................................................................................................
//Chế độ Three Card Poker (Bài cào) 

    // Hàm chạy chế độ Three Card Poker
    void run_Three_Card_Poker();

    // Hàm chia bài cho chế độ Three Card Poker
    std::vector<std::vector<std::string>> deal_cards_Three_Card_Poker(std::vector<std::string>& shuffled_pack, int number_player);

    // Hàm tính điểm cho chế độ Three Card Poker
    int calculate_player_score_Three_Card_Poker(std::vector<std::string>& player_cards);

    // Hàm xác định người chiến thắng trong chế độ Three Card Poker
    std::vector<int> determine_winners_Three_Card_Poker(std::vector<Player>& players, std::vector<std::vector<std::string>>& player_cards);




//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
// Hàm chọn chế độ chơi với cơ chế chống nhập sai
void select_game_mode(std::vector<Player>& players) {
    int mode_choice;
    bool valid_choice;

    std::cout << "\nChoose game mode: " << std::endl;
    std::cout << "1. Poker PVP mode (Player vs Player)" << std::endl;
    std::cout << "2. Poker PVE mode (Player vs Bot)" << std::endl;
    std::cout << "3. Single Card Duel" << std::endl;
    std::cout << "4. Three Card Poker" << std::endl;
    std::cout << "Enter your choice (1, 2, 3, 4): ";
    
    //Chống nhập sai
    do {
        std::cin >> mode_choice;

        // Kiểm tra nếu đầu vào không hợp lệ hoặc không nằm trong phạm vi
        if (std::cin.fail() || mode_choice < 1 || mode_choice > 4) {
            std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
            std::cin.clear(); // Xóa trạng thái lỗi của cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bỏ qua đầu vào không hợp lệ
            valid_choice = false;
        } else {
            valid_choice = true;
        }
    } while (!valid_choice);

    // Xử lý lựa chọn hợp lệ
    switch (mode_choice) {
        case 1:
            run_poker_pvp_mode();
            break;
        case 2:
            run_poker_pve_mode();
            break;
        case 3:
            run_Single_Card_Duel();
            break;
        case 4:
            run_Three_Card_Poker();
            break;
    }
}


// Tính điểm cho từng người chơi
void calculate_player_points(int number_player, const std::vector<std::vector<std::string>>& player_cards, int ranks[], int suits[], std::vector<int> &player_value_card_points, std::vector<int> &player_rank_points, bool check_print, bool pve_mode) {
    std::map<int, std::string> rank_map = {{1,"2"},{2,"3"},{3,"4"},{4,"5"},{5,"6"}, {6,"7"}, {7,"8"}, {8,"9"}, {9,"10"}, {10,"J"}, {11,"Q"}, {12,"K"}, {13,"A"}};

    for (int player_index = 0; player_index < number_player; player_index++) 
    {
        int value_card_point = 0;
        int rank_point = 0;
        // Check for hand combinations (straight flush, four of a kind, etc.)

        // Straight Flush
        if ((ranks[player_index * 5 + 1] == ranks[player_index * 5 + 0] + 1 &&
            ranks[player_index * 5 + 2] == ranks[player_index * 5 + 1] + 1 &&
            ranks[player_index * 5 + 3] == ranks[player_index * 5 + 2] + 1 &&
            ranks[player_index * 5 + 4] == ranks[player_index * 5 + 3] + 1) &&
            (suits[player_index * 5 + 0] == suits[player_index * 5 + 1] &&
             suits[player_index * 5 + 1] == suits[player_index * 5 + 2] &&
             suits[player_index * 5 + 2] == suits[player_index * 5 + 3] &&
             suits[player_index * 5 + 3] == suits[player_index * 5 + 4])) {
            if (check_print) {
                std::cout << (pve_mode && player_index == 1 ? "Bot got " : (pve_mode ? "Player " : "Player " + std::to_string(player_index + 1)) + " got ") << rank_map[ranks[player_index * 5 + 4]] << " Straight Flush!" << std::endl;
            }
            value_card_point += 8;
            rank_point += ranks[player_index * 5 + 4];

        // Four of a Kind
        } else if ((ranks[player_index * 5 + 0] == ranks[player_index * 5 + 1] &&
                    ranks[player_index * 5 + 1] == ranks[player_index * 5 + 2] &&
                    ranks[player_index * 5 + 2] == ranks[player_index * 5 + 3]) ||
                   (ranks[player_index * 5 + 1] == ranks[player_index * 5 + 2] &&
                    ranks[player_index * 5 + 2] == ranks[player_index * 5 + 3] &&
                    ranks[player_index * 5 + 3] == ranks[player_index * 5 + 4])) {
            
            // Determine the four of a rank card of four of a kind
            int four_of_a_kind_rank = 0;
            for (int i = 0; i < 5; ++i) {
                int current_rank = ranks[player_index * 5 + i];
                int count = 0;
                for (int j = 0; j < 5; ++j) {
                    if (ranks[player_index * 5 + j] == current_rank) {
                        count++;
                    }
                }
                if (count == 4) {
                    four_of_a_kind_rank = current_rank;
                    break;
                }
            }
            if (check_print) {
                std::cout << (pve_mode && player_index == 1 ? "Bot got Four of a Kind of " : "Player " + std::to_string(player_index + 1) + " got Four of a Kind of ") << rank_map[four_of_a_kind_rank] << std::endl;
            }
            value_card_point += 7;
            rank_point += four_of_a_kind_rank;

        // Full House
        } else if ((ranks[player_index * 5 + 0] == ranks[player_index * 5 + 1] &&
                    ranks[player_index * 5 + 1] == ranks[player_index * 5 + 2] &&
                    ranks[player_index * 5 + 3] == ranks[player_index * 5 + 4]) ||
                   (ranks[player_index * 5 + 0] == ranks[player_index * 5 + 1] &&
                    ranks[player_index * 5 + 2] == ranks[player_index * 5 + 3] &&
                    ranks[player_index * 5 + 3] == ranks[player_index * 5 + 4])) {
            
            // Determine the three of a kind and pair rank cards of full house
            int three_of_a_kind_rank = 0, pair_rank = 0;
            for (int i = 0; i < 5; ++i) {
                int current_rank = ranks[player_index * 5 + i];
                int count = 0;
                for (int j = 0; j < 5; ++j) {
                    if (ranks[player_index * 5 + j] == current_rank) {
                        count++;
                    }
                }
                if (count == 3) {
                    three_of_a_kind_rank = current_rank;
                } else if (count == 2) {
                    pair_rank = current_rank;
                }
            }
            if (check_print) {
                std::cout << (pve_mode && player_index == 1 ? "Bot got Full House! Three of " : (pve_mode ? "Player " : "Player " + std::to_string(player_index + 1)) + " got Full House! Three of ") << rank_map[three_of_a_kind_rank] << " and Pair of " << rank_map[pair_rank] << std::endl;
            }
            value_card_point += 6;
            rank_point += three_of_a_kind_rank;

        // Flush
        } else if (suits[player_index * 5 + 0] == suits[player_index * 5 + 1] &&
                   suits[player_index * 5 + 1] == suits[player_index * 5 + 2] &&
                   suits[player_index * 5 + 2] == suits[player_index * 5 + 3] &&
                   suits[player_index * 5 + 3] == suits[player_index * 5 + 4]) {
            if (check_print) {
                std::cout << (pve_mode && player_index == 1 ? "Bot got a Flush of " : (pve_mode ? "Player " : "Player " + std::to_string(player_index + 1)) + " got a Flush of ") << rank_map[ranks[player_index * 5 + 4]] << std::endl;
            }
            value_card_point += 5;
            rank_point += ranks[player_index * 5 + 4];

        // Straight
        } else if (ranks[player_index * 5 + 1] == ranks[player_index * 5 + 0] + 1 &&
                   ranks[player_index * 5 + 2] == ranks[player_index * 5 + 1] + 1 &&
                   ranks[player_index * 5 + 3] == ranks[player_index * 5 + 2] + 1 &&
                   ranks[player_index * 5 + 4] == ranks[player_index * 5 + 3] + 1) {
            if (check_print) {
                std::cout << (pve_mode && player_index == 1 ? "Bot got a Straight of " : (pve_mode ? "Player " :  "Player " + std::to_string(player_index + 1)) + " got a Straight of ") << rank_map[ranks[player_index * 5 + 4]] << std::endl;
            }
            value_card_point += 4;
            rank_point += ranks[player_index * 5 + 4];

        // Three of a Kind
        } else if ((ranks[player_index * 5 + 0] == ranks[player_index * 5 + 1] &&
                    ranks[player_index * 5 + 1] == ranks[player_index * 5 + 2]) ||
                   (ranks[player_index * 5 + 1] == ranks[player_index * 5 + 2] &&
                    ranks[player_index * 5 + 2] == ranks[player_index * 5 + 3]) ||
                   (ranks[player_index * 5 + 2] == ranks[player_index * 5 + 3] &&
                    ranks[player_index * 5 + 3] == ranks[player_index * 5 + 4])) {
            
            // Determine the rank card of three of a kind
            int three_of_a_kind_rank = 0;
            for (int i = 0; i < 5; ++i) {
                int current_rank = ranks[player_index * 5 + i];
                int count = 0;
                for (int j = 0; j < 5; ++j) {
                    if (ranks[player_index * 5 + j] == current_rank) {
                        count++;
                    }
                }
                if (count == 3) {
                    three_of_a_kind_rank = current_rank;
                    break;
                }
            }
            if (check_print) {
                std::cout << (pve_mode && player_index == 1 ? "Bot got Three of a Kind of " : (pve_mode ? "Player " : "Player " + std::to_string(player_index + 1)) + " got Three of a Kind of ") << rank_map[three_of_a_kind_rank] << std::endl;
            }
            value_card_point += 3;
            rank_point += three_of_a_kind_rank;

        } else {
            // Two pair, pair, high card
            int pair_count = 0;
            int pair1_rank = 0, pair2_rank = 0, high_card_rank = 0;

            // Count the pairs
            for (int i = 0; i < 4; ++i) {
                if (ranks[player_index * 5 + i] == ranks[player_index * 5 + i + 1]) {
                    pair_count++;
                    if (pair_count == 1) {
                        pair1_rank = ranks[player_index * 5 + i];
                    } else if (pair_count == 2) {
                        pair2_rank = ranks[player_index * 5 + i];
                    }
                    i++; // Skip the next card, as it's part of the pair
                } else {
                    high_card_rank = ranks[player_index * 5 + 4];
                }
            }

            // Determine the card in two pair
            if (pair_count == 2) {
                if (check_print) {
                    std::cout << (pve_mode && player_index == 1 ? "Bot got Two Pair of " : (pve_mode ? "Player " : "Player " + std::to_string(player_index + 1)) + " got Two Pair of ") << rank_map[pair1_rank] << " and " << rank_map[pair2_rank] << std::endl;
                }
                value_card_point += 2;

                if (pair1_rank > pair2_rank) {
                    rank_point += pair1_rank;
                } else {
                    rank_point += pair2_rank;
                }

            // Determine the card in pair
            } else if (pair_count == 1) {
                if (check_print) {
                    std::cout << (pve_mode && player_index == 1 ? "Bot got a Pair of " : (pve_mode ? "Player " :  "Player " + std::to_string(player_index + 1)) + " got a Pair of ") << rank_map[pair1_rank] << std::endl;
                }
                value_card_point += 1;
                rank_point = pair1_rank;

            // High card
            } else {
                if (check_print) {
                    std::cout << (pve_mode && player_index == 1 ? "Bot got a High Card of " : (pve_mode ? "Player " :  "Player " + std::to_string(player_index + 1)) + " got a High Card of ") << rank_map[high_card_rank] << std::endl;
                }
                rank_point = high_card_rank;
            }
        }
        
        player_value_card_points[player_index] = value_card_point;
        player_rank_points[player_index] = rank_point;
    }
}

void determine_winner(
    int number_player,
    std::vector<int>& player_value_card_points,
    std::vector<int>& player_rank_points,
    std::vector<Player>& players // Thêm danh sách Player vào tham số
) {
    int max_points = 0;
    std::vector<int> winning_players;

    // Tìm người chơi có số điểm cao nhất
    for (int i = 0; i < number_player; ++i) {
        if (player_value_card_points[i] > max_points) {
            max_points = player_value_card_points[i];
            winning_players.clear();
            winning_players.push_back(i);
        } else if (player_value_card_points[i] == max_points) {
            if (!winning_players.empty()) { // Check if winning_players is not empty
                if (player_rank_points[i] > player_rank_points[winning_players[0]]) {
                    winning_players.clear();
                    winning_players.push_back(i);
                } else if (player_rank_points[i] == player_rank_points[winning_players[0]]) {
                    winning_players.push_back(i);
                }
            } else {
                winning_players.push_back(i);
            }
        }
    }

    // Map các loại bài vào tên tương ứng
    std::map<Hand_Rank, std::string> hand_rank_names = {
        {HIGH_CARD, "High Card"},
        {PAIR, "Pair"},
        {TWO_PAIR, "Two Pair"},
        {THREE_OF_A_KIND, "Three of a Kind"},
        {STRAIGHT, "Straight"},
        {FLUSH, "Flush"},
        {FULL_HOUSE, "Full House"},
        {FOUR_OF_A_KIND, "Four of a Kind"},
        {STRAIGHT_FLUSH, "Straight Flush"}
    };

    std::cout << std::endl;

    // Xử lý trường hợp có một người thắng
    if (winning_players.size() == 1) {
        int winner = winning_players[0];
        std::cout << "Player " << winner + 1 << " wins with "
             << hand_rank_names[static_cast<Hand_Rank>(player_value_card_points[winner])]
             << "!" << std::endl;

        // Cập nhật thông tin người thắng
        players[winner].total_games++;
        players[winner].wins++;
        players[winner].win_rate = (static_cast<float>(players[winner].wins) / players[winner].total_games) * 100;

        // Cập nhật tình huống thắng
        std::string win_situation = hand_rank_names[static_cast<Hand_Rank>(player_value_card_points[winner])];
        players[winner].win_situations[win_situation]++;
    }
    // Xử lý trường hợp hòa
    else {
        std::cout << "It's a tie! The following players have won:\n";
        for (int i = 0; i < winning_players.size(); ++i) {
            int winner = winning_players[i];
            std::cout << "- Player " << winner + 1 << " with "
                 << hand_rank_names[static_cast<Hand_Rank>(player_value_card_points[winner])] << std::endl;

            // Cập nhật thông tin các người hòa
            players[winner].total_games++;
            players[winner].wins++;
            players[winner].win_rate = (static_cast<float>(players[winner].wins) / players[winner].total_games) * 100;

            // Cập nhật tình huống thắng
            std::string win_situation = hand_rank_names[static_cast<Hand_Rank>(player_value_card_points[winner])];
            players[winner].win_situations[win_situation]++;
        }
    }

    // Cập nhật thông tin cho các người chơi thua
    for (int i = 0; i < number_player; ++i) {
        if (std::find(winning_players.begin(), winning_players.end(), i) == winning_players.end()) {
            players[i].total_games++;
            players[i].win_rate = (static_cast<float>(players[i].wins) / players[i].total_games) * 100;
        }
    }
}


void determine_winner_pve(
    int number_player,
    std::vector<int>& player_value_card_points,
    std::vector<int>& player_rank_points,
    std::vector<Player>& players // Thêm danh sách Player vào tham số
) 
{
    int max_points = 0;
    std::vector<int> winning_players;

    // Tìm người chơi có số điểm cao nhất
    for (int i = 0; i < number_player; ++i) {
        if (player_value_card_points[i] > max_points) {
            max_points = player_value_card_points[i];
            winning_players.clear();
            winning_players.push_back(i);
        } else if (player_value_card_points[i] == max_points) {
            if (!winning_players.empty()) { // Check if winning_players is not empty
                if (player_rank_points[i] > player_rank_points[winning_players[0]]) {
                    winning_players.clear();
                    winning_players.push_back(i);
                } else if (player_rank_points[i] == player_rank_points[winning_players[0]]) {
                    winning_players.push_back(i);
                }
            } else {
                winning_players.push_back(i);
            }
        }
    }

    // Map các loại bài vào tên tương ứng
    std::map<Hand_Rank, std::string> hand_rank_names = {
        {HIGH_CARD, "High Card"},
        {PAIR, "Pair"},
        {TWO_PAIR, "Two Pair"},
        {THREE_OF_A_KIND, "Three of a Kind"},
        {STRAIGHT, "Straight"},
        {FLUSH, "Flush"},
        {FULL_HOUSE, "Full House"},
        {FOUR_OF_A_KIND, "Four of a Kind"},
        {STRAIGHT_FLUSH, "Straight Flush"}
    };

    std::cout << std::endl;

    // Xử lý trường hợp có một người thắng
    if (winning_players.size() == 1) {
        int winner = winning_players[0];
        std::cout << (winner == 0 ? "Player " : "Bot") << " wins with "
             << hand_rank_names[static_cast<Hand_Rank>(player_value_card_points[winner])]
             << "!" << std::endl;

        // Cập nhật thông tin người thắng
        players[winner].total_games++;
        players[winner].wins++;
        players[winner].win_rate = (static_cast<float>(players[winner].wins) / players[winner].total_games) * 100;

        // Cập nhật tình huống thắng
        std::string win_situation = hand_rank_names[static_cast<Hand_Rank>(player_value_card_points[winner])];
        players[winner].win_situations[win_situation]++;
    }
    // Xử lý trường hợp hòa
    else {
        std::cout << "It's a tie! Both Player and Bot have won:\n";
        for (int i = 0; i < winning_players.size(); ++i) {
            int winner = winning_players[i];
            std::cout << (i == 0 ? "- Player " : "- Bot " ) << " with "
                 << hand_rank_names[static_cast<Hand_Rank>(player_value_card_points[winner])] << std::endl;

            // Cập nhật thông tin các người hòa
            players[winner].total_games++;
            players[winner].wins++;
            players[winner].win_rate = (static_cast<float>(players[winner].wins) / players[winner].total_games) * 100;

            // Cập nhật tình huống thắng
            std::string win_situation = hand_rank_names[static_cast<Hand_Rank>(player_value_card_points[winner])];
            players[winner].win_situations[win_situation]++;
        }
    }

    // Cập nhật thông tin cho các người chơi thua
    for (int i = 0; i < number_player; ++i) {
        if (std::find(winning_players.begin(), winning_players.end(), i) == winning_players.end()) {
            players[i].total_games++;
            players[i].win_rate = (static_cast<float>(players[i].wins) / players[i].total_games) * 100;
        }
    }
}


// Hàm PVP Mode: Xử lý các bước trong chế độ PVP
void run_poker_pvp_mode() 
{
    std::cout << std::endl << "Welcome to Player vs Player mode!" << std::endl << std::endl;

    std::cout << "Do you want to read the guide to playing the PvP mode game?\n";

    if (check_Yes_No_Input()) 
    {
        // Hàm in hướng dẫn chơi chế độ PvP
        printPvPGuide();

    }
    std::cout << std::endl;

    // nhập số người chơi
    int number_player = input_number_of_players();

    // khởi tạo mảng gồm dữ liệu người chơi 
    std::vector<Player> players(number_player);

    std::cout << std::endl;
    
    // khởi tạo các người chơi mặc định
    std::cin.get();
    for (int i = 0; i < number_player; ++i) 
    {
        players[i] = create_player(i + 1);
        std::cout << std::endl;
    }

    int cnt = 0;
    
    // Vòng lặp chơi, chỉ hỏi từ lần thứ hai
    do {
        // Bộ bài 52 lá
        std::vector<std::string> pack = return_pack();

        // Xáo bài
        std::vector<std::string> shuffled_pack = return_shuffled_pack(pack);

        // Chia bài
        std::vector<std::vector<std::string>> player_cards = deal_cards(shuffled_pack, number_player);
        
        // Biến lưu loại bài của từng người chơi
        std::vector<Hand_Rank> player_hand_rank(number_player); 
        
        int ranks[50]; // thứ hạng của các lá bài
        int suits[50]; // lưu trữ chất của lá bài

        // sắp xếp lại lá bài của các người chơi để tính điểm
        rank_player_cards(player_cards, number_player, ranks, suits);

        // hiển thị lá bài của các người chơi
        print_all_player_cards(player_cards, number_player);
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
        // kiểm tra loại bài mỗi người chơi
        std::vector<int> player_value_card_points(number_player);
        std::vector<int> player_rank_points(number_player);
    
        calculate_player_points(number_player, player_cards, ranks, suits, player_value_card_points, player_rank_points, 1, 0);

        // Dertemine the winner
        determine_winner(number_player, player_value_card_points, player_rank_points, players);

        // In thông tin người chơi sau khi cập nhật
        std::cout << "\n==========================================================================================================" << "\n\n";
        for (const auto& player : players) 
        {
            print_player_info(player);
        }

        // Sau mỗi vòng chơi, hiển thị bảng xếp hạng
        leaderboard(players);
    
        // Tăng số lần chơi lên sau mỗi vòng
        ++cnt;

        // Câu hỏi tiếp tục chơi chỉ được hỏi từ lần thứ 2 trở đi
        if (cnt > 0) {
            std::cout << "Do you want to continue playing? (Y/N): ";
        }

    } while (cnt == 0 || check_Yes_No_Input());
    
    // In thông tin người chơi sau khi cập nhật
    final_leaderboard(players);

    save_game_data_to_file("Poker PvP mode", players);
}

//hàm tạo số ngẫu nhiên từ 1 đến 10
int return_random_number() {
    return rand() % 10 + 1;
}


// Chế độ PvE
void run_poker_pve_mode() 
{
    std::srand(std::time(0)); // Khởi tạo seed cho số ngẫu nhiên
    const int number_of_players = 2; // 1 bot và 1 người chơi

    std::cout << std::endl << "Welcome to Player vs Bot mode!" << std::endl;

    std::cout << "You will play against a bot (Our Super AI) in this mode." << std::endl << std::endl;

    std::cout << "Do you want to read the guide to playing the PvE mode game?\n";
    
    if (check_Yes_No_Input()) 
    {
        // Hàm in hướng dẫn chơi chế độ PvE
        printPvEGuide();
    }

    // Chọn mức độ khó của trò chơi
    int level_bot = selectGameLevel(); 
    
    // Tạo thông tin người chơi
    std::vector<Player> players(number_of_players);
    players[0] = create_player_Poker_PvE_mode(1); // Người chơi
    players[1] = create_player_Poker_PvE_mode(2); // Bot

    int cnt = 0;

    do {
        // Phase 1: Tạo bộ bài 52 lá và xào bài
        std::vector<std::string> pack = return_pack();
        std::vector<std::string> shuffled_pack = return_shuffled_pack(pack);

        // Chia bài cho bot và người chơi
        std::vector<std::vector<std::string>> player_cards = deal_cards(shuffled_pack, number_of_players);

        // Lưu trữ thứ hạng và chất của lá bài
        int ranks[10];
        int suits[10];

        // sắp xếp lại lá bài của người chơi để tính điểm
        rank_player_cards(player_cards, number_of_players, ranks, suits);

        // Xác định bài thắng/thua
        // Tính điểm cho từng người chơi
        std::vector<int> player_value_card_points(number_of_players);
        // lưu trữ điểm của từng lá bài
        std::vector<int> player_rank_points(number_of_players);

        // Tính điểm cho người chơi
        calculate_player_points(number_of_players, player_cards, ranks, suits, player_value_card_points, player_rank_points, 0, 0);

        // Ensure player keeps winning card and bot keeps losing card
        if (player_value_card_points[0] < player_value_card_points[1]) {
            std::swap(player_cards[0], player_cards[1]);
        }

        // Phase 2: Random to decide if bot keeps winning card
        int random_result = return_random_number();
    
        if (random_result <= 5 + level_bot) 
           std::swap(player_cards[0], player_cards[1]);
           
        // Phase 3: Display cards of player and bot
        std::cout << std::endl;
        std::cout << "Round " << cnt + 1 << std::endl;
        std::cout << "====================" << std::endl;
    
        std::cout << "Player's cards: ";
        for (const std::string& card : player_cards[0]) {
            std::cout << card << "  ";
        }
        std::cout << std::endl;

        std::cout << "Bot's cards: ";
        for (const std::string& card : player_cards[1]) {
            std::cout << card << "  ";
        }
        std::cout << std::endl << std::endl;

        // Calculate points and determine winner
        rank_player_cards(player_cards, number_of_players, ranks, suits);
        calculate_player_points(number_of_players, player_cards, ranks, suits, player_value_card_points, player_rank_points, 1, 1);
        determine_winner_pve(number_of_players, player_value_card_points, player_rank_points, players);
        std::cout << std::endl;
        
        // Display player and bot information
        print_pve_info(players[0], false, level_bot);
        std::cout << std::endl;
        print_pve_info(players[1], true, level_bot);

        // Display current leaderboard
        leaderboard_pve(players, level_bot);

        // Increase the number of plays
        ++cnt;

        // Ask if the player wants to continue playing
        if (cnt > 0) {
            std::cout << "Do you want to continue playing? (Y/N): ";
        }

    } while (cnt == 0 || check_Yes_No_Input());

    // Display final leaderboard
    final_leaderboard_pve(players, level_bot);

    save_game_data_to_file_poker_PvE_mode("Poker PvE mode", players, level_bot);
}



// Chế độ Single Card Duel
void run_Single_Card_Duel() {
    std::cout << std::endl << "Welcome to Single Card Duel mode!" << std::endl << std::endl;

    std::cout << "Do you want to read the guide to playing the Single Card Duel mode game?\n";

    if (check_Yes_No_Input()) {
        // Hàm in hướng dẫn chơi chế độ Single Card Duel
        printSingleCardDuelGuide();
    }
    std::cout << std::endl;

    // In ASCII Art
    printASCIIArt();
    
    // nhập số người chơi
    int number_player = input_number_of_players();

    // khởi tạo mảng gồm dữ liệu người chơi 
    std::vector<Player> players(number_player);

    // khởi tạo các người chơi mặc định
    std::cin.get();
    for (int i = 0; i < number_player; ++i) {
        players[i] = create_player(i + 1);
    }

    int cnt = 0;

    // Vòng lặp chơi, chỉ hỏi từ lần thứ hai
    do {
        // Bộ bài 52 lá
        std::vector<std::string> pack = return_pack();

        // Xáo bài
        std::vector<std::string> shuffled_pack = return_shuffled_pack(pack);

        // Chia bài, mỗi người chơi nhận 1 lá bài
        std::vector<std::vector<std::string>> player_cards = deal_cards_Single_Card_Duel(shuffled_pack, number_player);

        // Lưu trữ thứ hạng và chất của lá bài
        int ranks[10];
        int suits[10];

        // sắp xếp lại lá bài của các người chơi để tính điểm
        for (int i = 0; i < number_player; ++i) {
            ranks[i] = get_rank(player_cards[i][0]);
            suits[i] = get_suit(player_cards[i][0]);
        }

        // hiển thị lá bài của các người chơi
        print_all_player_cards(player_cards, number_player);

        // kiểm tra loại bài mỗi người chơi
        std::vector<int> player_value_card_points(number_player);
        std::vector<int> player_rank_points(number_player);

        calculate_player_points_Single_Card_Duel(number_player, player_cards, ranks, suits, player_value_card_points, player_rank_points, 1, 0);

        // Xác định người chiến thắng
        determine_winner_Single_Card_Duel(number_player, player_value_card_points, player_rank_points, players);

        // In thông tin người chơi sau khi cập nhật
        std::cout << "\n==========================================================================================================" << "\n\n";
        for (const auto& player : players) {
            print_player_info(player);
        }

        // Sau mỗi vòng chơi, hiển thị bảng xếp hạng
        leaderboard(players);

        // Tăng số lần chơi lên sau mỗi vòng
        ++cnt;

        // Câu hỏi tiếp tục chơi chỉ được hỏi từ lần thứ 2 trở đi
        if (cnt > 0) {
            std::cout << "Do you want to continue playing? (Y/N): ";
        }

    } while (cnt == 0 || check_Yes_No_Input());

    // In thông tin người chơi sau khi cập nhật
    final_leaderboard(players);

    save_game_data_to_file("Single Card Duel", players);
}

// Hàm tính điểm cho chế độ Single Card Duel
void calculate_player_points_Single_Card_Duel(int number_player, const std::vector<std::vector<std::string>>& player_cards, 
                                               int ranks[], int suits[], std::vector<int> &player_value_card_points, 
                                               std::vector<int> &player_rank_points, bool check_print, bool pve_mode) {

    // Map for ranks and suits
    std::map<int, std::string> rank_map = {{1, "2"}, {2, "3"}, {3, "4"}, {4, "5"}, {5, "6"}, {6, "7"}, {7, "8"},
                                          {8, "9"}, {9, "10"}, {10, "J"}, {11, "Q"}, {12, "K"}, {13, "A"}};
    
    std::map<int, std::string> suit_map = {{0, "Spades"}, {1, "Clubs"}, {2, "Diamonds"}, {3, "Hearts"}};

    // Iterate through each player
    for (int player_index = 0; player_index < number_player; player_index++) {
        // Get the rank and suit of the card for each player
        int rank = ranks[player_index];   
        int suit = suits[player_index];   

        // Set player card points: rank for value, suit for comparison order
        player_value_card_points[player_index] = rank;
        player_rank_points[player_index] = suit;

        // Optionally print the player's card details
        if (check_print) {
            std::cout << "Player " << player_index + 1 << " got " 
                      << rank_map[rank] << " of " << suit_map[suit] << std::endl;
        }
    }
}

// Hàm trong chế độ Single Card Duel: Xác định lá bài mạnh hơn
bool is_stronger_between_2_cards(const Card& a, const Card& b) {
    if (a.value != b.value) {
        return a.value > b.value; // Compare value first
    }
    return a.suit > b.suit; // Compare suit if values are equal
}

// Function to determine the winner of a single-card duel
void determine_winner_Single_Card_Duel(
    int number_player,
    std::vector<int>& player_value_card_points,
    std::vector<int>& player_rank_points,
    std::vector<Player>& players
) {
    int max_points = 0;
    std::vector<int> winning_players;

    // Find the player with the highest points
    for (int i = 0; i < number_player; ++i) {
        if (player_value_card_points[i] > max_points) {
            max_points = player_value_card_points[i];
            winning_players.clear();
            winning_players.push_back(i);
        } else if (player_value_card_points[i] == max_points) {
            if (player_rank_points[i] > player_rank_points[winning_players[0]]) {
                winning_players.clear();
                winning_players.push_back(i);
            } else if (player_rank_points[i] == player_rank_points[winning_players[0]]) {
                winning_players.push_back(i);
            }
        }
    }

    // Map card values and suits to strings
    std::map<int, std::string> value_names = {{1, "2"}, {2, "3"}, {3, "4"}, {4, "5"}, {5, "6"}, {6, "7"}, {7, "8"},
                                          {8, "9"}, {9, "10"}, {10, "J"}, {11, "Q"}, {12, "K"}, {13, "A"}};
    std::map<int, std::string> suit_names = {{0, "Spades"}, {1, "Clubs"}, {2, "Diamonds"}, {3, "Hearts"}};

    std::cout << std::endl;

    // Handle single winner case
    if (winning_players.size() == 1) {
        int winner = winning_players[0];
        std::cout << "Player " << players[winner].number << " wins with " 
                  << value_names[player_value_card_points[winner]] << " of " 
                  << suit_names[static_cast<Suit>(player_rank_points[winner])] 
                  << "!" << std::endl;

        // Update player stats
        players[winner].total_games++;
        players[winner].wins++;
        players[winner].win_rate = (static_cast<float>(players[winner].wins) / players[winner].total_games) * 100;
        
        // Record win situation
        players[winner].win_situations[value_names[player_value_card_points[winner]] + " of " + 
                                       suit_names[static_cast<Suit>(player_rank_points[winner])]]++;
    }
    // Handle tie case
    else {
        std::cout << "It's a tie! The following players have won:\n";
        for (int winner : winning_players) {
            std::cout << "- Player " << players[winner].number << " with " 
                      << value_names[player_value_card_points[winner]] << " of " 
                      << suit_names[static_cast<Suit>(player_rank_points[winner])] 
                      << std::endl;

            // Update player stats
            players[winner].total_games++;
            players[winner].wins++;
            players[winner].win_rate = (static_cast<float>(players[winner].wins) / players[winner].total_games) * 100;
            
            // Record win situation
            players[winner].win_situations[value_names[player_value_card_points[winner]] + " of " + 
                                           suit_names[static_cast<Suit>(player_rank_points[winner])]]++;
        }
    }

    // Update stats for losing players
    for (int i = 0; i < number_player; ++i) {
        if (std::find(winning_players.begin(), winning_players.end(), i) == winning_players.end()) {
            players[i].total_games++;
            players[i].win_rate = (static_cast<float>(players[i].wins) / players[i].total_games) * 100;
        }
    }
}


// Hàm chạy chế độ Three Card Poker
void run_Three_Card_Poker() {
    std::cout << std::endl << "Welcome to Three Card Poker mode!" << std::endl;

    // Hỏi người chơi có muốn đọc hướng dẫn không
    std::cout << "Do you want to read the guide to playing the Three Card Poker mode game?" << std::endl;
    if (check_Yes_No_Input()) {
        // In hướng dẫn chơi chế độ Three Card Poker
        printThreeCardPokerGuide();
    }
    
    std::cout << std::endl;

    // Nhập số người chơi
    int number_player = input_number_of_players();

    // Khởi tạo mảng người chơi
    std::vector<Player> players(number_player);

    // Khởi tạo các người chơi mặc định
    std::cin.get();
    for (int i = 0; i < number_player; ++i) {
        players[i] = create_player(i + 1);
    }

    int cnt = 0;

    // Vòng lặp chơi
    do {
        // Bộ bài 52 lá
        std::vector<std::string> pack = return_pack();

        // Xáo bài
        std::vector<std::string> shuffled_pack = return_shuffled_pack(pack);

        // Chia bài cho người chơi
        std::vector<std::vector<std::string>> player_cards = deal_cards_Three_Card_Poker(shuffled_pack, number_player);

        // Tính điểm cho người chơi
        std::vector<int> player_points(number_player);
        for (int i = 0; i < number_player; ++i) {
            player_points[i] = calculate_player_score_Three_Card_Poker(player_cards[i]);
        }

        // In ra lá bài của người chơi
        print_all_player_cards(player_cards, number_player);

        // Xác định người chiến thắng
        std::vector<int> winners = determine_winners_Three_Card_Poker(players, player_cards);

        // In ra người chiến thắng
        std::cout << "Winner(s): ";
        for (int i = 0; i < winners.size(); ++i) {
            std::cout << "Player " << winners[i] + 1;
            if (i != winners.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;

        // In thông tin người chơi sau mỗi vòng
        std::cout << "\n==========================================================================================================" << std::endl;
        for (const auto& player : players) {
            print_player_info(player);
        }

        // Sau mỗi vòng chơi, hiển thị bảng xếp hạng
        leaderboard(players);

        // Tăng số lần chơi lên
        ++cnt;

        // Câu hỏi tiếp tục chơi chỉ được hỏi từ lần thứ 2 trở đi
        if (cnt > 0) {
            std::cout << "Do you want to continue playing? (Y/N): ";
        }

    } while (cnt == 0 || check_Yes_No_Input());

    // In thông tin người chơi sau khi chơi xong
    final_leaderboard(players);

    // Lưu thông tin người chơi vào file
    save_game_data_to_file("Three Card Poker", players);
}

// Hàm chia bài cho chế độ Three Card Poker
std::vector<std::vector<std::string>> deal_cards_Three_Card_Poker(std::vector<std::string>& shuffled_pack, int number_player) {
    // Mảng 2 chiều chứa bài của từng người chơi
    std::vector<std::vector<std::string>> player_cards(number_player);  
    
    // Mỗi người chơi sẽ nhận 3 lá bài
    int card_index = 0;
    for (int i = 0; i < number_player; ++i) {
        for (int j = 0; j < 3; ++j) {
            player_cards[i].push_back(shuffled_pack[card_index]);
            card_index++;
        }
    }

    return player_cards;
}

// Hàm tính điểm cho chế độ Three Card Poker
int calculate_player_score_Three_Card_Poker(std::vector<std::string>& player_cards) {
    int score = 0;

    // Hàm phụ để tính giá trị của một lá bài
    auto get_card_value = [](const std::string& card) -> int {
        // Lấy giá trị của lá bài (2 đến 10, Jack = 10, Queen = 10, King = 10, Ace = 1)
        if (card[0] == 'A') return 1;
        if (card[0] == 'K' || card[0] == 'Q' || card[0] == 'J' || card[0] == '1') return 10;
        return card[0] - '0';  // Đối với các lá bài số từ 2 đến 9
    };

    // Tính tổng điểm của 3 lá bài, chỉ lấy chữ số hàng đơn vị
    for (const std::string& card : player_cards) {
        score += get_card_value(card);
    }

    return score % 10;  // Chỉ lấy chữ số hàng đơn vị
}


// Function to determine the winners in Three Card Poker mode
std::vector<int> determine_winners_Three_Card_Poker(std::vector<Player>& players, std::vector<std::vector<std::string>>& player_cards) {
    std::vector<int> winners;
    std::vector<int> player_scores(players.size());
    enum Suit { Clubs, Diamonds, Hearts, Spades };

    // Map card values and suits to strings for printing
    std::map<int, std::string> value_names = {{2, "2"}, {3, "3"}, {4, "4"}, {5, "5"}, {6, "6"}, {7, "7"}, {8, "8"},
                                    {9, "9"}, {10, "10"}, {11, "J"}, {12, "Q"}, {13, "K"}, {14, "A"}};
    std::map<int, std::string> suit_names = {{Clubs, "Clubs"}, {Diamonds, "Diamonds"}, {Hearts, "Hearts"}, {Spades, "Spades"}};

    // Calculate the score for each player
    for (int i = 0; i < players.size(); ++i) {
        player_scores[i] = calculate_player_score_Three_Card_Poker(player_cards[i]);
    }

    // Find the highest score
    int max_score = *std::max_element(player_scores.begin(), player_scores.end());

    // Find all players with the highest score
    for (int i = 0; i < players.size(); ++i) {
        if (player_scores[i] == max_score) {
            winners.push_back(i);
            players[i].wins++;  // Update win count for the winner
        }
        players[i].total_games++;  // Update total games played
        players[i].win_rate = (float)players[i].wins / players[i].total_games * 100;  // Update win rate
    }

    // Print the results and update player stats for winners
    if (winners.size() == 1) {
        // Single winner
        int winner = winners[0];
        std::cout << "Player " << players[winner].number << " wins with score: " << player_scores[winner] << std::endl;

        // Record the win situation with score
        players[winner].win_situations["Won with score: " + std::to_string(player_scores[winner])]++;

    } else {
        // Tie case
        std::cout << "It's a tie! The following players have won with score " << max_score << ":\n";
        for (int winner : winners) {
            std::cout << "Player " << players[winner].number << " with cards: ";
            for (const std::string& card : player_cards[winner]) {
                std::cout << card << " ";
            }
            std::cout << "and score: " << player_scores[winner] << std::endl;

            // Record the win situation for each winner
            players[winner].win_situations["Tied with score: " + std::to_string(player_scores[winner])]++;
        }
    }

    return winners;
}


