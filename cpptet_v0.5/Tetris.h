#pragma once
#include "Matrix.h"
#include <vector>
#include <string>

enum TetrisState { Running, NewBlock, Finished };

class Tetris {
	public:
		static void init(int *setOfBlockArrays[],int max_types,int max_degrees);
		Tetris();
		Tetris(int dy, int dx);
		~Tetris();
		int* createArrayScreen();
		TetrisState accept(char key);
		TetrisState state;
		void deleteFullLines();
	
		bool justStarted;
		static int nBlockTypes;
		static int nBlockDegrees;
		static std::vector<Matrix>setOfBlockObjects;
		static int iScreenDw;
		int iScreenDy;
		int iScreenDx;
		int arrayScreenDx;
		int arrayScreenDy;
		int* arrayScreen;
		Matrix* iScreen;
		Matrix* oScreen;
		int idxBlockType;
		int idxBlockDegree;
		Matrix currBlk;
		int top;
		int left;
		Matrix tempBlk;

		 
};
