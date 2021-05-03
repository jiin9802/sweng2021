#pragma once
#include "Tetris.h"
class CTetris : public Tetris {
	public:
		static std::vector<Matrix> setOfCBlockObjects;
		static void init(int *setOfBlockArrays[], int max_types,int max_degrees);
		~CTetris();
		CTetris(int dy, int dx);
		TetrisState accept(char key);
		void deleteFullLines();
	
		int* arrayscreen;
		Matrix* iCScreen;
		Matrix* oCScreen;
		Matrix currCBlk;
};
