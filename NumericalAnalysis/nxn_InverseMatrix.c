#include <stdio.h>
#include <stdlib.h>
#define N 100

int main(int argc, char *argv[]) {
	int i,j,k,n,p,o;
	double matris[N][N],I[N][N],a,b;
	printf("kare matrisiniz kaca satirlik?");
	scanf("%d",&n);
		for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("matrisin %d.satir-%d.sutununu giriniz:",i+1,j+1);
			scanf("%lf",&matris[i][j]);
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			I[i][j]=0;
		if(i==j)I[i][j]=1;
		}		
	}



	for(i=0;i<n;i++){
	 	a=matris[i][i];
	 	for(j=0;j<n;j++){
		    I[i][j]=I[i][j]/a;
		    matris[i][j]=matris[i][j]/a;
		}	
		for(j=0;j<n;j++){
			b=matris[j][i];
			if(i!=j){
				for(k=0;k<n;k++){
				matris[j][k]=matris[j][k]-(matris[i][k]*b);
				I[j][k]=I[j][k]-(I[i][k]*b);
				}	
			}
		}
			printf("asil matris\n");
	for(p=0;p<n;p++){
		printf("\n");
		for(o=0;o<n;o++){
			printf(" %lf ",matris[p][o]);
			
		}
	}
	}
	
	printf("\n\nmatrisin tersi\n");
	for(i=0;i<n;i++){
		printf("\n");
		for(j=0;j<n;j++){
			printf(" %lf ",I[i][j]);	
		}
	}
	return 0;
}
