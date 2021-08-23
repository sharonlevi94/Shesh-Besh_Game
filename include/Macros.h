#pragma once
//general:
enum PLAYER_COLOR { WHITE, BLACK, NO_COLOR };
enum DICE_STATE { ROLL, PLAY, AI_TURN, DONE, START, ROLL_START};
enum DIRECTION { RIGHT, LEFT};
constexpr auto FRAME_LIMIT = 60;
constexpr auto NUM_OF_POINTS = 24;
constexpr auto NO_POINT_CLICKED = -1;
//dice:
constexpr auto DICE_SIZE = 40;
constexpr auto NUM1 = 2;
constexpr auto NUM2 = 3;
constexpr auto NUM3 = 4;
constexpr auto NUM4 = 5;
constexpr auto NUM5 = 6;
constexpr auto NUM6 = 7;
//buttons:
constexpr auto BUTTON_POS_X = 1390;
constexpr auto BUTTON_POS_Y = 375;
constexpr auto CHAR_SIZE = 45;
//paths:
constexpr auto BOARD_PATH = "Board.png";
constexpr auto BLACK_PATH = "black.png";
constexpr auto WHITE_PATH = "white.png";
constexpr auto NUM1_PATH = "dice_numbers.png";
constexpr auto NUM2_PATH = "dice_numbers (2).png";
constexpr auto NUM3_PATH = "dice_numbers (3).png";
constexpr auto NUM4_PATH = "dice_numbers (4).png";
constexpr auto NUM5_PATH = "dice_numbers (5).png";
constexpr auto NUM6_PATH = "dice_numbers (6).png";

//boards backgrounds:
constexpr auto BOARD1 = 1;
constexpr auto BOARD2 = 2;
constexpr auto BOARD3 = 3;
constexpr auto BOARD4 = 4;
//screen dimensions:
constexpr auto WIN_WIDTH = 1600;
constexpr auto WIN_HEIGHT = 800;
//checker;
constexpr auto RADIUS = 30;
//points:
constexpr auto TOP = 40;
constexpr auto BOTTOM = 700;
constexpr auto LEFT_CORNER = 235;
constexpr auto HOME_LEFT = 850;
constexpr auto DIFF = 88;
constexpr auto RIGHT_CORNER = HOME_LEFT + (DIFF * 5);

constexpr auto POINT_AREA_X = RADIUS * 2;
constexpr auto POINT_AREA_Y = RADIUS * 10;
constexpr auto AREA_POS_BOT = BOTTOM - (RADIUS * 8);
//board:
constexpr auto BOARD_LEN = 24;
