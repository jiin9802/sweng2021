#include "Tetris.h"
#include <cmath>
int Tetris::nBlockTypes=0;
int Tetris::nBlockDegrees=0;
int Tetris::iScreenDw=0;
std::vector<Matrix> Tetris::setOfBlockObjects;

void Tetris::init(int *setOfBlockArrays[],int max_types,int max_degrees)
{
	nBlockTypes=max_types;
	nBlockDegrees=max_degrees;
	int arrayBlk_maxSize=0;
	int MaxSize[nBlockTypes];
	for (int i=0;i<max_types;i++)
	{	
		int length=0;
		while(setOfBlockArrays[i*max_degrees][length]!=-1){
			length+=1;
		}
		if (length>arrayBlk_maxSize)
			arrayBlk_maxSize=sqrt(length);
		MaxSize[i]=sqrt(length);
	}
	iScreenDw=arrayBlk_maxSize;

	for(int i=0;i<max_types;i++)
	{
		for(int j=0;j<max_degrees;j++)
		{
			setOfBlockObjects.push_back(Matrix(setOfBlockArrays[max_degrees*i+j],MaxSize[i],MaxSize[i]));
		}
	}
	
};
Tetris::Tetris(int iScreenDy,int iScreenDx)
{
	this->iScreenDy=iScreenDy;
	this->iScreenDx=iScreenDx;
	idxBlockDegree=0;
	arrayScreen=createArrayScreen();
	iScreen=new Matrix(arrayScreen, iScreenDw+iScreenDy,iScreenDw*2+iScreenDx);
	oScreen=iScreen;
	justStarted=true;
}
Tetris::~Tetris(){}

int *Tetris::createArrayScreen()
{
	
	int arrayScreenDx=iScreenDw*2+iScreenDx;
	int arrayScreenDy=iScreenDy+iScreenDw;
	int* arrayScreen=new int[arrayScreenDy*arrayScreenDx];
	for (int i=0;i<arrayScreenDy-iScreenDw;i++)
	{
		for(int j=0;j<iScreenDw;j++)
			arrayScreen[arrayScreenDx*i+j]=1;
		for(int j=iScreenDw ; j<arrayScreenDx-iScreenDw;j++)
			arrayScreen[arrayScreenDx*i+j]=0;
		for(int j=arrayScreenDx-iScreenDw ; j<arrayScreenDx;j++)
			arrayScreen[arrayScreenDx*i+j]=1;
	}
	for(int i=arrayScreenDy-iScreenDw; i<arrayScreenDy;i++)
	{
		for(int j=0;j<arrayScreenDx;j++)
			arrayScreen[arrayScreenDx*i+j]=1;
	}
	return arrayScreen;

}
TetrisState Tetris::accept(char key)
{
	state=Running;
	
	if (key>='0' && key<='6'){
		if(justStarted=false)
			deleteFullLines();
		iScreen=new Matrix(oScreen);
		idxBlockType=key-'0';
		idxBlockDegree=0;
		currBlk=setOfBlockObjects[nBlockDegrees*idxBlockType+idxBlockDegree];
		top=0;
		left=iScreenDw+iScreenDx/2-currBlk.get_dx()/2;
		tempBlk=iScreen->clip(top,left,top+currBlk.get_dy(),left+currBlk.get_dx());
		tempBlk=tempBlk.add(&currBlk);
		justStarted=false;
		cout<<"";

		if(tempBlk.anyGreaterThan(1))
			state=Finished;
		oScreen=new Matrix(iScreen);
		oScreen->paste(&tempBlk,top,left);
		return state;
	}
	else if(key=='a')
		left-=1;
	else if(key=='d')
		left+=1;
	else if(key=='s')
		top+=1;
	else if(key=='w'){
		idxBlockDegree=(idxBlockDegree+1)%nBlockDegrees;
		currBlk=setOfBlockObjects[nBlockDegrees*idxBlockType+idxBlockDegree];
	}	
	else if(key==' '){
		while (!tempBlk.anyGreaterThan(1)){
			top+=1;
			tempBlk=iScreen->clip(top,left,top+currBlk.get_dy(),left+currBlk.get_dx());
			tempBlk=tempBlk.add(&currBlk);
		}
	}
	else
		cout<<"Wrong Key!"<<endl;


	tempBlk=iScreen->clip(top,left,top+currBlk.get_dy(),left+currBlk.get_dx());
	tempBlk=tempBlk.add(&currBlk);

	if(tempBlk.anyGreaterThan(1)){
		if(key=='a')
			left+=1;
		else if(key=='d')
			left-=1;
		else if(key=='s'){
			top-=1;
			state=NewBlock;
		}
		else if(key=='w'){
			idxBlockDegree=(idxBlockDegree-1)&nBlockDegrees;
			currBlk=setOfBlockObjects[nBlockDegrees*idxBlockType+idxBlockDegree];
		}
		else if(key==' '){
			top-=1;
			state=NewBlock;
		}

		tempBlk=iScreen->clip(top,left,top+currBlk.get_dy(),left+currBlk.get_dx());
		tempBlk=tempBlk.add(&currBlk);

	}
	oScreen=new Matrix(iScreen);
	oScreen->paste(&tempBlk,top,left);
	return state;
}
void Tetris::deleteFullLines()
{

}



