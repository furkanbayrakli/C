#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Ogrenci{
	char ogrID[9];	
	char ad[30]; 
	char soyad[30]; 
	int puan; 
	struct Ogrenci *next; 
	struct Ogrenci *prev;
}Ogrenci;
typedef struct Yazar{
	int yazarID; 
	char yazarAd[30]; 
	char yazarSoyad[30]; 
	struct Yazar *next;
}Yazar;
typedef struct KitapOrnek{
	char EtiketNo[20]; 
	char Durum[8]; 
	struct KitapOrnek *next;
}KitapOrnek;
typedef struct Kitap {
	char kitapAdi[30]; 
	char ISBN[14]; 
	int adet;
	struct Kitap *next; 
	struct KitapOrnek *head;
}Kitap;

typedef struct KitapYazar{ 
	char ISBN[13]; 
	int YazarID;
}KitapYazar;
typedef struct Tarih{ 
	unsigned int gun:5; 
	unsigned int ay:4; 
	unsigned int yil:12;
}Tarih;
typedef struct KitapOdunc{ 
	char EtiketNo[20]; 
	char ogrID[9]; 
	unsigned int islemTipi:1; 
	struct Tarih islemTarihi;
}KitapOdunc;

int addy(Yazar**,Yazar*,int);
int addo(Ogrenci**,Ogrenci*,int);
int addk(Kitap**,int,int (*writekitap)(char*,Kitap*));
int addkOrnek(KitapOrnek**,KitapOrnek*);
int addBarrow(KitapOdunc**,Kitap**,Ogrenci*,Kitap*,int*,int);

int removey(Yazar**,KitapYazar*,int);
int removeo(Ogrenci**,int);
int removek(Kitap**,int);

int updatey(Yazar**,int);
int updateo(Ogrenci**,KitapOdunc*,int);
int updatek(Kitap**,int);
int updateky(KitapYazar**,Kitap**,Yazar**,int);

Kitap* findk(Kitap**,char*);
Yazar* findy(Yazar**,char*,char*);
Ogrenci* findo(Ogrenci**,char*,char*,char*,int);
int findky(KitapYazar*,char*,int,int);

void sort(Ogrenci**,int,int,int (*fptr)(Ogrenci*,Ogrenci*,int));
int name(Ogrenci*,Ogrenci*,int);
int surname(Ogrenci*,Ogrenci*,int);
int ID(Ogrenci*,Ogrenci*,int);
void swap(Ogrenci*,Ogrenci*);

void shelf(Kitap *headk);
void printgrounded(Ogrenci*);
void printDeptors(KitapOdunc*,Ogrenci*,int);
void timeouts(KitapOdunc*,Kitap*,int);
int matchKitapYazar(KitapYazar**,Kitap**,Yazar**,int*);

int readfiley(char*,Yazar**,int*);
int readfilek(char*,Kitap**,int*);
int readfileo(char*,Ogrenci**,int*);
int readfileko(char*,KitapOdunc**,int*);
int readfileky(char*,KitapYazar**,int*);
int writefileyStart(char*,Yazar*);
int writefileyEnd(char*,Yazar*);
int writefilekStart(char*,Kitap*);
int writefilekEnd(char*,Kitap*);
int writefilekyStart(char*,KitapYazar*,int);
int writefilekyEnd(char*,KitapYazar,int);
int writefileoStart(char*,Ogrenci*);
int writefileoEnd(char*,Ogrenci*);
int writefileKOrnek(char*,Kitap*);
int createfilekOrnek(char*,Kitap*,KitapOdunc*,int);

int control(int,int,char*);
void printo(Ogrenci*);
void printy(Yazar*);
void printk(Kitap*);
void printykInfo(Yazar*,Kitap*,KitapYazar*,int);
void printkyInfo(Kitap*,Yazar*,KitapYazar*,int);
void printkoInfo(Ogrenci*,Kitap*,KitapOdunc*,int);
void freey(Yazar*);
void freek(Kitap*);
void freeo(Ogrenci*);

int main() {
	int cho=0,cho2, ycount=0,ocount=0,kcount=0,kocount=0,kycount=0,type,i;
	char n[30],s[30],id[9];
	Yazar *heady=NULL,*tempy;
	Ogrenci *heado=NULL,*tempo;
	Kitap *headk=NULL,*tempk;
	KitapOrnek *tempko;
	KitapOdunc *headko=NULL;
	KitapYazar *headky=NULL;
	char *kitaplar="Kitaplar.csv",*yazarlar="Yazarlar.csv",*ogrenciler="Ogrenciler.csv",*kitapOdunc="KitapOdunc.csv",*kitapYazar="KitapYazar.csv",*kitapOrnek="KitapOrnek.csv";			
	int (*sortptr[3])(Ogrenci*,Ogrenci*,int)={name,surname,ID};
	int (*writeyazar[2])(char*,Yazar*)={writefileyStart,writefileyEnd};
	int (*writekitap[2])(char*,Kitap*)={writefilekStart,writefilekEnd};// sýralama ve dosyaya yazdýrma islemleri icin fonksiyon pointerlar
	int (*writeogrenci[2])(char*,Ogrenci*)={writefileoStart,writefileoEnd};

	readfilek(kitaplar,&headk,&kcount);	
	readfileko(kitapOdunc,&headko,&kocount);
	createfilekOrnek(kitapOrnek,headk,headko,kocount);// kitapoornek.csv dosyasýný eger olusturulmamýssa olusturuyorum
	
	while(cho!=4){
		printf("\n\n\t|*************************************************|\n");
		printf("\t|*******************  ANA MENU  ******************|\n");
		printf("\t|*************************************************|\n");
	 	cho=control(1,4,"\n\t 1- Yazar islemleri \n\t 2- Kitap islemleri \n\t 3- Ogrenci islemleri\n\t 4- Cikis...\n");// kodumda do while çok kullandým bu tip kontroller için fonkdiyon oluþturdum
		system("cls");
		switch(cho){	
			case 1:
				printf("\n\n\t|*************************************************|\n");
				printf("\t|***************  YAZAR ISLEMLERI  ***************|\n");
				printf("\t|*************************************************|\n");
				cho2=control(1,5,"\n\t 1- Yazar ekle\n\t 2- Yazar sil \n\t 3- Yazar guncelle\n\t 4- Yazar bilgisi goruntuleme\n\t 5- Bir onceki sayfa\n");
				system("cls");
				switch(cho2){	
					case 1:
						printf("\n\tSirasiyla yazar bilgilerini giriniz:(ad-soyad)  ");
						scanf("%s %s",n,s);
						if(findy(&heady,n,s)==NULL){
							freey(heady);heady=NULL;ycount=0;
							readfiley(yazarlar,&heady,&ycount);
							tempy=(Yazar*)malloc(sizeof(Yazar));
							if(tempy==NULL)return -1;
							strcpy(tempy->yazarAd,n);
							strcpy(tempy->yazarSoyad,s);
							tempy->yazarID=ycount+1;
							tempy->next=NULL;
							addy(&heady,tempy,ycount);
						    ycount++;
						    writeyazar[1](yazarlar,tempy);
						}
						else	printf("\n\tBu yazar eklenemez, halihazirda kayitli !!!\n");
						break;
					case 2:
						free(headky);headky=NULL;kycount=0;freey(heady);heady=NULL;ycount=0;
						readfileky(kitapYazar,&headky,&kycount);
						readfiley(yazarlar,&heady,&ycount);
						ycount=ycount-removey(&heady,headky,kycount);
						writeyazar[0](yazarlar,heady);
						writefilekyStart(kitapYazar,headky,kycount);
						break;
					case 3:
						freey(heady);heady=NULL;ycount=0;
						readfiley(yazarlar,&heady,&ycount);
						updatey(&heady,ycount);
						writeyazar[0](yazarlar,heady);
						break;
					case 4:	
						freey(heady);heady=NULL;ycount=0;free(headky);headky=NULL;kycount=0;
						readfiley(yazarlar,&heady,&ycount);
						readfileky(kitapYazar,&headky,&kycount);
						printf("\n\t Aramak istediginiz yazarin adi soyadi:   ");
						scanf("%s %s",n,s);
						tempy=findy(&heady,n,s);
						if(tempy!=NULL)	printykInfo(tempy,headk,headky,kycount);
						else	printf("\n\t Aradiginiz yazar bulunmamakta");
						break;
					case 5:
						break;
				}
				break;
			case 2:
				printf("\n\n\t|*************************************************|\n");
				printf("\t|***************  KITAP ISLEMLERI  ***************|\n");
				printf("\t|*************************************************|\n");
				cho2=control(1,9,"\n\t 1- Kitap ekle\n\t 2- Kitap  sil \n\t 3- Kitap  guncelle\n\t 4- Kitap  bilgisi goruntuleme\n\t 5- Raftaki kitaplari listele\n\t 6- Zamaninda teslim edilmeyen kitaplari listele\n\t 7- Kitap-Yazar Eslestir\n\t 8- Kitabin Yazarini Guncelle\n\t 9- Bir onceki sayfa\n");
				system("cls");
				switch(cho2){	
					case 1:
						freek(headk);headk=NULL;kcount=0;
						readfilek(kitaplar,&headk,&kcount);
						kcount+=addk(&headk,kcount,writekitap[1]);
						writefileKOrnek(kitapOrnek,headk);
						break;
					case 2:
						freek(headk);headk=NULL;kcount=0;
						readfilek(kitaplar,&headk,&kcount);
						kcount=kcount-removek(&headk,kcount);
						writefileKOrnek(kitapOrnek,headk);
						writekitap[0](kitaplar,headk);						
						break;
					case 3:
						freek(headk);headk=NULL;kcount=0;
						readfilek(kitaplar,&headk,&kcount);
						updatek(&headk,kcount);
						writekitap[0](kitaplar,headk);	
						writefileKOrnek(kitapOrnek,headk);					
						break;
					case 4:
						freek(headk);headk=NULL;kcount=0;free(headky);headky=NULL;kycount=0;freey(heady);heady=NULL;ycount=0;
						readfiley(yazarlar,&heady,&ycount);
						readfileky(kitapYazar,&headky,&kycount);
						readfilek(kitaplar,&headk,&kcount);
						printf("\n\t Goruntulemek istediginiz kitabin adi :  ");
						scanf(" %29[^\n]",n);
						tempk=findk(&headk,n);
						
						if(tempk!=NULL)printkyInfo(tempk,heady,headky,kycount);
						else printf("\n\t Boyle bir kitap bulunmamakta!!\n ");
						break;
					case 5:
						freek(headk);headk=NULL;kcount=0;free(headko);headko=NULL;kocount=0;
						readfileko(kitapOdunc,&headko,&kocount);
						readfilek(kitaplar,&headk,&kcount);
						shelf(headk);
						break;
					case 6:
						free(headko);headko=NULL;kocount=0;freek(headk);headk=NULL;kcount=0;
						readfilek(kitaplar,&headk,&kcount);
						readfileko(kitapOdunc,&headko,&kocount);
						timeouts(headko,headk,kocount);
						break;
					case 7:
						freek(headk);headk=NULL;kcount=0;
						freey(heady);heady=NULL;ycount=0;
						free(headky);headky=NULL;kycount=0;
						readfilek(kitaplar,&headk,&kcount);
						readfiley(yazarlar,&heady,&ycount);
						readfileky(kitapYazar,&headky,&kycount);
						matchKitapYazar(&headky,&headk,&heady,&kycount);
						writefilekyStart(kitapYazar,headky,kycount);						
						break;
					case 8:
						freek(headk);headk=NULL;kcount=0;
						freey(heady);heady=NULL;ycount=0;
						free(headky);headky=NULL;kycount=0;
						readfileky(kitapYazar,&headky,&kycount);
						readfilek(kitaplar,&headk,&kcount);
						readfiley(yazarlar,&heady,&ycount);
						updateky(&headky,&headk,&heady,kycount);
						writefilekyStart(kitapYazar,headky,kycount);
						break;
					case 9:
						break;
				}
				break;
			case 3:
				printf("\n\n\t|*************************************************|\n");
				printf("\t|**************  OGRENCI ISLEMLERI  **************|\n");
				printf("\t|*************************************************|\n");
				cho2=control(1,9,"\n\t 1- Ogrenci ekle\n\t 2- Ogrenci  sil \n\t 3- Ogrenci  guncelle\n\t 4- Ogrenci bilgisi goruntuleme\n\t 5- Kitap teslim etmemis ogrencileri listele\n\t 6- Cezali ogrencileri listele\n\t 7- Tum ogrencileri listele\n\t 8- Kitap odunc al/teslim et\n\t 9- Bir onceki sayfa\n");
				system("cls");
				switch(cho2){
					case 1:	
						tempo=(Ogrenci*)malloc(sizeof(Ogrenci));
						if(tempo==NULL)return -1;
						printf("\n\tSirasiyla ogrenci bilgilerini giriniz:(ad-soyad-8 haneli ID)  ");
						scanf("%s %s",tempo->ad,tempo->soyad);
						do{
							scanf("%s",id);
							if(strlen(id)<8)printf("\n\tID icin eksik rakam girdiniz!!\n ID yi tekrar giriniz:  ");
							else if(strlen(id)>8)printf("\n\tID icin rakam sinirini astiniz!!\n ID yi tekrar giriniz:  ");
						}while(strlen(id)!=8);
						strcpy(tempo->ogrID,id);
						tempo->puan=100;
						freeo(heado);heado=NULL;ocount=0;
						readfileo(ogrenciler,&heado,&ocount);
						addo(&heado,tempo,ocount);
					    ocount++;
					    writeogrenci[1](ogrenciler,tempo);
						//printo(heado);
						break;
					case 2:
						freeo(heado);heado=NULL;ocount=0;
						readfileo(ogrenciler,&heado,&ocount);
						ocount=ocount-removeo(&heado,ocount);
						writeogrenci[0](ogrenciler,heado);
						break;
					case 3:
						freeo(heado);heado=NULL;ocount=0;free(headko);headko=NULL;kocount=0;
						readfileo(ogrenciler,&heado,&ocount);
						readfileko(kitapOdunc,&headko,&kocount);
						updateo(&heado,headko,kocount);
						writefilekoStart(kitapOdunc,headko,kocount);
						writeogrenci[0](ogrenciler,heado);
						break;
					case 4:
						freeo(heado);heado=NULL;ocount=0;free(headko);headko=NULL;kocount=0;freek(headk);headk=NULL;kcount=0;
						readfileo(ogrenciler,&heado,&ocount);
						readfileko(kitapOdunc,&headko,&kocount);
						readfilek(kitaplar,&headk,&kcount);
						type=control(1,2,"\n 1- ID ye gore arama\n 2- Isim ve soyisme gore arama\n");
						if(type==1){
							printf("\n\t Goruntulenmek istenen ogrencinin id si:  ");
							scanf("%s",id);	
							tempo=findo(&heado,"","",id,type);
						}
						else{
							printf("\n\t Goruntulenmek isteyen ogrencinin adi soyadi :  ");
							scanf("%s %s",n,s);	
							tempo=findo(&heado,n,s,"",type);
						}
						if(tempo!=NULL) printkoInfo(tempo,headk,headko,kocount);
						else	printf("\n\t Boyle bir ogrenci bulunmamakta !!");
						break;
					case 5:
						free(headko);headko=NULL;kocount=0;freeo(heado);heado=NULL;ocount=0;
						readfileko(kitapOdunc,&headko,&kocount);
						readfileo(ogrenciler,&heado,&ocount);
						printDeptors(headko,heado,kocount);
						break;
					case 6:
						freeo(heado);heado=NULL;ocount=0;
						readfileo(ogrenciler,&heado,&ocount);
						printgrounded(heado);	
						break;
					case 7:
						freeo(heado);heado=NULL;ocount=0;
						readfileo(ogrenciler,&heado,&ocount);
						type=control(1,3,"\n\t 1- Ada gore listeleme\n\t 2- Soyada gore listeleme\n\t 3- ID'ye gore listeleme\n");
						
						sort(&heado,ocount,type,sortptr[type-1]);
						printo(heado);
						writeogrenci[0](ogrenciler,heado);
						break;
					case 8:
						freeo(heado);heado=NULL;ocount=0;free(headko);headko=NULL;kocount=0;freek(headk);headk=NULL;kcount=0;
						readfileo(ogrenciler,&heado,&ocount);
						readfileko(kitapOdunc,&headko,&kocount);
						readfilek(kitaplar,&headk,&kcount);
						printf("\n\t Kitap odunc alacak/geri iade edecek ogrencinin id si:  ");
						scanf("%s",id);
						tempo=findo(&heado,"","",id,1);
						if(tempo!=NULL){
							if(tempo->puan>0){
								printf("\n\t Odunc almak/veya geri iade etmek istediginiz kitabin adi:  ");
								scanf(" %29[^\n]",n);
								tempk=findk(&headk,n);
								if(tempk!=NULL){
									type=control(1,2,"\n 1- Kitap alma\n 2- Kitap iade\n");
									addBarrow(&headko,&headk,tempo,tempk,&kocount,type);
								}		
								else	printf("\n\t Boyle bir kitap bulunmamakta !!\n");
							}
							else printf("\n\t Yetersiz ogrenci puani !!! \n");	
						}
						else printf("\n\t Boyle bir ogrenci bulunmamakta !!\n");
						writefilekoStart(kitapOdunc,headko,kocount);
					    writefileKOrnek(kitapOrnek,headk);	
					    writekitap[0](kitaplar,headk);	
					    writeogrenci[0](ogrenciler,heado);
						break;
					case 9:
						break;	
				}
				break;
			case 4:
				break;			
		}
		getch();
		system("cls");
	}
	return 0;
}
int name(Ogrenci *p1,Ogrenci *p2,int way){
	int i=0;
	if(way==1){
		while(p1->ad[i]!='\0' && p2->ad[i]!='\0'){
			if(p1->ad[i] - p2->ad[i]!=0)	return (p1->ad[i] - p2->ad[i]);
			i++;
		}
		return strcmp(p1->ad,p2->ad);
	}
	i=0; // isim uzunluklari eþit olmayacagi icin strcmp kullanamadým
	while(p1->ad[i]!='\0' && p2->ad[i]!='\0'){
		if(p2->ad[i]-p1->ad[i]!=0)	return (p2->ad[i] - p1->ad[i]);
		i++;
	}
	return strcmp(p2->ad,p1->ad);
	
}
int surname(Ogrenci *p1,Ogrenci *p2,int way){
int i=0;
	if(way==1){
		while(p1->soyad[i]!='\0' && p2->soyad[i]!='\0'){
			if(p1->soyad[i] - p2->soyad[i]!=0) return p1->soyad[i] - p2->soyad[i];
			i++;
		}
		return strcmp(p1->soyad,p2->soyad);
	}
	i=0;// isim uzunluklari eþit olmayacagi icin strcmp kullanamadým
	while(p1->soyad[i]!='\0' && p2->soyad[i]!='\0'){
		if(p2->soyad[i] - p1->soyad[i]!=0) return p2->soyad[i] - p1->soyad[i];
		i++;
	}
	return strcmp(p2->soyad,p1->soyad);
	
}
int ID(Ogrenci *p1,Ogrenci *p2,int way){
	if(way==1){
		return strcmp(p1->ogrID,p2->ogrID);
	}
	return strcmp(p2->ogrID,p1->ogrID);
}
void swap(Ogrenci *p1,Ogrenci *p2){
	char tmp[30];
	int a;
	strcpy(tmp,p1->ad);
	strcpy(p1->ad,p2->ad);
	strcpy(p2->ad,tmp);
	strcpy(tmp,p1->soyad);
	strcpy(p1->soyad,p2->soyad);
	strcpy(p2->soyad,tmp);
	strcpy(tmp,p1->ogrID);
	strcpy(p1->ogrID,p2->ogrID);
	strcpy(p2->ogrID,tmp);
	a=p2->puan;
	p2->puan=p1->puan;
	p1->puan=a;
}
void sort(Ogrenci **head,int count,int type,int (*sortptr)(Ogrenci*,Ogrenci*,int)){
	int i,j,way;
	Ogrenci *iter=*head,*iter2,*p1,*p2,*p3=NULL;
	do{
		if(type==3){
			printf("\n\t 1- Kucukten--->buyuge listeleme\n\t 2- Buyukten--->kucuge listeleme\n");
			scanf("%d",&way);
		}
		else{
			printf("\n\t 1- Alfabetik siraya gore listeleme\n\t 2- Alfabenin tersine gore listeleme\n");
			scanf("%d",&way);
		}
	}while(way!=1 && way!=2);
	
	for(i=0;i<count;i++){
		p1=iter;// karsilastirilacak eleman
		p3=iter; // swap yapilacak eleman
		p2=p1->next; // linked listteki diger elemanlar
		for(j=i;j<count-1;j++){
			if(sortptr(p3,p2,way)>0){
				p3=p2;
			}
			if(p2->next!=NULL)p2=p2->next;
		}
		if(p1!=p3)swap(p1,p3);
		if(iter->next!=NULL)iter=iter->next;
	}
}

int addy(Yazar **heady,Yazar *temp,int count){
	Yazar *iter=*heady;
	if((*heady)==NULL)*heady=temp;	
	else{
		while(iter->next!=NULL)iter=iter->next;
		iter->next=temp;
	}
	return 0;		
}
int addo(Ogrenci **heado,Ogrenci* temp,int count){
	int i;
	Ogrenci *iter=*heado;
	
	if(*heado==NULL){
		*heado=temp;
		(*heado)->next=NULL;
 		(*heado)->prev=NULL;
	} 
	else{
		while(iter->next!=NULL)iter=iter->next;
		iter->next=temp;
		iter->next->prev=iter;
		iter->next->next=NULL;
	}
	return 0;	
}
int addk(Kitap **headk,int count,int (*writekitap)(char*,Kitap*)){
	int i,cont=0,cont2=0,num;
	char n[30],ISBN[13];
	Kitap *iter=*headk,*iter2=*headk,*temp=(Kitap*)malloc(sizeof(Kitap));
	KitapOrnek *temp2=(KitapOrnek*)malloc(sizeof(KitapOrnek)),*temp3;
	temp->head=(KitapOrnek*)malloc(sizeof(KitapOrnek));
	if(temp==NULL || temp2==NULL || temp->head==NULL)return -1;

	printf("\n\t Kitap adini giriniz: ");
	scanf(" %29[^\n]",temp->kitapAdi);
	if(*headk==NULL){
		do{
			printf("\n\t Kitabn ISBN numarasini giriniz : ");
			scanf("%s",ISBN);
		}while(strlen(ISBN)!=13);
		strcpy(temp->ISBN,ISBN);
		strcpy(temp->head->EtiketNo,temp->ISBN);	
		strcat(temp->head->EtiketNo,"_1");
		strcpy(temp->head->Durum,"Rafta");
		temp->adet=1;
		temp->head->next=NULL;
		*headk=temp;
		(*headk)->next=NULL;
	} 
	else{
		while(iter2->next!=NULL){	
		 	if(strcmp(iter2->kitapAdi,temp->kitapAdi)==0)cont=1;
			iter2=iter2->next;
		}
		if(strcmp(iter2->kitapAdi,temp->kitapAdi)==0)cont=1;
		if(cont==0){  // data da kitap yoksa etiket numarasini _1 den baslatiyorum
			do{
				printf("\n\t Kitabn ISBN numarasini giriniz : ");
				scanf("%s",ISBN);iter2=*headk;
				cont2=0;
				while(iter2->next!=NULL && cont2==0){	
			 		if(strcmp(iter2->ISBN,ISBN)==0)cont2=1;
					iter2=iter2->next;
				}
				if(strcmp(iter2->ISBN,ISBN)==0)cont2=1;
				if(cont2==1)printf("\n\t Girmis oldugunuz ISBN coktan kayitli !!\n");
				if(strlen(ISBN)>13)printf("\n\t ISBN icin karakter sinirini(13) astiniz !!\n");
				else if(strlen(ISBN)<13)printf("\n\t ISBN icin yeterli sayida(13) karakter giriniz !!\n");
			}while(strlen(ISBN)!=13 || cont2==1);
			strcpy(temp->ISBN,ISBN);
			strcpy(temp->head->EtiketNo,temp->ISBN);
			strcat(temp->head->EtiketNo,"_1");
			strcpy(temp->head->Durum,"Rafta");
			temp->adet=1;
			temp->head->next=NULL;
			while(iter->next!=NULL)iter=iter->next;
			iter->next=temp;
			iter->next->next=NULL;
		}
		else{ // datada halihazirda kitap varsa etiket numarasiyla oynamalar yapiyorum
			while(strcmp(iter->kitapAdi,temp->kitapAdi)!=0){
				iter=iter->next;
			}	
			iter->adet++;
			temp3=iter->head;
			while(temp3->next!=NULL){
				temp3=temp3->next;
			}
			strcpy(temp2->EtiketNo,temp3->EtiketNo);
			temp->adet+=1;
			i=strlen(temp2->EtiketNo)-1;
					
			while( temp3->EtiketNo[i]=='9'){
				temp2->EtiketNo[i]='0';						
				i--;
			}
			if(temp3->EtiketNo[i]=='_'){
				strcat(temp2->EtiketNo,"0");
				temp2->EtiketNo[i+1]='1';
			}
			else temp2->EtiketNo[i]=temp2->EtiketNo[i]+1;
			strcpy(temp2->Durum,"Rafta");
			temp3->next=temp2;
			temp3->next->next=NULL;
			return 0;
		}	
	}
	writekitap("Kitaplar.csv",temp); //sadece temp sona ekleyecegim icin fonksiyon pointerimi burda kullaniyorum global degisken yasak oldugu icinde mainde tanimladýgým *kitaplar pointerimi kullanamadim
	return 1;	
}
int addBarrow(KitapOdunc** headko,Kitap** headk,Ogrenci* ogr,Kitap* kit,int *kocount,int type){
	int a,b,c,i=0;
	KitapOdunc temp;
	KitapOrnek *temp2;
	
	strcpy(temp.ogrID,ogr->ogrID);
	printf("\n\t Islem tarihini giriniz:gun ay yil");
	scanf("%d %d %d",&a,&b,&c);
	temp.islemTarihi.gun=a;
	temp.islemTarihi.ay=b;
	temp.islemTarihi.yil=c;
	temp.islemTipi=type-1;
	if(temp.islemTipi==1){// kitap iade
		do{
			printf("\n\t Iade edeceginiz kitabin etiket numarasi:  ");
			scanf("%s",temp.EtiketNo);
			i=0;
			while(i<*kocount && ((*headko)[i].islemTipi==1 || strcmp((*headko)[i].ogrID,ogr->ogrID)!=0 || strcmp((*headko)[i].EtiketNo,temp.EtiketNo)!=0))i++;
			if((strcmp((*headko)[i].ogrID,ogr->ogrID)!=0 || strcmp((*headko)[i].EtiketNo,temp.EtiketNo)!=0)) printf("\n Bu etiket numarasina ait kitabiniz bulunmamaktadir !!!\n");
			if((*headko)[i].islemTipi==1 ) printf("\n\t Bu kitabi coktan geri iade etmissiniz !!\n");
		}while((*headko)[i].islemTipi==1 ||(strcmp((*headko)[i].ogrID,ogr->ogrID)!=0 || strcmp((*headko)[i].EtiketNo,temp.EtiketNo)!=0));
		temp2=kit->head;
		while(temp2->next!=NULL && strcmp(temp2->EtiketNo,temp.EtiketNo)!=0)temp2=temp2->next;
		if(strcmp(temp2->EtiketNo,temp.EtiketNo)==0) strcpy(temp2->Durum,"Rafta");
		
		if(strcmp(temp.EtiketNo,(*headko)[i].EtiketNo)==0){
			if((*headko)[i].islemTarihi.yil==c){
				if((*headko)[i].islemTarihi.ay==b){
					if(a-(*headko)[i].islemTarihi.gun>15)ogr->puan-=10;
				}
				else{
					if(b-(*headko)[i].islemTarihi.ay>1)ogr->puan-=10;
					else if(a+30-(*headko)[i].islemTarihi.gun>15)ogr->puan-=10;
				}	
			}
			else{
				if(c-(*headko)[i].islemTarihi.yil>1)ogr->puan-=10;
				else if((*headko)[i].islemTarihi.ay==b){
					if(a-(*headko)[i].islemTarihi.gun>15)ogr->puan-=10;
				}
				else if(b-(*headko)[i].islemTarihi.ay>-11)ogr->puan-=10;
				else if(a+30-(*headko)[i].islemTarihi.gun>15)ogr->puan-=10;
			}	
		}
		
		(*headko)[*kocount]=temp;
		*kocount+=1;
		(*headko)=(KitapOdunc*)realloc(*headko,(*kocount+1)*sizeof(KitapOdunc));
	}
	if(temp.islemTipi==0){// kitap odunc
		temp2=kit->head;
		while(temp2->next!=NULL && strcmp(temp2->Durum,"Rafta")!=0)temp2=temp2->next;
		if(strcmp(temp2->Durum,"Rafta")==0){
			strcpy(temp.EtiketNo,temp2->EtiketNo);
			strcpy(temp2->Durum,temp.ogrID);
			(*headko)[*kocount]=temp;
			*kocount+=1;
			(*headko)=(KitapOdunc*)realloc(*headko,(*kocount+1)*sizeof(KitapOdunc));
		}
		else printf("\n\t Aradiginiz kitabin butun kopyalari odunc alinmis !!\n\n");
	}

	return 0;
}
int addkOrnek(KitapOrnek **head,KitapOrnek *temp){
	KitapOrnek *iter=*head;	
	if((*head)==NULL){
		*head=temp;
		return 0;	
	}
	while(iter->next!=NULL)iter=iter->next;
	iter->next=temp;
	return 0;	
}

int removey(Yazar**heady,KitapYazar *headky,int count){
	int i,id;
	char n[30],s[30];
	Yazar *iter=*heady,*prev=NULL;
	printf("\n\t Silmek istediginiz yazarin sirasiyla adi soyadi ID'si\n");
	scanf("%s %s %d",n,s,&id);
	while(iter!=NULL){
		if(strcmp(iter->yazarAd,n)==0 && strcmp(iter->yazarSoyad,s)==0 && iter->yazarID==id){
			if(prev==NULL){
			prev=*heady;
			*heady=iter->next;
			free(prev);
			}
			else if(iter->next!=NULL){
				prev->next=iter->next;
				free(iter);
			}
			else{
				prev->next=NULL;
				free(iter);
			}
			for(i=0;i<count;i++){
				if(headky[i].YazarID==id)	headky[i].YazarID=-1;
			}
			return 1;
		}
		prev=iter;
		iter=iter->next;
	}
	printf("\n\tBoyle bir yazar bulunmamakta!!\n");
	return 0;
}
int removeo(Ogrenci **heado,int count){
	int i;
	char n[30],s[30],ID[9];
	Ogrenci *iter=*heado,*prev=NULL;
	printf("\n\t Silmek istediginiz ogrencinin sirasiyla adi soyadi ID'si\n");
	scanf("%s %s ",n,s);
	do{
		scanf("%s",ID);
		if(strlen(ID)<8)printf("\n\tID icin eksik rakam girdiniz!!\n ID yi tekrar giriniz:  ");
		else if(strlen(ID)>8)printf("\n\tID icin rakam sinirini astiniz!!\n ID yi tekrar giriniz:  ");
	}while(strlen(ID)!=8);
	for(i=0;i<count;i++){
		if(strcmp(iter->ad,n)==0 && strcmp(iter->soyad,s)==0 && strcmp(iter->ogrID,ID)==0){
			if(iter->prev==NULL)*heado=iter->next;
			else if(iter->next!=NULL){
				iter->prev->next=iter->next;
				iter->next->prev=iter->prev;
				free(prev);
			}
			else{
				iter->prev->next=NULL;
				free(iter);
			}	
			return 1;
		}	
		iter=iter->next;
	}
	printf("\n\t Bu bilgilere sahip bir ogrenci bulunmamakta!!\n");
	return 0;
}
int removek(Kitap **headk,int count){
	int i;
	char n[30],etno[20];
	Kitap *iter=*headk,*prev=NULL,*temp1;
	KitapOrnek *temp2,*prev2=NULL;
	printf("\n\t Silmek istediginiz kitabin adi: \n");
	scanf(" %29[^\n]",n);
	temp1=findk(headk,n);
	if(temp1!=NULL){
		temp2=temp1->head;
		while(temp2->next!=NULL){
			printf("\n\t%s %s",temp2->EtiketNo,temp2->Durum);
			temp2=temp2->next;
		}
		printf("\n\t %s %s\n",temp2->EtiketNo,temp2->Durum);
		printf("\n\t Silmek istediginiz kitabin etiket numarasini giriniz: ");
		scanf("%s",etno);
		temp2=temp1->head;
		while(temp2->next!=NULL && strcmp(temp2->EtiketNo,etno)!=0){
			prev2=temp2;
			temp2=temp2->next;
		}	
		if(strcmp(temp2->EtiketNo,etno)!=0){
			printf("\n\t Boyle bir kitap bulunmamakta!!\n");
			return 0;
		}
		if(prev2==NULL && temp2->next==NULL){
			for(i=0;i<count;i++){
				if(strcmp(iter->kitapAdi,n)==0 ){
					if(prev==NULL){
					prev=*headk;
					*headk=iter->next;
					free(prev);
					}
					else if(iter->next!=NULL){
						prev->next=iter->next;
						free(iter);
					}
					else{
						prev->next=NULL;
						free(iter);
					}
					return 1;
				}
				prev=iter;
				iter=iter->next;
			}
		}
		else if(prev2==NULL){
		  	temp1->head=temp2->next;
		  	temp1->adet--;
		  	free(temp2);
		}
		else{
			prev2->next=temp2->next;
			temp1->adet--;
			free(temp2);	
		}
		return 1;
	}
	else	printf("\n\t Boyle bir kitap bulunmamakta!!\n");

	return 0;
}

int updatey(Yazar** heady,int count){
	char n[30],s[30];
	int id,i;
	Yazar *iter=*heady;
	printf("\n\t Bilgilerini guncellemek istediginiz yazarin sirasiyla adi soyadi ID'si\n");
	scanf("%s %s %d",n,s,&id);
	for(i=0;i<count;i++){
		if(strcmp(iter->yazarAd,n)==0 && strcmp(iter->yazarSoyad,s)==0 && iter->yazarID==id){
			printf("\n\t Yazarin yeni adi soyadi \n");
			scanf("%s %s",iter->yazarAd,iter->yazarSoyad);
			return 0;
		}
		iter=iter->next;
	}
	printf("\n\t Boyle bir yazar bulunmamakta!!\n");
	return 1;
	
}
int updateo(Ogrenci** heado,KitapOdunc *headko,int count){
	int i;
	char n[30],s[30],ID[9];
	Ogrenci *iter=*heado;
	printf("\n\t Bilgilerini guncellemek istediginiz ogrencinin sirasiyla adi soyadi ID'si\n");
	scanf("%s %s ",n,s);
	do{
		scanf("%s",ID);
		if(strlen(ID)<8)printf("\n\t ID icin eksik rakam girdiniz!!\n ID yi tekrar giriniz:  ");
		else if(strlen(ID)>8)printf("\n\t ID icin rakam sinirini astiniz!!\n ID yi tekrar giriniz:  ");
	}while(strlen(ID)!=8);
		
	while(iter!=NULL){
		if(strcmp(iter->ad,n)==0 && strcmp(iter->soyad,s)==0 && strcmp(iter->ogrID,ID)==0){
			printf("\n\t Ogrencinin yeni adi ,soyadi, ID si ");
			scanf("%s %s",iter->ad,iter->soyad);
			do{
				scanf("%s",ID);
				if(strlen(ID)<8)printf("\n\t ID icin eksik rakam girdiniz!!\n ID yi tekrar giriniz:  ");
				else if(strlen(ID)>8)printf("\n\t ID icin rakam sinirini astiniz!!\n ID yi tekrar giriniz:  ");
			}while(strlen(ID)!=8);
			for(i=0;i<count;i++){
				if(strcmp(headko[i].ogrID,iter->ogrID)==0)	strcpy(headko[i].ogrID,ID);
			}
			strcpy(iter->ogrID,ID);
			return 0;
		}
		iter=iter->next;
	}
	printf("\n\t Boyle bir ogrenci bulunmamakta!!\n");
	return 1;
}
int updatek(Kitap** headk,int count){
	char n[30],ISBN[14],etno[20];
	char *token;
	int cont;
	Kitap *iter=*headk,*iter2;
	KitapOrnek *iter3;
	printf("\n\t Guncellemek istediginiz kitabin adi:  ");
	scanf(" %29[^\n]",n);
	while(iter!=NULL){
		if(strcmp(iter->kitapAdi,n)==0){
			printf("\n\t Kitabin yeni ismini giriniz:  ");
			scanf(" %29[^\n]",n);
			if(findk(headk,n)!=NULL){
				printf("\n \tBu kitap zaten kayitli islem iptal ediliyor...\n");
				return -1;
			}
			do{
				printf("\n\t Kitabn yeni ISBN numarasini giriniz : ");
				scanf("%s",ISBN);
				cont=0;iter2=*headk;
				while(iter2->next!=NULL && cont==0){	
			 		if(strcmp(iter2->ISBN,ISBN)==0)cont=1;
					else iter2=iter2->next;
				}
				if(strcmp(iter2->ISBN,ISBN)==0)cont=1;
				if(cont==1)printf("\n\t Girmis oldugunuz ISBN coktan kayitli !!\n");
				if(strlen(ISBN)>13)printf("\n\t ISBN icin karakter sinirini(13) astiniz !!\n");
				else if(strlen(ISBN)<13)printf("\n\t ISBN icin yeterli sayida(13) karakter giriniz !!\n");
			}while(strlen(ISBN)!=13 || cont==1);
			strcpy(iter->kitapAdi,n);
			strcpy(iter->ISBN,ISBN);
			iter3=iter->head;
			while(iter3!=NULL){
				strcpy(etno,iter3->EtiketNo);
				token=strtok(etno,"_");
				token=strtok(NULL,"_");
				strcpy(iter3->EtiketNo,ISBN);
				strcat(iter3->EtiketNo,"_");
				strcat(iter3->EtiketNo,token);
				iter3=iter3->next;
			}
			return 0;
		}
		iter=iter->next;
	}
	printf("\n\t Boyle bir kitap bulunmamaktadir!!\n");
	return -1;
}
int updateky(KitapYazar **headky,Kitap **headk,Yazar **heady,int count){
	int i;
	char n[30],s[30];
	Kitap *temp;
	Yazar *temp2;
	printf("\n \tGuncellemek istediginiz kitabin adi:  ");
	scanf(" %[^\n]s",n);
	temp=findk(headk,n);
	if(temp==NULL){
		printf("\n\n\t Boyle bir kitap bulunmamakta !!");return -1;
	}
	printf("\n \tGuncellemek istediginiz yazarin adi soyadi:  ");
	scanf("%s %s",n,s);
	temp2=findy(heady,n,s);
	if(temp2!=NULL){
		i=findky(*headky,temp->ISBN,temp2->yazarID,count); // datada kitap yazar eslesmesini arýyor yoksa -1 donduruyor
		if(i!=-1){
			printf("\n\t Yeni yazar adi soyadi:  ");
			scanf("%s %s",n,s);
			temp2=findy(heady,n,s);
			if(temp2==NULL){
				printf("\n\n\t Boyle bir yazar bulunmamakta !!");return -1;
			}
			if(findky(*headky,temp->ISBN,temp2->yazarID,count)==-1)	(*headky)[i].YazarID=temp2->yazarID; // bu kitapla yazar daha önceden eslesmisse bidaha eslestirmiyor
			else printf("\n \tGirmis oldugunuz yeni kitap yazar eslesmesi zaten bulunmakta !!");
		}
		else printf("\n\t Girmis oldugunuz kitap yazar eslesmesinde bir kayit bulunmamaktadir!!");
	}
	else printf("\n\t Girmis oldugunuz kitap bulunmamakta!! ");
	return 0;
}

Yazar* findy(Yazar **heady,char *n,char *s){
	Yazar *iter=*heady;
	while(iter!=NULL){
		if(strcmp(iter->yazarAd,n)==0 && strcmp(iter->yazarSoyad,s)==0)return iter;
		iter=iter->next;
	}
	 return iter;
}
Ogrenci* findo(Ogrenci **heado,char*n,char*s,char*ID,int type){
	Ogrenci *iter=*heado;
	
	if(type==1){
		while(iter!=NULL){
			if(strcmp(iter->ogrID,ID)==0)return iter;
			iter=iter->next;
		}
	}
	else{
		while(iter!=NULL){
			if(strcmp(iter->ad,n)==0 && strcmp(iter->soyad,s)==0)return iter;
			iter=iter->next;
		}
	}
	return iter;
}
Kitap* findk(Kitap **headk,char* n){
	Kitap *iter=*headk;
	
	while(iter!=NULL){
		if(strcmp(iter->kitapAdi,n)==0) return iter;
		iter=iter->next;
	}
	return iter;
}
int findky(KitapYazar *headky,char *ISBN,int id,int count){
	int i;
	
	for(i=0;i<count;i++){
		if(strcmp(ISBN,headky[i].ISBN)==0 && id==headky[i].YazarID) return i;	
	}
	
	return -1;
}

void shelf(Kitap *headk){
	Kitap *iter=headk;
	KitapOrnek *iter2;
	while(iter!=NULL){
		iter2=iter->head;
		while(iter2->next!=NULL){
			if(strcmp(iter2->Durum,"Rafta")==0)printf("\n\tKitap: %s  ISBN:%s Etiket:%s Durum:%s",iter->kitapAdi,iter->ISBN,iter2->EtiketNo,iter2->Durum);
			iter2=iter2->next;
		}
		
		if(strcmp(iter2->Durum,"Rafta")==0)printf("\n\tKitap: %s  ISBN:%s Etiket:%s Durum:%s\n",iter->kitapAdi,iter->ISBN,iter2->EtiketNo,iter2->Durum);
		iter=iter->next;
	}
	
}
void printgrounded(Ogrenci *heado){
	Ogrenci *iter=heado;
	int s=0;
	printf("\n\t Cezali ogrenciler:\n");
	while(iter!=NULL){
		if(iter->puan<0){
			printf("\n\t ID:%s --- %s %s --- puan: %d",iter->ogrID,iter->ad,iter->soyad,iter->puan);
			s=1;
		}
		iter=iter->next;
	}	
	if(s==0){
		system("cls");	printf("\n\t Cezali ogrenci bulunmamakta  \n");
	} 
}
void printDeptors(KitapOdunc *headko,Ogrenci *heado,int kocount){
	int i,j,s=0,cont;
	Ogrenci *temp;
	printf("\n\t Elinde kitap olan ogrenciler: \n");
	for(i=0;i<kocount;i++){
		temp=findo(&heado,"","",headko[i].ogrID,1);
		if(temp!=NULL && headko[i].islemTipi==0){
			cont=0;
			for(j=i+1;j<kocount;j++){
				if(strcmp(headko[i].EtiketNo,headko[j].EtiketNo)==0 && headko[j].islemTipi==1)cont=1;
				else if(strcmp(headko[i].EtiketNo,headko[j].EtiketNo)==0 && headko[j].islemTipi==0)cont=0;
			}
			if(cont==0){
				printf("\n\tID:%s --- %s %s --- puan: %d --- Etiketno:%s --- Alindigi tarih:%d.%d.%d",temp->ogrID,temp->ad,temp->soyad,temp->puan,headko[i].EtiketNo,headko[i].islemTarihi.gun,headko[i].islemTarihi.ay,headko[i].islemTarihi.yil);
				s=1;
			}
		} 
	}
	if(s==0){
		system("cls");
		printf("\n\t Borclu ogrenci bulunmamakta ");
	} 
}
void timeouts(KitapOdunc *headko,Kitap *headk,int kocount){
	int i,g,a,y,cont;
	do{
		printf("\n\t Tarihi giriniz gun ay yil :    ");
		scanf("%d %d %d",&g,&a,&y);
	}while(g>30 || a>12);
	
	printf("\n\n\t--- Zamani gecmis kitaplar ---\n\n");												
	for(i=0;i<kocount;i++){
		cont=0;// aradaki gün farkini hesaplamak icin dusundugum bir sistem dýstan icedogru karsýlastýrarak yýl esitmi degilmi ay esitmi degilmi gibi ilerleyerek gun farkýný bulmaya calistim
		if(headko[i].islemTarihi.yil==y){
			if(headko[i].islemTarihi.ay==a){
				if(g-headko[i].islemTarihi.gun>15)cont=1;
			}
			else{
				if(a-headko[i].islemTarihi.ay>1)cont=1;
				else if(g+30-headko[i].islemTarihi.gun>15)cont=1;
			}	
		}
		else{
			if(y-headko[i].islemTarihi.yil>1)cont=1;
			else if(headko[i].islemTarihi.ay==a){
				if(g-headko[i].islemTarihi.gun>15)cont=1;
			}
			else if(a-headko[i].islemTarihi.ay>-11)cont=1;
			else if(g+30-headko[i].islemTarihi.gun>15)cont=1;
		}	
		if(cont==1)	printf("\t %s  %s %d  %d.%d.%d\n",headko[i].EtiketNo,headko[i].ogrID,headko[i].islemTipi,headko[i].islemTarihi.gun,headko[i].islemTarihi.ay,headko[i].islemTarihi.yil);
		 
	}
}

int matchKitapYazar(KitapYazar **headky,Kitap **headk,Yazar **heady,int *count){
	char n[30],s[30];
	int a,i=0,t;
	Kitap *temp;
	Yazar *temp2;
	KitapYazar temp3;
	printf("\n\t Eslestirmek istediginiz kitabin adi (ismi yazinca enter'a basin):   ");
	scanf(" %[^\n]s",n);
	temp=findk(headk,n);
	if(temp==NULL){
		printf("\n\n\t Boyle bir kitap bulunmamakta !!");return -1;
	}
	printf("\n\n \tKitaba kac yazar ekleyeceksiniz ?  ");
	scanf("%d",&a);
	while(i<a){
		printf("\n\n \tEmegi gecen %d. yazari adi-soyadi:   ",i+1);
		scanf("%s %s",n,s);
		temp2=findy(heady,n,s);
		if(temp2!=NULL){
			if(findky(*headky,temp->ISBN,temp2->yazarID,*count)==-1){
				strcpy(temp3.ISBN,temp->ISBN);
				temp3.YazarID=temp2->yazarID;
				if(*headky==NULL)	*headky=(KitapYazar*)malloc(sizeof(KitapYazar));
				else	*headky=(KitapYazar*)realloc((*headky),(*count+1)*sizeof(KitapYazar));
				if(*headky==NULL)return -1;
				(*headky)[*count]=temp3;
				*count+=1;
				writefilekyEnd("KitapYazar.csv",temp3,*count);
			}
			else printf("\n \tBu yazar zaten secmis oldugunuz kitapla eslesmis siradaki yazara geciniz...\n");
			i++;
		}
		else{
			printf("\n\n\t Boyle bir yazar bulunmamakta !!\n");
			t=control(1,2,"\n 1- Tekrar yazar girisi yapmak icin\n 2- Cikis\n");
			if(t==2)return -1;
		}
	}
	return 0;
}

int readfiley(char* fn,Yazar** head,int* count){
	FILE *fp=fopen(fn,"r");
	Yazar *temp;
	if(fp==NULL){
		fclose(fp);
		return -1;
	}
	while(feof(fp)==0){
		temp=(Yazar*)malloc(sizeof(Yazar));
		if(temp==NULL)return -1;		
		fscanf(fp,"%d, %29[^,], %s\n",&temp->yazarID,temp->yazarAd,temp->yazarSoyad);	
		temp->next=NULL;
		addy(head,temp,*count);	
	}
	*count=temp->yazarID;
	fclose(fp);
	return 0;
}
int readfilek(char*fn,Kitap**headk,int *kcount){
	FILE *fp=fopen(fn,"r"),*fp2;
	Kitap *temp,*iter;
	KitapOrnek *temp2;
	char etno[20],etno2[20],durum[20];
	if(fp==NULL){
		printf(" \tdosya acilamadi");
		fclose(fp);return -1;
	}
	
	while(feof(fp)==0){
		temp=(Kitap*)malloc(sizeof(Kitap));
		temp->head=(KitapOrnek*)malloc(sizeof(KitapOrnek));
		if(temp==NULL || temp->head==NULL)return -1;
	
		fscanf(fp,"%29[^,], %13[^,], %d\n",temp->kitapAdi,temp->ISBN,&temp->adet);
		temp->next=NULL;
		temp->head=NULL;
			
		fp2=fopen("KitapOrnek.csv","r");
		if(fp2!=NULL){
			temp->adet=0;
			while(feof(fp2)==0){
				fscanf(fp2,"%20[^,], %s\n",etno,durum);
				strcpy(etno2,etno);
				etno2[13]='\0';
				if(strcmp(temp->ISBN,etno2)==0){
					temp2=(KitapOrnek*)malloc(sizeof(KitapOrnek));
					if(temp2==NULL)return -1;
					temp2->next=NULL;
					temp->adet++;
					strcpy(temp2->EtiketNo,etno);strcpy(temp2->Durum,durum);
					addkOrnek(&temp->head,temp2);
				}
			}
			if(temp->adet==0)	temp->adet++;
			
		}
		fclose(fp2);
		if(*headk==NULL)*headk=temp;
		else{
			iter=*headk;
			while(iter->next!=NULL)iter=iter->next;
			iter->next=temp;
		}
		*kcount=*kcount+1;
	}
	fclose(fp);
	
	return 0;
}

int readfileo(char*fn,Ogrenci**heado,int*count){
	FILE *fp=fopen(fn,"r");
	Ogrenci *temp;
	char id[10],n[30],s[30],p[4];
	if(fp==NULL){
		printf("\n\t Dosya acilamadi!!! \n");
		fclose(fp); return -1;
	}
	
	while(!feof(fp)){
		temp=(Ogrenci*)malloc(sizeof(Ogrenci));
		if(temp==NULL)return -1;
		fscanf(fp,"%8[^,], %29[^,], %29[^,], %d\n",temp->ogrID,temp->ad,temp->soyad,&temp->puan);
		addo(heado,temp,*count);
		*count+=1;
	}
	return 0;
}
int readfileko(char*fn,KitapOdunc** headko,int *count){
	FILE *fp=fopen(fn,"r");
	if(fp==NULL){
		printf("\n Dosya acilamadi!! ");
		fclose(fp); return-1;
	}
	KitapOdunc temp;
	int i,j=0,a,b,c,t;
	
	if(*headko==NULL){
		(*headko)=(KitapOdunc*)malloc(sizeof(KitapOdunc));
		if(*headko==NULL)return -1;
	}
	
	while(feof(fp)==0){
		fscanf(fp,"%20[^,], %8[^,], %d, %d.%d.%d\n",temp.EtiketNo,temp.ogrID,&t,&a,&b,&c);
		temp.islemTipi=t;
		temp.islemTarihi.gun=a;
		temp.islemTarihi.ay=b;
		temp.islemTarihi.yil=c;
		(*headko)[(*count)]=temp;
		*count+=1;
		(*headko)=(KitapOdunc*)realloc(*headko,(*count+1)*sizeof(KitapOdunc));
	}
	fclose(fp);
	return 0;
}
int readfileky(char*fn,KitapYazar **headky,int *count){
	FILE *fp=fopen(fn,"r");
	KitapYazar temp;
	if(fp==NULL){
		printf("\n Dosya acilamadi !!");fclose(fp);return -1;
	}
	
	if(*headky==NULL){
		*headky=(KitapYazar*)malloc(sizeof(KitapYazar));
		if(*headky==NULL)return -1;
	}
	while(!feof(fp)){
		fscanf(fp,"%13[^,], %d\n",temp.ISBN,&temp.YazarID);
		(*headky)[*count]=temp;
		*count+=1;
		*headky=(KitapYazar*)realloc(*headky,(*count+1)*sizeof(KitapYazar));
	}
	fclose(fp);
	return 0;
}

int writefileyStart(char* fn,Yazar *head){
	FILE *fp=fopen(fn,"w");
	Yazar *iter=head;
	if(fp==NULL){
		printf("dosya acilamadi!!\n");
		fclose(fp);
		return -1;
	}
	while(iter->next!=NULL){
		fprintf(fp,"%d, %s, %s\n",iter->yazarID,iter->yazarAd,iter->yazarSoyad);
		iter=iter->next;
	}
	fprintf(fp,"%d, %s, %s\n",iter->yazarID,iter->yazarAd,iter->yazarSoyad);
	fclose(fp);
	return 0;
}
int writefileyEnd(char* fn,Yazar* temp){
	FILE *fp=fopen(fn,"a");
	if(fp==NULL){
		printf("dosya acilamadi!!\n");
		fclose(fp);
		return -1;
	}
	fprintf(fp,"%d, %s, %s\n",temp->yazarID,temp->yazarAd,temp->yazarSoyad);
	fclose(fp);
	return 0;
}
int writefilekStart(char *fn,Kitap *head){
	FILE *fp=fopen(fn,"w");
	if(fp==NULL){
		printf(" Dosya acilamadi");
		fclose(fp);return -1;
	}
	Kitap *iter=head;
	while(iter->next!=NULL){
		fprintf(fp,"%s, %s, %d\n",iter->kitapAdi,iter->ISBN,iter->adet);
		iter=iter->next;
	}
	fprintf(fp,"%s, %s, %d\n",iter->kitapAdi,iter->ISBN,iter->adet);
	fclose(fp);
	return 0;
}
int writefilekEnd(char *fn,Kitap *temp){
	FILE *fp=fopen(fn,"a");
	if(fp==NULL){
		printf("dosya acilamadi!!\n");
		fclose(fp);
		return -1;
	}
	fprintf(fp,"%s, %s, %d\n",temp->kitapAdi,temp->ISBN,temp->adet);
	fclose(fp);
	return 0;
}
int writefileoStart(char *fn,Ogrenci *head){
	FILE *fp=fopen(fn,"w");
	if(fp==NULL){
		printf("dosya acilamadi");
		fclose(fp);return-1;
	}
	Ogrenci *iter=head;
	while(iter->next!=NULL){
		fprintf(fp,"%s, %s, %s, %d\n",iter->ogrID,iter->ad,iter->soyad,iter->puan);
		iter=iter->next;
	}
	fprintf(fp,"%s, %s, %s, %d\n",iter->ogrID,iter->ad,iter->soyad,iter->puan);
	fclose(fp);
	return 0;
}
int writefileoEnd(char *fn,Ogrenci *temp){
	FILE *fp=fopen(fn,"a");
	if(fp==NULL){
		printf("dosya acilamadi");
		fclose(fp);return-1;
	}
	fprintf(fp,"%s, %s, %s, %d\n",temp->ogrID,temp->ad,temp->soyad,temp->puan);
	fclose(fp);
	return 0;
}
int writefilekyStart(char *fn,KitapYazar *head,int count){
	FILE *fp=fopen(fn,"w");
	int i;
	if(fp==NULL){
		printf("dosya acilamadi");
		fclose(fp);return-1;
	}
	for(i=0;i<count;i++) 	fprintf(fp,"%s, %d\n",head[i].ISBN,head[i].YazarID);
	fclose(fp);
	return 0;
}
int writefilekyEnd(char *fn,KitapYazar temp,int count){
	FILE *fp=fopen(fn,"a");
	if(fp==NULL){
		printf("dosya acilamadi");
		fclose(fp);return -1;
	}
	fprintf(fp,"%s, %d\n",temp.ISBN,temp.YazarID);
	fclose(fp);
	return 0;
}
int writefilekoStart(char *fn,KitapOdunc *head,int count){
	FILE *fp=fopen(fn,"w");
	if(fp==NULL){
		printf("dosya acilamadi");
		fclose(fp);return -1;
	}
	int i;
	for(i=0;i<count;i++)	fprintf(fp,"%s, %s, %d, %d.%d.%d\n",head[i].EtiketNo,head[i].ogrID,head[i].islemTipi,head[i].islemTarihi.gun,head[i].islemTarihi.ay,head[i].islemTarihi.yil);
	fclose(fp);
	return 0;
}
int writefileKOrnek(char *fn,Kitap *headk){
	FILE *fp=fopen(fn,"w");
	if(fp==NULL){
		printf("dosya acilamadi");
		fclose(fp);return -1;
	}
	Kitap *iter1=headk;
	KitapOrnek *iter2;
	while(iter1!=NULL){
		iter2=iter1->head;
		while(iter2->next!=NULL){
			fprintf(fp,"%s, %s\n",iter2->EtiketNo,iter2->Durum);
			iter2=iter2->next;
		}
		fprintf(fp,"%s, %s\n",iter2->EtiketNo,iter2->Durum);
		iter1=iter1->next;
	}
	fclose(fp);
	return 0;
}
int createfilekOrnek(char *fn,Kitap *headk,KitapOdunc *headko,int kocount){
	FILE *fp=fopen(fn,"r");
	if(fp==NULL){
		fclose(fp);
		fp=fopen(fn,"w");
		if(fp==NULL){
			printf("dosya acilamadi");
			fclose(fp);return -1;
		}
		Kitap *iter1=headk;
		KitapOrnek *iter2,*temp2;
		int i,j;
		char num[8];
		temp2=(KitapOrnek*)malloc(sizeof(KitapOrnek));
		if(temp2==NULL){
			fclose(fp);return -1;	
		}
		temp2->next=NULL;
		while(iter1!=NULL){
			i=1;
			while(i<=iter1->adet){
				strcpy(temp2->EtiketNo,iter1->ISBN);
				strcat(temp2->EtiketNo,"_");
				sprintf(num,"%d",i);
				strcat(temp2->EtiketNo,num);
				strcpy(temp2->Durum,"");
				for(j=0;j<kocount;j++){
					if(strcmp(headko[j].EtiketNo,temp2->EtiketNo)==0 && headko[j].islemTipi==0)strcpy(temp2->Durum,headko[j].ogrID);
					else if(strcmp(headko[j].EtiketNo,temp2->EtiketNo)==0 && headko[j].islemTipi==1)strcpy(temp2->Durum,"Rafta");
				}	
				if(strcmp(temp2->Durum,"")==0)strcpy(temp2->Durum,"Rafta");
				fprintf(fp,"%s, %s\n",temp2->EtiketNo,temp2->Durum);
				i+=1;
			}
			iter1=iter1->next;
		}
		free(temp2);
	}
	
	fclose(fp);return 0;
}

void printo(Ogrenci *heado){
	Ogrenci *iter=heado;
	while(iter!=NULL){
		printf("\n\tID:%s --- %s %s --- puan: %d",iter->ogrID,iter->ad,iter->soyad,iter->puan);
		iter=iter->next;
	}
}
void printykInfo(Yazar *tempy,Kitap *headk,KitapYazar *headky,int count){
	Kitap *iter;
	int i;
	printf("\n\t%s %s ID:%d \n\n\tYazdigi kitaplar:\n",tempy->yazarAd,tempy->yazarSoyad,tempy->yazarID);
	for(i=0;i<count;i++){
		if(tempy->yazarID==headky[i].YazarID){
			iter=headk;
			while(iter->next!=NULL){
				if(strcmp(iter->ISBN,headky[i].ISBN)==0)printf("\t%s ISBN:%s\n",iter->kitapAdi,iter->ISBN);
				iter=iter->next;
			}
			if(strcmp(iter->ISBN,headky[i].ISBN)==0)printf("\t%s ISBN:%s\n",iter->kitapAdi,iter->ISBN);
		}
	}
}
void printkyInfo(Kitap *tempk,Yazar *heady,KitapYazar *headky,int count){
	int i;
	Yazar *iter;
	printf("\t%s  ISBN: %s  Adet:%d \n\tKitapta emegi gecen yazarlar:\n\n",tempk->kitapAdi,tempk->ISBN,tempk->adet);
	for(i=0;i<count;i++){
		if(strcmp(tempk->ISBN,headky[i].ISBN)==0){
			iter=heady;
			while(iter->next!=NULL){
				if(iter->yazarID==headky[i].YazarID)printf("\t%s  %s  ID:%d\n",iter->yazarAd,iter->yazarSoyad,iter->yazarID);
				iter=iter->next;
			}
			if(iter->yazarID==headky[i].YazarID)printf("\t%s  %s  ID:%d\n",iter->yazarAd,iter->yazarSoyad,iter->yazarID);
		}
	}
}
void printkoInfo(Ogrenci *tempo,Kitap *headk,KitapOdunc *headko,int count){
	int i;
	char temp[14];
	Kitap *iter;
	printf("\t%s %s  ID: %s\n\tOgrencide bulunan kitaplar:\n\n",tempo->ad,tempo->soyad,tempo->ogrID);
	for(i=0;i<count;i++){
		if(strcmp(tempo->ogrID,headko[i].ogrID)==0){
			iter=headk;
			while(iter->next!=NULL){
				strcpy(temp,headko[i].EtiketNo);
				temp[13]='\0';
				if(strcmp(iter->ISBN,temp)==0 && headko[i].islemTipi==0)printf("\t%s  EtiketNo: %s  Alindigi tarih: %d.%d.%d\n",iter->kitapAdi,headko[i].EtiketNo,headko[i].islemTarihi.gun,headko[i].islemTarihi.ay,headko[i].islemTarihi.yil);
				iter=iter->next;
			}
			if(strcmp(iter->ISBN,temp)==0 && headko[i].islemTipi==0)printf("\t%s  EtiketNo: %s  Alindigi tarih: %d.%d.%d\n",iter->kitapAdi,headko[i].EtiketNo,headko[i].islemTarihi.gun,headko[i].islemTarihi.ay,headko[i].islemTarihi.yil);
		}
	}
}

int control(int alt,int ust,char *metin){
	int cho;
	do{
		printf("%s",metin);
		scanf("%d",&cho);
		if(cho>ust || cho<alt)printf("\n\tBoyle bir islem bulunmamakta!! tekrar giriniz...\n");
	}while(cho>ust || cho<alt);
	return cho;
}

void freey(Yazar *head){
	Yazar *iter=head,*prev;
	while(iter!=NULL){
		prev=iter;
		iter=iter->next;
		free(prev);
	}
}
void freek(Kitap *head){
	Kitap *iter=head,*prev;
	KitapOrnek *iterh,*prevh;
	while(iter!=NULL){
		prev=iter;
		iterh=iter->head;
		while(iterh!=NULL){
			prevh=iterh;
			iterh=iterh->next;
			free(prevh);
		}
		iter=iter->next;
		free(prev);
	}
}
void freeo(Ogrenci *head){
	Ogrenci *iter=head;
	while(iter!=NULL){
		if(iter->prev!=NULL)free(iter->prev);
		iter=iter->next;
	}
}

void printy(Yazar *heady){
	Yazar *temp=heady;
	while(temp!=NULL){
		printf("\n\tID:%d --- %s %s",temp->yazarID,temp->yazarAd,temp->yazarSoyad);
		temp=temp->next;
	}		
}
void printk(Kitap *headk){
	Kitap *iter=headk;
	KitapOrnek *temp;
	while(iter!=NULL){
		printf("\n\n\tKitap: %s  ISBN:%s adet:%d ",iter->kitapAdi,iter->ISBN,iter->adet);
		temp=iter->head;
		while(temp->next!=NULL){
			printf("\n\tKitap: %s Etiket:%s Durum:%s",iter->kitapAdi,temp->EtiketNo,temp->Durum);
			temp=temp->next;
		}
		printf("\n\tKitap: %s Etiket:%s Durum:%s",iter->kitapAdi,temp->EtiketNo,temp->Durum);
		iter=iter->next;
	}
}

