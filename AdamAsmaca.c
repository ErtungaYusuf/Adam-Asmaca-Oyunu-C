#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//t�k�e dil deste�i i�in eklenen k�t�phane
#include <string.h>

#define MaxKelimeUzunluk 15 //sorulacak kelimenin maximum uzunlu�unu tutar

void rastgeleAta(char *kelime,int *can){//soruda kullan�lacak kelimeyi rastgele atayan ve can'� da ona g�re belirleyen fonksiyon
    srand(time(NULL));//random fonksiyonu i�in
    char *wordList[] = { "Araba","Avokado","Mandalina","Amerika","Ven�s","Kitap","Ser�e","Bilgisayar","Zebra"};//kelime listesi, ekleme ��karma yap�labilir
    
    int wordCount = sizeof(wordList) / sizeof(wordList[0]);//ka� tane kelime oldu�unu bulma
    strcpy(kelime, wordList[rand() % wordCount]); //rastgele bir indexteki kelimeyi oyunda kullanaca��m�z kelime de�i�kenine kopyalama
    
    *can = strlen(kelime)*2;//can de�i�keninin kelime say�s�n�n 2 kat� olarak belirlenmesi
}
int IsIncludedKontrol(char denenenler[], char denenen[]) {//gelen harfin dizi i�erisinde olup olmad���n� kontrol eden fonksiyon iki ayr� yerde kullan�l�yor
    int i;//d�ng� de�i�keni
    for(i = 0; i < strlen(denenenler); i++) {//denenenler dizisinin t�m elemanlar�n�n gezilmesi
        if(tolower(denenenler[i]) == tolower(denenen[0])) { //b�y�k k���k harflerin sorun olmamas� i�in hepsi k���k harfe �evriliyor ve kontrol ediliyor
            return 1; //e�er varsa 1
        }
    }
    return 0;//yoksa 0 d�nd�r�yor
}

int main(int argc, char *argv[]) {//adam asmaca oyununda kullan�c�n�n kelimeyi ve can'� isterse kendisinin de belirleyebilmesini istedim bu y�zden argv ve argc kulland�m
                                  // kullanmak i�in exe dosyas� konumu ile beraber C:../AdamAsmaca.exe -c 10 -k "BirKelime" �eklinde �al��t�r�labilir.
    setlocale(LC_ALL, "Turkish");//t�rk�e dil deste�i
    char *kelime;//oyunda sorulan kelimeyi tutan
    int can;//can� tutan
    int yanlis = 0;
    char denenenler[29];//denenen tm harfleri depolayan
    char denenen[2];//anl�k denenen harfi     depolayan de�i�kenler
    
    int i,j;//d�ng� i�in
    kelime = (char*) malloc(MaxKelimeUzunluk * sizeof(char));//kelime i�in hafizada yer ay�rma
    rastgeleAta(kelime,&can);//rastgeleAta fonksiyonu ile kelimenin rastgele se�ilmesi

    for(i=0;i<argc;i++){//argc de�erlerin d�n�lmesi �rne�in "-c","10","-k","BirKelime"
        if(strcmp(argv[i], "-k")==0){// -k olan elemandan bir sonraki eleman� kelimeye e�itler
            kelime = (char*) realloc(kelime, (strlen(argv[i+1])+1) * sizeof(char));//bunun i�in kelimenin boyutunu reallocla tekarar olu�turur
            strcpy(kelime,argv[i+1]);//bir sonraki eleman�n kopyalanma i�lemi
            
        }
        if(strcmp(argv[i], "-c")==0){//ayn� i�lemlerin -c i�in yap�lmas�
           sscanf(argv[i+1], "%d", &can);//bir sonraki eleman�n kopyalanma i�lemi  
        }
    }
    
    printf("\nAdam asmaca oyununa ho�geldiniz\n");//kullan�c�y� selamlama
    
   for(i = 0;i<strlen(kelime);i++){//kullan�c�n�n ilk oyun ba�lad���nda tahmin etti�i kelimenin ka� harfli oldu�unu bilmesi i�in yazd�rma
   	   printf("_");
   	
   }
   
   int won;//won isimli bool de�i�ken(int ama bool olara kullan�ld�)
   
   while(can >= 0){//can 0 da dahil 0dan b�y�k oldu�u s�rece deneme hakk� veren d�ng�. Yani can = 0 oldu�unda da son bir deneme hakk� kalm�� oluyor
   	won = 1;//her d�ng�n�n ba��nda won 1 yap�l�yor e�er kapal� olan harf varsa geri 0 yap�l�yor 	
   	while(1){//e�er kullan�c� daha �nce denedi�i bir harfi denrse bu d�ng�den ��kam�yor
   		
    printf("\nBir harf deneyin:");
    scanf(" %c", &denenen);//kullan�c�dan denenen harfin al�nmas�
    printf("\n");
    
    if(IsIncludedKontrol(denenenler,denenen)){//denenen harf daha �nce denenmi�mi diye kontrol ediliyor edilmi�se bir uyar� mesaj� verilip d�ng� ba�a al�n�yor
    	printf("\n %c, daha �nce denediniz ba�ka bir �ey deneyin.\n",denenen[0]);//uyar� mesaj�
	}else{
		break;//e�er daha �nce edilmemi�se d�ng� k�r�l�p oyuna devam ediliyor
	}
	  
	   } 
   
    strcat(denenenler, denenen);//yeni denenen eski denenenlerin listesine ekleniyor
    for(i = 0; i < strlen(kelime); i++){//kelimenin t�m elemanlar� geziliyor
        for(j = 0; j < strlen(denenenler); j++){//denenenlerin hepsi geziliyor. Kelimedeki harfler buna g�re a��k veya kapal� oluyor
            if(tolower(kelime[i]) == tolower(denenenler[j])){//denenen harflerin kelimedeki harflerle kar��la�t�r�lmas�. ��lemler b�y�k-k���k harf uyumsuzlu�unu �nlemek i�in
            //tolower ile k���lt�l�p yap�l�yor
                printf("%c", kelime[i]);//e�er harf tahmin edilmi�se a��k olarak yaz�l�yor
                break;//bulunduktan sonra d�nmeye devam etmenin anlam� yok
            } 
        }
        if(j == strlen(denenenler)){//e�er j denenenlerin son harfine kadar gelebilmi�se kullan�c� do�ru tahmin yapamam�� demektir
            printf("_");//harf tahmin edilmemi�se kapal� olarak yaz�l�yor ve won 0'a e�itleniyor
            won = 0;//won 0 yap�l�yor yani bu tur kazanamad� buraya hi� girmezse kazanm��t�r demektir.
        }
    }
    if(won){//e�er kazanm��sa kullan�c� tebrik ediliyor ve program bitiyor
    	printf("\nTebrikler Kazand�n�z.\n");
    	break;
	}
	if(!IsIncludedKontrol(kelime,denenen)){//her turda kelimenin i�inde denenen var m� kontrol ediliyor bu sayede can sadece yanl�� tahminlerde azalt�l�yor
			can--;//can�n azalt�lmas�
		    yanlis++;//yanl�� sayac� 
	}

    if(can >= 0){//can 0dan b�y�k oldu�u s�rece kalan can ve toplam yanl�� de�ereleri yazd�r�l�yor
    	   printf("\nKalan Can: %d Toplam Yanl�� Tahmin: %d\n",can,yanlis);//yap�lan hata say�s� ve can'�n her turda yaz�lmas�
	}
	
	if(can <0){//can 0'�n alt�na d��t���nde uyar� mesaj� veriliyor ve hemen bir sonraki d�ng�n�n ba��nda da program bitiyor
		printf("\nKaybettiniz kelime , %s idi",kelime);
	}
 
}

   
    free(kelime);//bellek serbest b�rak�l�yor
    return 0;
}
