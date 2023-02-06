#include <stdio.h>
#include <stdlib.h>
#define N 100

int main(int argc, char *argv[]) {
	int i,j,k,n;
	double matris[N][N+1],I[N],a,b;
	printf("denkleminiz kac bilinmeyenli?");
	scanf("%d",&n);
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
	system("cls");
	for(i=0;i<n;i++)I[i]=0;
	printf("denklem matrisi\n");
	for(i=0;i<n;i++){
		printf("\n");
		for(j=0;j<n+1;j++){
			if(j==n)printf("  | %0.3lf |",matris[i][j]);
			else  printf(" %0.3lf ",matris[i][j]);
		
		}
	}

	for(i=0;i<n;i++){
	 	a=matris[i][i];
	 	for(j=i;j<n+1;j++){
		    matris[i][j]=matris[i][j]/a;
		}	
		for(j=i+1;j<n;j++){
			b=matris[j][i];
			for(k=i;k<n+1;k++){
				matris[j][k]=matris[j][k]-(matris[i][k]*b);
			}
		}
	}
	
	printf("\n\n\n\n\n   denklem bilinmeyenleri  \n");
	for(i=n-1;i>=0;i--){
		I[i]=matris[i][n];
		for(j=i+1;j<n;j++){
			a=0;
			for(k=n-1;k>i;k--){
				a=a+(I[k]*matris[i][k]);
			}
			I[i]=matris[i][n]-a;
		}
	}
		for(i=0;i<n;i++){
			printf("    %d. bilinmeyen= %0.3lf ",i+1,I[i]);
			printf("\n");
	}
	return 0;
}
