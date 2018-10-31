#include <iostream>
#include <stdio.h>
using namespace std;
int findKthLargest(int A[],int k,int len);
int partition(int A[],int left,int right);
int main(){
	int size;
	scanf("%d",&size);
	int A[size];
	int k;
	scanf("%d",&k);
	for(int i=0;i<size;i++){
		scanf("%d",&A[i]);
	}
	printf("%d\n",findKthLargest(A,k,size));
	return 0;
}
int findKthLargest(int A[],int k,int len){
	int left=0;
	int right=len-1;
	while(true){
		int pos=partition(A,left,right);
		if(pos==(k-1)){
			return A[pos];
		}else if(pos>(k-1)){
			right=pos-1;
		}else{
			left=pos+1;
		}
	}
}
int partition(int A[],int left,int right){
	int pivot=A[left];
	int l=left+1;
	int r=right;
	while(l<=r){
		if(A[l]<pivot&&A[r]>pivot){
			swap(A[l++],A[r--]);
		}
		if(A[l]>=pivot){
			++l;
		}
		if(A[r]<=pivot){
			--r;
		}
	}
	swap(A[left],A[r]);
	return r;
}





