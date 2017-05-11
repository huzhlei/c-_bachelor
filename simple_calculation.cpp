#include<iostream>
#include<cmath>
#include<cassert>
using namespace std;
template<typename T>class Stack;
template<typename T>class Node{                 
	T info;
	Node<T> *link;
public:
	Node(T data=0,Node<T> *next=NULL){
		info=data;
		link=next;
	}
	friend class Stack<T>;
};
template<typename T>class Stack{                  
	Node<T> *top;                              
public:
	Stack(){top=NULL;}
	~Stack();
	void Push(const T &data);                      
	T Pop();                                    
	T GetTop();                                 
	void MakeEmpty();                           
	bool IsEmpty(){return top==NULL;}
};
template<typename T> Stack<T>::~Stack(){MakeEmpty();}
template<typename T>void Stack<T>::MakeEmpty(){
	Node<T> *temp;
	while(top!=NULL){temp=top;top=top->link;delete temp;}
}
template<typename T> void Stack<T>::Push(const T &data){
	top=new Node<T>(data,top);
}
template<typename T> T Stack<T>::Pop(){
	assert(!IsEmpty());
	Node<T> *temp=top;
	T data=temp->info;
	top=top->link;                             
	delete temp;                               
	return data;                                
}
template<typename T> T Stack<T>::GetTop(){
	assert(!IsEmpty());
	return top->info;
}
class Calculator{
	Stack<double>Nstack;
	Stack<char>Ostack;
public:
	Calculator(void){};
	void Cal(void);
	void GetTwoNum(double &Num1,double &Num2);
	void Compute(char Opr);
	void Clear(void);
};
void Calculator::Clear(){
	Nstack.MakeEmpty();
	Ostack.MakeEmpty();
}
void Calculator::GetTwoNum(double &Num1,double &Num2){
	Num1=Nstack.Pop();
	Num2=Nstack.Pop();
}
void Calculator::Compute(char Opr){
	double Num1,Num2;
	if(Opr!='=') GetTwoNum(Num1,Num2);
	switch(Opr){
	case'+':Nstack.Push(Num2+Num1);break;
	case'-':Nstack.Push(Num2-Num1);break;
	case'*':Nstack.Push(Num2*Num1);break;
	case'/':Nstack.Push(Num2/Num1);break;
	case'=':cout<<Nstack.Pop()<<endl;
	}
}
void Calculator::Cal(){
	bool b1=true,b2=true,b3=true;
	char ch1,ch2,str[50];
	int k=-1;
	while(b2){
		cin>>ch1;
		if(ch1>='0'&&ch1<='9'||ch1=='.'){
			k++;
			str[k]=ch1;
		}
		else{
			if(k>=0){
				str[k+1]='\0';
				Nstack.Push(atof(str));
				k=-1;
			}
			switch(ch1){
			case'c':Clear();break;
			case'+':case'-':
				while(!Ostack.IsEmpty()&&b1){
					ch2=Ostack.Pop();
					if(ch2=='('){
						Ostack.Push(ch2);
						b1=false;
					}
					else Compute(ch2);
				}
				Ostack.Push(ch1);
				b1=true;
				break;
			case'*':case'/':
				while(!Ostack.IsEmpty()&&b1){
					ch2=Ostack.Pop();
					if(ch2=='*'||ch2=='/') Compute(ch2);
					else{
						Ostack.Push(ch2);
						b1=false;
					}
				}
				Ostack.Push(ch1);
				b1=true;
				break;
			case'=':
				while(!Ostack.IsEmpty()){
					ch2=Ostack.Pop();
					Compute(ch2);
				}
				Compute(ch1);
				break;
			case')':
				ch2=Ostack.Pop();
				Compute(ch2);
				Ostack.Pop();
				break;
			case'(':
				Ostack.Push(ch1);
				break;
			}
			if(ch1=='z')b2=false;
		}
	}
}
int main(){
	Calculator Calcul;
	cout<<"请输入四则运算式（可带括号）："<<endl;
	Calcul.Cal();
	return 0;
}