#include "CTetris.h"
std::vector<Matrix> CTetris::setOfCBlockObjects;

void CTetris::init(int* setOfBlockArrays[],int max_types,int max_degrees)
{
	Tetris::init(setOfBlockArrays,max_types,max_degrees);
	for(int i=0;i<max_types;i++)
	{
		for(int j=0;j<max_degrees;j++)
		{
			Matrix obj=Matrix(setOfBlockObjects[max_degrees+j]);
			obj.mulc(i+1);
			setOfCBlockObjects.push_back(obj);
		}
	}
	return;

};
CTetris::CTetris(int dy,int dx):Tetris(dy,dx)
{
	arrayScreen=createArrayScreen();
	iCScreen=new Matrix(arrayScreen,iScreenDw+dy,iScreenDw*2+dx);
	oCScreen=iCScreen;
	return;

};
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

	currCBlk=setOfCBlockObjects[nBlockDegrees*idxBlockType+idxBlockDegree];
	
	tempBlk=iCScreen->clip(top,left,top+currCBlk.get_dy(),left+currCBlk.get_dy());
	tempBlk=tempBlk.add(&currBlk);

	oCScreen=new Matrix(iCScreen);
	oCScreen->paste(&tempBlk,top,left);
	return state;
};
void CTetris::deleteFullLines()
{
	for(int i=0;i<iScreenDy;i++)
	{
		int cnt=oCScreen->binary()->clip(i,iScreenDw, i+1,iScreenDw+iScreenDx)->sum();
		if(cnt==iScreenDx)
			oCScreen->paste(oCScreen->clip(0,iScreenDw,i,iScreenDw+iScreenDx),1,iScreenDw);

	}
};
CTetris::~CTetris(){}
