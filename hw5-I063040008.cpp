/*
Author: I063040008 胡智強
Date: Nov. 9,2018
Purpose:  Linkedlist處理兩多項式加法與乘法 
*/ 
#include<iostream>
#include<cstdlib>
using namespace std;

struct Node	//Node 裡面可放係數和指數,還有前後指標 
{
	float Coefficient;
	int Exponent;
	struct Node *Next=NULL;
	struct Node *Prev=NULL;
};

class Polynomial{
	public:
		Polynomial(); //initialize 
		bool IsEmpty();	//檢查是否為空 
		void Add(float c,int e);	//加法	
		void Add(Node *inputNode);	// 加法多載 
	 	static Polynomial Add(Polynomial inputA,Polynomial inputB);	//加法實作operator overloading; 
		void Multiply(float c,int e);	//乘法 
		void Multiply(Node *inputNode);	//乘法多載 
		static Polynomial Multiply(Polynomial inputA,Polynomial inputB);	//乘法實作operator overloading; 
		void RemoveByCoefficient(float c);	//移除特定係數的node 
		void RemoveByExponent(int e);	//移除特定指數的node 
		Node *SearchNodeByExponent(int Exp);	//尋找相同指數的node 
		void Insert(Node *newNode);	//插入node 
		void Remove(Node *newNode);	//移除某項 
		Polynomial CopyPolynomial();	//複製整個多項式做運算 
		friend Polynomial operator+(Polynomial inputA,Polynomial inputB){ //operator overloaing 
			return Polynomial::Add(inputA,inputB);
		}
		friend Polynomial operator*(Polynomial inputA,Polynomial inputB){ //operator overloaing
			return Polynomial::Multiply(inputA,inputB);
		}
		void show(); //印出 
	private:
		Node *head;
		Node *tail;	
};

Polynomial::Polynomial(){  
	head=NULL;
	tail=NULL;
}

bool Polynomial::IsEmpty(){
	return head==NULL;
}

void Polynomial::Add(float c,int e){ //係數c指數e 
	Node *newNode=new Node;				//建立新結點 
	newNode->Coefficient=c;
	newNode->Exponent=e;	
	Node *NodeToBeSearched=SearchNodeByExponent(e); //尋找此項指數是否存在，存在直接加 
	if(IsEmpty()||NodeToBeSearched==NULL){
		Insert(newNode);
	}else{
		NodeToBeSearched->Coefficient+=c;
		delete newNode;
	}
}

void Polynomial::Multiply(float c,int e){	//多項式乘上係數c指數e的單項式 
	Node *newNode=head;
	while(newNode!=NULL){
		newNode->Coefficient*=c;
		newNode->Exponent+=e;
		newNode=newNode->Next;
	}
}

void Polynomial::Add(Node *inputNode){	//多載 
	Add(inputNode->Coefficient,inputNode->Exponent);
}

void Polynomial::Multiply(Node *inputNode){	//多載 
	Multiply(inputNode->Coefficient,inputNode->Exponent);
}

Polynomial Polynomial::Add(Polynomial inputA,Polynomial inputB){ //operator overloading實作 
	Polynomial ans=inputA.CopyPolynomial();
	Node *newNodeB=inputB.head;
	while(newNodeB!=NULL){
		ans.Add(newNodeB);
		newNodeB=newNodeB->Next;
	}
	return ans;
}


Polynomial Polynomial::Multiply(Polynomial inputA,Polynomial inputB){ //operator overloading實作  
	Polynomial flag;
	Polynomial ans;
	Node *newNodeB=inputB.head;
	while(newNodeB!=NULL){
		flag=inputA.CopyPolynomial();
		flag.Multiply(newNodeB);
		ans=Polynomial::Add(ans,flag);
		newNodeB=newNodeB->Next;
	}
	return ans;
}

void Polynomial::RemoveByCoefficient(float c){
	Node *newNode=head;
	while(newNode!=NULL){
		if(newNode->Coefficient==c){
			Remove(newNode);
			RemoveByCoefficient(c);
			return;
		}
			newNode=newNode->Next;
	}
}

void Polynomial::RemoveByExponent(int e){ //移除指數e的項 
	Node *newNode=head;
	while(newNode!=NULL){
		if(newNode->Exponent==e){
			Remove(newNode);
			RemoveByExponent(e);
			return;
		}
		newNode=newNode->Next;
	}
}

Polynomial Polynomial::CopyPolynomial(){ //copy整個多項式 
	Polynomial newPolynomial;
	Node *newNode=head;
	while(newNode!=NULL){
		newPolynomial.Add(newNode);
		newNode=newNode->Next;
	}
	return newPolynomial;
}
Node* Polynomial::SearchNodeByExponent(int Exp){	//尋找這個指數多項式存不存在 
	Node *newNode=head;
	while(newNode!=NULL){
		if(newNode->Exponent==Exp){
			return newNode;
		}
		newNode=newNode->Next;
	}
	return NULL;
}

void Polynomial::Insert(Node *newNode){ //插入多項式並且排序 
	if(IsEmpty()){							
		head=newNode;
		tail=newNode;
		return;
	}
	Node *NodeToBeCompared=head;
	while(NodeToBeCompared!=NULL){ //分成插入項比第一項大、中間項，插入項比最後一項小三種情況 
		if(NodeToBeCompared->Prev==NULL&&newNode->Exponent>NodeToBeCompared->Exponent){
			newNode->Next=head;
			head->Prev=newNode;
			head=newNode;
			return;
		}else if(NodeToBeCompared->Exponent>newNode->Exponent&&NodeToBeCompared->Next!=NULL&&newNode->Exponent>NodeToBeCompared->Next->Exponent){
					newNode->Next=NodeToBeCompared->Next;
					newNode->Prev=NodeToBeCompared;
					NodeToBeCompared->Next->Prev=newNode;
					NodeToBeCompared->Next=newNode;
					return;
		}else if(NodeToBeCompared->Next==NULL){
			newNode->Prev=tail;
			tail->Next=newNode;
			tail=newNode;
			return;
		}
		NodeToBeCompared=NodeToBeCompared->Next;
	}
	return;
}

void Polynomial::Remove(Node *newNode){ //移除某項 
	if(newNode->Prev==NULL&&newNode->Next==NULL){ //只有一項、為第一項 、中間項、最後一項，四種情況分別處理 
		head=NULL;
		tail=NULL;
	}else if(newNode->Prev==NULL){
		head=newNode->Next;
		newNode->Next->Prev=NULL;
	}else if(newNode->Next==NULL){
		tail=newNode->Prev;
		newNode->Prev->Next=NULL;  
	}else{
		newNode->Prev->Next=newNode->Next;
		newNode->Next->Prev=newNode->Prev;
	}
	delete newNode;
}

void Polynomial::show(){ //印出結果 
	if(IsEmpty()){
		cout<<"0*X^0";
		return;
	}
	Node *newNode=head;
	bool IsFirst=true;
	while(newNode!=NULL){
		if(!IsFirst){
			if(newNode->Coefficient>=0)cout<<"+";
		}
		cout<<newNode->Coefficient<<"X^"<<newNode->Exponent;
		IsFirst=false;
		newNode=newNode->Next;
	}
	return;
}

int main(){
	int NumA,NumB;
	Polynomial PolyA,PolyB;
	float coefficient;
	int exponent;
	int counter=0;
	while(1){ //輸入兩個0跳出 
		counter++;
		PolyA=Polynomial();
		PolyB=Polynomial();
		cin>>NumA;	//第一個多項式項數 
		if(NumA>0){
			while(NumA--){
				cin>>coefficient>>exponent;
				PolyA.Add(coefficient,exponent);
			}
		}
		cin>>NumB; //第二個多項式項數  
		if(NumA==0&&NumB==0){
			break;
		}else if(NumB>0){
			while(NumB--){
				cin>>coefficient>>exponent;
				PolyB.Add(coefficient,exponent);
			}
		}
		cout<<"Case"<<counter<<":"<<endl;
		PolyA.RemoveByCoefficient(0); //清除係數為0的項 
		PolyB.RemoveByCoefficient(0);	//清除係數為0的項 
		Polynomial AnsOfAdd=(PolyA+PolyB);
		AnsOfAdd.RemoveByCoefficient(0); //清除係數為0的項  
		cout<<"ADD Result: ";
		AnsOfAdd.show();
		cout<<endl;
		Polynomial AnsOfMultiply=(PolyA*PolyB);
		AnsOfMultiply.RemoveByCoefficient(0); //清除係數為0的項  
		cout<<"MULTIPLY Result: ";
		AnsOfMultiply.show();
		cout<<endl;
	}
	return 0;
}
