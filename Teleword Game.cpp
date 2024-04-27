#include <iostream>
#include <fstream>
#include <windows.h>
#include<stdlib.h>
#include <conio.h>
#include <chrono>

using namespace std;

void ReadData(char grid[15][15], char getWords[500], int j, int i, int k, int m) {
	ifstream FileObj;
	FileObj.open("teleword_3.txt", ios::in);

	if (!FileObj) {
		cout << "There is no such file: ";
	}
	else {

		for (i = 0; i < 15; i++) {
			for (j = 0; j < 15; ) {

				FileObj >> grid[i][j];
				if (grid[i][j] >= 'A' && grid[i][j] <= 'Z') {
					cout << grid[i][j] << " ";
					j++;
				}
			}
			cout << endl;
		}
		cout << endl;
		k = 0;
		if (i == 15) {
			while (getWords[k] != '.') {
				FileObj >> getWords[k];
				cout << getWords[k];

				if (getWords[k] == ',') {
					cout << " ";
				}
				if (getWords[k] != '.') {
					k++;
				}
			}
		}
		k = 0;
		cout << endl;
		while (getWords[k] != '.') {
			if (getWords[k] >= 'a' && getWords[k] <= 'z') {
				getWords[k] = getWords[k] - 32;
				k++;
			}
			else if ((getWords[k] >= 'A' && getWords[k] <= 'Z') || getWords[k] == '.' || getWords[k] == ',') {
				k++;
			}
		}
		getWords[k] = '.';
	}
	cout << endl << endl;
	FileObj.close();
}


void horizontal_L2R(char words[], char grid[][15], int countlettercovered[15][15], int i, int m, int gridcol, int gridrow, int& count, int& h_lr, int heavyrow[15], int heavycol[]) {
	int num = gridcol + 2;
	for (int k = i + 1; k < m; k++) {
		if (words[k] == grid[gridrow][num]) {
			count++;
			num++;
		}
		else {
			count = 1;
			break;
		}
	}

	if (count == m) {
		heavyrow[gridrow]++;
		for (int t = gridcol; t < gridcol + m; t++) {
			countlettercovered[gridrow][t]++;
			heavycol[t]++;
		}
		h_lr++;
	}
}



void horizontal_R2L(char words[], char grid[][15], int countlettercovered[15][15], int i, int m, int gridcol, int gridrow, int& count, int& h_rl, int heavyrow[], int heavycol[]) {
	int num = gridcol - 2;
	for (int k = i + 1; k < m; k++) {
		if (words[k] == grid[gridrow][num]) {
			count++;
			num--;
		}
		else {
			count = 1;
			break;
		}
	}
	if (count == m) {
		heavyrow[gridrow]++;
		for (int t = gridcol; t > gridcol - m; t--) {
			countlettercovered[gridrow][t]++;
			heavycol[t]++;
		}
		h_rl++;
	}
}

void verticle_U2D(char words[], char grid[][15], int countlettercovered[15][15], int i, int m, int gridcol, int gridrow, int& count, int& v_ud, int heavyrow[], int heavycol[]) {
	int num = gridrow + 2;
	for (int k = i + 1; k < m; k++) {
		if (words[k] == grid[num][gridcol]) {
			count++;
			num++;
		}
		else {
			count = 1;
			break;
		}
	}
	if (count == m) {
		heavycol[gridcol]++;
		for (int t = gridrow; t < gridrow + m; t++) {
			countlettercovered[t][gridcol]++;
			heavyrow[t]++;
		}
		v_ud++;
	}
}

void verticle_D2U(char words[], char grid[][15], int countlettercovered[15][15], int i, int m, int gridcol, int gridrow, int& count, int& v_du, int heavyrow[], int heavycol[]) {
	int num = gridrow - 2;
	for (int k = i+1 ; k < m; k++) {
		if (words[k] == grid[num][gridcol]) {
			count++;
			num--;
		}
		else {
			count = 1;
			break;
		}
	}
	if (count == m) {
		heavycol[gridcol]++;
		for (int t = gridrow; t > gridrow - m; t--) {
			countlettercovered[t][gridcol]++;
			heavyrow[t]++;
		}
		v_du++;
	}
}

void diagonal_UnR(char words[], char grid[][15], int countlettercovered[15][15], int i, int m, int gridcol, int gridrow, int& count, int& d_ur, int heavyrow[], int heavycol[]) {
	int num1 = gridrow - 2;
	int num2 = gridcol + 2;
	for (int k = i + 1; k < m; k++) {
		if (words[k] == grid[num1][num2]) {
			count++;
			num1--;
			num2++;
		}
		else {
			count = 1;
			break;
		}
	}
	if (count == m) {
		for (int t = gridrow; t > gridrow - m; t--) {
			countlettercovered[t][gridcol]++;
			heavyrow[t]++;
			heavycol[gridcol]++;
			gridcol++;
		}
		d_ur++;
	}
}

void diagonal_UnL(char words[], char grid[][15], int countlettercovered[15][15], int i, int m, int gridcol, int gridrow, int& count, int& d_ul, int heavyrow[], int heavycol[]) {
	int num1 = gridrow - 2;
	int num2 = gridcol - 2;
	for (int k = i + 1; k < m; k++) {
		if (words[k] == grid[num1][num2]) {
			count++;
			num1--;
			num2--;
		}
		else {
			count = 1;
			break;
		}
	}
	if (count == m) {
		for (int t = gridrow; t > gridrow - m; t--) {
			countlettercovered[t][gridcol]++;
			heavyrow[t]++;
			heavycol[gridcol]++;
			gridcol--;
		}
		d_ul++;
	}
}

void diagonal_DnR(char words[], char grid[][15], int countlettercovered[15][15], int i, int m, int gridcol, int gridrow, int& count, int& d_dr, int heavyrow[], int heavycol[]) {
	int num1 = gridrow + 2;
	int num2 = gridcol + 2;
	for (int k = i + 1; k < m; k++) {
		if (words[k] == grid[num1][num2]) {
			count++;
			num1++;
			num2++;
		}
		else {
			count = 1;
			break;
		}
	}
	if (count == m) {
		for (int t = gridrow; t < gridrow + m; t++) {
			countlettercovered[t][gridcol]++;
			heavyrow[t]++;
			heavycol[gridcol]++;
			gridcol++;
		}
		d_dr++;
	}
}

void diagonal_DnL(char words[], char grid[][15], int countlettercovered[15][15], int i, int m, int gridcol, int gridrow, int& count, int& d_dl, int heavyrow[], int heavycol[]) {
	int num1 = gridrow + 2;
	int num2 = gridcol - 2;
	for (int k = i + 1; k < m; k++) {
		if (words[k] == grid[num1][num2]) {
			count++;
			num1++;
			num2--;
		}
		else {
			count = 1;
			break;
		}
	}
	if (count == m) {
		for (int t = gridrow; t < gridrow + m; t++) {
			countlettercovered[t][gridcol]++;
			heavyrow[t]++;
			heavycol[gridcol]++;
			gridcol--;
		}
		d_dl++;
	}
}

void colorgrid(int countlettercovered[][15], char grid[][15]) {
	HANDLE CC = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (countlettercovered[i][j] == 1) {
				SetConsoleTextAttribute(CC, 6);
				cout << grid[i][j] << " ";
			}
			else if (countlettercovered[i][j] == 2) {
				SetConsoleTextAttribute(CC, 1);
				cout << grid[i][j] << " ";
			}
			else if (countlettercovered[i][j] == 3) {
				SetConsoleTextAttribute(CC, 4);
				cout << grid[i][j] << " ";
			}
			else {
				SetConsoleTextAttribute(CC, 7);
				cout << grid[i][j] << " ";
			}
		}
		SetConsoleTextAttribute(CC, 7);
		cout << endl;
	}
}

void teleword(int countlettercovered[][15], char grid[15][15]) {

	cout << endl << "Teleword: ";
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (countlettercovered[i][j] == 0) {
				cout << grid[i][j];
			}
		}
	}
	cout << endl;
}

int main() {

	char grid[15][15] = {};
	int countlettercovered[15][15] = { 0 };
	char getWords[500] = {};
	int i = 0, j = 0, k = 0, m = 0, numofwords = 0, h_lr = 0, h_rl = 0, v_ud = 0, v_du = 0, d_ur = 0, d_dr = 0, d_ul = 0, d_dl = 0, scatterRow = 0, heavycol[15] = {}, heavyrow[15] = {};

	ReadData(grid, getWords, j, i, k, m);


	char option;
	cout << "1. Press S to solve the puzzle at once. \n2. Press T to solve the puzzle step by step. \n3. Press X to print puzzle statistics." << endl;
	cin >> option;
	auto startTime = std::chrono::steady_clock::now();

	k = 0;
	int L = 0;
	char words[15] = {};
	int count = 0, max = 0, min = 100000;

	while (getWords[L] != '.') {
		m = 0;
		while (getWords[L] != ',' && getWords[L] != '.') {
			words[m] = getWords[L];
			L++;
			m++;
		}
		if (getWords[L] == ',') {
			numofwords++;
		}
		if (m > max) {
			max = m;
		}
		if (m < min) {
			min = m;
		}

		count = 0;
		for (int gridrow = 0; gridrow < 15; gridrow++) {
			for (int gridcol = 0; gridcol < 15; gridcol++) {
				if (words[i] == grid[gridrow][gridcol]) {
					i++;
					count++;
					if (words[i] == grid[gridrow][gridcol + 1]) {
						count++;
						horizontal_L2R(words, grid, countlettercovered, i, m, gridcol, gridrow, count, h_lr, heavyrow, heavycol);
					}

					if (words[i] == grid[gridrow][gridcol - 1]) {
						count++;
						horizontal_R2L(words, grid, countlettercovered, i, m, gridcol, gridrow, count, h_rl, heavyrow, heavycol);
					}

					if (words[i] == grid[gridrow + 1][gridcol]) {
						count++;
						verticle_U2D(words, grid, countlettercovered, i, m, gridcol, gridrow, count, v_ud, heavyrow, heavycol);
					}

					if (words[i] == grid[gridrow - 1][gridcol]) {
						count++;
						verticle_D2U(words, grid, countlettercovered, i, m, gridcol, gridrow, count, v_du, heavyrow, heavycol);
					}

					if (words[i] == grid[gridrow - 1][gridcol + 1]) {
						count++;
						diagonal_UnR(words, grid, countlettercovered, i, m, gridcol, gridrow, count, d_ur, heavyrow, heavycol);
					}

					if (words[i] == grid[gridrow - 1][gridcol - 1]) {
						count++;
						diagonal_UnL(words, grid, countlettercovered, i, m, gridcol, gridrow, count, d_ul, heavyrow, heavycol);
					}

					if (words[i] == grid[gridrow + 1][gridcol + 1]) {
						count++;
						diagonal_DnR(words, grid, countlettercovered, i, m, gridcol, gridrow, count, d_dr, heavyrow, heavycol);
					}

					if (words[i] == grid[gridrow + 1][gridcol - 1]) {
						count++;
						diagonal_DnL(words, grid, countlettercovered, i, m, gridcol, gridrow, count, d_dl, heavyrow, heavycol);
					}

					else {
						i = 0;
						count = 0;
					}
					if (count == m) {
						break;
					}
				}
				else {
					i = 0;
					count = 0;
				}
			}
			if (count == m) {
				break;
			}
		}
		if (getWords[L] != '.') {
			L++;
		}
		if (option == 'T') {
			colorgrid(countlettercovered, grid);
			_getch();
		}

		if (option == 'T' && getWords[L] != '.') {
			system("cls");
		}

	}
	auto endTime = std::chrono::steady_clock::now();

	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			if (countlettercovered[i][j] == 0) {
				scatterRow++;
				break;
			}
		}
	}

	if (option == 'S') {
		colorgrid(countlettercovered, grid);
		cout << endl;
	}

	if (option == 'T' || option == 'S') {
		teleword(countlettercovered, grid);
	}
	int maxrow = heavyrow[0], heaviestRow = 0, maxcol = heavycol[0], heaviestCol = 0;
	for (i = 1; i < 15; i++) {
		if (heavyrow[i] > maxrow) {
			maxrow = heavyrow[i];
			heaviestRow = i;
		}
		if (heavycol[i] > maxcol) {
			maxcol = heavycol[i];
			heaviestCol = i;
		}
	}
	double TimeTaken = double(std::chrono::duration_cast <std::chrono::microseconds> (endTime - startTime).count());
	if (option == 'X') {
		colorgrid(countlettercovered, grid);
		teleword(countlettercovered, grid);
		cout << endl;
		cout << "Time Taken: " << TimeTaken << " microseconds" << endl;
		cout << "Longest Word Length: " << max << endl;
		cout << "Shortest Word Length: " << min << endl;
		cout << "Average Word Length: " << (L-numofwords) / (numofwords + 1) << endl;
		cout << "Word Distribution: " << endl;
		cout << '\t' << "Horizontal: " << h_rl + h_lr << " (" << h_lr << ", " << h_rl << ")" << endl;
		cout << '\t' << "Vertical: " << v_ud + v_du << " (" << v_ud << ", " << v_du << ")" << endl;
		cout << '\t' << "Diagonal: " << d_ur + d_dr + d_dl + d_ul << " (" << d_ur + d_dr << ", " << d_dl + d_ul << ")" << endl;
		cout << "Teleword Scatter: " << scatterRow << endl;
		cout << "Heaviest Row: " << heaviestRow << endl;
		cout << "Heaviest Column: " << heaviestCol << endl;
	}

	return 0;
}
