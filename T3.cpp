#include "T3.h"

//#include <bits/stc++>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include <map>
#include <thread>
#include <windows.h>
#include <vector>

using namespace std::chrono_literals;

struct compareMin {
	bool operator()(const std::pair<char, int>& left, const std::pair<char, int>& right) {
		return left.second < right.second;
	}
};

struct compareMax {
	bool operator()(const std::pair<char, int>& left, const std::pair<char, int>& right) {
		return left.second > right.second;
	}
};

T3::T3() {
	this->ttt['a'] = '0';
	this->ttt['b'] = '0';
	this->ttt['c'] = '0';
	this->ttt['d'] = '0';
	this->ttt['e'] = '0';
	this->ttt['f'] = '0';
	this->ttt['g'] = '0';
	this->ttt['h'] = '0';
	this->ttt['i'] = '0';
}

T3::T3(std::map<char, char> myMap) {
	this->ttt = myMap;
}


char T3::judgeX() {
	char nextMove = this->lastMoveLeft();
	if(nextMove)
		return nextMove;

	nextMove = this->grabWinX();
	if(nextMove)
		return nextMove;

	nextMove = this->twoXO('X');
	if(nextMove)
		return nextMove;

	nextMove = this->miniMaxX();
	return nextMove;
}

char T3::lastMoveLeft(){
	char move;
	int count = 0;

	while(this->ttt.find('0') != this->ttt.end())
		count++;

	if(count == 1){
		for(int i = 0; i < 3; i++) {
			if(this->ttt[ this->row1[i] ] == '0')
				return this->row1[i];

			if(this->ttt[ this->row2[i] ] == '0')
				return this->row2[i];

			if(this->ttt[ this->row3[i] ] == '0')
				return this->row3[i];
		}
	} else
			return '\0';
}

//evaluates the board
int T3::evalTTT() {
	if(this->winX())
		return 10000;

	if(this->winO())
		return -10000;

	int countX = 0;
	int countO = 0;
	int kX = 0;
	int kO = 0;

	for(int i = 0; i< 3; i++) {
		if(this->ttt[ this->row1[i] ] == '@')
			kO++;

		if(this->ttt[ this->row1[i] ] == 'X')
			kX++;
	}

	if(kO == 0)
		countX++;

	if(kX == 0)
		countO++;
	kX = 0; kO = 0;

	for(int i = 0; i< 3; i++) {
		if(this->ttt[ this->row2[i] ] == '@')
			kO++;

		if(this->ttt[ this->row2[i] ] == 'X')
			kX++;
	}

	if(kO == 0)
		countX++;

	if(kX == 0)
		countO++;
	kX = 0; kO = 0;


	for(int i = 0; i< 3; i++) {
		if(this->ttt[ this->row3[i] ] == '@')
			kO++;

		if(this->ttt[ this->row3[i] ] == 'X')
			kX++;
	}

	if(kO == 0)
		countX++;

	if(kX == 0)
		countO++;
	kX = 0; kO = 0;

	for(int i = 0; i< 3; i++) {
		if(this->ttt[ this->col1[i] ] == '@')
			kO++;

		if(this->ttt[ this->col1[i] ] == 'X')
			kX++;
	}

	if(kO == 0)
		countX++;

	if(kX == 0)
		countO++;
	kX = 0; kO = 0;

	for(int i = 0; i< 3; i++) {
		if(this->ttt[ this->col2[i] ] == '@')
			kO++;

		if(this->ttt[ this->col2[i] ] == 'X')
			kX++;
	}

	if(kO == 0)
		countX++;

	if(kX == 0)
		countO++;
	kX = 0; kO = 0;

	for(int i = 0; i< 3; i++) {
		if(this->ttt[ this->col3[i] ] == '@')
			kO++;

		if(this->ttt[ this->col3[i] ] == 'X')
			kX++;
	}

	if(kO == 0)
		countX++;

	if(kX == 0)
		countO++;
	kX = 0; kO = 0;

	for(int i = 0; i< 3; i++) {
		if(this->ttt[ this->dia1[i] ] == '@')
			kO++;

		if(this->ttt[this->dia1[i] ] == 'X')
			kX++;
	}

	if(kO == 0)
		countX++;

	if(kX == 0)
		countO++;
	kX = 0; kO = 0;

	for(int i = 0; i< 3; i++) {
		if(this->ttt[ this->dia2[i] ] == '@')
			kO++;

		if(this->ttt[ this->dia2[i] ] == 'X')
			kX++;
	}

	if(kO == 0)
		countX++;

	if(kX == 0)
		countO++;
	kX = 0; kO = 0;
	int diff = countX - countO;
	std::cout << diff << " difference" << std::endl;
	return countX - countO;

}

void T3::present() {

  this->presentRow(this->row1, true);
  this->presentRow(this->row2, true);
  this->presentRow(this->row3, false);

  std::cout << std::endl;
}

void T3::presentRow(char c[3], bool line) {
	std::cout <<"\t";

	for(int i = 0; i < 3; i++) {
		if(this->ttt[c[i] ] == '0') {
			std::cout << c[i];
			if(i < 2)
				std::cout << " | ";
		} else {
			std::cout << this->ttt[ c[i] ];
			if(i < 2)
				std::cout << " | ";
		}
	}
	std::cout << std::endl;
	if(line)
		std::cout << "\t---------" << std::endl;
}

void T3::putX() {
	char good = this->judgeX();
	char single = this->lastMoveLeft();

	while(true) {
		char pick;
		std::cout << "Choose a place for X: ";
		std::cin >> pick;
		std::cout << std::endl;

		if(this->ttt[pick] == '0') {
			this->ttt[pick] = 'X';

			/*/TODO: Need to work on this
			if(pick == single)
				this->history.insert(i, 'X', 'HP: +-');
			else if(pick == good)
				this->history.insert('X', pick, 'HP: ++')
			else
				this->history.insert('X', pick, 'HP: --')
				*/
		break;
		} else {
			std::cout << "Can't do that, choose again\n";
		}

	}
}

void T3::responseO() {
	this->present();
	std::cout << "Playing an @\n";
	char nextMove = this->grabWinO();

	//if next move is winning move
	if(nextMove != '0') {
		this->ttt[nextMove] = '@';
		return;
	}
	nextMove = this->twoXO('X');
	
	//block opponents move if required
	if(nextMove != '0') {
		this->ttt[nextMove] = '@';
		return;
	}

	//make the best move
	nextMove = this->maxiMinO();
	this->ttt[nextMove] = '@';
}

std::pair<char, int> T3::getMin(std::map<char, int> myMap) {
	std::pair<char, int> min = *std::min_element(myMap.begin(), myMap.end(), compareMin());
	return min;
}

char T3::maxiMinO() {
	std::map<char, T3> nextBoardsForO = this->tttsForXO('@');

	std::map<char, int> maxesForX;

	for( std::map<char, T3>::iterator it = nextBoardsForO.begin();
		 it != nextBoardsForO.end(); it++) {
		int maxX = this->maxesForXUnderO(it->second);
		maxesForX.insert(std::pair<char, int>(it->first, maxX) );
		
	}

	//get the minimum second value, and place o on the first vlaue of the tuple
	std::pair<char, int> placeO = this->getMin(maxesForX);

	printf("... O maximins at %c\n", placeO.first);
	return placeO.first;
}

std::pair<char, int> T3::getMax(std::map<char, int> myMap) {
	std::pair<char, int> min = *std::min_element(myMap.begin(), myMap.end(), compareMax());
	return min;
}

char T3::miniMaxX() {
	std::map<char, T3> nextBoardsForX = this->tttsForXO('X');

	std::map<char, int> minsForO;

	for(std::map<char, T3>::iterator it = nextBoardsForX.begin();
		it != nextBoardsForX.end(); it++) {
		int minO = this->minsForOUnderX(it->second);
		minsForO.insert(std::pair<char, int>(it->first, minO) );
		
	}

	std::pair<char, int> placeX = this->getMax(minsForO);

	printf("... X minimaxes at %s\n", placeX.first);
	return placeX.first;
}

std::map<char, T3> T3::tttsForXO(char S) {
	std::vector<char> placesForXO;
	std::map<char, T3> tttsForXO;

	for(std::map<char, char>::iterator it = this->ttt.begin();
		it != this->ttt.end(); it++) {
		if(it->second == '0'){
			placesForXO.push_back(it->first);
		}
	}

	if(placesForXO.empty())
		return tttsForXO;



	for(std::vector<char>::iterator it = placesForXO.begin();
		it != placesForXO.end(); it++) {

		std::map<char, char> copiedMap;
		//need to deep copy the map
		for(std::map<char, char>::iterator it1 = this->ttt.begin();
			it1 != this->ttt.end(); it1++) {
				char c = *(new char(it1->second) );
				copiedMap[it1->first] = c;
		}
		char d = *(new char(*it));
		copiedMap[d] = S;
		T3 nextT3(copiedMap);
		tttsForXO.insert(std::pair<char, T3>(d, nextT3) );
	}
	return tttsForXO;
}

int T3::maxesForXUnderO(T3 OBoard) {
	std::vector<char> placesForX;

	for(std::map<char, char>::iterator it = OBoard.ttt.begin();
		it != OBoard.ttt.end(); it++) {
			if(it->second == '0')
				placesForX.push_back(it->first);
	}

	int maxEval = -100000;
	for(std::vector<char>::iterator it = placesForX.begin();
		it != placesForX.end(); it++) {
		
		//deep copy
		std::map<char, char> copiedMap;
		for(std::map<char, char>::iterator it1 = this->ttt.begin();
			it1 != this->ttt.end(); it1++) {
				copiedMap[it1->first] = *(new char(it1->second));
		}
		copiedMap[*it] = 'X';
		T3 nextT3(copiedMap);
		int nextEval = nextT3.evalTTT();
		if(nextEval > maxEval){
			maxEval = nextEval;
		}

		return maxEval;
	}
}

int T3::minsForOUnderX(T3 XBoard) {
	std::vector<char> placesForO;

	for(std::map<char, char>::iterator it = XBoard.ttt.begin();
		it != XBoard.ttt.end(); it++) {
			if(it->second == '0')
				placesForO.push_back(it->first);
	}

	int maxEval = 100000;
	for(std::vector<char>::iterator it = placesForO.begin();
		it != placesForO.end(); it++) {
		
		//deep copy
		std::map<char, char> copiedMap;
		for(std::map<char, char>::iterator it1 = this->ttt.begin();
			it1 != this->ttt.end(); it1++) {
				copiedMap[it1->first] = *(new char(it1->second));
		}
		copiedMap[*it] = '@';
		T3 nextT3(copiedMap);
		int nextEval = nextT3.evalTTT();
		if(nextEval < maxEval)
			maxEval = nextEval;

		return maxEval;
	}
}

char T3::grabWinO() {
	char toPlay = this->twoXO('@');
	if(toPlay != '0') {
		printf("... O grabs a win at %c", toPlay);
		return toPlay;
	}

	return '0';
}

char T3::grabWinX() {
	char toPlay = this->twoXO('X');
	if(toPlay != '0') {
		printf("... X grabs a win at %c", toPlay);
		return toPlay;
	}

	return '0';
}

char T3::twoXO(char S) {
	std::vector<char> r2 = this->twoXORow(S);
	std::vector<char> c2 = this->twoXOCol(S);
	std::vector<char> d2 = this->twoXODiag(S);

	std::vector<char> picks = r2;
	picks.insert(picks.end(), c2.begin(), c2.end() );
	picks.insert(picks.end(), d2.begin(), d2.end() );

 	if(!picks.empty()) {
 		srand(time(NULL));
 		int random = rand() % (picks.size() - 1);
 		char block = picks[random];
 		if(S == 'X')
 			printf("... two X to be blocked at %s", block);
 		return block;
 	}

 	return '0';

}

 std::vector<char> T3::twoXORow(char S) {
 	std::vector<char> picks;
 	std::vector<char> places(this->row1,
 	                         this->row1 + sizeof(this->row1)/sizeof(char) );

 	for(int i = 0; i < places.size(); i++) {
 		char x = places[i];
 		if(this->ttt[x] == S)
 			places.erase(places.begin() + i);

	}
 	if(places.size() == 1 and this->ttt[places[0] ] == '0')
 		picks.push_back(places[0]);

 	places = std::vector<char>(this->row2,
 	                           this->row2 + sizeof(this->row2)/sizeof(char) );
 	
 	for(int i = 0; i < places.size(); i++) {
 		char x = places[i];
 		if(this->ttt[x] == S)
 			places.erase(places.begin() + i);
	}
 	if(places.size() == 1 and this->ttt[places[0] ] == '0')
 		picks.push_back(places[0]);

 	places = std::vector<char>(this->row3,
 	                           this->row3 + sizeof(this->row3)/sizeof(char) );
 	
 	for(int i = 0; i < places.size(); i++) {
 		char x = places[i];
 		if(this->ttt[x] == S)
 			places.erase(places.begin() + i);
	}
 	if(places.size() == 1 and this->ttt[places[0] ] == '0')
 		picks.push_back(places[0]);

 	return picks;
 }

 std::vector<char> T3::twoXOCol(char S) {
 	std::vector<char> picks;
 	std::vector<char> places(this->col1,
 	                         this->col1 + sizeof(this->col1)/sizeof(char) );

 	for(int i = 0; i < places.size(); i++) {
 		char x = places[i];
 		if(this->ttt[x] == S)
 			places.erase(places.begin() + i);

	}
 	if(places.size() == 1 and this->ttt[places[0] ] == '0')
 		picks.push_back(places[0]);

 	places = std::vector<char>(this->col2,
 	                           this->col2 + sizeof(this->col2)/sizeof(char) );
 	
 	for(int i = 0; i < places.size(); i++) {
 		char x = places[i];
 		if(this->ttt[x] == S)
 			places.erase(places.begin() + i);
	}
 	if(places.size() == 1 and this->ttt[places[0] ] == '0')
 		picks.push_back(places[0]);

 	places = std::vector<char>(this->col3,
 	                           this->col3 + sizeof(this->col3)/sizeof(char) );
 	
 	for(int i = 0; i < places.size(); i++) {
 		char x = places[i];
 		if(this->ttt[x] == S)
 			places.erase(places.begin() + i);
	}
 	if(places.size() == 1 and this->ttt[places[0] ] == '0')
 		picks.push_back(places[0]);

 	return picks;
 }

 std::vector<char> T3::twoXODiag(char S) {
 	std::vector<char> picks;
 	std::vector<char> places(this->dia1,
 	                         this->dia1 + sizeof(this->dia1)/sizeof(char) );

 	for(int i = 0; i < places.size(); i++) {
 		char x = places[i];
 		if(this->ttt[x] == S)
 			places.erase(places.begin() + i);

	}
 	if(places.size() == 1 and this->ttt[places[0] ] == '0')
 		picks.push_back(places[0]);

 	places = std::vector<char>(this->dia2,
 	                           this->dia2 + sizeof(this->dia2)/sizeof(char) );
 	
 	for(int i = 0; i < places.size(); i++) {
 		char x = places[i];
 		if(this->ttt[x] == S)
 			places.erase(places.begin() + i);
	}
 	if(places.size() == 1 and this->ttt[places[0] ] == '0')
 		picks.push_back(places[0]);

 	return picks;
 }

void T3::giveInstructions() {

	std::cout << "\t Tic-Tac-Toe\n";
	std::cout << "Choose a cell by entering a character\n";
}

bool T3::fullRow(char symb) {
	std::string rs = std::string(1, symb);
	rs = rs + rs + rs;
	return rs == this->rcdValues(this->row1) or
	       rs == this->rcdValues(this->row2) or
	       rs == this->rcdValues(this->row3);
}

bool T3::fullCol(char symb) {
	std::string rs = std::string(1, symb);
	rs = rs + rs + rs;
	return rs == this->rcdValues(this->col1) or
	       rs == this->rcdValues(this->col2) or
	       rs == this->rcdValues(this->col3);
}

bool T3::fullDiag(char symb) {
	std::string rs = std::string(1, symb);
	rs = rs + rs + rs;
	return rs == this->rcdValues(this->dia1) or
	       rs == this->rcdValues(this->dia2);
}

bool T3::winX() {
	return this->fullRow('X') or
	       this->fullCol('X') or
	       this->fullDiag('X');
}

bool T3::winO() {
	return this->fullRow('@') or
	       this->fullCol('@') or
	       this->fullDiag('@');
}

bool T3::fullBoard() {
	int count = 0;
	for(std::map<char, char>::iterator it = this->ttt.begin();
		it != this->ttt.end(); it++) {
		if(it->second == '0')
			count++;
	}

	return count == 0;
}

void T3::reset() {
	for(std::map<char, char>::iterator it = this->ttt.begin();
		it != this->ttt.end(); it++) {

		it->second == '0';
	}
}

std::string T3::rcdValues(char rcd[3]) {
	std::string values = "";
	for(int i = 0; i < 3; i++)
		values += this->ttt[ rcd[i] ];

	return values;
}

void T3::play() {
	this->reset();
	this->giveInstructions();
	while( !this->winX() and !this->winO() ){
		this->present();
		
		if(this->fullBoard()){
			std::cout << "\nX and O, you tie\n\n";
			break;
	    }
	    this->putX();
	    if(this->winX()) {
	    	this->present();
	    	std::cout << "X, you win\n\n";
	    }

	    if(!this->fullBoard()) {
	    	this->responseO();
	    	if(this->winO()) {
	    		this->present();
	    		std::cout << "O wins, you lose \n\n";
	    	}
	    }
	}
}