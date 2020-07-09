#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
#include<sstream>
#include<vector>
#include<queue>
#include <windows.h>
#define NROUND 8
#define BOARD_WIDTH 4

using namespace std;

struct pos {
	int r;
	int c;
};

int mv[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };

void initialize_map(int chessboard[BOARD_WIDTH][BOARD_WIDTH]) {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			chessboard[i][j] = 0;
		}
	}
}

void print_map(int chessboard[BOARD_WIDTH][BOARD_WIDTH]) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << setw(4) << "";
	for (int j = 1; j <= BOARD_WIDTH; j++) {
		cout << setw(4) << j;
	}

	cout << endl;
	char c = 'A';
	for (int i = -1; i < BOARD_WIDTH; i++) {
		for (int j = -1;j< BOARD_WIDTH; j++) {
			if (i == -1) {
				cout << setw(4) << "____";
			}
			else if (j == -1) {
				cout << setw(3) << c<<'|';
				c++;
			}
			else {
				if (chessboard[i][j] == 0) {
					cout << setw(4) << "_";
				}
				else {
					if (chessboard[i][j] < 0) {
						SetConsoleTextAttribute(hConsole, 11);
						cout << setw(4) << -1 * chessboard[i][j];
						SetConsoleTextAttribute(hConsole, 7);
					}
					else {
						SetConsoleTextAttribute(hConsole, 12);
						cout << setw(4) << chessboard[i][j];
						SetConsoleTextAttribute(hConsole, 7);
					}
				}
			}
		}
		cout << endl;
	}
}

bool valid_input(int chessboard[BOARD_WIDTH][BOARD_WIDTH], string input, int& r, int& c) {
	vector<string>result;
	result.clear();
	stringstream ss(input);
	for (string s; ss >> s;) {
		result.push_back(s);
	}
	//check arguments
	if (result.size() != 2) {
		cout << "Invalid input: there should only be two arguments! However, you have entered "<<result.size()<<" arguments." << endl;
		return false;
	}
	//check rows
	if (result[0].length() != 1 || !(result[0][0] >= 'A' && result[0][0] <= 'A' + BOARD_WIDTH)) {
		cout << "Invalid input: row invalid" << endl;
		return false;
	}
	//check cols
	bool is_number = true;
	for (int i = 0; i < result[1].length(); i++) {
		if (!(result[1][i] >= '0' && result[1][i] <= '9')) {
			is_number = false;
			break;
		}
	}
	if (!is_number) {
		cout << "Invalid input: column invalid" << endl;
		return false;
	}
	//check if the pos already taken
	int row = (int)(result[0][0] - 'A');
	int col = stoi(result[1]);
	if (!(col >= 1 && col <= BOARD_WIDTH)) {
		cout << "Invalid input: column invalid" << endl;
		return false;
	}
	if (chessboard[row][col-1]!=0) {
		cout << "Invalid input: position already taken" << endl;
		return false;
	}

	r = row;
	c = col-1;
	//cout << r << " " << c << endl;
	return true;
}

void place_chess(int chessboard[BOARD_WIDTH][BOARD_WIDTH], int player_id, int chess_value, int r, int c) {
	if (player_id == 1) {
		chessboard[r][c] = chess_value;
	}
	else {
		chessboard[r][c] = -chess_value;
	}
}

void get_result(int chessboard[BOARD_WIDTH][BOARD_WIDTH]) {

	//Player one get Score
	int P1_MaxPieceCnt = 0;
	vector<int>P1_MaxPiece;
	int P1_MaxPieceScore = 0;
	queue<pos>P1_q;
	bool P1_visited[BOARD_WIDTH][BOARD_WIDTH];
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			P1_visited[i][j] = false;
		}
	}
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (P1_visited[i][j]) {
				continue;
			}
			else {
				if (chessboard[i][j] <= 0) {
					P1_visited[i][j] = true;
					continue;
				}
				else {
					pos root;
					root.r = i;
					root.c = j;
					P1_visited[i][j] = true;
					vector<int>temp_piece;
					int temp_score = chessboard[i][j];
					temp_piece.push_back(chessboard[i][j]);
					P1_q.push(root);
					while (!P1_q.empty()) {
						pos cur = P1_q.front();
						P1_q.pop();
						for (int k = 0; k < 4; k++) {
							pos nxt;
							nxt.r = cur.r + mv[k][0];
							nxt.c = cur.c + mv[k][1];
							//check range
							if (nxt.r < 0 || nxt.r >= BOARD_WIDTH || nxt.c < 0 || nxt.c >= BOARD_WIDTH) {
								continue;
							}
							//check if is allies
							if (chessboard[nxt.r][nxt.c] > 0 &&P1_visited[nxt.r][nxt.c]==false) {
								P1_q.push(nxt);
								temp_piece.push_back(chessboard[nxt.r][nxt.c]);
								temp_score += chessboard[nxt.r][nxt.c];
								P1_visited[nxt.r][nxt.c] = true;
							}
						}
					}

					if (temp_piece.size() > P1_MaxPieceCnt || (temp_piece.size() == P1_MaxPieceCnt && temp_score>P1_MaxPieceScore)) {
						P1_MaxPieceCnt = temp_piece.size();
						P1_MaxPiece.clear();
						for (int z = 0; z < temp_piece.size(); z++) {
							P1_MaxPiece.push_back(temp_piece[z]);
						}
						P1_MaxPieceScore = temp_score;
					}

				}
			}
		}
	}

	///////////////////////////////////////////////////////////////
	//Player two get score
	//Player one get Score
	int P2_MaxPieceCnt = 0;
	vector<int>P2_MaxPiece;
	int P2_MaxPieceScore = 0;
	queue<pos>P2_q;
	bool P2_visited[BOARD_WIDTH][BOARD_WIDTH];
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			P2_visited[i][j] = false;
		}
	}
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (P2_visited[i][j]) {
				continue;
			}
			else {
				if (chessboard[i][j] >= 0) {
					P2_visited[i][j] = true;
					continue;
				}
				else {
					pos root;
					root.r = i;
					root.c = j;
					P2_visited[i][j] = true;
					vector<int>temp_piece;
					int temp_score = chessboard[i][j];
					temp_piece.push_back(chessboard[i][j]);
					P2_q.push(root);
					while (!P2_q.empty()) {
						pos cur = P2_q.front();
						P2_q.pop();
						for (int k = 0; k < 4; k++) {
							pos nxt;
							nxt.r = cur.r + mv[k][0];
							nxt.c = cur.c + mv[k][1];
							//check range
							if (nxt.r < 0 || nxt.r >= BOARD_WIDTH || nxt.c < 0 || nxt.c >= BOARD_WIDTH) {
								continue;
							}
							//check if is allies
							if (chessboard[nxt.r][nxt.c] < 0 && P2_visited[nxt.r][nxt.c] == false) {
								P2_q.push(nxt);
								temp_piece.push_back(chessboard[nxt.r][nxt.c]);
								temp_score += chessboard[nxt.r][nxt.c];
								P2_visited[nxt.r][nxt.c] = true;
							}
						}
					}

					if (temp_piece.size() > P2_MaxPieceCnt || (temp_piece.size() == P2_MaxPieceCnt && temp_score < P2_MaxPieceScore)) {
						P2_MaxPieceCnt = temp_piece.size();
						P2_MaxPiece.clear();
						for (int z = 0; z < temp_piece.size(); z++) {
							P2_MaxPiece.push_back(temp_piece[z]);
						}
						P2_MaxPieceScore = temp_score;
					}

				}
			}
		}
	}
	///////////////////////////////////////////////
	// announce results
	cout << "The result of the game is :" << endl;

	cout << "Player 1:" << endl;
	cout << "Max Piece Size: " << P1_MaxPieceCnt << endl;
	cout << "Including: " << endl;
	for (int i = 0; i < P1_MaxPiece.size(); i++) {
		cout << P1_MaxPiece[i] << " ";
	}
	cout << endl;
	cout << "Final Score: " << P1_MaxPieceScore << endl;
	cout << endl;

	cout << "Player 2:" << endl;
	cout << "Max Piece Size: " << P2_MaxPieceCnt << endl;
	cout << "Including: " << endl;
	for (int i = 0; i < P2_MaxPiece.size(); i++) {
		cout << -1* P2_MaxPiece[i] << " ";
	}
	cout << endl;
	cout << "Final Score: " << -1* P2_MaxPieceScore << endl;
	cout << endl;

	P2_MaxPieceScore = -1 * P2_MaxPieceScore;
	if (P1_MaxPieceScore > P2_MaxPieceScore) {
		cout << "Player 1 wins!" << endl;
	}
	else if (P1_MaxPieceScore < P2_MaxPieceScore) {
		cout << "Player 2 wins!" << endl;
	}
	else {
		cout << "It's a tie!" << endl;
	}
}

int sample_chess1[BOARD_WIDTH][BOARD_WIDTH] = {
	{8,-4,5,6},
	{-6,-3,-2,7},
	{-7,3,4,-5},
	{1,2,-1,-8}
};

int sample_chess2[BOARD_WIDTH][BOARD_WIDTH] = {
	{1,2,-6,-7},
	{4,-5,5,-8},
	{-3,-4,7,8},
	{3,6,-1,-2}
};
void game_explanation() {
	cout << "Rules: \n";
	cout << "1. Two players take turns placing chess on the board \n";
	cout << "2. Each chess is marked with a number that represents its value.Both players will start with chess 1 to chess 8.\n";
	cout << "3. Two chess is said to be connected if they are adjacent(on the left, right, top, or bottom side of each other).\n";
	cout << "4. After all the chess is placed, the score of each player will be the sum of all the chess¡¦ value in the ¡§largest connected component in terms of area.\n";
	cout << "5. If there's more than one 'largest connected component', the score will be the one with the largest value.\n";
	cout << "6. The player with a higher score will win\n";
	cout << endl;
	cout << "Example 1:" << endl;
	print_map(sample_chess1);
	//get_result(sample_chess1);
	cout << "In this example, Player 1(Red) has a score of 10 (1+2+3+4) while Player 2(Blue) has a score of 22(2+3+4+6+7)" << endl;
	cout << "Note that even though Player 1 has another connected component with value 18(5+6+7), which is bigger than 10, the final score is still 10 cause it has more chess (4 vs. 3)" << endl;

	cout << endl;
	cout << "Example 2:" << endl;
	print_map(sample_chess2);
	//get_result(sample_chess1);
	cout << "In this example, Player 1(Red) has a score of 20 (5+7+8) while Player 2(Blue) has a score of 19(6+7+8)" << endl;
	cout << "Note that even though Player 1 has another connected component with same size (1+2+4), the final score is still 20 because it's higher" << endl;
}