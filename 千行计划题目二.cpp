#include<stdio.h>
int main(){
	int first_number;
	int change=0;
	int i;	
	int a=1;
	for(i=0;i<10;i++){
		change=a+1;
		change=change*2;
		a=change;	
	}	
	first_number=change;
	printf("С���ӵ�һ�칲ժ��%d������",first_number);
	return 0;
}
