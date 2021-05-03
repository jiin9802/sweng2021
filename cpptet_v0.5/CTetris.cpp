#include "CTetris.h"
std::vector<vector<Matrix>> CTetris::setOfCBlockObjects;

void CTetris::init(int* setOfBlockArrays[],int max_types,int max_degrees)
{
	Tetris::init(setOfBlockArrays,max_types,max_degrees);
	for(int i=0;i<max_types;i++)
	{
		std::vector<Matrix> CVec_Blk;
		for(int j=0;j<nBlockDegrees;j++)
		{
			Matrix obj=Matrix(setOfBlockObjects[i][j]);
			obj.mulc(i+1);
			CVec_Blk.push_back(obj);
		}
		setOfCBlockObjects.push_back(CVec_Blk);
	}
	return;

}
CTetris::CTetris(int dy,int dx):Tetris(dy,dx)
{
	arrayScreen=createArrayScreen();
	iCScreen=new Matrix(arrayScreen,iScreenDw+dy,iScreenDw*2+dx);
	oCScreen=iCScreen;
	return;

}
TetrisState CTetris::accept(char key)
{
//	state=Running;

	if(key>='0' &&key<='6')
	{
		if(justStarted==false)
			deleteFullLines();
		iCScreen=new Matrix(oCScreen);
	}
	state=Tetris::accept(key);

	currCBlk=setOfCBlockObjects[idxBlockType][idxBlockDegree];
	
	tempBlk=iCScreen->clip(top,left,top+currCBlk.get_dy(),left+currCBlk.get_dx());
	tempBlk=tempBlk.add(&currBlk);

	oCScreen=new Matrix(iCScreen);
	oCScreen->paste(&tempBlk,top,left);
	return state;
}
void CTetris::deleteFullLines()
{
	
}
CTetris::~CTetris(){}
