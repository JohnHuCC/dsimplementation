/*
Author: I063040008 胡智強
Date: Oct. 27,2018
Purpose:  西洋棋騎士(knight) 走完棋盤的順序 ，使用recursive 
*/ 
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

int **board; //宣告動態陣列全域都可使用 
int n=-1,steps; //一開始陣列大小設為-1 

enum Setting{	//使用列舉，將走過與未走過的點做標記 
	WalkedPoint,
	UnWalkedPoint
};

class Knight_Travel{  
	public:
		int Row,Col;
		Knight_Travel(){ //constructor，初始化起點 
			init();
		}
		
		Knight_Travel(int row,int col){ //constructor，傳入起點 
			Row=row;
			Col=col;
		}
		
		Knight_Travel Next_Direction(int DirNum){	//取得走下一步後的位置 
			if(DirNum<0||DirNum>=8){
				throw "Error Direction";
			}
			Knight_Travel newKnight(Row,Col);
			newKnight.Knight_Move(DirNum);
			return newKnight;
		}
	private:
		int	rowMove[8]={-2,-1,1,2,2,1,-1,-2}; //y軸垂直的位移 
		int colMove[8]={1,2,2,1,-1,-2,-2,-1}; //x軸橫向的位移 
		void init(){	//初始化起點 
			Row=0;
			Col=0;
		}
		
		void Knight_Move(int DirNum){	//對所在位置做移動 
			if(DirNum<0||DirNum>7){
				throw "Error Direction";
			}
			Row+=rowMove[DirNum];
			Col+=colMove[DirNum];
		}
};

void CreateBoard(){	//利用動態陣列建立棋盤 
		if(n<0)cout<<"Error size of board"<<endl;
		board=new int*[n];
		for(int i=0;i<n;i++){
			board[i]=new int[n];
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				board[i][j]=0;
			}
		}
}

void DeleteBoard(){	//結束後刪除棋盤 
	if(n<=0)cout<<"Error delete board"<<endl;
	for(int i=0;i<n;i++){
			delete []board[i];
	}
	delete []board;
}

bool If_Is_GoodStep(Knight_Travel knight){ //判斷下一步是不是可以走，不能超出棋盤且為0 
	if(knight.Row>=n||knight.Col>=n||knight.Row<0||knight.Col<0)return false;
    else if(board[knight.Row][knight.Col]>0)return false;
    return true;
}

void SetBoard(Setting inputSetting,Knight_Travel knight,int steps){	//可以走的話，把第幾步加上 
	if(inputSetting==WalkedPoint&&If_Is_GoodStep(knight)){
		board[knight.Row][knight.Col]=steps;
	}else if(inputSetting==UnWalkedPoint){
		board[knight.Row][knight.Col]=0;
	}			
}

int GetNumOfNextStep(Knight_Travel knight){	//取得某點可以走的下一步的數量 
	int NumOfNextStep=0;
	for(int i=0;i<8;i++){
		Knight_Travel newKnight=knight.Next_Direction(i);
        if(!If_Is_GoodStep(newKnight))continue;
        else NumOfNextStep++;
    }
   // cout<<NumOfNextStep<<endl;
    return NumOfNextStep;
}
void Print_Board(){	//印出結果 
	if(n<=0)cout<<"Error print board"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<board[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
}



void SetVisitOrder(int *data,Knight_Travel knight){	//J.C. Warnsdorff的演算法，算出下一步走的數量，往數量少的方向走，達到加速的目的 
    int minNumber,minDir;
    bool IsBook[8];
    memset(IsBook,false,sizeof(IsBook));
    for(int i=0;i<8;i++){
        minNumber=-1;
        minDir=0;
        for(int j=0;j<8;j++){
            if((minNumber==-1||minNumber>GetNumOfNextStep(knight.Next_Direction(j)))&&!IsBook[j]){
                minNumber=GetNumOfNextStep(knight.Next_Direction(j));
                minDir=j;
            }
   		}
        data[i]=minDir;
        IsBook[minDir]=true;	
	}
}

void DFS(Knight_Travel knight){	//遞迴走訪 
	if(!If_Is_GoodStep(knight))return;
	int visitOrder[8];
	SetVisitOrder(visitOrder,knight);
	SetBoard(WalkedPoint,knight,++steps); //設定現在位置已經走過 
	for(int i =0;i<8;i++){
		DFS(knight.Next_Direction(visitOrder[i])); //深入走訪 
		if(steps==n*n)return; //遞迴走完結束 
	}
	SetBoard(UnWalkedPoint,knight,steps--); //設定現在位置尚未走過 
}

int main(){	//main 
	Knight_Travel RealKnight;
	for(n=1;n<=6;n++){
		if(n==1){
			cout<<"n="<<n<<endl;
            cout<<n<<endl<<endl;
            continue;
        }
		CreateBoard();
		steps=0;
		RealKnight=Knight_Travel(0,0); //起點 
		DFS(RealKnight);
		if(steps==n*n){
			cout<<"n="<<n<<endl;
			Print_Board();
		}else{
			cout<<"n="<<n<<endl<<"\nNo Solution"<<endl<<endl;
		}
		DeleteBoard();
	}	
}
