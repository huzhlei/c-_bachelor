#include<iostream>
#include<time.h>
#include<string>
using namespace std;

template <typename T,int size>class Orderedlist{
	int maxsize;
	int last;
	T slist[size];
public:
	Orderedlist(){last=-1;maxsize=size;}
	void Randlist(int n);
	int Length() const{return last+1;}
	int Partition (const int low,const int high);
	void QuickSort(const int left,const int right);
	void ShellSort();
	void ShellInsert(int dk);
	void BubbleSort();
};
template <typename T,int size> void Orderedlist<T,size>::Randlist(int n){
	int i;
	last=n-1;
	srand((unsigned)time(NULL));
	for(i=0;i<=last;i++){
		slist[i]=(T)(rand()%n);
	}
}
template <typename T,int size> void Orderedlist<T,size>::QuickSort(const int left,const int right){
	if(left<right){	
		int pivotpos=Partition(left,right);
		QuickSort(left,pivotpos-1);	
		QuickSort(pivotpos+1,right);
	}
}
template <typename T,int size> int Orderedlist<T,size>::Partition (const int low,const int high){
	int i=low,j=high;
	T pivot=slist[low];	
	do{
		while((slist[j]>=pivot)&&(i<j))	j--;
		if(i<j) slist[i++]=slist[j];
		while((slist[i]<=pivot)&&( i<j)) i++;	
		if(i<j) slist[j--]=slist[i];
	}while(i!=j);
	slist[i]=pivot;	
	return i;
}
template <typename T,int size> void Orderedlist<T,size>::ShellSort(){
	int dk=last/2;
	for(;dk>=1;dk/=2)   
		ShellInsert(dk); 
}
template <typename T,int size> void Orderedlist<T,size>::ShellInsert(int dk){
	T temp;
	for(int i=dk;i<=last;i++){
		if(slist[i]<slist[i-dk]){
			temp=slist[i];
			int j;
			for(j=i-dk;j>0&&temp<slist[j];j-=dk) slist[j+dk]=slist[j];
			slist[j+dk]=temp;
		}
	}
}
template <typename T,int size> void Orderedlist<T,size>::BubbleSort(){
	bool noswap;
	int i,j;
	T temp;
	for(i=0;i<last;i++){
		noswap=true;
		for(j=last;j>i;j--){
			if(slist[j]<slist[j-1]){
				temp=slist[j];
				slist[j]=slist[j-1];
				slist[j-1]=temp;
				noswap=false;
			}
		}
		if(noswap) break;
	}
}

void main(){
	int n,i;
	string goodsort,badsort;
	double  d[3][20],dur[3]={};
	while(1){
		cout<<"«Î ‰»Î ˝æ›πÊƒ£1-10000"<<endl;
		cin>>n;
		if(n>=1&&n<=10000)break;
	}
	for(i=0;i<20;i++){
		clock_t start, finish;
		Orderedlist<int,10000> alist;
	    alist.Randlist(n);
		start = clock();
		alist.QuickSort(0,n-1);
		finish = clock();
		d[0][i] = (double)(finish - start) / CLOCKS_PER_SEC;
		dur[0] += d[0][i];
	}
	dur[0] /=20;
	for(i=0;i<20;i++){
		clock_t start, finish;
		Orderedlist<int,10000> alist;
	    alist.Randlist(n);
		start = clock();
		alist.ShellSort();
		finish = clock();
		d[1][i] = (double)(finish - start) / CLOCKS_PER_SEC;
		dur[1] += d[1][i];
	}
	dur[1] /=20;
	for(i=0;i<20;i++){
		clock_t start, finish;
		Orderedlist<int,10000> alist;
	    alist.Randlist(n);
		start = clock();
		alist.BubbleSort();
		finish = clock();
		d[2][i] = (double)(finish - start) / CLOCKS_PER_SEC;
		dur[2] += d[2][i];
	}
	dur[2] /=20;
	cout<<"≈≈–Ú÷÷¿‡£∫"<<'\t'<<"øÏÀŸ≈≈–Ú"<<'\t'<<"œ£∂˚≈≈–Ú"<<'\t'<<"√∞≈›≈≈–Ú"<<endl;
	for(i=0;i<20;i++) cout<<i+1<<":\t"<<'\t'<<d[0][i]<<'\t'<<'\t'<<d[1][i]<<'\t'<<'\t'<<d[2][i]<<endl;
	cout<<"∏˜∆Ωæ˘ ±º‰£∫"<<'\t'<<dur[0]<<'\t'<<'\t'<<dur[1]<<'\t'<<'\t'<<dur[2]<<endl;
	if(dur[0]<dur[1]&&dur[0]<dur[2]) goodsort="øÏÀŸ≈≈–Ú";
	else if(dur[1]<dur[0]&&dur[1]<dur[2]) goodsort="œ£∂˚≈≈–Ú";
	else if(dur[2]<dur[1]&&dur[2]<dur[0]) goodsort="√∞≈›≈≈–Ú";
	else if(dur[0]==dur[1]&&dur[0]<dur[2]) {
		goodsort="øÏÀŸ≈≈–Ú&œ£∂˚≈≈–Ú";
		badsort="√∞≈›≈≈–Ú";
	}
	else if(dur[0]==dur[2]&&dur[0]<dur[1]) {
		goodsort="øÏÀŸ≈≈–Ú&√∞≈›≈≈–Ú";
		badsort="œ£∂˚≈≈–Ú";
	}
	else if(dur[1]==dur[2]&&dur[1]<dur[0]) {
		goodsort="œ£∂˚≈≈–Ú&√∞≈›≈≈–Ú";
		badsort="øÏÀŸ≈≈–Ú";
	}
	else if(dur[1]==dur[2]&&dur[1]==dur[0]){
		goodsort="øÏÀŸ≈≈–Ú&œ£∂˚≈≈–Ú&√∞≈›≈≈–Ú";
		badsort="øÏÀŸ≈≈–Ú&œ£∂˚≈≈–Ú&√∞≈›≈≈–Ú";
	}
	if(dur[0]>dur[1]&&dur[0]>dur[2]) badsort="øÏÀŸ≈≈–Ú";
	else if(dur[1]>dur[0]&&dur[1]>dur[2]) badsort="œ£∂˚≈≈–Ú";
	else if(dur[2]>dur[1]&&dur[2]>dur[0]) badsort="√∞≈›≈≈–Ú";
	else if(dur[0]=dur[1]&&dur[0]>dur[2]) {
		goodsort="√∞≈›≈≈–Ú";
		badsort="øÏÀŸ≈≈–Ú&œ£∂˚≈≈–Ú";
	}
	else if(dur[0]=dur[2]&&dur[0]>dur[1]) {
		goodsort="œ£∂˚≈≈–Ú";
		badsort="øÏÀŸ≈≈–Ú&√∞≈›≈≈–Ú";
	}
	else if(dur[1]=dur[2]&&dur[1]>dur[0]) {
		goodsort="øÏÀŸ≈≈–Ú";
		badsort="œ£∂˚≈≈–Ú&√∞≈›≈≈–Ú";
	}
	cout<<"◊Ó∫√≈≈–Ú£∫"<<goodsort<<'\t'<<"◊Óªµ≈≈–Ú:"<<badsort<<'\t'<<"∆Ωæ˘ ±º‰£∫"<<(dur[0]+dur[1]+dur[2])/(double)3<<endl;
	system("Pause");
}
