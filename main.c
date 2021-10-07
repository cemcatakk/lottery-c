#include <stdio.h>
#include <stdlib.h>

int dizidemi(int dizi[],int boyut,int sayi){
	int i; //Bir bilette ayni sayilarin olmamasi icin bu metotu kullandik
	for(i=0;i<boyut;i++){
		if(dizi[i]==sayi){
			return 1;//1 Donerse sayi vardir
		}
	}
	return 0; //0 Donerse yoktur
}
int* cekilisYap(){
	int* dizi = (int*)malloc(sizeof(int)*22);
	int i,sayi; //22 Adet farkli sayi olusturularak dizinin icine ekliyoruz
	for(i=0;i<22;i++){
		sayi = 1+rand()%80;
		while(dizidemi(dizi,22,sayi)==1){
			sayi = 1+rand()%80;//Sayilarin araligi 1-80 arasi olmali, farkli eleman bulunana kadar dongude rastgele sayi uretiyoruz
		}
		dizi[i] = sayi;
	}
	return dizi;//Ardindan talihli sayilari geri donduruyoruz
}
int* rastgeleBilet(){
	int* bilet = (int*)malloc(sizeof(int)*10);
	int i,sayi; //10 Adet rastgele sayi olusturarak, rastgele bir bilet olusturuyoruz
	for(i=0;i<10;i++){
		sayi = 1+rand()%80;
		while(dizidemi(bilet,10,sayi)==1){//Bu dongude her sayinin farkli olmasini sagliyoruz
			sayi = 1+rand()%80;
		}
		bilet[i] = sayi;
	}
	return bilet;//Ardindan diziyi donduruyoruz
}

int biletAnalizi(int* talihliSayilar,int *bilet){
	int i,j,sayac=0;
	printf("Bilet kontrol ediliyor..\n");
	for(i=0;i<22;i++){//Bilet analizi, talihli sayilar ile bir biletin her rakamini karsilastirir, eslesen sayilari ekrana yazar ve bilinen sayisinia rttirir
		for(j=0;j<10;j++){
			if(talihliSayilar[i]==bilet[j]){ //Eger talihli sayi ve bilet sayisi esit ise sayac 1 arttirilir
				sayac++;
				printf("Bilinen Sayi: %d\n",bilet[j]); 
			}
		}
	}
	printf("Toplam bilinen: %d\n\n",sayac);
}
int* biletOyna(){
	int i,sayi;//Kullanicidan 10 adet sayi alinarak, bir diziye aktarili 
	int *dizi = (int*)malloc(sizeof(int)*10);
	for(i=0;i<10;i++){
		while(1){
			printf("1-80 Arasi %d. sayiyi giriniz:",i+1);
			scanf("%d",&sayi); //Bu sayinin 1-80 arasinda ve dizide olmamasi gerekir, bunu dongude kontrol ediyoruz
			if(sayi>=1&&sayi<=80){
				if(dizidemi(dizi,10,sayi)==0)break;
			}
		}
		dizi[i]=sayi;
	}
	return dizi; //Ardindan diziyi donduruyoruz
}
void biletYazdir(int * bilet,int adet){
	int i;
	printf("Bilet bilgisi: ");
	for(i=0;i<adet;i++){//Bilet bilgisi ekrana yazdiriliyor
		printf("%d-",bilet[i]);
	}
	printf("\n");
}
int main(int argc, char *argv[]) {
	int secim,biletadet=0;
	int** biletler = (int**)malloc(sizeof(int*)*100); //Bu 2 boyutlu dizi, biletleri tutacak
	while(1){ //Sonsuz bir dongu acip kullanici cekilis yapana kadar calistiriyoruz
		printf("1-Rastgele Bilet Ekle\n2-Bilet Ekle\n3-Cekilisi Baslat\n>>");
		scanf("%d",&secim);
		if(secim==1){
			biletler[biletadet] = rastgeleBilet(); //Rastgele bilet olusturup diziye ekliyoruz ve ekrana yazdiriyoruz
			biletYazdir(biletler[biletadet],10); 
			biletadet++;
		}
		else if(secim==2){
			biletler[biletadet] = biletOyna(); //Kullaniciya bilet oynatip diziye ekliyoruz ve ekrana yazdiriyoruz
			biletYazdir(biletler[biletadet],10);
			biletadet++;
		}
		else if(secim==3){
			int i;
			int* talihliSayilar = cekilisYap();
			printf("******TALIHLI SAYILAR*********\n");
			biletYazdir(talihliSayilar,22); //Once talihli sayilari yazdiriyoruz
			for(i=0;i<biletadet;i++){
				printf("**%d Numarali Bilet Bilgisi**\n",i+1);
				biletYazdir(biletler[i],10); //Ardindan her bilet bilgisi ve analizini yazdiriyoruz
				biletAnalizi(talihliSayilar,biletler[i]);
			}
			printf("Cekilis sonuclari yukarida listelenmistir! Bir dahaki sefere bol sans!\n");
			exit(1);//Ardindan uygulamadan cikiyoruz
		}
		else printf("Hatali giris.\n");
	}
	return 0;
}
