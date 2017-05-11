#include<iostream>
#include <string.h>
#include <time.h>
using namespace std;
bool rn(int year);
int td(int month,int day);
bool pd(int year,int mon,int day);
int feb;
int main(){
	int y,runnian=0,week,total=0,pty,ptm,ptd;
	struct tm *pt,t;
	time_t long_time;
    time( &long_time );             
    pt=localtime( &long_time );
    pty=pt->tm_year+1900;
	ptm=pt->tm_mon+1;
	ptd=pt->tm_mday;
	cout<<"请输入任意日期"<<endl;
	cin>>t.tm_year>>t.tm_mon>>t.tm_mday;
	while(pd(t.tm_year,t.tm_mon,t.tm_mday)){
		cout<<"请重新输入任意日期"<<endl;
		cin>>t.tm_year>>t.tm_mon>>t.tm_mday;
	}
	if(t.tm_year>pty){
		for(y=pty;y<t.tm_year;y++){
		if(rn(y)) runnian++;
		}
	    total=(t.tm_year-pty)*365+runnian;
	}
	else if(t.tm_year<pty){
		for(y=t.tm_year;y<pty;y++){
		if(rn(y)) runnian++;
		}
		total=(t.tm_year-pty)*365-runnian;
	}
	else total=0;

    rn(pty);
	total-=td(ptm,ptd);
	rn(t.tm_year);
	total+=td(t.tm_mon,t.tm_mday);
	cout<<t.tm_year<<'/'<<t.tm_mon<<'/'<<t.tm_mday<<"与当前相差"<<total<<"天"<<endl;
	week=pt->tm_wday+total%7;
	cout<<t.tm_year<<'/'<<t.tm_mon<<'/'<<t.tm_mday<<"为";
	switch(week){
	case 0:cout<<"星期日"<<endl;break;
	case 1:cout<<"星期一"<<endl;break;
	case 2:cout<<"星期二"<<endl;break;
	case 3:cout<<"星期三"<<endl;break;
	case 4:cout<<"星期四"<<endl;break;
	case 5:cout<<"星期五"<<endl;break;
	case 6:cout<<"星期六"<<endl;break;
	}
	return 0;

}
bool rn(int year){
	if(year%4==0&&year%100!=0||year%400==0) {
		feb=29;
		return 1;
	}
	else{
		feb=28;
		return 0;

	}
}
int td(int month,int day){
	int m=0,n=0;
	for(;m<month;m++){
		switch(m){
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:n=n+31;break;
		case 4:case 6:case 9:case 11:n=n+30;break;
		case 2:n=n+feb;break;
		default:n=0;
		}
	}
	n=n+day;
	return n;
}
bool pd(int year,int mon,int day){
	switch(mon){
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			{
			if(day>=1&&day<=31) return 0;
			else return 1;
			}break;
		case 4:case 6:case 9:case 11:
			{
			if(day>=1&&day<=30)return 0;
			else return 1;
			} break;
		case 2:
			{
			if(rn(year)&&day>=1&&day<=29)return 0;
			else if(rn(year)==0&&day>=1&&day<=28)return 0;
			else return 1;
			}break;
		default:return 1;break;
		}
}