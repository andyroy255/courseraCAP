
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <queue>

#define PUZZLE_SIZE 25
#define ROW_SIZE 5
#define TOP 0
#define LEFT 1
#define BOT 2
#define RIGHT 3

using namespace std;

class square
{
public:
	square();
	void printSquare();
	vector <string> sides;
	uint8_t squareNumber;
};

class puzzle
{
public:
	puzzle();
	vector <square> sList;
	vector <uint8_t> solvedP;
	bool complete;
	void printPuzzle();
	void printAnswer();
	bool edgeMatch(uint8_t pos, const square * s);
	bool neighborMatch(uint8_t pos, const square * s);

	bool makePuzzle(vector <uint8_t> foundList, uint8_t puzzlePos);
};

int main()
{
	puzzle p;

	//p.printPuzzle();


	vector<uint8_t> fList;

	uint8_t pPos = 0;

	p.makePuzzle(fList, pPos);

//	cout << "\n\n";
	p.printAnswer();


//	cout << "\n\n";
/*
	uint8_t ansCount[25] = { 0 };

	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
		ansCount[p.solvedP[i]]++;

	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
		cout << (int)ansCount[i] << "\n";
*/
	getch();
	return 0;
}

square::square()
{
	string tempLine;
	string temp;

	std::getline(std::cin, tempLine);

	while (!tempLine.empty())
	{
		if (tempLine.at(0) == '(' || tempLine.at(0) == ')' || tempLine.at(0) == ' ')
		{
			tempLine.erase(0, 1);
		}

		else if (tempLine.at(0) == ',')
		{
			tempLine.erase(0, 1);
			sides.push_back(temp);
			temp.clear();
		}

		else
		{
			temp.append(tempLine, 0, 1);
			tempLine.erase(0, 1);
		}
	}
	sides.push_back(temp);
	return;
}
puzzle::puzzle()
{
	complete = false;
	solvedP.resize(PUZZLE_SIZE);

	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		square newSquare;
		newSquare.squareNumber = i;
		sList.push_back(newSquare);
	}
	return;
}

void square::printSquare()
{
	for (uint8_t i = 0; i < sides.size(); i++)
	{
		cout << sides[i] << "\n";
	}
	return;
}

void puzzle::printPuzzle()
{
	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		cout << "Square: " << (int)i << "\n";
		sList[i].printSquare();
		cout << "\n";
	}
}

void puzzle::printAnswer()
{
	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		cout << "(" << sList[solvedP[i]].sides[TOP] << "," << sList[solvedP[i]].sides[LEFT] << "," << sList[solvedP[i]].sides[BOT] << "," << sList[solvedP[i]].sides[RIGHT] << ")";

		if ((i + 1) % ROW_SIZE == 0)
			cout << "\n";// << (int)sList[solvedP[i]].squareNumber << " \n";
		else
			cout << ";";
	}
}
bool puzzle::edgeMatch(uint8_t pos, const square * s)
{
	bool isEdge = false;
	//Top Check
	if (pos < ROW_SIZE)
	{
		isEdge = true;
		//		cout << "Position: " << (int)pos << " in puzzle is in top row\n";

		if (s->sides[TOP] != "black")
		{
			//			cout << "Square is not a valid match. Failed top side check. \n";
			return false;
		}
	}
	else if (s->sides[TOP] == "black")
		return false;

	//Left Check
	if ((pos % ROW_SIZE) == 0)
	{
		isEdge = true;
		//		cout << "Position: " << (int)pos << " in puzzle is in left column\n";

		if (s->sides[LEFT] != "black")
		{
			//			cout << "Square is not a valid match. Failed left side check. \n";
			return false;
		}
	}
	else if (s->sides[LEFT] == "black")
		return false;

	//Bot Check
	if (pos >= PUZZLE_SIZE - ROW_SIZE)
	{
		isEdge = true;
		//		cout << "Position: " << (int)pos << " in puzzle is in bottom row\n";

		if (s->sides[BOT] != "black")
		{
			//			cout << "Square is not a valid match. Failed bot side check. \n";
			return false;
		}
	}
	else if (s->sides[BOT] == "black")
		return false;

	//Right Check
	if (((pos + 1) % ROW_SIZE) == 0)
	{
		isEdge = true;
		//		cout << "Position: " << (int)pos << " in puzzle is in right column\n";

		if (s->sides[RIGHT] != "black")
		{
			//			cout << "Square is not a valid match. Failed right side check. \n";
			return false;
		}
	}
	else if (s->sides[RIGHT] == "black")
		return false;

	return true;
}


bool puzzle::neighborMatch(uint8_t pos, const square * s)
{
	//Top neighbor
	if (pos >= ROW_SIZE)
	{
		if (s->sides[TOP] != sList[solvedP[pos - ROW_SIZE]].sides[BOT])
		{
			//			cout << "Top neighbor was not a match \n";
			return false;
		}
	}

	//Left neighbor
	if ((pos % ROW_SIZE) != 0)
	{
		if (s->sides[LEFT] != sList[solvedP[pos - 1]].sides[RIGHT])
		{
			//			cout << "left neighbor was not a match \n";
			return false;
		}
	}

	return true;
}

bool isUsed(const vector <uint8_t> foundList, uint8_t squareNumber)
{
	for (uint8_t i = 0; i < foundList.size(); i++)
	{
		if (foundList[i] == squareNumber)
		{
//			cout << "Blocked from foundlist\n";
			return true;
		}
	}
	return false;
}


bool puzzle::makePuzzle(vector <uint8_t> foundList, uint8_t puzzlePos)
{
//	cout << "\nEntering makePuzzle foundList size is: " << (int)foundList.size() << " puzzlePos is: " << (int)puzzlePos << "\n";

	if (complete == true)
	{
	//	cout << "Cmplete from start\n";
		return true;
	}

	queue<square> q;
	bool matchFound = false;

	//Fill up the queue with valid moves
	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		if ((edgeMatch(puzzlePos, &sList[i]) && neighborMatch(puzzlePos, &sList[i])) && (!isUsed(foundList, i)))
		{
//			cout << "Square: " << (int)i << " is a match at puzzle position:  " << (int)puzzlePos << "\n";
			matchFound = true;
			q.push(sList[i]);

			//Check for last one should move out of loop if too slow
			if (puzzlePos == PUZZLE_SIZE - 1)
			{
//				cout << "COMPLETE\n\n";
				complete = true;
				solvedP[PUZZLE_SIZE - 1] = i;
				return true;
			}
		}
	}

	if (!matchFound)
	{
		cout << "No matches found returning false\n";
		return false;
	}

	while (!q.empty() && !complete)
	{
//		cout << "Before pop q size is: " << q.size() << "\n";
		square poppedSquare = q.front();
		q.pop();

		solvedP[puzzlePos] = poppedSquare.squareNumber;

		vector<uint8_t> newFoundList = foundList;
		newFoundList.push_back(poppedSquare.squareNumber);

		makePuzzle(newFoundList, puzzlePos + 1);
	}
	return true;
}







/*
(black,black,blue,cyan)
(black,brown,maroon,red)
(black,cyan,yellow,brown)
(black,red,green,black)
(black,red,white,red)
(blue,black,orange,yellow)
(blue,cyan,white,black)
(brown,maroon,orange,yellow)
(green,blue,blue,black)
(maroon,black,yellow,purple)
(maroon,blue,black,orange)
(maroon,orange,brown,orange)
(maroon,yellow,white,cyan)
(orange,black,maroon,cyan)
(orange,orange,black,black)
(orange,purple,maroon,cyan)
(orange,purple,purple,purple)
(purple,brown,black,blue)
(red,orange,black,orange)
(white,cyan,red,orange)
(white,orange,maroon,blue)
(white,orange,orange,black)
(yellow,black,black,brown)
(yellow,cyan,orange,maroon)
(yellow,yellow,yellow,orange)





(black,black,blue,cyan)
(black,brown,maroon,red)
(black,cyan,yellow,brown)
(black,red,green,black)
(black,red,white,red)
(blue,black,orange,yellow)
(blue,cyan,white,black)
(brown,maroon,orange,yellow)
(green,blue,blue,black)
(maroon,black,yellow,purple)

(maroon,orange,brown,orange)
(maroon,yellow,white,cyan)
(orange,black,maroon,cyan)

(orange,purple,maroon,cyan)
(orange,purple,purple,purple)



(white,cyan,red,orange)
(white,orange,maroon,blue)
(white,orange,orange,black)


(yellow,cyan,orange,maroon)
(yellow,yellow,yellow,orange)


(yellow,black,black,brown)
(purple,brown,black,blue)
(maroon,blue,black,orange)
(red,orange,black,orange)
(orange,orange,black,black)
*/