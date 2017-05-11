#include<iostream>
using namespace std;

template<typename T>class List;
template<typename T>class Node{
	T info;                                    
	Node<T> *link;                            
public:
	Node();                        
	Node(const T & data);;
	void InsertAfter(Node<T>* P);    
	Node<T>* RemoveAfter();          
	friend class List<T>;
};
template <typename T> Node<T>::Node(){link=NULL;}
template <typename T> Node<T>::Node(const T & data){
	info=data;
	link=NULL;
}
template<typename T>void Node<T>::InsertAfter(Node<T>* p){
	p->link=link;
	link=p;
}
template<typename T>Node<T>* Node<T>::RemoveAfter(){
	Node<T>* tempP=link;
	if(link==NULL) tempP=NULL;                
	else link=tempP->link;
	return tempP;
}
template<typename T>class List{
	Node<T> *head,*tail;
public:
	List();             
	~List();                                   
	void MakeEmpty();                             
	Node<T>* Find(T data);                                         
	void PrintList();                        
	void InsertRear(Node<T>* p);       
	void InsertOrder(Node<T>* p);
	List<T>& operator=(List<T>& ls);
	Node<T>*CreatNode(T data);            
	Node<T>*DeleteNode(Node<T>* p);
	void InsertSort();
	void SelectSort();
};
template<typename T>List<T>::List(){
	head=tail=new Node<T>();
}
template<typename T>List<T>::~List(){
	MakeEmpty();
	delete head;
}
template<typename T>void List<T>::MakeEmpty(){
	Node<T> *tempP;
	while(head->link!=NULL){
		tempP=head->link;
		head->link=tempP->link;  
		delete tempP;           
	}
	tail=head;  
}
template<typename T> Node<T>* List<T>::Find(T data){
	Node<T> *tempP=head->link;
	while(tempP!=NULL&&tempP->info!=data) tempP=tempP->link;
	return tempP;       
}
template<typename T>void List<T>::PrintList(){
	Node<T>* tempP=head->link;
	while(tempP!=NULL){
		cout<<tempP->info<<'\t';
		tempP=tempP->link;
	}
	cout<<endl;
}
template<typename T>void List<T>::InsertRear(Node<T> *p){
	p->link=tail->link;
	tail->link=p;
	tail=p;
}
template<typename T>void List<T>::InsertOrder(Node<T> *p){
	Node<T> *tempP=head->link,*tempQ=head;        
	while(tempP!=NULL){
		if(p->info<tempP->info)break;
		tempQ=tempP;
		tempP=tempP->link;
	}
	tempQ->InsertAfter(p);	
	if(tail==tempQ) tail=tempQ->link;
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
template<typename T>Node<T>* List<T>::CreatNode(T data){
	Node<T>*tempP=new Node<T>(data);
	return tempP;
}
template<typename T>Node<T>* List<T>::DeleteNode(Node<T>* p){
	Node<T>* tempP=head;
	while(tempP->link!=NULL&&tempP->link!=p) tempP=tempP->link;
	if(tempP->link==tail) tail=tempP;
	return tempP->RemoveAfter();       
}
template<typename T>void List<T>::InsertSort(){
	List<T> tempL;
	Node<T>*tempP,*tempQ;
	for(tempP=head->link;tempP!=NULL;tempP=tempP->link){
		tempQ= new Node<T>(tempP->info);
		tempL.InsertOrder(tempQ);
	}
	(*this)=tempL;
}
template<typename T>void List<T>::SelectSort(){
	List<T> tempL;
	Node<T> *Min,*tempP,*tempQ;
	while(head->link!=NULL){
		for(tempP=head->link,Min=head->link;tempP->link!=NULL;tempP=tempP->link){
			if(tempP->link->info<Min->info) Min=tempP->link;
		}
		tempQ= new Node<T>(Min->info);
		tempL.InsertRear(tempQ);
		(*this).DeleteNode(Min);
	}
	(*this)=tempL;
}

void main(){
	Node<int> *P1;
	List<int> list1,list2;
	int a[10],b[10],i;
	cout<<"请输入10个整数"<<endl;
	for(i=0;i<10;i++) cin>>a[i];
	for(i=0;i<10;i++){
		P1=list1.CreatNode(a[i]);
		list1.InsertRear(P1);
	}
	cout<<"选择排序前："<<endl;
	list1.PrintList();
	list1.SelectSort();
	cout<<"选择排序后："<<endl;
	list1.PrintList();
	cout<<"请再输入10个整数"<<endl;
	for(i=0;i<10;i++) cin>>b[i];
	for(i=0;i<10;i++){
		P1=list2.CreatNode(b[i]);
		list2.InsertRear(P1);
	}
	cout<<"插入排序前："<<endl;
	list2.PrintList();
	list2.InsertSort();
	cout<<"插入排序后："<<endl;
	list2.PrintList();
	system("Pause");
}