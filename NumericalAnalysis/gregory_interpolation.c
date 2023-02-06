#include <stdio.h>
#include <stdlib.h>
#define N 10


int main(int argc, char *argv[]) {
	int i,n,sayac=1;
	double Fx[N],F0[N],h,x[N],Q,sonuc=0,k=1,s=1;
	do{
	printf("kac adet deger girilecek?");
	scanf("%d",&n);	
	}while(n<2);
	printf("\n\n\n");
	for(i=0;i<n;i++){
		printf("%d.  x degeri:",i+1);	
	    scanf("%lf",&x[i]);
	    printf("%d. x degerinin fonksiyon esitligi:",i+1);
	    scanf("%lf",&Fx[i]);
    	printf("\n\n");
	}
	sonuc=Fx[0];
	
	printf("fonksiyonda hangi x degerini ariyorsunuz?");
	scanf("%lf",&Q);
	while(Fx[0]-Fx[1]!=0){
		for(i=0;i<n-1;i++){
			F0[i]=Fx[i+1]-Fx[i];
			Fx[i]=F0[i];
		}
		k=1;
		s=1;
		for(i=1;i<=sayac;i++){
			h=x[i]-x[i-1];
			k=k*i*h;
			s=s*(Q-x[i-1]);
		}
		sonuc=sonuc+F0[0]*s/k;
		sayac++;
		n--;
	}
	
	printf("\n\nF(%lf) = %.3lf",Q,sonuc);
	
	
	return 0;
}
