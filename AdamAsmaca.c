#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//tükçe dil desteði için eklenen kütüphane
#include <string.h>

#define MaxKelimeUzunluk 15 //sorulacak kelimenin maximum uzunluðunu tutar

void rastgeleAta(char *kelime,int *can){//soruda kullanýlacak kelimeyi rastgele atayan ve can'ý da ona göre belirleyen fonksiyon
    srand(time(NULL));//random fonksiyonu için
    char *wordList[] = { "Araba","Avokado","Mandalina","Amerika","Venüs","Kitap","Serçe","Bilgisayar","Zebra"};//kelime listesi, ekleme çýkarma yapýlabilir
    
    int wordCount = sizeof(wordList) / sizeof(wordList[0]);//kaç tane kelime olduðunu bulma
    strcpy(kelime, wordList[rand() % wordCount]); //rastgele bir indexteki kelimeyi oyunda kullanacaðýmýz kelime deðiþkenine kopyalama
    
    *can = strlen(kelime)*2;//can deðiþkeninin kelime sayýsýnýn 2 katý olarak belirlenmesi
}
int IsIncludedKontrol(char denenenler[], char denenen[]) {//gelen harfin dizi içerisinde olup olmadýðýný kontrol eden fonksiyon iki ayrý yerde kullanýlýyor
    int i;//döngü deðiþkeni
    for(i = 0; i < strlen(denenenler); i++) {//denenenler dizisinin tüm elemanlarýnýn gezilmesi
        if(tolower(denenenler[i]) == tolower(denenen[0])) { //büyük küçük harflerin sorun olmamasý için hepsi küçük harfe çevriliyor ve kontrol ediliyor
            return 1; //eðer varsa 1
        }
    }
    return 0;//yoksa 0 döndürüyor
}

int main(int argc, char *argv[]) {//adam asmaca oyununda kullanýcýnýn kelimeyi ve can'ý isterse kendisinin de belirleyebilmesini istedim bu yüzden argv ve argc kullandým
                                  // kullanmak için exe dosyasý konumu ile beraber C:../AdamAsmaca.exe -c 10 -k "BirKelime" þeklinde çalýþtýrýlabilir.
    setlocale(LC_ALL, "Turkish");//türkçe dil desteði
    char *kelime;//oyunda sorulan kelimeyi tutan
    int can;//caný tutan
    int yanlis = 0;
    char denenenler[29];//denenen tm harfleri depolayan
    char denenen[2];//anlýk denenen harfi     depolayan deðiþkenler
    
    int i,j;//döngü için
    kelime = (char*) malloc(MaxKelimeUzunluk * sizeof(char));//kelime için hafizada yer ayýrma
    rastgeleAta(kelime,&can);//rastgeleAta fonksiyonu ile kelimenin rastgele seçilmesi

    for(i=0;i<argc;i++){//argc deðerlerin dönülmesi örneðin "-c","10","-k","BirKelime"
        if(strcmp(argv[i], "-k")==0){// -k olan elemandan bir sonraki elemaný kelimeye eþitler
            kelime = (char*) realloc(kelime, (strlen(argv[i+1])+1) * sizeof(char));//bunun için kelimenin boyutunu reallocla tekarar oluþturur
            strcpy(kelime,argv[i+1]);//bir sonraki elemanýn kopyalanma iþlemi
            
        }
        if(strcmp(argv[i], "-c")==0){//ayný iþlemlerin -c için yapýlmasý
           sscanf(argv[i+1], "%d", &can);//bir sonraki elemanýn kopyalanma iþlemi  
        }
    }
    
    printf("\nAdam asmaca oyununa hoþgeldiniz\n");//kullanýcýyý selamlama
    
   for(i = 0;i<strlen(kelime);i++){//kullanýcýnýn ilk oyun baþladýðýnda tahmin ettiði kelimenin kaç harfli olduðunu bilmesi için yazdýrma
   	   printf("_");
   	
   }
   
   int won;//won isimli bool deðiþken(int ama bool olara kullanýldý)
   
   while(can >= 0){//can 0 da dahil 0dan büyük olduðu sürece deneme hakký veren döngü. Yani can = 0 olduðunda da son bir deneme hakký kalmýþ oluyor
   	won = 1;//her döngünün baþýnda won 1 yapýlýyor eðer kapalý olan harf varsa geri 0 yapýlýyor 	
   	while(1){//eðer kullanýcý daha önce denediði bir harfi denrse bu döngüden çýkamýyor
   		
    printf("\nBir harf deneyin:");
    scanf(" %c", &denenen);//kullanýcýdan denenen harfin alýnmasý
    printf("\n");
    
    if(IsIncludedKontrol(denenenler,denenen)){//denenen harf daha önce denenmiþmi diye kontrol ediliyor edilmiþse bir uyarý mesajý verilip döngü baþa alýnýyor
    	printf("\n %c, daha önce denediniz baþka bir þey deneyin.\n",denenen[0]);//uyarý mesajý
	}else{
		break;//eðer daha önce edilmemiþse döngü kýrýlýp oyuna devam ediliyor
	}
	  
	   } 
   
    strcat(denenenler, denenen);//yeni denenen eski denenenlerin listesine ekleniyor
    for(i = 0; i < strlen(kelime); i++){//kelimenin tüm elemanlarý geziliyor
        for(j = 0; j < strlen(denenenler); j++){//denenenlerin hepsi geziliyor. Kelimedeki harfler buna göre açýk veya kapalý oluyor
            if(tolower(kelime[i]) == tolower(denenenler[j])){//denenen harflerin kelimedeki harflerle karþýlaþtýrýlmasý. Ýþlemler büyük-küçük harf uyumsuzluðunu önlemek için
            //tolower ile küçültülüp yapýlýyor
                printf("%c", kelime[i]);//eðer harf tahmin edilmiþse açýk olarak yazýlýyor
                break;//bulunduktan sonra dönmeye devam etmenin anlamý yok
            } 
        }
        if(j == strlen(denenenler)){//eðer j denenenlerin son harfine kadar gelebilmiþse kullanýcý doðru tahmin yapamamýþ demektir
            printf("_");//harf tahmin edilmemiþse kapalý olarak yazýlýyor ve won 0'a eþitleniyor
            won = 0;//won 0 yapýlýyor yani bu tur kazanamadý buraya hiç girmezse kazanmýþtýr demektir.
        }
    }
    if(won){//eðer kazanmýþsa kullanýcý tebrik ediliyor ve program bitiyor
    	printf("\nTebrikler Kazandýnýz.\n");
    	break;
	}
	if(!IsIncludedKontrol(kelime,denenen)){//her turda kelimenin içinde denenen var mý kontrol ediliyor bu sayede can sadece yanlýþ tahminlerde azaltýlýyor
			can--;//canýn azaltýlmasý
		    yanlis++;//yanlýþ sayacý 
	}

    if(can >= 0){//can 0dan büyük olduðu sürece kalan can ve toplam yanlýþ deðereleri yazdýrýlýyor
    	   printf("\nKalan Can: %d Toplam Yanlýþ Tahmin: %d\n",can,yanlis);//yapýlan hata sayýsý ve can'ýn her turda yazýlmasý
	}
	
	if(can <0){//can 0'ýn altýna düþtüðünde uyarý mesajý veriliyor ve hemen bir sonraki döngünün baþýnda da program bitiyor
		printf("\nKaybettiniz kelime , %s idi",kelime);
	}
 
}

   
    free(kelime);//bellek serbest býrakýlýyor
    return 0;
}
