#include "StudentAI.h"
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

//The following part should be completed by students.
//The students can modify anything except the class name and exisiting functions and varibles.
StudentAI::StudentAI(int col,int row,int p)
	:AI(col, row, p)
{
    board = Board(col,row,p);
    board.initializeGame();
    player = 2;
}

Move StudentAI::GetMove(Move move)
{
    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }
    vector<vector<Move>> moves = board.getAllPossibleMoves(player);
    
    Move bestMove = FindBestMove(moves);

    board.makeMove(bestMove,player);
    return bestMove;
}

Move StudentAI::FindBestMove(vector<vector<Move>> move_options){
    int max = -1000;
    Move bestMove;
    for(auto checker_moves : move_options){
        for(auto m: checker_moves){
            board.makeMove(m, player);
            int move_max = minimax(5, false, -1000, 1000);
            board.Undo();
            if(move_max > max){
                max = move_max;
                bestMove = m;
            }
            //tie breaker
            if(move_max == max){
                int rd = rand()%2;
                if(rd == 0){
                    max = move_max;
                    bestMove = m;
                }
            }
        }
    }
    return bestMove;
}

//Comparator For Move Object
struct greaterMove{
    bool operator()(const Move& a, const Move& b) const{
        return a.seq.size() > b.seq.size();
    }
};

struct smallerMove{
    bool operator()(const Move& a, const Move& b) const{
        return a.seq.size() < b.seq.size();
    }
};

int StudentAI::minimax(int depth, bool isMax, int a, int b){

    int turn = isMax?(player == 1?2:1):player;
    if(board.isWin(turn) == player){
        return 1000;
    }

    if(board.isWin(turn) == (player == 1?2:1)){
        return -1000;
    }

    if(board.isWin(turn) == -1){
        return 0;
    }

    if(depth == 0){
        return simple_heuristic();
    }
    
    vector<vector<Move>> possible_moves;
    if(isMax){
        possible_moves = board.getAllPossibleMoves(player);
    }
    else{
        possible_moves = board.getAllPossibleMoves(player == 1?2:1);
    }

    //use to sort the moves
    vector<Move> moves;
    for(auto checker_moves : possible_moves){
        for(auto m : checker_moves){
            moves.push_back(m);
        }
    }

    if(isMax){
        int max = -1000;
        sort(moves.begin(), moves.end(), greaterMove());
        for(auto m : moves){
            board.makeMove(m, player);
            int value = minimax(depth-1, false, a, b);
            max = value>max?value:max;
            a = max>a?max:a;
            board.Undo();

            if(b <= a){
                break;
            }
        }
        return max;
    }


    else{
        int min = 1000;
        sort(moves.begin(), moves.end(), smallerMove());
        for(auto m : moves){
            board.makeMove(m, player == 1?2:1);
            int value = minimax(depth-1, true, a, b);
            min = value<min?value:min;
            b = min<b?min:b;
            board.Undo();

            if(b <= a){
                break;
            }
        }
        return min;
    }
}

int StudentAI::simple_heuristic(){
    if(player == 2){
        return board.whiteCount-board.blackCount;
    }else{
        return board.blackCount-board.whiteCount;
    }
}

int StudentAI::optimal_heuristic(){
    int black_score = 0;
    int white_score = 0;
    vector<vector<Checker>>& checkers = board.board;
    for(auto cl : checkers){
        for(auto c : cl){
            if(c.color == "B"){
                if(c.isKing){
                    black_score += 3;
                }
                else{
                    black_score += 1;
                }
            }

            else{
                if(c.isKing){
                    white_score += 3;
                }
                else{
                    white_score += 1;
                }
            }
        }
    }
    if(player == 2){
        return white_score - black_score;
    }else{
        return black_score - white_score;
    }
}

