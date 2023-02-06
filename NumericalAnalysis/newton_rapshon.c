#include <stdio.h>
#include <stdlib.h>
#define N 100

int main() {
	int n,i=0,j=0; 
	double f[N],f_turev[N-1],a,b,c,E,k1,k2,sonuc1,sonuc2;
	printf("fonksiyonunuz kacinci dereceden?");
	scanf("%d",&n);
	do{
	   printf("%d. dereceli elemanin kat sayisini giriniz: ",i);
	   scanf("%lf",&f[i]);
	   i++;
	}while(i<=n);
	i=0;
	while(i<=n){
		f_turev[i]=f[i]*i;
		i++;
	}
	printf(" baslangýc degeri nedir? ");
	scanf("%lf",&a);
	for(i=0;i<=n;i++){
		k1=1;
			for(j=i;j>0;j--){
				k1=k1*a;			
			}
			sonuc1=sonuc1+(f[i]*k1);
			sonuc2=sonuc2+(f_turev[i]*k1/a);
		}
	if(sonuc1==0){
	printf("kokunuz:%lf",a);
	return 0;
	}
	printf("hata payi (E) kac?");
	scanf("%lf",&E);
	do{
	    sonuc1=0,sonuc2=0,k1=1,k2=1;
		for(i=0;i<=n;i++){
			k1=1;
			for(j=0;j<i;j++){
				k1=k1*a;	
			}
			sonuc1=sonuc1+(f[i]*k1);
			sonuc2=sonuc2+(f_turev[i]*k1/a);
		}
		b=a-(sonuc1/sonuc2);
		printf("%lf",b);
		c=a;
		a=b;
	}while(((c-b)>E && (c-b)>=0) || ((b-c)>E && (b-c)>=0));
	printf("kokunuz: %lf",b);
	
	return 0;
}
