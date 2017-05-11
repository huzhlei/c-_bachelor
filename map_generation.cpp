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
	cout<<"输出地图在根目录下"<<endl;
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
	cout<<"输出地图在根目录下"<<endl;
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
	cout<<"本地图生成器由数字表示地形高度，字母表示地形类型的小方块表示的像素块组成"<<endl;
	cout<<"正方形元素随机地图中元素例如11 表示该像素块的地形类型为a，地形高度为1"<<endl;
	cout<<"                            bb"<<endl;
	cout<<"六边形元素随机地图中元素例如 00 表示该像素块的地形类型为a，地形高度为1"<<endl;
	cout<<"                            0a10"<<endl;
	cout<<"                             00"<<endl;
	srand(unsigned(time(NULL)));
	while(1){
		int num,l,w;
		cout<<"生成正方形元素随机地图请输入1，读入正方形元素地图请输入2"<<endl;
		cout<<"生成六边形元素随机地图请输入3，读入六边形元素地图请输入4"<<endl;
		cin>>num;
		if(num==1){
			cout<<"请输入地形的长和宽"<<endl;
			cin>>l>>w;
			map mapsq(l,w);
			mapsq.randmap();
			mapsq.outputmap();

		}
		if(num==2){
			map read(0,0);
			cout<<"请将地图放在程序根目录并重命名为mysqmap"<<endl;
			system("pause>nul");
			ifstream mapread;
			mapread.open("mysqmap.txt");
			while(!mapread){
				cout<<"请重新将地图放在程序根目录并重命名为mysqmap"<<endl;
			}
			read.getmap(mapread);
			read.outputmap();
			mapread.close();
		}
		if(num==3){
			cout<<"请输入地形的长和宽"<<endl;
			cin>>l>>w;
			map maphex(l,w);
			maphex.randmap();
			maphex.outputmaphex();
		}
		if(num==4){
			map read(0,0);
			cout<<"请将地图放在程序根目录并重命名为myhexmap"<<endl;
			system("pause>nul");
			ifstream mapread;
			mapread.open("myhexmap.txt");
			while(!mapread){
				cout<<"请重新将地图放在程序根目录并重命名为myhexmap"<<endl;
			}
			read.getmaphex(mapread);
			read.outputmaphex();
			mapread.close();
		}
	}

}