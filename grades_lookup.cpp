#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int allmember=0,classmember,sexmember;

class student{
private:int id;
		string name;
		string sex;
		double score;
public:student(){}
	   student(int,string,string,double);
	   int getid(){return id;}
	   string getname(){return name;}
	   string getsex(){return sex;}
	   double getscore(){return score;}
};
student::student(int aid,string aname,string asex,double ascore){
	id=aid;
	name=aname;
	sex=asex;
	score=ascore;
}

void sort(student *alist[],int member);
void selectclass(student *alist[],student *cllist[],int cl,int member);
void selectsex(student *alist[],student *sexlist[],string s,int member);
void findid(student *alist[],int theid,int member);
void findname(student *alist[],string thename,int member);
void calc(student *alist[],double low,double high,int member);
void show(student *alist[],int member);

int main(){
	int num,i=0,n,aid;
	double ascore;
	student *alist[100];
	string aname,asex;
	student stlist[100];
	ifstream lt;

	cout<<"�뽫��Ҫ������ļ������ڸ�Ŀ¼�²�����Ϊlist.txt"<<endl;
	system("pause"); 
	lt.open("list.txt");

	cout<<"��ȡ�ļ��С�����"<<endl;
	while(1){
		lt>>aid>>aname>>asex>>ascore;
		stlist[i]=student(aid,aname,asex,ascore);
		i++;
		allmember++;
		if(lt.eof()!=0) break;
	}
	
	lt.close();
	
	for(n=0;n<100;n++) alist[n]=&stlist[n];
	sort(alist,allmember);

	while(1){
		cout<<"����������1-7�������²���"<<endl;
		cout<<"����1��ʾȫ����Ա�ĳɼ�����"<<endl;
		cout<<"����2��ʾͬ��ĳɼ�����"<<endl;
		cout<<"����3��ʾ��/Ů���ĳɼ�����"<<endl;
		cout<<"����4����ѧ�Ų�ѯ�ɼ�������"<<endl;
		cout<<"����5����������ѯ�ɼ�������"<<endl;
		cout<<"����6��������ķ�����ͳ�������;���"<<endl;
		cout<<"����7���˳�����"<<endl;
		cin>>num;
		switch(num){
		default:break;
		case 1:{
			show(alist,allmember);
			break;
			   }
		case 2:{
			int cl;
			student *cllist[100];
			cout<<"�������������İ༶��1-6��ѡ��"<<endl;
			cin>>cl;
			if(cl>=1&&cl<=6){
				selectclass(alist,cllist,cl,allmember);
				show(cllist,classmember);
			}
			else cout<<"�������"<<endl;
			break;
			   }
		case 3:{
			string s;
			student *sexlist[100];
			cout<<"�����л�Ů��ʾ������Ů��������"<<endl;
			cin>>s;
			if(s=="��"||s=="Ů"){
				selectsex(alist,sexlist,s,allmember);
				show(sexlist,sexmember);
			}
			else cout<<"�������"<<endl;
			break;
			   }
		case 4:{
			int theid;
			cout<<"��������Ҫ��ѯ��ѧ��"<<endl;
			cin>>theid;
			findid(alist,theid,allmember);
			break;
			   }
		case 5:{
			string thename;
			cout<<"��������Ҫ��ѯ������"<<endl;
			cin>>thename;
			findname(alist,thename,allmember);
			break;
			   }
		case 6:{
			double low,high;
			cout<<"��������ͷֺ���߷�"<<endl;
			cin>>low>>high;
			if(low<=high)calc(alist,low,high,allmember);
			else cout<<"�������"<<endl;
			break;
			   }
		case 7:return 0;
		}
	}
}

void sort(student *alist[],int member){
	student *temp;
	int low,high,mid,i,j;
	for(i=1;i<member;i++){
		temp=alist[i];
		low=0;
		high=i-1;
		while(low<=high){
			mid=(low+high)/2;
			if((*temp).getscore()>(*alist[mid]).getscore()) high=mid-1;
			else low=mid+1;
		}
		for(j=i-1;j>=low;j--) alist[j+1]=alist[j];
		alist[low]=temp;
	}
}

void selectclass(student *alist[],student *cllist[],int cl,int member){
	int i=0,j=0;
	classmember=0;
	for(;i<member;i++){
		if((((*alist[i]).getid())/100)%10==cl){
			cllist[j]=alist[i];
			j++;
			classmember++;
		}
	}
}

void selectsex(student *alist[],student *sexlist[],string s,int member){
	int i=0,j=0;
	sexmember=0;
	for(;i<member;i++){
		if((*alist[i]).getsex()==s){
			sexlist[j]=alist[i];
			j++;
			sexmember++;
		}
	}
}
	
void findid(student *alist[],int theid,int member){
	int i=0;
	for(;i<member;i++){
		if((*alist[i]).getid()==theid){
			cout<<(*alist[i]).getid()<<'\t'<<(*alist[i]).getname()<<"�ɼ�Ϊ��"<<'\t'<<(*alist[i]).getscore()<<"����Ϊ��"<<i<<endl;
			break;
		}
	}
}

void findname(student *alist[],string thename,int member){
	int i=0;
	for(;i<member;i++){
		if((*alist[i]).getname()==thename){
			cout<<(*alist[i]).getid()<<'\t'<<(*alist[i]).getname()<<"�ɼ�Ϊ��"<<'\t'<<(*alist[i]).getscore()<<"����Ϊ��"<<i<<endl;
			break;
		}
	}
}

void calc(student *alist[],double low,double high,int member){
	int i=0,j=0,number;
	double sum=0,average;
	for(;i<member;i++){
		if((*alist[i]).getscore()<low) break;
		if((*alist[i]).getscore()>high) j=i;
		if((*alist[i]).getscore()<=high) sum+=(*alist[i]).getscore();
	}
	number=i-j-1;
	average=sum/(double)number;
	cout<<"�����δ�"<<low<<"��"<<high<<"������Ϊ��"<<number<<'\t'<<"����Ϊ"<<average<<endl;
}

void show(student *alist[],int member){
	for(int i=0;i<member;i++){
		cout<<(*alist[i]).getid()<<'\t'<<(*alist[i]).getname()<<'\t'<<(*alist[i]).getsex()<<'\t'<<(*alist[i]).getscore()<<endl;
	}
}