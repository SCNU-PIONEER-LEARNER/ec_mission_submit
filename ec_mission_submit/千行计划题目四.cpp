#include<stdio.h>
int main(){
	int a[7];
	int i;
	for(i=0;i<7;i++){
		printf("请输入数组中第%d个数\n",i+1);
		scanf("%d",&a[i]);
	}
	int j;
	int k;
	int temp;
	for(j=0;j<6;j++){
		for(k=0;k<6-j;k++){
			if(a[k]>a[k+1]){
				 temp=a[k];
				a[k]=a[k+1];
				a[k+1]=temp;
			}
		}
		
	}
	printf(": \n");
    for (i = 0; i < 7; i++) {
        printf("%d ", a[i]);
    }
	
	return 0;
}
