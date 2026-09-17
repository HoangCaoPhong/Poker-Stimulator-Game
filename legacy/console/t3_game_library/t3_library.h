#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>            
#include <sstream>            
#include <map>                
#include <vector>             
#include <ctime>              
#include <algorithm>           
#include <iomanip>             
#include "52_cards.h"           // Thêm thư viện này để sử dụng các hàm liên quan đến bộ bài 52 lá
#include "game_database.h"      // Thêm thư viện này để sử dụng các hàm liên quan đến Database
#include "poker_desk.h"         // Thêm thư viện này để sử dụng các hàm liên quan đến giao diện game
#include "file_manipulation.h"  // Thêm thư viện này để sử dụng các hàm liên quan đến nhập xuất file
#include "gameMode.h"           // Thêm thư viện này để sử dụng các hàm liên quan đến chế độ game




//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================

//Mô tả: Thư viện này bao gồm tất cả thư viện con được dùng trong dự án Poker của Triple_Star team,

/*
Tác giả:
    + Hoàng Cao Phong
    + Nguyễn Trung Kiên
    + Võ Thúc Trí

Mọi sao chép và sử dụng nội dung trong thư viện này cần được sự đồng ý của nhóm tác giả
Vui lòng liên hệ với nhóm tác giả để liên hệ hợp tác!
*/

//Hướng dẫn sử dụng: 
    //Để sử dụng bộ thư viện này, bạn cần include thư viện này vào file của mình bằng cách thêm dòng lệnh sau:
    //#include "t3_game_library/t3_library.h"

/*Bộ thư viện này bao gồm các thư viện

    #include "52_cards.h"
    Mô tả: Thư viện này bao gồm các hàm liên quan đến việc khởi tạo và sử dụng bộ bài 52 lá

    #include "game_database.h"
    Mô tả: Thư viện này bao gồm các hàm liên quan đến việc xây dựng Database cho trò chơi

    #include "poker_desk.h"
    Mô tả: Thư viện này bao gồm các hàm liên quan đến việc nhập xuất và hiển thị thông tin

    #include "gameMode.h"
    Mô tả: Thư viện này bao gồm các hàm liên quan đến việc khởi tạo và thực thi các chế độ game

    #include "file_manipulation.h"
    Mô tả: Thư viện này bao gồm các hàm liên quan đến việc nhập xuất file

*/

//====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================


