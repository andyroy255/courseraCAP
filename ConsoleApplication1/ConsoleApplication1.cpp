
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <queue>
#define PUZZLE_SIZE 9
#define ROW_SIZE 3
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

};

class puzzle
{
public:
	puzzle();
	vector <square> sList;
	vector <uint8_t> solvedP;

	void printPuzzle();
	bool edgeMatch(uint8_t pos, const square * s);
	bool neighborMatch(uint8_t pos, const square * s);

	bool makePuzzle(vector <uint8_t> foundList, uint8_t puzzlePos);
};

int main()
{
	puzzle p;
	
	p.printPuzzle();

	p.solvedP[0] = 6;

	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		cout << "\nSquare " << (int) i << "\n";
		p.neighborMatch(1, &p.sList[i]);
	}
	

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
	solvedP.resize(PUZZLE_SIZE);

	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		square newSquare;
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
	for(uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		cout << "Square: " << (int) i << "\n";
		sList[i].printSquare();
		cout << "\n";
	}
}


bool puzzle::edgeMatch(uint8_t pos, const square * s)
{
	
	bool isEdge = false;
	//Top Check
	if(pos < ROW_SIZE)
	{
		isEdge = true;
//		cout << "Position: " << (int)pos << " in puzzle is in top row\n";

		if (s->sides[TOP] != "black")
		{
//			cout << "Square is not a valid match. Failed top side check. \n";
				return false;
		}
	}
	//Left Check
	if((pos % ROW_SIZE) == 0)
	{
		isEdge = true;
//		cout << "Position: " << (int)pos << " in puzzle is in left column\n";
		
		if (s->sides[LEFT] != "black")
		{
//			cout << "Square is not a valid match. Failed left side check. \n";
			return false;
		}
	}

	//Bot Check
	if(pos >= PUZZLE_SIZE - ROW_SIZE)
	{
		isEdge = true;
//		cout << "Position: " << (int)pos << " in puzzle is in bottom row\n";

		if (s->sides[BOT] != "black")
		{
//			cout << "Square is not a valid match. Failed bot side check. \n";
			return false;
		}
	}
	//Right Check
	if(((pos + 1) % ROW_SIZE) == 0)
	{
		isEdge = true;
//		cout << "Position: " << (int)pos << " in puzzle is in right column\n";

		if (s->sides[RIGHT] != "black")
		{
//			cout << "Square is not a valid match. Failed right side check. \n";
			return false;
		}
	}

	if(isEdge)
		cout << "Square and pos are matching edges\n";
	else
		cout << "Square and pos are both not edges\n";

	return true;
}


bool puzzle::neighborMatch(uint8_t pos, const square * s)
{
	//Top neighbor
	if(pos > ROW_SIZE)
	{
		if (s->sides[TOP] != sList[solvedP[pos - ROW_SIZE]].sides[BOT])
		{
			cout << "Top neighbor was not a match \n";
			return false;
		}
	}

	//Left neighbor
	if((pos % ROW_SIZE) != 0)
	{
		if (s->sides[LEFT] != sList[solvedP[pos - 1]].sides[RIGHT])
		{
			cout << "left neighbor was not a match \n";
			return false;
		}
	}
}

bool isUsed(const vector <uint8_t> foundList, uint8_t squareNumber)
{
	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		if (foundList[i] == squareNumber)
			return true;
	}
	return false;
}


bool puzzle::makePuzzle(vector <uint8_t> foundList, uint8_t puzzlePos)
{

	queue<square> q;
	bool matchFound = false;

	//Fill up the queue with valid moves
	for (uint8_t i = 0; i < PUZZLE_SIZE; i++)
	{
		if (edgeMatch(puzzlePos, &sList[i]) && (neighborMatch(puzzlePos, &sList[i]) && !(isUsed(foundList, i))));
		{
			cout << "Square: " << i << " is a match at puzzle position:  " << puzzlePos << "\n";
			matchFound = true;
			q.push(sList[i]);
		}
	}

	if (!matchFound)
		return false;
	/*
	use neighbor and edge to queue all possible next pieces based on Puzzle pos. 

	while queue is non-empty:
		popFront of queue, call self with new foundlist(plus new square) and puzzlePos +1.

	If no matches are found, return false.


	if puzzle pos is == to size call print Answer and end
	
	How to clear as we move back on a fail?
	*/
}







/*
Find all valid squares for a position place them in queue. 
	Pop first square, repeat, 
		if puzzle completes print out answer.

If puzzle does not complete delete findings (how) 
	Pop next square repeat

Data:
Found list
Puzzle array

Could pass a vector of found and a vector of puzzle each time. 

nieghborCheck

Based on position check
compare

check if edge
top: - Row size
right + 1
left  - 1
bottom + row size




0 1 2 3 4
5 6 7 8 9
1011121314




*/