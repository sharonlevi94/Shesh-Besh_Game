#pragma once
//enum:
enum PLAYER_COLOR { WHITE, BLACK, NO_COLOR };
enum DICE_STATE { ROLL, PLAY, AI_TURN, DONE, START, ROLL_START};
enum DIRECTION { RIGHT, LEFT};
enum SOUND
{
	MENU,
	ROLL_SOUND,
	EAT,
	WONGAME,
	LOSTGAME,
	TIMEEND,
	BUTTON,
	PLAY_STEP
};

//-----------------------------------------------------------------------------

//general:
constexpr auto FRAME_LIMIT = 60;
constexpr auto NUM_OF_POINTS = 24;
constexpr auto NO_POINT_CLICKED = -1;
constexpr auto THINKING_TIME = 1000;
constexpr auto MUSIC_VOLUME = 50;

//-----------------------------------------------------------------------------

//dice:
constexpr auto DICE_SIZE = 40;
constexpr auto NUM1 = 2;
constexpr auto NUM2 = 3;
constexpr auto NUM3 = 4;
constexpr auto NUM4 = 5;
constexpr auto NUM5 = 6;
constexpr auto NUM6 = 7;

//-----------------------------------------------------------------------------

//buttons:
constexpr auto BUTTON_POS_X = 1390;
constexpr auto BUTTON_POS_Y = 375;
constexpr auto CHAR_SIZE = 45;

//-----------------------------------------------------------------------------

//texture files paths:
constexpr auto BOARD_PATH = "Board.png";
constexpr auto BLACK_PATH = "black.png";
constexpr auto WHITE_PATH = "white.png";
constexpr auto NUM1_PATH = "dice_numbers.png";
constexpr auto NUM2_PATH = "dice_numbers (2).png";
constexpr auto NUM3_PATH = "dice_numbers (3).png";
constexpr auto NUM4_PATH = "dice_numbers (4).png";
constexpr auto NUM5_PATH = "dice_numbers (5).png";
constexpr auto NUM6_PATH = "dice_numbers (6).png";

//sound files paths:
constexpr auto ROLL_SOUND_PATH = "dice_throw.ogg";
constexpr auto BUTTON_SOUND_PATH = "button_click.ogg";
constexpr auto PLAY_SOUND_PATH = "play_step.ogg";

//-----------------------------------------------------------------------------

//boards backgrounds:
constexpr auto BOARD1 = 1;
constexpr auto BOARD2 = 2;
constexpr auto BOARD3 = 3;
constexpr auto BOARD4 = 4;

//-----------------------------------------------------------------------------

//screen dimensions:
constexpr auto WIN_WIDTH = 1600;
constexpr auto WIN_HEIGHT = 800;

//-----------------------------------------------------------------------------

//checker;
constexpr auto RADIUS = 30;

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

//board:
constexpr auto BOARD_LEN = 24;
constexpr auto AI_HOME = 18;
constexpr auto PLAYER_HOME = 5;
constexpr auto BLOCK = 2;

//-----------------------------------------------------------------------------

//scores:
constexpr auto OPEN_HOME_NOT_FREE = 0;
constexpr auto EAT_HOME = 1;
constexpr auto OPEN_OUT_NOT_FREE = 2;
constexpr auto OPEN_FREE_OUT = 3;
constexpr auto EAT_OUT_NOT_FREE = 4;
constexpr auto EAT_OUT_FREE = 5;
constexpr auto OPEN_FREE_HOME = 6;
constexpr auto EBLOCK_HOME = 7;
constexpr auto EBLOCK_OUT = 8;
constexpr auto NBLOCK_OUT = 9;
constexpr auto NBLOCK_HOME = 10;
constexpr auto EAT_BLOCK_OUT = 11;
constexpr auto EAT_BLOCK_HOME = 12;

//-----------------------------------------------------------------------------

//probabilities
constexpr auto NUM_OF_OPTIONS = 12;
constexpr auto PROB_LIMIT = 0.3;
constexpr auto ONE = 0.305;
constexpr auto TWO = 0.333;
constexpr auto THREE = 0.361;
constexpr auto FOUR = 0.3888;
constexpr auto FIVE = 0.416;
constexpr auto SIX = 0.444;
constexpr auto SEVEN = 0.1667;
constexpr auto EIGHT = 0.1389;
constexpr auto NINE = 0.1111;
constexpr auto TEN = 0.0833;
constexpr auto ELEVEN = 0.0556;
constexpr auto TWELVE = 0.0278;
