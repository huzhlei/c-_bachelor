#include<iostream>
using namespace std; 

template<typename T>class List;

template<typename T>class Node{
	T info;
	Node<T>*link;
	public:
		Node();
		Node(const T &data);
		Node(Node<T>&);
		friend class List<T>;
};
template <typename T> Node<T>::Node(){link=NULL;}
template <typename T> Node<T>::Node(const T & data){
	info=data;
	link=NULL;
}
template <typename T> Node<T>::Node(Node<T>&node){
	info=node.info;
	link=NULL;
}

template<typename T>class List{
	Node<T>*head,*tail;
	public:
		List();
		List(List<T>&ls);
		~List();
		void MakeEmpty();
		void PrintList();
		List<T>& operator=(List<T>& ls);
		List<T>& operator+=(Node<T>* p);
		List<T>& operator+=(List<T>& ls);
		List<T>& operator+(List<T>& ls);
		Node<T>* CreatNode(T data);
};
template<typename T> List<T>::List(){
	head=tail=new Node<T>();
}
template<typename T> List<T>::List(List<T>&ls){
	Node<T>*tempP=ls.head->link,*P1;
	head=tail=new Node<T>();
	while(tempP!=NULL){
		P1=new Node<T>(*tempP);
		P1->link=tail->link;
		tail->link=P1;
		tail=P1;
		tempP=tempP->link;
	}
}
template<typename T> List<T>::~List(){
	MakeEmpty();
	delete head;
}
template<typename T> void List<T>::MakeEmpty(){
	Node<T>*tempP;
	while(head->link!=NULL){
		tempP=head->link;
		head->link=tempP->link;
		delete tempP;
	}
	tail=head;
}
template<typename T> void List<T>::PrintList(){
	Node<T>*tempP=head->link;
	while(tempP!=NULL){
		cout<<tempP->info<<'\t';
		tempP=tempP->link;
	}
	cout<<endl;
}
template<typename T> List<T>& List<T>::operator=(List<T>& ls){
	Node<T>*tempP=ls.head->link,*P1;
	MakeEmpty();
	while(tempP!=NULL){
		P1=new Node<T>(*tempP);
		P1->link=tail->link;
		tail->link=P1;
		tail=P1;
		tempP=tempP->link;
	}
	return *this;
}
template<typename T> List<T>& List<T>::operator+=(Node<T>* p){
	p->link=tail->link;
	tail->link=p;
	tail=p;
	return *this;
}
template<typename T> List<T>& List<T>::operator+=(List<T>& ls){
	Node<T>*tempP=ls.head->link,*P1;
	while(tempP!=NULL){
		P1=new Node<T>(*tempP);
		P1->link=tail->link;
		tail->link=P1;
		tail=P1;
		tempP=tempP->link;
	}
	return *this;
}
template<typename T> List<T>& List<T>::operator+(List<T>& ls){
	List<T>*tempL=new List(*this);
	(*tempL)+=ls;
	return *tempL;
}
template<typename T> Node<T>* List<T>::CreatNode(T data){
	Node<T> *tempP=new Node<T>(data);
	return tempP;
}

void main(){
	Node<int> *P1;
	List<int> list1,list2,list3,list4;
	int a[10],b[10],i;
	cout<<"请输入10个整数"<<endl;
	for(i=0;i<10;i++) cin>>a[i];
	for(i=0;i<10;i++){
		P1=list1.CreatNode(a[i]);
		list1+=P1;
	}
	cout<<"链表一为："<<endl;
	list1.PrintList();
	list2=list1;
	cout<<"与链表一相同的链表二为："<<endl;
	list2.PrintList();
	list2+=list1;
	cout<<"链表一加到链表二上为："<<endl;
	list2.PrintList();
	cout<<"请再输入10个整数"<<endl;
	for(i=0;i<10;i++) cin>>b[i];
	for(i=0;i<10;i++){
		P1=list3.CreatNode(b[i]);
		list3+=P1;
	}
	cout<<"链表三为："<<endl;
	list3.PrintList();
	list4=list1+list3;
	cout<<"链表一与链表三相加得链表四为："<<endl;
	list4.PrintList();
	system("Pause");
}