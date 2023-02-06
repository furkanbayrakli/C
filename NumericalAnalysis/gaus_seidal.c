#include <stdio.h>
#include <stdlib.h>
#define N 100

int main(int argc, char *argv[]) {
	int i,j,k=0,n,b,a;
	double matris[N][N],B[N],A[2*N],temp,maks,E,x;
		do{
		printf("denkleminiz kac bilinmeyenli?");
	    scanf("%d",&n);
		}while(n<1);
		for(i=0;i<n;i++){
		for(j=0;j<n+1;j++){
			if(j==n){
				printf("%d. denklemin esitligini giriniz:",i+1);
			scanf("%lf",&matris[i][j]);
			}
			else{	
			printf(" %d.denklemin-%d.bilinmeyeninin kat sayisini giriniz:",i+1,j+1);
			scanf("%lf",&matris[i][j]);
			}
		}
	}
	for(i=0;i<n;i++){
		printf("%d. bilinmeyeninizin baslangýc degeri nedir?",i+1);
		scanf("%lf",&B[i]);
	}
	printf("hata payini giriniz:");
	scanf("%lf",&E);
	//matrisin maks satýr olarak kullanýlan satýrýný bir daha kullanmamak için A dizisini oluþturdun! 
	for(i=0;i<n;i++)A[i]=0;
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
     		if(A[i]==0){
	    		maks=matris[i][0];
	    		for(j=0;j<n;j++){
					if((maks>=0 && (maks<matris[i][j] || maks<-matris[i][j]) ) || (maks<0 && (maks>matris[i][j] || maks>-matris[i][j])) ){
						maks=matris[i][j];
						a=i;
						b=j;   	
					}
				}
			}
		}
	    for(j=0;j<n+1;j++){
			temp=matris[a][j];
			matris[a][j]=matris[b][j];
			matris[b][j]=temp;
			A[a]=1;
	   }	
	}
	for(i=0;i<n;i++)A[i]=B[i];
	k=n;
    do{
		for(i=0;i<n;i++){
		    x=0;
		    for(j=0;j<n;j++){
		    	if(i!=j){
		    		x=x-matris[i][j]*B[j];
				}
			}
			x=(x+matris[i][n])/matris[i][i];
			A[k]=x;
			B[i]=A[k];
			if(k==2*n-1)k=0;
			else k++;
			
		}
	}while((A[k%n]-A[n+(k%n)])>E || (A[n+(k%n)]-A[k%n])>E);
	
	if(k==0)k=2*n-1;
	else k=n-1;
	
	do{
		printf("%d. kokunuz= %lf\n",(k%3)+1,A[k]);
		k--;
	}while(k!=-1 && k!=n-1);
	return 0;
}
