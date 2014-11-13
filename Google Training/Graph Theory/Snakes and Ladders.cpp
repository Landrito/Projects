#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

//The main way to view this problem is to look at the whole board as a directed graph
//At each position(node), the node either connects to 6 spaces(dice roll) or to a single space(snakes/ladders)
//An easy way to represent the board would be to make a 10x10 array and at the spots where
//a ladder or snake is at, just put the end position of the ladder or snake.
//After making the board, do a bfs until you get to 100

struct playerState{
	int position;
	int moveNum;
};

int * getGameBoard();
int minimumNumMoves(const int * board);

int main() { 
	int ** boards;
	int numBoards = 0;
	assert( scanf("%d", &numBoards) == 1 );
	boards = new int * [numBoards];
	for(int i = 0; i < numBoards; i++){
		boards[i] = getGameBoard();
	}
	for(int i = 0; i < numBoards; i++){
		printf("%d\n", minimumNumMoves(boards[i]));
	}

    return 0;
}

int * getGameBoard(){
	//Initialize the board;
	int * board = new int[100];
	for(int i = 0; i < 100; i++){
		board[i] = i;
	}

	//get the number of snakes and ladders
	int numLadders = 0;
	int numSnakes = 0;
	assert( scanf("%d,%d", &numLadders, &numSnakes) == 2 );

	//set the points in the array
	for(int i = 0; i < numLadders; i++){
		int ladderStart = 0;
		int ladderEnd = 0;
		assert( scanf("%d,%d", &ladderStart, &ladderEnd) == 2 );
		board[ladderStart - 1] = ladderEnd - 1;
	}
	for(int i = 0; i < numSnakes; i++){
		int snakeStart = 0;
		int snakeEnd = 0;
		assert( scanf("%d,%d", &snakeStart, &snakeEnd) == 2 );
		board[snakeStart - 1] = snakeEnd - 1;
	}

	return board;
}

int minimumNumMoves(const int * board){
	vector<playerState> stateQueue;
	stateQueue.push_back( (playerState){0,0} );
	for(int i = 0; i < stateQueue.size(); i++){
		for(int j = 6; j > 0; j--){
			if( stateQueue[i].position + j == 99 ){
				return stateQueue[i].moveNum + 1;
			} else if( stateQueue[i].position + j < 100 ){
				stateQueue.push_back( (playerState){board[stateQueue[i].position + j], stateQueue[i].moveNum + 1} );
			}
		}
	}
	return -1;
}







