#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	char level[7],array1[8][9]={"********","********","********","********","********","********","********","********"};
	int i=0,j=0,k=0,m=0,s=0,n,a=1,line1,column1,line2,column2,turn=1,g=1,guess1=0,guess2=0,pg=0,cg=0,flag=0,scorep=0,scorecpu=0,tr=1,f,memory[3][16],array2[8][8];
    
	srand(time(NULL));
	printf("\n\n\n                 __  __  __  __  __  __  __  __  __ \n");
	printf("                |__||__||__||__||__||__||__||__||__|\n");
	printf("                |__|                            |__|\n");
	printf("                |__|****************************|__|\n");
	printf("                |__|******* BE READY FOR *******|__|\n");
	printf("                |__|******* BRAIN TEASER *******|__|\n"); 
	printf("                |__|****************************|__|\n");
	printf("                |__| __  __  __  __  __  __  __ |__|\n");
	printf("                |__||__||__||__||__||__||__||__||__|\n\n\n\n\n\n");

    printf("                ***********************************\n");
	printf("                ***********************************\n");
	printf("                ***** Tap the Enter to start. *****\n");
	printf("                ***********************************\n");
	printf("                ***********************************\n");
	getch();
	system("cls");
	printf("\n\n\n             >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("             <<>> Please choose a level: (easy-normal-hard) <<>>\n");
	printf("             <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	scanf("\n\n\n%s",level);
	system("cls");
	if(level[0]=='e'){
        n=4;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				array2[i][j]=1+rand()%(n*n/2);
				
		        for(k=0;k<=i;k++){
		        	if(k==i){
					    for(m=0;m<=j;m++){
		        		if(array2[i][j]==array2[k][m])flag++;
					    }
					    
		        	   
		            }
		            else{
		            	for(m=0;m<n;m++){
		        		if(array2[i][j]==array2[k][m])flag++;
					    }
					}
					if(flag>2)j--;
					
				}
		        flag=0;
		        
			}
			
		}
		
	//	kontrol satýrlarý::
        
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)printf("%d ",array2[i][j]);
			printf("\n");
		}
		
/*		printf("\n%d",flag);
		printf("%d",array2[0][0]);
*/		
    while((scorep+scorecpu<n*n*5) && (scorep<=(n*n*5)/2 && scorecpu<=(n*n*5)/2)){
		printf("\n     ");
		for(i=0;i<n;i++)printf(" %d",i+1);
		printf("\n     ");
		for(i=0;i<n;i++)printf(" |");
		printf("\n\n");
		for(i=0;i<n;i++){
			printf(" %d-- ",i+1);
			for(j=0;j<n;j++){
		    printf(" %c",array1[i][j]);
			}
			printf("\n");
		}
		if(turn==1){
			g=1;
			pg++;
	        while(g<3){
		    
		    printf(" Player's turn, please write the locations of your %d. card:",g);
		    if(g==1){
	      	scanf("%d %d",&line1,&column1);
		    printf("%d,%d : %d\n",line1,column1,array2[line1-1][column1-1]);	
			guess1=array2[line1-1][column1-1];
		    memory[0][flag]=line1;
		    memory[1][flag]=column1;
		    memory[2][flag]=array2[line1-1][column1-1];
		        if(array1[line1-1][column1-1]=='-' || line1>n || column1>n || line1<1 || column1<1){
      		    printf("1...you can not choose this location!! choose another one.\n\n\n\n"); 
			    }
			    else{ 
				    if(flag!=1)flag++;
			        else flag=0;
					 g++;
				}  
			  }
	     	else{
			scanf("%d %d",&line2,&column2);
		    printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
			 guess2=array2[line2-1][column2-1];
			  memory[0][flag]=line2;
		    	memory[1][flag]=column2;
		    	memory[2][flag]=array2[line2-1][column2-1];
		    	 if(array1[line2-1][column2-1]=='-' || line2>n || column2>n || line2<1 || column2<1 ||(line1==line2 && column1==column2)  ){
      		    printf("2...you can not choose this location!! choose another one.\n\n\n\n"); 
			    }
			    else{ 
				    if(flag!=1)flag++;
			        else flag=0;
					 g++;
				}
			 } 
	      	}
	      	g=1;
	    }
		else{
			g=1;
			cg++;
			// cpu first card 
			
			printf("\n  Computer's turn, the locations of  %d. card:\n",g);
	        line1=1+rand()%n;
			column1=1+rand()%n;
		    while(g==1){
				if(array1[line1-1][column1-1]=='-'){
				line1=1+rand()%n;
				column1=1+rand()%n;
				}
				else g=2;
			}
	        guess1=array2[line1-1][column1-1];
	        printf("%d,%d : %d\n",line1,column1,array2[line1-1][column1-1]);
	        
	            //cpu second card 
				for(j=0;j<2;j++){
					if((memory[0][j]!=line1 || memory[1][j]!=column1) && memory[2][j]==array2[line1-1][column1-1] ){
	        		    printf("\n Computer's turn, the locations of  2. card:\n");
						line2=memory[0][j];
	        	    	column2=memory[1][j];
	        	    	guess2=array2[line2-1][column2-1];
	        	    	printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
	        	    	printf("Press any button to continue.\n");
	                    getch();
	        	    	g=1;
	        	    	
	        	    }
	            }
			    if(g==2){
			    	printf("\n  Computer's turn, the locations of  %d. card:\n",g);
	                line2=1+rand()%n;
					column2=1+rand()%n;
					while(g==2){
						if(array1[line2-1][column2-1]=='-' || (line2==line1 && column2==column1)){
						line2=1+rand()%n;
					    column2=1+rand()%n;
						}
						else g=1;
					}
	                guess2=array2[line2-1][column2-1];
	                printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
	                printf("Press any button to continue.\n");
	                getch();
	                
			    }	
			            if(flag>1) flag=0;
						memory[0][flag]=line1;
		            	memory[1][flag]=column1;
		            	memory[2][flag]=array2[line1-1][column1-1];
		            	flag++;
		            	if(flag>1) flag=0;
		            	memory[0][flag]=line2;
		    	        memory[1][flag]=column2;
		    	        memory[2][flag]=array2[line2-1][column2-1];
		            	flag++;
		            		if(flag>1) flag=0;
						
					
		}
		if(guess1!=guess2){
			if(turn==1)turn=2;
			else turn=1;
			printf("\n\n Wrong matchup!! Press any button for changing turns.\n\n");
			getch();
			system("cls");
		}
		else{
			
			if(turn==1){
			printf("\n Perfect!! Player found one per more.\n");
			scorep+=10;
			printf(" Player's total score: %d \n\n\n",scorep);
			}
			else{
			scorecpu+=10;
			printf("\n Computer found one per more.\n");
			printf(" Computer's total score: %d \n",scorecpu);
			} 
			array1[line1-1][column1-1]='-';
			array1[line2-1][column2-1]='-';
			
		}
	}
	}
	else if(level[0]=='n'){
		n=6;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				array2[i][j]=1+rand()%(n*n/2);
				
		        for(k=0;k<=i;k++){
		        	if(k==i){
					    for(m=0;m<=j;m++){
		        		if(array2[i][j]==array2[k][m])flag++;
					    }
					    
		        	   
		            }
		            else{
		            	for(m=0;m<n;m++){
		        		if(array2[i][j]==array2[k][m])flag++;
					    }
					}
					if(flag>2)j--;
					
				}
		        flag=0;
		        
			}
			
		}
		
	//	kontrol satýrlarý::
        
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)printf("%d ",array2[i][j]);
			printf("\n");
		}
		
/*		printf("\n%d",flag);
		printf("%d",array2[0][0]);
*/		
    while((scorep+scorecpu<n*n*5) && (scorep<=(n*n*5)/2 && scorecpu<=(n*n*5)/2)){
		printf("\n     ");
		for(i=0;i<n;i++)printf(" %d",i+1);
		printf("\n     ");
		for(i=0;i<n;i++)printf(" |");
		printf("\n\n");
		for(i=0;i<n;i++){
			printf(" %d-- ",i+1);
			for(j=0;j<n;j++){
		    printf(" %c",array1[i][j]);
			}
			printf("\n");
		}
		if(turn==1){
			g=1;
			pg++;
	        while(g<3){
		    printf(" Player's turn, please write the locations of your %d. card:",g);
		    if(g==1){
	      	scanf("%d %d",&line1,&column1);
		    printf("%d,%d : %d\n",line1,column1,array2[line1-1][column1-1]);	
			guess1=array2[line1-1][column1-1];
		    memory[0][flag]=line1;
		    memory[1][flag]=column1;
		    memory[2][flag]=array2[line1-1][column1-1];
		     if(array1[line1-1][column1-1]=='-' || line1>n || column1>n || line1<1 || column1<1){
      		    printf("1...you can not choose this location!! choose another one.\n\n\n\n"); 
			    }
			    else{ 
				   	if(flag!=5){
			        flag+=1;
			        }
			        else if(flag==5){
			        flag=0;
			        } 
			        g++;
				}  
			}
	     	else{
			scanf("%d %d",&line2,&column2);
		    printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
			guess2=array2[line2-1][column2-1];
			memory[0][flag]=line2;
		    memory[1][flag]=column2;
		    memory[2][flag]=array2[line2-1][column2-1];
		    	 if(array1[line2-1][column2-1]=='-' || line2>n || column2>n || line2<1 || column2<1 ||(line1==line2 && column1==column2)  ){
      		    printf("2...you can not choose this location!! choose another one.\n\n\n\n"); 
			    }
			    else{ 
				    
				    if(flag!=5){
					    if(guess1==guess2){
			 	        memory[2][flag]=0;
			 	            if(flag==0)memory[2][5]=0;
			 	            else memory[2][flag-1]=0;
			            }
			        flag+=1;
			        }
			        else if(flag==5){ 
					    if(guess1==guess2){
			 	        memory[2][flag]=0;
			 	        memory[2][flag-1]=0;
			            }
			        flag=0;
			        } 
			        g++;
				}
			} 
			}
	      	g=1;
	    }
		else{
			g=1;
			cg++;
			s=0;
			f=(tr-1)*2 ;
			if(f>6)f=6;
			for(i=0;i<f;i++){
				for(j=0;j<f;j++){
					if((memory[2][i]==memory[2][j] && memory[2][i]!=0) && (memory[0][i]!=memory[0][j] || memory[1][i]!=memory[1][j]) && j!=i && array1[memory[0][i]][memory[1][i]]!='-'){
						s=1;
						line1=memory[0][i];
						column1=memory[1][i];
						line2=memory[0][j];
						column2=memory[1][j];
						guess1=array2[line1-1][column1-1];	
			            guess2=array2[line2-1][column2-1];
			            if(guess1==guess2){
			        	memory[2][j]=0;
			        	memory[2][i]=0;
			            }
						j=f;
						i=f;
					}
				}
			}
			
			if(s==1){ 
			printf("\n Computer's turn, the locations of  1. card:\n");
			printf("%d,%d : %d\n",line1,column1,array2[line1-1][column1-1]);
			printf("Press any button to continue.\n");
	        getch();
			printf("\n Computer's turn, the locations of  2. card:\n");
			printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
			printf("Press any button to continue.\n");
	        getch(); 
			    if(flag>5) flag=0;
				memory[0][flag]=line1;
		       	memory[1][flag]=column1;
		      	memory[2][flag]=0;
            	flag++;
		       	if(flag>5) flag=0;
		        memory[0][flag]=line2;
		        memory[1][flag]=column2;
    	        memory[2][flag]=0;
		       	flag++;
        		if(flag>5) flag=0;								
			}
			else{
			g=1;		
			printf("\n  Computer's turn, the locations of  %d. card:\n",g);
	        line1=1+rand()%n;
			column1=1+rand()%n;
		    while(g==1){
				if(array1[line1-1][column1-1]=='-'){
				line1=1+rand()%n;
				column1=1+rand()%n;
				}
				else g=2;
			}
	        guess1=array2[line1-1][column1-1];
	        printf("%d,%d : %d\n",line1,column1,array2[line1-1][column1-1]);
				for(j=0;j<f;j++){
					if((memory[0][j]!=line1 || memory[1][j]!=column1) && memory[2][j]==guess1 ){
	        		    printf("\n Computer's turn, the locations of  2. card:\n");
						line2=memory[0][j];
	        	    	column2=memory[1][j];
	        	    	guess2=array2[line2-1][column2-1];
	        	    	printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
	        	    	printf("Press any button to continue.\n");
	                    getch();
	        	    	g=1;
	        	        if(guess1==guess2){
			        	memory[2][j]=0;
			            }
	        	    	j=f;
					    if(flag>5) flag=0;
						memory[0][flag]=line1;
		            	memory[1][flag]=column1;
		            	memory[2][flag]=0;
		            	flag++;
		            	if(flag>5) flag=0;
		            	memory[0][flag]=line2;
		    	        memory[1][flag]=column2;
		    	        memory[2][flag]=0;
		            	flag++;
		            		if(flag>5) flag=0;
						 	
	        	    }
	            }
				if(g==2){
			    	printf("\n  Computer's turn, the locations of  %d. card:\n",g);
	                line2=1+rand()%n;
					column2=1+rand()%n;
					while(g==2){
						if(array1[line2-1][column2-1]=='-' || (line2==line1 && column2==column1)){
						line2=1+rand()%n;
					    column2=1+rand()%n;
						}
						else g=1;
					}
	                guess2=array2[line2-1][column2-1];
	                printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
				    printf("Press any button to continue.\n");
	                getch();
			    }	
			            if(flag>5) flag=0;
						memory[0][flag]=line1;
		            	memory[1][flag]=column1;
		            	memory[2][flag]=array2[line1-1][column1-1];
		            	flag++;
		            	if(flag>5) flag=0;
		            	memory[0][flag]=line2;
		    	        memory[1][flag]=column2;
		    	        memory[2][flag]=array2[line2-1][column2-1];
		    	        if(guess1==guess2){
			        	memory[2][flag]=0;
			            }
		            	flag++;
		            	if(flag>5) flag=0;
						
					
            }
			
		}
		if(guess1!=guess2){
			if(turn==1)turn=2;
			else turn=1;
			printf("\n\n Wrong matchup!! Press any button for changing turns.\n\n");
			getch();
			system("cls");
			tr+=1;
		}
		else{
			
			if(turn==1){
			printf("\n Perfect!! Player found one per more.\n");
			
			scorep+=10;
			printf(" Player's total score: %d \n\n\n",scorep);
			}
			else{
			scorecpu+=10;
			printf("\n Computer found one per more.\n");
			
			printf(" Computer's total score: %d \n",scorecpu);
			} 
			array1[line1-1][column1-1]='-';
			array1[line2-1][column2-1]='-';
			tr+=1;
		}
		f=(tr-1)*2 ;
		if(f>6)f=6;	
	}
		
	}
	else if(level[0]=='h'){
			n=8;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				array2[i][j]=1+rand()%(n*n/2);
				
		        for(k=0;k<=i;k++){
		        	if(k==i){
					    for(m=0;m<=j;m++){
		        		if(array2[i][j]==array2[k][m])flag++;
					    }
					    
		        	   
		            }
		            else{
		            	for(m=0;m<n;m++){
		        		if(array2[i][j]==array2[k][m])flag++;
					    }
					}
					if(flag>2)j--;
					
				}
		        flag=0;
		        
			}
			
		}
		
	//	kontrol satýrlarý::
        
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)printf("%d ",array2[i][j]);
			printf("\n");
		}
/*		printf("\n%d",flag);
		printf("%d",array2[0][0]);
*/		
    while((scorep+scorecpu<n*n*5) && (scorep<=(n*n*5)/2 && scorecpu<=(n*n*5)/2)){
		printf("\n     ");
		for(i=0;i<n;i++)printf(" %d",i+1);
		printf("\n     ");
		for(i=0;i<n;i++)printf(" |");
		printf("\n\n");
		for(i=0;i<n;i++){
			printf(" %d-- ",i+1);
			for(j=0;j<n;j++){
		    printf(" %c",array1[i][j]);
			}
			printf("\n");
		}
		if(turn==1){
			g=1;
			pg++;
	        while(g<3){
		    printf(" Player's turn, please write the locations of your %d. card:",g);
		    if(g==1){
	      	scanf("%d %d",&line1,&column1);
		    printf("%d,%d : %d\n",line1,column1,array2[line1-1][column1-1]);	
			guess1=array2[line1-1][column1-1];
		    memory[0][flag]=line1;
		    memory[1][flag]=column1;
		    memory[2][flag]=array2[line1-1][column1-1];
		    if(array1[line1-1][column1-1]=='-' || line1>n || column1>n || line1<1 || column1<1){
      		    printf("1...you can not choose this location!! choose another one.\n\n\n\n"); 
			    }
			    else{ 
				   	if(flag!=15){
			        flag+=1;
			        }
			        else if(flag==15){
			        flag=0;
			        }  
			    g++;
				}  
			}
	     	else{
			scanf("%d %d",&line2,&column2);
		    printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
			 guess2=array2[line2-1][column2-1];
			memory[0][flag]=line2;
		    memory[1][flag]=column2;
		    memory[2][flag]=array2[line2-1][column2-1];
		        if(array1[line2-1][column2-1]=='-' || line2>n || column2>n || line2<1 || column2<1 ||(line1==line2 && column1==column2)  ){
      		        printf("2...you can not choose this location!! choose another one.\n\n\n\n"); 
			    }
			    else{ 
				    
				    if(flag!=15){
					    if(guess1==guess2){
			 	        memory[2][flag]=0;
			 	            if(flag==0)memory[2][15]=0;
			 	            else memory[2][flag-1]=0;
			           }
			        flag+=1;
			        }
			        else if(flag==15){	        	
				    if(guess1==guess2){
			 	    memory[2][flag]=0;
			 	    memory[2][flag-1]=0;
			        }
			        flag=0;
			        } 
			        g++;
			    }
			} 
			}
	      	g=1;
	    }
		else{
			g=1;
			cg++;
			s=0;
			f=(tr-1)*2 ;
			if(f>16)f=16;
			for(i=0;i<f;i++){
				for(j=0;j<f;j++){
					if((memory[2][i]==memory[2][j] && memory[2][i]!=0) && (memory[0][i]!=memory[0][j] || memory[1][i]!=memory[1][j]) && j!=i && array1[memory[0][i]][memory[1][i]]!='-'){
						s=1;
						line1=memory[0][i];
						column1=memory[1][i];
						line2=memory[0][j];
						column2=memory[1][j];
						guess1=array2[line1-1][column1-1];	
			            guess2=array2[line2-1][column2-1];
			            if(guess1==guess2){
			        	memory[2][j]=0;
			        	memory[2][i]=0;
						j=f;
						i=f;
			            }
						
					}
				}
			}
			
			if(s==1){
			
			printf("\n Computer's turn, the locations of  1. card:\n");
			printf("%d,%d : %d\n",line1,column1,array2[line1-1][column1-1]);
			printf("Press any button to continue.\n");
	        getch();
			printf("\n Computer's turn, the locations of  2. card:\n");
			printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
			printf("Press any button to continue.\n");
	        getch(); 
					    if(flag>15) flag=0;
						memory[0][flag]=line1;
		            	memory[1][flag]=column1;
		            	memory[2][flag]=0;
		            	flag++;
		            	if(flag>15) flag=0;
		            	memory[0][flag]=line2;
		    	        memory[1][flag]=column2;
		    	        memory[2][flag]=0;
		            	flag++;
		            	if(flag>15) flag=0;
						
								
			}
			else{
			g=1;
			printf("\n  Computer's turn, the locations of  %d. card:\n",g);
	        line1=1+rand()%n;
			column1=1+rand()%n;
		    while(g==1){
				if(array1[line1-1][column1-1]=='-' || column1>8 || column1<1 || line1>8 || line1<1){
				line1=1+rand()%n;
				column1=1+rand()%n;
				}
				else g=2;
			}
	        guess1=array2[line1-1][column1-1];
	        printf("%d,%d : %d\n",line1,column1,array2[line1-1][column1-1]);
				for(j=0;j<f;j++){
					if((memory[0][j]!=line1 || memory[1][j]!=column1) && memory[2][j]==guess1 ){
							 	
	        		    printf("\n Computer's turn, the locations of  2. card:\n");
						line2=memory[0][j];
	        	    	column2=memory[1][j];
	        	    	guess2=array2[line2-1][column2-1];
	        	    	printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
	        	    	printf("Press any button to continue.\n");
	                    getch();
	        	    	g=1;
	        	    
	        	        if(guess1==guess2){
			        	memory[2][j]=0;
			            }
	        	    	j=f;
					    if(flag>15) flag=0;
						memory[0][flag]=line1;
		            	memory[1][flag]=column1;
		            	memory[2][flag]=0;
		            	flag++;
		            	if(flag>15) flag=0;
		            	memory[0][flag]=line2;
		    	        memory[1][flag]=column2;
		    	        memory[2][flag]=0;
		            	flag++;
		            		if(flag>15) flag=0;
						 	
	        	    }
	            }
				if(g==2){
					printf("\n  Computer's turn, the locations of  %d. card:\n",g);
	                line2=1+rand()%n;
					column2=1+rand()%n;
					while(g==2){
						if(array1[line2-1][column2-1]=='-' || (line2==line1 && column2==column1) || column2>8 || column2<1 || line2>8 || line2<1){
						line2=1+rand()%n;
					    column2=1+rand()%n;
						}
						else g=1;
					}
	                guess2=array2[line2-1][column2-1];
	                printf("%d,%d : %d\n",line2,column2,array2[line2-1][column2-1]);
				    printf("Press any button to continue.\n");
	                getch();
			    }	
			        	if(flag>15) flag=0;
						memory[0][flag]=line1;
		            	memory[1][flag]=column1;
		            	memory[2][flag]=array2[line1-1][column1-1];
		            	flag++;
		            	if(flag>15) flag=0;
		            	memory[0][flag]=line2;
		    	        memory[1][flag]=column2;
		    	        memory[2][flag]=array2[line2-1][column2-1];
		    	        if(guess1==guess2){
			        	memory[2][flag]=0;
			            }
		            	flag++;
		            	if(flag>15) flag=0;
						
					
            }
			
		}
	/*	for(j=0;j<f;j++){
			printf("%d-)%d:%d= %d     ",j+1,memory[0][j],memory[1][j],memory[2][j]);
		}
		printf("\n f=%d \n",f);
	*/
		if(guess1!=guess2){
			if(turn==1)turn=2;
			else turn=1;
			printf("\n\n Wrong matchup!! Press any button for changing turns.\n\n");
			getch();
			system("cls");
			tr+=1;
		}
		else{
			
			if(turn==1){
			printf("\n Perfect!! Player found one per more.\n");
			
			scorep+=10;
			printf(" Player's total score: %d \n\n\n",scorep);
			}
			else{
			scorecpu+=10;
			printf("\n Computer found one per more.\n");
			
			printf(" Computer's total score: %d \n",scorecpu);
			} 
			array1[line1-1][column1-1]='-';
			array1[line2-1][column2-1]='-';
			tr+=1;
		}	
			f=(tr-1)*2 ;
			if(f>16)f=16;
	}

	}
		
	
	else printf("Wrong text type or text please do not use upper words!!");
	
	system("cls");
	if(scorep>scorecpu)
    printf("\n\n\n Congratulations, you did %d guess, %d points and beat the computer.\n\n\n\n",pg,scorep);
    else if(scorecpu>scorep)
	printf("\n\n\n----GAME OVER---- You did graet job, you were %d points close to beat computer.Computer's total guess: %d     ----TRY AGAIN----\n\n\n\n",scorecpu,(scorecpu-scorep),cg);
	else if(scorep==scorecpu && scorep!=0) 
	printf("\n\n\n---- WHAT A GAME ---- Game is draw, you were too close to beat computer. Total guess: %d    ----TRY AGAIN----\n\n\n\n",scorep,(pg+cg));
	
	return 0;
}
