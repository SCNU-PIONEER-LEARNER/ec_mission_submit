#include<stdio.h>
int main(){
	int i;
	int o;
	int p;
	int number;
	int count;
	for(i=1;i<=4;i++){
		for(o=1;o<=4;o++){
			for(p=1;p<=4;p++){
			number=i*100+o*10+p;
			printf("%d\n",number);
			count++;
			}
		}	
	}
	printf("一共有%d个数\n",count);
	return 0;
}
