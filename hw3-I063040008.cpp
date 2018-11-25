/*
Author: I063040008 胡智強
Date: Oct. 27,2018
Purpose:  西洋棋騎士(knight) 走完棋盤的順序 
*/ 
#include<iostream>
using namespace std;

typedef struct Knight{ 	//利用struct代替class將要存入stack的資料包在一起 
	int row,col,d,steps;
}KNIGHT;

template<class T>
class StackArray{	 //利用陣列實作stack 
	public:
		StackArray(int stackCapacity=10); //constructor 
		void Push(const KNIGHT& x); //push
		KNIGHT Pop(); //pop
		bool IsEmpty() const; //檢查stack是否為空 
		KNIGHT Top() const; //回傳stack最頂端資料 
		int getSize(); //回傳stack的資料量 
	private:
		int capacity; //stack的大小 
		int top; //表示stack最頂端 
		KNIGHT *stack; //動態陣列避免overflow 
}; 


template<class T>
StackArray<T>::StackArray(int stackCapacity):capacity(stackCapacity) //constructor，初始化stack 
{
	top=-1;
	stack=new KNIGHT[capacity];
}

template<class T>
inline bool StackArray<T>::IsEmpty() const //如果頂端沒有值回傳false 
{
	return top==-1;
}

template<class T>
inline KNIGHT StackArray<T>::Top() const{ //回傳stack最頂端資料 
	if(IsEmpty()) cout<<"Stack is empty"<<endl;
	return stack[top];
}

template<class T>
void StackArray<T>::Push(const KNIGHT& x){ //push
	if(top==capacity-1){
		cout<<"Stack Overflows"<<endl;
	}
	++top;
	stack[top]=x;
}

template<class T>
KNIGHT StackArray<T>::Pop(){ //pop
	if(IsEmpty()){
		cout<<"Stack is empty. Cannot delete."<<endl;
	}else{
		return(stack[top--]); //因為回朔要用到前一的資料所以不能使用destructor 
		//stack[top--].~KNIGHT();
	}
}

template<class T>
int StackArray<T>::getSize(){  //回傳大小 
	return top+1;
}

int If_In_board(int x,int y,int N){ //判斷是否下一步在棋盤內 
	if(x>=0&&x<N&&y>=0&&y<N)
		return 1;
	else
		return 0;
}  

void Print_board(int **board,int d,int steps,int n){ //印出結果 
	if(d!=8&&steps!=1)
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					cout<<board[i][j]<<"\t";
				}
			cout<<endl;
			}
		cout<<endl;
}

int KnightTravel(int row,int col){ //騎士遍歷 
	StackArray<int> s(100); //stack大小預設100 
	int colMove[]={1,2,2,1,-1,-2,-2,-1}; //x軸橫向的位移 
	int	rowMove[]={-2,-1,1,2,2,1,-1,-2}; //y軸垂直的位移 
	
	for(int n=1;n<=6;n++){  
		if(n==1){ //n=1 印出1 
			cout<<"n="<<n<<endl;
			cout<<n<<endl<<endl;
			continue;	
		}
		row=0;col=0;
		cout<<"n="<<n<<endl;
		int **board=new int*[n];
		for(int i=0;i<n;i++){
			board[i]=new int[n]; //初始化動態陣列 
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				board[i][j]=0; //棋盤歸零 
			}
		}
		int steps=1,d=0,nRow,nCol;
		Knight k1;
		board[row][col]=steps; //出發的地方設為第一步 
		while(steps<n*n){	//start
			for(;d<8;d++){	//測試8個方向 
				nCol=col+colMove[d];
				nRow=row+rowMove[d];
				if(If_In_board(nRow,nCol,n)&&board[nRow][nCol]==0){ //判斷8個方向，可以走就將所在位置以及方向還有第幾步的資料一起推入stack 
					k1.row=row;
					k1.col=col;
					k1.d=d;
					k1.steps=steps;
					s.Push(k1);
					board[nRow][nCol]=++steps;
					
					d=0; //方向歸零 
					row=nRow; //所在位置前進 
					col=nCol;
					break;  
				}
			}
			if(d==8){ //當八個方向都不能再走 
				if(steps==1){
					cout<<"no solution!"<<endl<<endl; //退到不能再退就無解 
					break;
				}
				board[row][col]=0; //所在位置歸零 
				k1=s.Pop(); //拿出資料 
				row=k1.row; //退回原位 
				col=k1.col;
				d=k1.d;
				steps=k1.steps;
				d++; //測其他方向 
			}
		
		}
		Print_board(board,d,steps,n); //印出 
	}
	cout<<endl;
}

int main(){ //main 
	KnightTravel(0,0);  
}

