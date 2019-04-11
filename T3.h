#include <iostream>
#include <map>
#include <string>
#include <vector>

class T3
{
public:
	std::map<char, char> ttt;


	T3();
	T3(std::map<char,char> myMap);
	char judgeX();
	char lastMoveLeft();
	int evalTTT();
	void present();
	void presentRow(char c[3], bool line);
	void putX();
	void responseO();
	std::pair<char, int> getMin(std::map<char, int> myMap);
	char maxiMinO();
	std::pair<char, int> getMax(std::map<char, int> myMap);
	char miniMaxX();
	std::map<char, T3> tttsForXO(char S);
	int maxesForXUnderO(T3 OBoard);
	int minsForOUnderX(T3 XBoard);
	char grabWinO();
	char grabWinX();
	char twoXO(char S);
	std::vector<char> twoXORow(char S);
	std::vector<char> twoXOCol(char S);
	std::vector<char> twoXODiag(char S);
	void giveInstructions();
	bool fullRow(char symb);
	bool fullCol(char symb);
	bool fullDiag(char symb);
	bool winX();
	bool winO();
	bool fullBoard();
	std::string rcdValues(char rcd[3]);
	void play();
	void reset();
	std::string str();
	
	

private:
	char row1[3] = {'a', 'b', 'c'};
	char row2[3] = {'d', 'e', 'f'};
	char row3[3] = {'g', 'h', 'i'};
	char col1[3] = {'a', 'd', 'g'};
	char col2[3] = {'b', 'e', 'h'};
	char col3[3] = {'c', 'f', 'g'};
	char dia1[3] = {'a', 'e', 'i'};
	char dia2[3] = {'c', 'e', 'g'};

	

};