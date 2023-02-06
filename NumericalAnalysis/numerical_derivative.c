#include <stdio.h>
#include <stdlib.h>
#define N 100
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int n,i,j,y;
	double f[N],x,h,f1=0,f2=0,f3=0,k1,k2,k3;
	printf("fonksiyonunuz kacinci dereceden?");
	scanf("%d",&n);
	do{
	   printf("%d. dereceli elemanin kat sayisini giriniz: ",i);
	   scanf("%lf",&f[i]);
	   if(i==n && f[i]==0){
	   	printf("\n\ngirdiginiz fonksiyonun derecesi belirttiginiz degerde degil!!!!");
	   	return 1;
	   }
	   i++;
	}while(i<=n);
	printf("turevini istediginiz kok?");
	scanf("%lf",&x);
	printf("adim araligini giriniz:");
	scanf("%lf",&h);
	
		for(i=0;i<=n;i++){
		k1=1,k2=1,k3=1;
			for(j=i;j>0;j--){
			k1=k1*(x-h);
			k2=k2*x;
			k3=k3*(x+h);
			} 	
			f1=f1+(f[i]*k1);
			f2=f2+(f[i]*k2);
			f3=f3+(f[i]*k3);
		}
	do {	
	    printf("hangi yontemle turev sonucunuzu istiyorsunuz? (1-geri  2- ileri  3-merkezi)");
		scanf("%d",&y);
	}while(y<1 || y>3);	
	
    if(y==1)printf("f'(.3%lf) = %lf",x,(f2-f1)/h);
    else if(y==2)printf("f'(.3%lf) = %lf",x,(f3-f2)/h);
    else printf("f'(%.3lf) = %lf",x,(f3-f1)/(2*h));
	return 0;
}
