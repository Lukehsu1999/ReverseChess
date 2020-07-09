#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
#include<sstream>
#include<vector>
#define NROUND 8
#define BOARD_WIDTH 4
using namespace std;

void initialize_map(int chessboard[BOARD_WIDTH][BOARD_WIDTH]);
void print_map(int chessboard[BOARD_WIDTH][BOARD_WIDTH]);
void place_chess(int chessboard[BOARD_WIDTH][BOARD_WIDTH],int player_id, int chess_value, int r, int c);
bool valid_input(int chessboard[BOARD_WIDTH][BOARD_WIDTH],string input, int& r, int& c);
void get_result(int chessboard[BOARD_WIDTH][BOARD_WIDTH]);
void game_explanation();