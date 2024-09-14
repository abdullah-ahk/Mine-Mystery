#include<iostream>
#include <fstream>
#include <string>
#include <utility>
#include <ctime>
#include <conio.h>
using namespace std;

//global
int gridsize = 0, totalmines = 0, mine = 0, jol, movesleft = 0; 
time_t ini = time(NULL);

//prototypes for minesweeper
bool inRange(int row, int col, int gridsize);
bool isMine(char** realarray, int gridsize, int row, int col);
bool opened(char** fakearray, int gridsize, int row, int col);
bool random(int randomRow, int randomCol, int* checkerRow, int totalmines, int* checkerCol,int i);
//bool win(char** fakearray, char** realarray, int gridsize, int totalmines, int row, int col);
void diffselector(int& gridsize, int& totalmines, int&movesleft);
void iniarray(char** realarray, char** fakearray, int gridsize);
void placemines(char** realarray, int gridsize, int totalmines);
int	checkadjacentmines(char** realarray, int gridsize, int row, int col, int mine);
void printboard(char** fakearray, int gridsize);
void input(char** fakearray, char** realarray, int gridsize, int& row, int& col);
int playgamerepeatedly(char** fakearray, char** realarray, int gridsize, int mine, int row, int col, int& movesleft);
void showmines(char** realarray, char** fakearray, int gridsize);
int exchangecell(char** realarray, int gridsize, int& row, int& col);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//prototypes for login
void login();
int Registration(bool &exitlogin);
int Login(bool& exitlogin);
int ForgotPassword(bool& exitlogin);
void initialtime();
void lines();
/////////////////////////////////

 struct Minesweeper {

	 string userID;
	 string PASS;
	 string enteredusername;
	 string enteredpassword;
	 string forgotuser;
	 int initialtime = 0;
	 int count = 0;
	 int initialcore = 0;
	 int totalscore = 0;
	 int Newtotalscore = 0;
 };
 Minesweeper Player;
 
 ////////LOGIN////////////

 int readfile() {
	 Minesweeper Player;
	 ifstream Myfile;
	 Myfile.open("playerrecords.txt", ios::in);

	 if (!Myfile) {
		 cout << "File not opened";
	 }
	 else {
		 while (Myfile >> Player.userID >> Player.PASS) {
			 cout << Player.userID << " " << Player.PASS << endl;
		 }
		 Myfile.close();
	 }
	 return 0;
 }
 /////////////////

 int writefile(const Minesweeper& Player) {
	 ofstream Myfile;
	 Myfile.open("playerrecords.txt", ios::app);
	 if (!Myfile) {
		 cout << "File not opened";
	 }
	 else {
		 Myfile << Player.enteredusername << ' ' << Player.enteredpassword << ' ' << Player.totalscore << endl;
		 Myfile.close();
	 }
	 return 0;
 }

 int readfile(Minesweeper& Player, int choose) {
	 bool userFound = false;
	 
	 ifstream Myfile;
	 Myfile.open("playerrecords.txt", ios::in | ios::app);

	 if (!Myfile) {
		 cout << "File not opened";
	 }
	 else {
		 while (Myfile >> Player.userID >> Player.PASS) {
			 switch (choose) {
			 case 1:
				 if (Player.userID == Player.enteredusername && Player.PASS == Player.enteredpassword) {
					 Player.count = 1;
					 break;
				 }
				 break;

			 case 3:
				 if (Player.userID == Player.forgotuser) {
					 cout << "\nCongrats, Your account was found, Please enter a new password: ";
					 cin >> Player.enteredpassword;
					 writefile(Player);
					 bool exitlog = true;
					 return exitlog;
					 userFound = true;
					 break;
				 }

			 default:
				 break;
			 }
		 }
		 if (choose == 3 && !userFound) {
			 cout << "\nAccount not found";
		 }
		 Myfile.close();
	 }
	 return 0;
 }


 int Login(bool & exitlogin) {
	 Minesweeper Player;
	 int choose = 1;

	 cin.ignore();
	 cout << "Please Enter Your Username: ";
	 getline(cin, Player.enteredusername);
	 if (Player.enteredusername=="admin")
	 {
		 cout << "Login Successful! Welcome Back " << Player.enteredusername << endl;
		 exitlogin = true;
		 Player.totalscore = 1;
		 return 0;
	 }

	 cout << "Enter your password: ";
	 getline(cin, Player.enteredpassword);

	 readfile(Player, choose);

	 if (Player.count == 1) {
		 cout << "Login Successful! Welcome Back " << Player.enteredusername << ". Your Highscore is: " << Player.totalscore << endl;
		 exitlogin = true;
	 }
	 else {
		 system("CLS");
		 cout << "Invalid Username Or Password. Login failed" << endl;
		 exitlogin = false;

	 }

	 return 0;
 }


 int Registration(bool &exitlogin) {
	 Minesweeper Player;
	 cin.ignore();
	 int choose = 2;

	 cout << "Please Enter Your Username:" << endl;
	 getline(cin, Player.enteredusername);

	 cout << "Enter your password:" << endl;
	 getline(cin, Player.enteredpassword);

	 writefile(Player);
	 readfile(Player, choose);

	 cout << "Registration Is Successful!" << endl;
	 exitlogin = true;
	 return 0;
 }

 int ForgotPassword(bool & exitlogin) {
	 Minesweeper Player;

	 int choose = 3;

	 cout << "Enter the username that you remember:" << endl;
	 cin >> Player.forgotuser;
	 exitlogin = readfile(Player, choose);

	 return 0;
 }

 
 void Scorecard(Minesweeper& Player) {
	 time_t currentTime;
	 time(&currentTime);
	 tm gottime;

	 if (localtime_s(&gottime, &currentTime) == 0) {
		 int mins = 0, hours = 0, secs = 0;
		 hours = gottime.tm_hour * 3600;
		 mins = gottime.tm_min * 60;
		 secs = gottime.tm_sec;

		 int elapsedTime = hours + secs + mins - Player.initialtime;

		 cout << "You have finished your game in: " << elapsedTime / 3600 << "h:"
			 << (elapsedTime % 3600) / 60 << "m:" << elapsedTime % 60 << "s" << endl;

		 Player.totalscore = elapsedTime;


		/*	 while (input >> Player.totalscore) {
			 if (Player.Newtotalscore > Player.totalscore) {
				 Player.count = 1;
				 break;
			 }
		 }*/
		 writefile(Player);
			 cout << "Congratulations! Your New Minesweeper Score Is " << Player.totalscore << endl;
		 
	 }
	 else {
		 cout << "Error getting local time" << endl;
	 }
 }


 void lines() {
	 for (int i = 0; i < 30; i++) {
		 cout << '=';
	 }
	 cout << endl;
 }



void login() {
	string username, password, userID, PASS, NEWusername, NEWpassword, Fusername, FuserID, Fpass;
	int choice, count = 0;
	string mychoice;
	bool exitlogin = false;
	do
	{
		lines();
		cout << "  Welcome to Minesweeper! " << endl;
		lines();
		cout << "      Menu      " << endl;
		lines();
		cout << " Press 1 to Login: " << endl;
		cout << " Press 2 to Register: " << endl;
		cout << " Press 3 If you have forgotten your password: " << endl;
		cout << " Press 4 to Exit" << endl;
		cout << " Please Enter Your Choice " << endl;
		lines();
		
		cin >> mychoice;

		choice = atoi(mychoice.c_str());

		if (choice == 0 && mychoice != "0") {
			cout << "\nINVALID INPUT. Please enter a number." << endl;
			continue;     
		}
		

		switch (choice) {
		case 1:
			lines();
			Login(exitlogin);
			lines();
			break;
		case 2:
			lines();
			Registration(exitlogin);
			lines();
			break;
		case 3:
			lines();
			ForgotPassword(exitlogin);
			lines();
			break;
		case 4:
			cout << "Thank You!" << endl;
			exit(EXIT_SUCCESS);
			break;
		default:
			cout << "Please Select from the options given on your screen" << endl;
		}

	} while (exitlogin == false);

}

/////////////////////////////////////////////
void initialtime() {
	time_t currentTime;
	time(&currentTime);
	tm gottime;

	if (localtime_s(&gottime, &currentTime) == 0) {
		int mins = 0, hours = 0, secs = 0;
		hours = gottime.tm_hour * 3600;
		mins = gottime.tm_min * 60;
		secs = gottime.tm_sec;

		Player.initialtime = hours + secs + mins;
	}
	else {
		cout << "Error getting local time" << endl;
	}
}
////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////

int tutorial() {
	if (Player.totalscore == 0) {
		char choice;
		do {
			string display =
				"    a b c\n"
				"  +-----+\n"
				"a |- - -|\n"
				"b |- - -|\n"
				"c |- - -|\n"
				"  +-----+";

			string displaymine =
				"    a b c\n"
				"  +-----+\n"
				"a |- - -|\n"
				"b |- * -|\n"
				"c |- - -|\n"
				"  +-----+";

			string nearmine =
				"    a b c\n"
				"  +-----+\n"
				"a |- - -|\n"
				"b |1 - -|\n"
				"c |- - -|\n"
				"  +-----+";

			cout << "\n^ Welcome to the Minesweeper Game!" << endl;
			cout << "Objective: Uncover all cells without mines." << endl;
			cout << "Commands:" << endl;
			cout << "- 'T': Choose to play the tutorial" << endl;
			cout << "- 'Q': Skip the tutorial" << endl;
			cout << "Let's get started!" << endl;

			cin >> choice;
			if (choice == 'Q') {
				system("CLS");
				return 0;
			}

			else if (choice == 'T') {
				system("CLS");
				cout << "The Minesweeper game is simple yet requires skill and a bit of luck. We'll teach you the basics." << endl
					<< "- First, select the difficulty level or create a custom board size." << endl
					<< "- You'll be presented with a 3x3 grid for this tutorial:" << endl;
				cout << display << endl;
				cout << "- The letters outside are the columns, while the dashes inside are unrevealed cells. Input the cell coordinates, e.g., 'a b': ";
				char z, x;
				do {
					cin >> z >> x;
				} while (z != 'a' && x != 'b');

				cout << endl << nearmine << endl << "- Great! Now, notice the number in the cell you revealed? It indicates the number of mines in a 1x1 radius." << endl
					<< "Now try pressing the letters 'b b' in succession: ";
				do {
					cin >> z >> x;
				} while (z != 'b' && x != 'b');

				cout << displaymine << "\nGame Over! Your Highscore is 0." << endl << endl
					<< "Oops! You struck a mine and lost the game, but don't worry, this was just the tutorial." << endl
					<< "I hope you are ready for the real challenge! Remember, the faster you win, the better your score. Good luck, player!";
				system("CLS");
				return 0;
			}
			else {
				cout << "\nEnter valid choice.";
			}
		} while (choice != 'T');
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////

//used to check for duplicates in input method
bool random(int randomRow, int randomCol, int* checkerRow, int totalmines, int* checkerCol, int i)
{
	for (int k = 0; k < i; k++)
	{
		if (checkerRow[k] == randomRow && checkerCol[k] == randomCol)
		{
			return true;
		}
	}
	return false;
}

//used to replace mine
int exchangecell(char** realarray, int gridsize, int &row, int &col)
{
	for (int i = 0; i < gridsize;i++) {
		for (int j = 0; j < gridsize; j++)
		{
			if (realarray[i][j] != '*')
			{
				realarray[i][j] = '-';
				realarray[row][col] = '*';
				return 0;
			}
		}
	}
	return 0;
}

//check if cell opened
bool opened(char** fakearray, int gridsize, int row, int col)
{
	if (inRange(row, col, gridsize) == true) {
		if (fakearray[row][col] == '-')
		{
			return false;
		}
		return true;
	}
	return true;
}

//check if cell is valid
bool inRange(int row, int col, int gridsize)
{
	if ((row >= 0) && (row < gridsize) && (col >= 0) && (col < gridsize))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//check is cell is a mine
bool isMine(char** realarray, int gridsize, int row, int col)
{
	if (realarray[row][col] == '*')
	{
		return(true);
	}
	else {
		return(false);
	}
}

//dificulty selector
void diffselector(int& gridsize, int& totalmines,int& movesleft)
{
	char option;
	string myoption;
	lines();
	cout << "Select the difficulty level" << endl << "1) Easy 'e' (16x16 grid & 40 mines) \n2) Medium 'm' (10x10 grid & 30 mines) \n3) Hard 'h' (6x6 grid, one life) \n4)Feeling crazy! 'c' " << endl;

	do {
		cin >> myoption;
	} while (!(myoption == "e" || myoption == "m" || myoption == "h" || myoption == "c"));

	option = myoption[0];

	lines();
	switch (option)
	{
	case 'e':
		gridsize = 16;
		totalmines = 40;
		movesleft = (gridsize * gridsize) - totalmines;		
		break;
	case 'm':
		gridsize = 10;
		totalmines = 30;
		movesleft = (gridsize * gridsize) - totalmines;		
		break;
	case 'h':
		gridsize = 6;
		totalmines = 35;
		movesleft = (gridsize * gridsize) - totalmines;
		break;

	case 'c':
		cout << "So you want to create your own custom grid?\nThen please enter your preferred grid size: ";
		cin >> gridsize;
		do {
			cout << "Please enter the number of mines you would like to add(less than or equal to your gridsize): ";
			cin >> totalmines;
		} while (totalmines > pow(gridsize,2) && totalmines < 0);
	}
}



//initializing real board
void iniarray(char** realarray, char** fakearray, int gridsize) {

	// Assign all the cells as mine-free
	for (int i = 0; i < gridsize; i++)
	{
		for (int j = 0; j < gridsize; j++)
		{
			realarray[i][j] = '-';
			fakearray[i][j] = '-';
		}
	}
}

//placing mines
void placemines(char** realarray, int gridsize, int totalmines)
{
		//temp dynamic array
		int* checkerRow = new int[totalmines];
		int* checkerCol = new int[totalmines];

		for (int i = 0; i < totalmines; i++) {
			int randomRow = rand() % gridsize;
			int randomCol = rand() % gridsize;

			while (random(randomRow, randomCol, checkerRow, totalmines, checkerCol, i)==true) {
				randomRow = rand() % gridsize;
				randomCol = rand() % gridsize;
			}

			checkerRow[i] = randomRow;
			checkerCol[i] = randomCol;

			// Place the mine in the selected cell
			realarray[randomRow][randomCol] = '*';
		}

		delete[] checkerRow;
		delete[] checkerCol;
	
}

//checking adjacent mines
int	checkadjacentmines(char** realarray, int gridsize, int row, int col, int mine)
{
	mine = 0;
	//north
	if (inRange(row - 1, col, gridsize) == true)
	{
		if (isMine(realarray, gridsize, row - 1, col) == true)
		{
			mine++;
		}
	}
	//north-east
	if (inRange(row - 1, col + 1, gridsize) == true)
	{
		if (isMine(realarray, gridsize, row - 1, col + 1) == true)
		{
			mine++;
		}
	}
	//north-west
	if (inRange(row - 1, col - 1, gridsize) == true)
	{
		if (isMine(realarray, gridsize, row - 1, col - 1) == true)
		{
			mine++;
		}
	}
	//east
	if (inRange(row, col + 1, gridsize) == true)
	{
		if (isMine(realarray, gridsize, row, col + 1) == true)
		{
			mine++;
		}
	}
	//west
	if (inRange(row, col - 1, gridsize) == true)
	{
		if (isMine(realarray, gridsize, row, col - 1) == true)
		{
			mine++;
		}
	}
	//south
	if (inRange(row + 1, col, gridsize) == true)
	{
		if (isMine(realarray, gridsize, row + 1, col) == true)
		{
			mine++;
		}
	}
	//south-east
	if (inRange(row + 1, col + 1, gridsize) == true)
	{
		if (isMine(realarray, gridsize, row + 1, col + 1) == true)
		{
			mine++;
		}
	}
	//south-west
	if (inRange(row + 1, col - 1, gridsize) == true)
	{
		if (isMine(realarray, gridsize, row + 1, col - 1) == true)
		{
			mine++;
		}
	}
	return (mine);
}

//DISPLAY
void printboard(char** fakearray, int gridsize) {

	// guides
	char* guiderow = new char[gridsize];
	char* guidecol = new char[gridsize];

	// Fill gr and gc
	for (int i = 0; i < gridsize; ++i) {
		guiderow[i] = (char)i + 'a';
	}

	for (int i = 0; i < gridsize; ++i) {
		guidecol[i] = (char)i + 'a';
	}
	lines();
	// outputting guides with border

	cout << "   ";
	for (int i = 0; i < gridsize; i++) {
		cout << guiderow[i] << " ";
	}

	cout << endl<<"  +";
	for (int i = 0; i < gridsize; i++) {
		cout << "--";
	}
	cout << "+" << endl;


	for (int i = 0; i < gridsize; i++) {
		cout << guidecol[i] << " |";
		for (int j = 0; j < gridsize; j++) {
			cout << fakearray[i][j] << " ";
		}
		cout << "|" << endl;
	}

	cout << "  +";
	for (int i = 0; i < gridsize; i++) {
		cout << "--";
	}
	cout << "+" << endl;

	delete[] guiderow;
	delete[] guidecol;
}

//getinput from user
void input(char** fakearray, char** realarray, int gridsize, int& row, int& col) {

	char inputRow, inputCol;

	do {
		cout << "Please enter your row and col (a, b, c, ...): ";
		cin >> inputRow >> inputCol;
		inputRow = tolower(inputRow);
		inputCol = tolower(inputCol);

		if (inputRow == 'q' && inputCol== 'w')
		{
			showmines(realarray, fakearray, gridsize);
		}

		// Convert the row input to an integer ( 'a' is mapped to 0)
		row = (int)inputRow - 'a';
		col = (int)inputCol - 'a';

	} while (inRange(row, col, gridsize) == false && opened(fakearray, gridsize, row, col) == true);
}


//RECURSIVE WAY TO REVEAL CELLS AND CHECK FOR MINES
int playgamerepeatedly(char** fakearray, char** realarray, int gridsize, int mine, int row, int col, int &movesleft)
{
	if (fakearray[row][col] != '-')
		return (false);

	if (realarray[row][col] == '*')
	{
		fakearray[row][col] = '*';

		for (int i = 0; i < gridsize; i++)
			for (int j= 0; j < gridsize; j++)
			{
				fakearray[i][j] = '*';
			}
		printboard(fakearray, gridsize);
		cout << "\nGame Over!\n" << "Your Highscore is " << Player.totalscore;
		return true;
	}
	else {
		int track = checkadjacentmines(realarray, gridsize, row, col, mine);
		fakearray[row][col] = (char)track + '0';
		movesleft--;

		if (track == 0)
		{

			//north
			if (inRange(row - 1, col, gridsize) == true)
			{
				if (isMine(realarray, gridsize, row - 1, col) == false)
					playgamerepeatedly(fakearray, realarray, gridsize, mine, row - 1, col, movesleft);
			}

			//south
			if (inRange(row + 1, col, gridsize) == true)
			{
				if (isMine(realarray, gridsize, row + 1, col) == false)
					playgamerepeatedly(fakearray, realarray, gridsize, mine, row + 1, col, movesleft);
			}

			//east
			if (inRange(row, col + 1, gridsize) == true)
			{
				if (isMine(realarray, gridsize, row, col + 1) == false)
					playgamerepeatedly(fakearray, realarray, gridsize, mine, row, col + 1, movesleft);
			}

			//west
			if (inRange(row, col - 1, gridsize) == true)
			{
				if (isMine(realarray, gridsize, row, col - 1) == false)
					playgamerepeatedly(fakearray, realarray, gridsize, mine, row, col - 1, movesleft);
			}

			//n-east
			if (inRange(row - 1, col + 1, gridsize) == true)
			{
				if (isMine(realarray, gridsize, row - 1, col + 1) == false)
					playgamerepeatedly(fakearray, realarray, gridsize, mine, row - 1, col + 1, movesleft);
			}

			//n-west
			if (inRange(row - 1, col - 1, gridsize) == true)
			{
				if (isMine(realarray, gridsize, row - 1, col - 1) == false)
					playgamerepeatedly(fakearray, realarray, gridsize, mine, row - 1, col - 1, movesleft);
			}

			//s-east
			if (inRange(row + 1, col + 1, gridsize) == true)
			{
				if (isMine(realarray, gridsize, row + 1, col + 1) == false)
					playgamerepeatedly(fakearray, realarray, gridsize, mine, row + 1, col + 1, movesleft);
			}

			//s-west
			if (inRange(row + 1, col - 1, gridsize) == true)
			{
				if (isMine(realarray, gridsize, row + 1, col - 1) == false)
					playgamerepeatedly(fakearray, realarray, gridsize, mine, row + 1, col - 1, movesleft);
			}
		}
	}


	return (false);
}

//main game
int playminesweeper() {
	//--------------dynamic fake array---------------------//
	char** fakearray = new char* [gridsize];
	for (int i = 0; i < gridsize; ++i) {
		fakearray[i] = new char[gridsize];
	}
	//--------------dynamic real array---------------------//
	char** realarray = new char* [gridsize];
	for (int i = 0; i < gridsize; i++) {
		realarray[i] = new char[gridsize];
	}
	//--------------------------------------//
	int  row = 1, col = 1;


	iniarray(fakearray, realarray, gridsize);
	placemines(realarray, gridsize, totalmines);

	bool gameover = false;
	int OngoingMove = 0;
	while (gameover == false) {
		system("CLS");
		printboard(fakearray, gridsize);
		input(fakearray, realarray, gridsize, row, col);

		if (OngoingMove == 0)
		{
			if (isMine(realarray, gridsize, row, col))
			{
				exchangecell(realarray,gridsize,row,col);
			}
		}
		OngoingMove = 1;

		gameover = playgamerepeatedly(fakearray, realarray, gridsize, mine, row, col, movesleft);

		if ((gameover == false) && (movesleft == 0))
		{

			lines();
			cout << endl;
			for (int i = 0; i < gridsize; i++)
			{
				for (int j = 0; j < gridsize; j++) {

					fakearray[i][j] = realarray[i][j];
				}
			}
			printboard(fakearray,gridsize);
			cout << "YOU WIN!!!" << endl;
			gameover = true;
			Scorecard(Player);
		}
	}
	
	
	for (int i = 0; i < gridsize; ++i) {
		delete[] fakearray[i];
		delete[] realarray[i];
	}
	delete[] fakearray;
	delete[] realarray;
	return 0;
}
////////////////CHEATS///////////////////
void showmines(char** realarray, char** fakearray, int gridsize)
{
	for (int i = 0; i < gridsize; i++)
	{
		for (int j = 0; j < gridsize; j++)
		{
			cout << realarray[i][j];
		}
		cout << endl;
	}
}

/////////////////MAIN////////////////////
int main() {
	string answer;
	Minesweeper Player;
	login();
	tutorial();

	do {
		srand(time(NULL));
		initialtime();
		diffselector(gridsize, totalmines, movesleft);
		playminesweeper();

		cout << "\nDo you want to play again?: ";
		cin >> answer;

		lines();
	} while (answer[0]== 'y'|| answer[0]=='Y');
	system("pause");
	return 0;
}