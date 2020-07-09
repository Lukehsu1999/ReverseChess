#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
#include<vector>
#include<windows.h>
#include"GameFunctions.h"
#define NROUND 8
#define BOARD_WIDTH 4

/*
Board_size = BOARD_WIDTH^2
NROUND = Board_size/2
*/

using namespace std;

//global variables
int chessboard[BOARD_WIDTH][BOARD_WIDTH];

//global functions


int main() {
	game_explanation();
replay:
	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Game started!!!" << endl;
	initialize_map(chessboard);
	for (int R = 1; R <= NROUND; R++) {
		cout << "It's round " << R << endl;
		cout << endl;
		print_map(chessboard);
		cout << endl;

	P1_restart:
		cout << "Player 1 (Red)'s turn" << endl;
		cout << "Please input the location you want to place your chess (ex.A 1 )" << endl;
		string P1_input="";
		getline(cin,P1_input);
		int P1_r, P1_c;
		if (!valid_input(chessboard,P1_input, P1_r, P1_c)) {
			goto P1_restart;
		}
		place_chess(chessboard, 1, R, P1_r, P1_c);

		print_map(chessboard);
		cout << endl;

	P2_restart:
		cout << "Player 2 (Blue)'s turn" << endl;
		cout << "Please input the location you want to place your chess (ex.A 1 )" << endl;
		string P2_input="";
		getline(cin, P2_input);
		int P2_r, P2_c;
		if (!valid_input(chessboard, P2_input, P2_r, P2_c)) {
			cout << "please input again!" << endl;
			cout<< endl;
			goto P2_restart;
		}
		place_chess(chessboard, 2, R, P2_r, P2_c);

		cout << "--------------------------------------------------------------------------------" << endl;
		cout << endl;
	}
	get_result(chessboard);
	
	cout << "Replay? y/n" << endl;
	char ans;
	cin >> ans;
	if (ans == 'y') {
		goto replay;
	}
}