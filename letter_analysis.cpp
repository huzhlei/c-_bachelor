#include<iostream>
#include<string>
#include <stdlib.h>
using namespace std;
void main(){
	string str="",str1="",str2="",str3;
	int i=0,j,pos,n=0,len,len1,lenm,max=0;
	char ch;
	double f,chd;
	int nword=0,nch=0,chars[26]={0};
	int isword=0;
	cout<<"������һƪ����"<<endl;
	/*getline(cin,str,'\n');*/
	while(1){
		ch=cin.get();
		if(ch==EOF) break;
		str+=ch;
	}
	len1=str.length();
	str=str.substr(0,len1-1);
	len1=len1-1;
	for(;i<len1;i++){
		ch=str[i];
		if(ch!=' '&&ch!='\t'&&ch!='\n'&&ch!=EOF&&ch!='!'&&ch!=','&&ch!=';'&&ch!=':'&&ch!='.'&&ch!='?'){
			if(!isword) nword++;
			nch++;
			isword=1;
			for(j=0;j<=25;j++){
				if(ch-'A'==j||ch-'a'==j){
					chars[j]++;
					break;
				}
			}
		}
		else isword=0;
		
	}
	
	cout<<"Ӣ����ĸ������Ϊ:"<<nch<<endl;
	cout<<"���ʵ�����:"<<nword<<endl;
	for(i=0;i<=25;i++){
		f=(double)chars[i]/(double)nch;
		cout<<"��ĸ"<<(char)(65+i)<<"���ֵ�Ƶ��Ϊ��"<<f<<endl;
	}
	cout<<"���������ַ���"<<endl;
	cin.clear();
	while(1){
		ch=cin.get();
		if(cin.eof()!=0) break;
		str1+=ch;
	}
	len=str1.length();
	str1=str1.substr(0,len-1);
	pos=str.find(str1);
	while(pos!=-1){
		n++;
		pos+=(len-1);
		pos=str.find(str1,pos);
	}
	cout<<"���ַ����������г���"<<n<<"��"<<endl;
	cin.clear();
	cout<<"������һƪ����"<<endl;
	while(1){
		ch=cin.get();
		if(cin.eof()!=0) break;
		str2+=ch;
	}
	len=str2.length();
	str2=str2.substr(0,len-1);
	len=len-1;
	for(j=len;j>0;j--){
		for(i=0;i+j<=len;i++){
			str3=str2.substr(i,j);
			lenm=str3.length();
			pos=str.find(str3);
			if(pos!=-1&&lenm>max) max=lenm;
		}
	}
	
	chd=(double)max/(double)len1;
	cout<<"��ƪ���µ��غ϶�Ϊ��"<<chd<<endl;
	system("pause>nul");

	
}