/*
Author: I063040008 胡智強
Date: Oct. 13,2018
Purpose: 建造c++的集合類別 
*/ 
#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
class set{
	public:
		set(); //default constructor 
		set(char *str); //constructor 用來將物件傳入的陣列做排序與消除重複字元，並將資料存成binaryv型態 
		void selectionsort(char *a); //sort 
		void swap(char *a,char *b); 
		int RemoveDuplicateChar(char *ArrayToSave,char *str); //消除重複字元 
		friend const set operator +(const set& A,const set& B); //聯集 
		friend const set operator *(const set& A,const set& B); //交集 
		friend const set operator -(const set& A,const set& B);	//差集 
		friend const bool operator >=(const set& A,const set& B); //包含 
		friend ostream& operator <<(ostream& outputStream,const set& s); //output operator 
	    bool in(char input,char *str); //屬於 
	private:
		char C[256];
		bool D[256];
};
int main(){
	int Input_times;
	cin>>Input_times;
	for(int i=0;i<Input_times;i++){
		char strA[1000],strB[1000],word=' ';
		cin.ignore();
		gets(strA); //讀入字串包含空白 
		gets(strB);
		cin.get(word); //讀入字元包含空白 
		cout<<"Test Case "<<i+1<<":"<<endl;
		cout<<"A: ";
		set s1(strA);
		cout<<"B: ";
		set s2(strB);
		cout<<"A+B: {"<<s1+s2<<"}"<<endl;
		cout<<"A*B: {"<<s1*s2<<"}"<<endl;
		cout<<"A-B: {"<<s1-s2<<"}"<<endl;
		cout<<"B-A: {"<<s2-s1<<"}"<<endl;
		if(s1>=s2)
			cout<<"A contain B"<<endl;
		else
			cout<<"A does not contain B"<<endl;
		if(s2>=s1)
			cout<<"B contain A"<<endl;
		else
			cout<<"B does not contain A"<<endl;
		if(s1.in(word,strA))
			cout<<"'"<<word<<"' is in A"<<endl;
		else
			cout<<"'"<<word<<"' is not in A"<<endl;	
		if(s1.in(word,strB))
			cout<<"'"<<word<<"' is in B"<<endl;
		else
			cout<<"'"<<word<<"' is not in B"<<endl;		
		cout<<endl;
	}
}

const set operator +(const set& A,const set& B){
	set save;
	for(int i=0;i<256;i++){
		save.D[i]=A.D[i]||B.D[i]; //聯集,binary資料做OR運算 
	}
	return save;
}


const set operator *(const set& A,const set& B){
	set save;
	for(int i=0;i<256;i++){
		save.D[i]=A.D[i]&&B.D[i]; //交集,binary資料做AND運算  
	}
	return save;
}

const set operator -(const set& A,const set& B){
	set save;
	for(int i=0;i<256;i++){
		save.D[i]=A.D[i]&&!B.D[i];  //差集,binary資料做AND運算,其中一個set反相  
	}
	return save;
}

const bool operator >=(const set& A,const set& B){
	for(int i=0;i<256;i++){
		if(!A.D[i]&&B.D[i]){ //包含,其中一筆資料沒有在另一筆當中回傳false  
			return false;
		}
	}
	return true;
}

bool set::in(char input,char *str){ //屬於,將輸入的字元跟陣列中的字元比對，有就回傳true 
	for(int i=0;i<256;i++){
		C[i]=0;		
	}
	RemoveDuplicateChar(C,str);
	selectionsort(C);
	int n=strlen(C);
	for(int i=0;i<n;i++){
		if(input==C[i])
		return true;
	}
	return false;
}
ostream& operator <<(ostream& outputStream,const set& s){ //輸出運算子，將bool陣列中為1的資料輸出成字元 
	for(int i=0;i<256;i++){
		if(s.D[i]==1)
			outputStream<<(char)i;
	}
	return outputStream;
}
set::set(){ //default constructor
} 
set::set(char *str){ //constructor 將輸入的陣列去相同字元並排序儲存成binary型態 
	for(int i=0;i<256;i++){  
		C[i]=0;		
	}
	RemoveDuplicateChar(C,str);
	selectionsort(C);
	int n=strlen(C);
	cout<<"{";
	for(int i=0;i<n;i++){
		cout<<C[i];
	}
	cout<<"}"<<endl;
	for(int i=0;i<256;i++){
		D[i]=0;		
	}
	for(int i=0;i<n;i++){
		D[C[i]]=1;
	}
}

int set::RemoveDuplicateChar(char *ArrayToSave,char *str){
	int index=0,n=strlen(str);
	ArrayToSave[index]=str[0];
	int j;
	for(int i=1;i<n;i++){
		for(j=0;j<n;j++){
			if(ArrayToSave[j]==str[i])
			break;
		}
		if(j==n){
			index++;
			ArrayToSave[index]=str[i];
		}
	}
	return index+1;
}

void set::selectionsort(char *a){
	int n=strlen(a); 
	for(int i=0;i<n;i++){
		int j=i;
		for(int k=i+1;k<n;k++){
			if(a[k]<a[j]) j=k;
		}
		swap(&a[i],&a[j]);
	}
}

void set::swap(char *a,char *b){ //swap，要利用傳址陣列內容才會真的交換 
	char temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
