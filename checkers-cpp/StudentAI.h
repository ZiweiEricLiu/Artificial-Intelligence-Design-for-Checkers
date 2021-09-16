#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
    Board board;
	StudentAI(int col, int row, int p);
	virtual Move GetMove(Move board);
	Move FindBestMove(vector<vector<Move>> move_options);
	int minimax(int depth, bool isMax, int a, int b);
	int simple_heuristic();
	int optimal_heuristic();
};

#endif //STUDENTAI_H
