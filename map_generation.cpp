#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;

class pixel{
private:
	int height;
	char type;
public:
	pixel(){
		height=0;
		type=0;
	}
	pixel(int h,char t){
		height=h;
		type=t;
	}
	int geth(){
		return height;
	}
	char gett(){
		return type;
	}
	pixel randps();
};
pixel pixel::randps(){
	height=rand()%10;
	type='a'+rand()%26;
	return pixel(height,type);
}

class map{
private:
	int length;
	int width;
	pixel temppl[600][800];
public:
	map(int l,int w){
		length=l;
		width=w;
	}
	void randmap();
	void outputmap();
	void getmap(ifstream&);
	void outputmaphex();
	void getmaphex(ifstream&);
};
void map::randmap(){
	int l=0,w;
	for(;l<length;l++){
		for(w=0;w<width;w++){
			temppl[l][w]=temppl[l][w].randps();
		}
	}
}
void map::outputmap(){
	int l=0,w,i,j;
	cout<<"�����ͼ�ڸ�Ŀ¼��"<<endl;
	ofstream msq;
	msq.open("squaremap.txt");
	msq<<length<<'\t'<<width<<endl;
	for(;l<length;l++){
		for(i=0;i<=1;i++){
			for(w=0;w<width;w++){
				for(j=0;j<=1;j++){
					if(i==0) msq<<temppl[l][w].geth();
					if(i==1) msq<<temppl[l][w].gett();
					}
			}
			msq<<endl;
		}
	}
	msq.close();
}
void map::getmap(ifstream& sqmap){
	int l,w,temp[800],i=0,j=0;
	char ch;
	sqmap>>l;
	sqmap>>w;
	length=l;
	width=w;
	while(sqmap.eof()==0){
		ch=sqmap.get();
		if(ch!=char(10)&&j<l){
			if(i>=4*w){
				j++;
				i=0;
			}
			if(i%2==0&&i<(2*w)) temp[i/2]=ch-'0';
			if(i%2==0&&i>=(2*w)&&i<(4*w)){
				int t=(i-(2*w))/2;
				pixel tsq(temp[t],ch);
				temppl[j][t]=tsq;
			}
			i++;
		}
	}
}
void map::outputmaphex(){
	int l=0,w;
	cout<<"�����ͼ�ڸ�Ŀ¼��"<<endl;
	ofstream mhex;
	mhex.open("hexmap.txt");
	mhex<<length<<'\t'<<width<<endl;
	for(w=0;w<width;w++){
		mhex<<" 00 ";
	}
	mhex<<endl;
	for(;l<length;l++){
		if(l%2==0) {
			for(w=0;w<width;w++){
			mhex<<'0'<<temppl[l][w].gett()<<temppl[l][w].geth()<<'0';
			}
			mhex<<'0'<<endl;
		}
		else{
			mhex<<' ';
			for(w=0;w<width;w++){
			mhex<<"00"<<temppl[l][w].gett()<<temppl[l][w].geth();
			}
			mhex<<'0'<<endl;
		}
	}
	if(length%2==0){
		mhex<<"  ";
		for(w=0;w<width;w++){
		mhex<<" 00 ";
		}
	}
	else{
		for(w=0;w<width;w++){
		mhex<<" 00 ";
		}
	}
}
void map::getmaphex(ifstream& hexmap){
	int l,w,i=0,j=0,h;
	char ch,t;
	hexmap>>l;
	hexmap>>w;
	length=l;
	width=w;
	ch=hexmap.get();
	hexmap.clear();
	while(1){
		ch=hexmap.get();
		if(ch==char(10))break;
	}
	hexmap.clear();
	for(;j<l;j++){
		int x=0;
		for(i=0;i<=(4*w);){
			ch=hexmap.get();
			if(ch!=char(10)&&ch!=' '){
				if(j%2==0){
					if(i%4==1) t=ch;
					if(i%4==2){
						h=ch-'0';
						pixel thex(h,t);
						temppl[j][x]=thex;
						x++;
					}
				}
				else{
					if(i%4==2) t=ch;
					if(i%4==3){
						h=ch-'0';
						pixel thex(h,t);
						temppl[j][x]=thex;
						x++;
					}
				}
				i++;
			}
		}
	}
}
void main(){
	cout<<"����ͼ�����������ֱ�ʾ���θ߶ȣ���ĸ��ʾ�������͵�С�����ʾ�����ؿ����"<<endl;
	cout<<"������Ԫ�������ͼ��Ԫ������11 ��ʾ�����ؿ�ĵ�������Ϊa�����θ߶�Ϊ1"<<endl;
	cout<<"                            bb"<<endl;
	cout<<"������Ԫ�������ͼ��Ԫ������ 00 ��ʾ�����ؿ�ĵ�������Ϊa�����θ߶�Ϊ1"<<endl;
	cout<<"                            0a10"<<endl;
	cout<<"                             00"<<endl;
	srand(unsigned(time(NULL)));
	while(1){
		int num,l,w;
		cout<<"����������Ԫ�������ͼ������1������������Ԫ�ص�ͼ������2"<<endl;
		cout<<"����������Ԫ�������ͼ������3������������Ԫ�ص�ͼ������4"<<endl;
		cin>>num;
		if(num==1){
			cout<<"��������εĳ��Ϳ�"<<endl;
			cin>>l>>w;
			map mapsq(l,w);
			mapsq.randmap();
			mapsq.outputmap();

		}
		if(num==2){
			map read(0,0);
			cout<<"�뽫��ͼ���ڳ����Ŀ¼��������Ϊmysqmap"<<endl;
			system("pause>nul");
			ifstream mapread;
			mapread.open("mysqmap.txt");
			while(!mapread){
				cout<<"�����½���ͼ���ڳ����Ŀ¼��������Ϊmysqmap"<<endl;
			}
			read.getmap(mapread);
			read.outputmap();
			mapread.close();
		}
		if(num==3){
			cout<<"��������εĳ��Ϳ�"<<endl;
			cin>>l>>w;
			map maphex(l,w);
			maphex.randmap();
			maphex.outputmaphex();
		}
		if(num==4){
			map read(0,0);
			cout<<"�뽫��ͼ���ڳ����Ŀ¼��������Ϊmyhexmap"<<endl;
			system("pause>nul");
			ifstream mapread;
			mapread.open("myhexmap.txt");
			while(!mapread){
				cout<<"�����½���ͼ���ڳ����Ŀ¼��������Ϊmyhexmap"<<endl;
			}
			read.getmaphex(mapread);
			read.outputmaphex();
			mapread.close();
		}
	}

}