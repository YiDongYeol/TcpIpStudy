#include <stdio.h>

void main(){

	int ind;
	int res=0;
	
	printf("INPUT => ");
	scanf("%d",&ind);

	res+=(ind%2);
	ind/=2;

	for(int i=0; i<ind; i++){
		res += ((i*2)+1);
		res += ((i*2)+2);
	}

	printf("%d\n",res);

}

