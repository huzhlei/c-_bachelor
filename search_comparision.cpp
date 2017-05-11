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
		cout<<"���������ݹ�ģ1-10000"<<endl;
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
	cout<<"�������ࣺ"<<'\t'<<"��������"<<'\t'<<"ϣ������"<<'\t'<<"ð������"<<endl;
	for(i=0;i<20;i++) cout<<i+1<<":\t"<<'\t'<<d[0][i]<<'\t'<<'\t'<<d[1][i]<<'\t'<<'\t'<<d[2][i]<<endl;
	cout<<"��ƽ��ʱ�䣺"<<'\t'<<dur[0]<<'\t'<<'\t'<<dur[1]<<'\t'<<'\t'<<dur[2]<<endl;
	if(dur[0]<dur[1]&&dur[0]<dur[2]) goodsort="��������";
	else if(dur[1]<dur[0]&&dur[1]<dur[2]) goodsort="ϣ������";
	else if(dur[2]<dur[1]&&dur[2]<dur[0]) goodsort="ð������";
	else if(dur[0]==dur[1]&&dur[0]<dur[2]) {
		goodsort="��������&ϣ������";
		badsort="ð������";
	}
	else if(dur[0]==dur[2]&&dur[0]<dur[1]) {
		goodsort="��������&ð������";
		badsort="ϣ������";
	}
	else if(dur[1]==dur[2]&&dur[1]<dur[0]) {
		goodsort="ϣ������&ð������";
		badsort="��������";
	}
	else if(dur[1]==dur[2]&&dur[1]==dur[0]){
		goodsort="��������&ϣ������&ð������";
		badsort="��������&ϣ������&ð������";
	}
	if(dur[0]>dur[1]&&dur[0]>dur[2]) badsort="��������";
	else if(dur[1]>dur[0]&&dur[1]>dur[2]) badsort="ϣ������";
	else if(dur[2]>dur[1]&&dur[2]>dur[0]) badsort="ð������";
	else if(dur[0]=dur[1]&&dur[0]>dur[2]) {
		goodsort="ð������";
		badsort="��������&ϣ������";
	}
	else if(dur[0]=dur[2]&&dur[0]>dur[1]) {
		goodsort="ϣ������";
		badsort="��������&ð������";
	}
	else if(dur[1]=dur[2]&&dur[1]>dur[0]) {
		goodsort="��������";
		badsort="ϣ������&ð������";
	}
	cout<<"�������"<<goodsort<<'\t'<<"�����:"<<badsort<<'\t'<<"ƽ��ʱ�䣺"<<(dur[0]+dur[1]+dur[2])/(double)3<<endl;
	system("Pause");
}
