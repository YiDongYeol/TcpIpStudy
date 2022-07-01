#include <stdio.h>

void main(){
	int inp;
	int res = 0;
	printf("INPUT => ");
	scanf("%d",&inp);
	for(int i = 1; i < inp + 1; i++){
		res+=i;
	}

	printf("%d\n",res);

}
