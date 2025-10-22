#include<stdio.h>
/*int main(){
	int a;
	int b;
	int i;
	int ret;
	printf("");
	scanf("%d %d",&a,&b);
	if(a>=b){
			for(i=1;i<=a;i++){
		if(a%i==0){
			if(b%i==0){
				ret=i;
			}
		}
		
	}
	}
	else{
			for(i=1;i<=b;i++){
		if(a%i==0){
			if(b%i==0){
				ret=i;
			}
		}
		
	}	
	}
	printf("%d\n",ret);
	return 0;
}*/
int main(){
	int a;
	int b;
	int yushu;
	printf("请输入两个数\n");
	scanf("%d %d",&a,&b);
	while(b!=0){
		yushu=a%b;
		a=b;
		b=yushu;
	}
	printf("最大公约数为%d\n",a);
	
	
	return 0;
}
