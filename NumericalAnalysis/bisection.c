#include <stdio.h>
#include <stdlib.h>
#define N 1000
int main() {
	//bisection yöntemi 3 ayrý denklemde denendi 
	int n,i=0,j=0; 
	double f[N],a,b,c,E,k1=1,k2=1,k3=1,sonuc1=0,sonuc2=0,sonuc3=0;
	printf("fonksiyonunuz kacinci dereceden?");
	scanf("%d",&n);
	do{
	   printf("%d. dereceli elemanin kat sayisini giriniz: ",i);
	   scanf("%lf",&f[i]);
	   i++;
	}while(i<=n);
	do{
		sonuc1=0,sonuc2=0,k1=1,k2=1;
	printf(" Hangi aralikta kok araniyor ?? ");
	scanf("%lf%lf",&a,&b);
	for(i=0;i<=n;i++){
		k1=1,k2=1;
			for(j=i;j>0;j--){
				k1=k1*a;
				k2=k2*b;			
			}
			sonuc1=sonuc1+(f[i]*k1);
			sonuc2=sonuc2+(f[i]*k2);
		}
	}while(sonuc1*sonuc2>0);
	if(sonuc1==0){
	printf("kokunuz:%lf",a);
	return 0;
	}
	else if(sonuc2==0){
		printf("kokunuz:%lf",b);
		return 0;
	}
	
	printf("hata payi (E) kac?");
	scanf("%lf",&E);
	while(((a-b)>E && (a-b)>=0) || ((b-a)>E && (b-a)>=0)){
		sonuc1=0,sonuc2=0,sonuc3=0,k1=1,k2=1,k3=1;
		c=(a+b)/2;
		for(i=0;i<=n;i++){
			k1=1,k2=1,k3=1;
			for(j=0;j<i;j++){
				k1=k1*a;
				k2=k2*b;
				k3=k3*c;
			}
			sonuc1=sonuc1+(f[i]*k1);
			sonuc2=sonuc2+(f[i]*k2);
			sonuc3=sonuc3+(f[i]*k3);
		}
		if(sonuc3*sonuc1<0)b=c;
		else a=c;	
	}
	printf("kokunuz: %lf",c);
	
	return 0;
}
