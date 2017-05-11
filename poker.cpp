#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class card{
private:
	int type;
	int num;
public:
	card(){}
	card(int,int);
	int gettype(){return type;}
	int getnum(){return num;}
	void showtype();
	void shownum();
	void showcard();
};

card::card(int anum,int atype){
	num=anum;
	type=atype;
}

void card::showtype(){
	if(type==0) cout<<"红桃";
	else if(type==1) cout<<"黑桃";
	else if(type==2) cout<<"梅花";
	else if(type==3) cout<<"方块";

}
void card::shownum(){
	if(num>=2&&num<=10) cout<<num;
	else if(num==1) cout<<"A";
	else if(num==11) cout<<"J";
	else if(num==12) cout<<"Q";
	else if(num==13) cout<<"K";
}
void card::showcard(){
	showtype();
	shownum();
	cout<<'\t';
}

class poker{
private:
card cards[52];
public:
	poker();
	void shuffle();
	card getacard(int i){return cards[i];}
};

poker::poker(){
	for(int i=0;i<52;i++){
		switch(i/13+1){
		case 1:cards[i]=card(i%13+1,0);break;
		case 2:cards[i]=card(i%13+1,1);break;
		case 3:cards[i]=card(i%13+1,2);break;
		case 4:cards[i]=card(i%13+1,3);break;
		default:break;
		}
	}
}



void poker::shuffle(){
	card temp(0,0);
	srand((unsigned)time(NULL));
	for(int i=0;i<52;i++){
		int n=rand()%52;
		temp=cards[i];
		cards[i]=cards[n];
		cards[n]=temp;
	}
}

void showcards(card[],int);
void sortcards(card[],int);
void cardstype(card[],int);

void main(){
	poker apoker;
	apoker.shuffle();
	card c[13];
	for(int i=0;i<13;i++) c[i]=apoker.getacard(i);
	showcards(c,13);
	sortcards(c,13);
	showcards(c,13);
	cardstype(c,13);
}

void showcards(card c[],int n){
	for(int i=0;i<n;i++){
		c[i].showcard();
		if((i+1)%6==0) cout<<endl;
	}
	cout<<endl;
}

void sortcards(card c[],int n){
	card temp;
	int low,high,mid,i,j;
	for(i=1;i<n;i++){
		temp=c[i];
		low=0;
		high=i-1;
		while(low<=high){
			mid=(low+high)/2;
			if(temp.gettype()<c[mid].gettype()) high=mid-1;
			else if((temp.gettype())==(c[mid].gettype())&&temp.getnum()<c[mid].getnum()) high=mid-1;
			else low=mid+1;
		}
		for(j=i-1;j>=low;j--) c[j+1]=c[j];
		c[low]=temp;
	}
}

void cardstype(card c[],int n){
	int i,j,k,a[4][13]={},b[13];
	int two=0,three=0,four=0,shun=0,tshun=0;
	for(i=1;i<=13;i++){
		for(j=0;j<n;j++){
			if(c[j].getnum()==i) {
				if(i==1) a[c[j].gettype()][12]++;
				else a[c[j].gettype()][i-2]++;
			}
		}
	}
	for(i=0;i<13;i++){
		b[i]=a[0][i]+a[1][i]+a[2][i]+a[3][i];
		switch(b[i]){
		case 2: two++;break;
		case 3: three++;break;
		case 4: four++;break;
		}
	}
	for(i=0;i<9;){
		if(b[i]>0&&b[i+1]>0&&b[i+2]>0&&b[i+3]>0&&b[i+4]>0){
			shun++;
			b[i]--;
			b[i+1]--;
			b[i+2]--;
			b[i+3]--;
			b[i+4]--;
			for(j=i+5;j<13;){
				if(b[j]>0) {
					b[j]--;
					j++;
				}
				else break;
			}
		}
		else i++;
	}
	for(k=0;k<4;k++){
		for(i=0;i<9;){
			if(a[k][i]>0&&a[k][i+1]>0&&a[k][i+2]>0&&a[k][i+3]>0&&a[k][i+4]>0){
				tshun++;
			    a[k][i]--;
			    a[k][i+1]--;
				a[k][i+2]--;
				a[k][i+3]--;
				a[k][i+4]--;
				for(j=i+5;j<13;){
					if(a[k][j]>0) {
						a[k][j]--;
						j++;
					}
					else break;
				}
			}
			else i++;
		}
	}
	cout<<"对子数量为："<<two<<'\t'<<"三条数量为："<<three<<'\t'<<"炸弹数量为："<<four<<endl;
	cout<<"顺子数量为："<<shun<<'\t'<<"同花顺数量为："<<tshun<<endl;
}

