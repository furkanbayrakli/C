#include <stdio.h>
#include <stdlib.h>
#define N 100
int main() {
	int n,i,j,h,sayac=0;
	double f[N],sonuc1,k1,a,b,delta,k,S=0;
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
	do{	
	system("cls");
	printf("alanini istediginiz araligi giriniz(kuckten buyuge):");
	scanf("%lf %lf",&a,&b);
	}while(a>b);
	do{
	system("cls");
	printf("alan hesaplanirken kullanilacak n degeri?");
	scanf("%d",&h);
	}while(h<1);
	delta=(b-a)/h;
	k=a;
	while(k<=b){
		sonuc1=0;
		for(i=0;i<=n;i++){
		k1=1;
			for(j=i;j>0;j--) k1=k1*k;	
			sonuc1=sonuc1+(f[i]*k1);
		}
	    if(k!=a && k!=b && sayac%2==0)S=S+2*sonuc1;
	    else if(k!=a && k!=b && sayac%2==1)S=S+4*sonuc1;
	    else S=S+sonuc1;
	    k=k+delta;
	    sayac++;
	}
	S=S*delta/3;
	printf("verilen fonksiyonun istenen araliginin x ekseni ile arasinda kalan alan= %lf ",S);
	
	
	return 0;
}
