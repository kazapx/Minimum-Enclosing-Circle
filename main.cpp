#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <graphics.h>


int main()
{
	FILE* f;
	f = fopen("coordinates.txt", "r");
	if (f == NULL) { // dosyaya erisilemiyorsa NULL olur
		printf("dosya acilamadi\n");
		exit(1);
	}



//BLOK------------------------------------------------------------------------------

// "x_y_sayisi" degeri "sayilar" dizisinin boyutunu belirliyor ve.
int x_y_sayisi=0;
char cha;
printf("TXT dosyasindan cekilecek metin: ");
while ((cha = fgetc(f)) != EOF) {
printf("%c", cha);                        //kontrol icin sonra silinecek

if(cha=='}')
    x_y_sayisi++;
}
x_y_sayisi=(x_y_sayisi-1)*2;

printf("\n\n Toplam x ve y sayisi: %d\n\n",x_y_sayisi);


//BLOK----------------------------------------------------------------------------------


// "sayilar" dizisinin her elemanini 0 a ataması yapılıyor
int sayilar[x_y_sayisi];
for(int f=0;x_y_sayisi>f;f++)
    sayilar[f]=0;


fclose(f);
f = fopen("coordinates.txt", "r"); //fgetc yuzunden cursor txt dosyasında ilerledi cursoru tekrar basa getirmek icin

   char al[999];
    fgets(al, 999, f); //txt dosyasından diziye kopyalama işlemi
    printf("Stringe atilan metin: %s  \n",al); //txtden kordinatlari alip al stringine yazdirdim ve suan stringi printliyorum.

fclose(f);    //Artık txt ile isimiz yok , kapatiyoruz


//BLOK-------------------------------------------------------------------------------------------


// SUSLU PARANTEZ VE VIRGUL ICIN BOSLUK ATAMASI YAPILAN KISIM
int ii;
for (ii = 0; al[ii] != '\0'; ii++) {
        if (al[ii] == ',' || al[ii] == '{' || al[ii] == '}')
            al[ii] = ' ';
    }

    printf("\n");
printf("Gereksiz isaretlerden sadelestirilen dizi: %s \n\n",al);


//BLOK---------------------------------------------------------------------------------------------


// STRING'TEN INTEGER'A ÇEVİRME VE SAYILAR(int) DIZISINE ATMA KISMI
int negatif_mi=0;
int j = -1;
int i;
 for (i = 0; al[i] != '\0'; i++) {
         if((al[i]==' ') && negatif_mi == 1)
        {      sayilar[j] = sayilar[j]*(-1);
               negatif_mi=0;
        }
         if (al[i] == ' '&& isdigit(al[i+1]) )
        { j++;
        }
        if (al[i] == '-'&& isdigit(al[i+1]) )
        { j++;
        i++;
        sayilar[j] = sayilar[j] * 10 + (al[i] - 48);
        negatif_mi =1;
        continue;
        }

        if(isdigit(al[i])) {
sayilar[j] = sayilar[j] * 10 + (al[i] - 48);  //48, 0'ın yani rakamların asciide baslangıc noktası.
        }


    }


printf("Integer dizisine atildi: ");
for(int asdf=0;x_y_sayisi>asdf;asdf++)  // DIZIYI YAZDIR
    printf(" %d ",sayilar[asdf]); //kontrol amaclı printledik

printf("\n");


//BLOK-------------------------------------------------------------------------------------------




// KOORDİNATLARI X VE Y DIZILERINE AYIRMA VE YAZDIRMA KISMI
int kordinat_sayisi = x_y_sayisi/2;
int x[kordinat_sayisi];
int y[kordinat_sayisi];
int xx=0;
int yy=0;
for(int asdfg=0;x_y_sayisi>asdfg;asdfg++)
  {

   x[xx]=sayilar[asdfg];xx++;
   asdfg++;
    y[yy]=sayilar[asdfg];yy++;

}



//Dosya işlemleri tamamlandı. Diziler hazırlandı. Buradan yukarısı değiştirilmeyecek.
//BLOK-----------------------------------------------------------------------------------------


// DAIRE
//STEP1

printf("\n Girilen koordinat sayisi: %d \n\n",kordinat_sayisi);

float eski_uzaklik=0;
int j2,i2;
float d1,d2;
float yeni_uzaklik;

int p1x,p1y,p2x,p2y;

for(j2=0;kordinat_sayisi>j2;j2++){
 for(i2=0;kordinat_sayisi>i2;i2++){

  d1=pow((x[j2]-x[i2]),2);

   d2=pow((y[j2]-y[i2]),2);

yeni_uzaklik = sqrt(d1+d2);

if(eski_uzaklik<yeni_uzaklik){
eski_uzaklik=yeni_uzaklik;
p1x=x[j2]; p1y=y[j2]; //en uzak noktalari kaydetme olayi
p2x=x[i2]; p2y=y[i2];
}


}
}

float yaricap=eski_uzaklik/2.0;

float cembermerkez_x=(p1x+p2x)/2.0;
float cembermerkez_y=(p1y+p2y)/2.0;



//EKRAN İŞLEMLERİ
float yirmi=20;
// *yirmi çemberi ve noktaları büyütmek için 20x20 koordinat oluştu daha büyük koordinat düzlemi için *yirmileri ve x y belirteçlerini silmek yeterli


int gm = 800, gr = 800; //pencere boyutu ayarı
initwindow(gm,gr,"Minimum Covering Circle"); //pencere açma


setbkcolor(RED);
outtextxy(10, 10, "Minimum Covering Circle");


circle(400+cembermerkez_x*yirmi,400-cembermerkez_y*yirmi,6); //MERKEZ
setfillstyle(SOLID_FILL,RED);
floodfill(400+cembermerkez_x*yirmi,400-cembermerkez_y*yirmi,15);
setbkcolor(0);
outtextxy(410+cembermerkez_x*yirmi,390-cembermerkez_y*yirmi,"M" );


line(400,0,400,800); //y çizgisi
line(0,400,800,400); //x çizgisi

for(int i=0;800>i;i+=yirmi)//x belirteçleri
line(i,405,i,395);

for(int i=0;800>i;i+=yirmi)//y belirteçleri
line(395,i,405,i);

circle(400+cembermerkez_x*yirmi,400-cembermerkez_y*yirmi,yaricap*yirmi); //cember (400+lar merkezden başlatmak için graphics.h sol köşeden 0 olarak başlıyor)

for(i=0;kordinat_sayisi>i;i++){
circle(400+x[i]*yirmi,400-y[i]*yirmi,6); //noktalari koyma
}


//BLOK------------------------------------------------------------------------------------------------------


//STEP2'YE GECİLMEYE GEREK VAR MI KONTROL ETME KISMI
//HER NOKTANIN STEP1 DE CIZILEN DAIRENIN MERKEZINE UZAKLIGINA BAKILIR/ YARICAPTAN BUYUK OLAN UZAKLIK VARSA STEP2 YE GECILIR

int p3x,p3y; //Daire dışında kalan nokta olursa koordinatlarını bu değişkenlere atayacağız

float en_uzak_nokta_uzakligi = 0;
for(int b=0;kordinat_sayisi>b;b++){

  d1=pow((cembermerkez_x-x[b]),2);

   d2=pow((cembermerkez_y-y[b]),2);

float center_distance = sqrt(d1+d2);

if(center_distance>yaricap){ //p1 a b -- p2 c d --a[b] y[b]ef
p3x=x[b];
p3y=y[b];
en_uzak_nokta_uzakligi = center_distance;
yaricap=en_uzak_nokta_uzakligi;

}
}


//"en_uzak_nokta_uzakligi"==0 KALMISSA STEP1 DEKI DAIRENIN YARICAPINI ASAN NOKTA YOKTUR DEMEKTIR VE SONRAKI STEPLERI YAPMAYA GEREK YOKTUR.
if(en_uzak_nokta_uzakligi == 0.0){
    printf("\n");

printf("Birbirine en uzak noktalar (%d , %d) ve (%d , %d) \n",p1x,p1y,p2x,p2y);
printf("Birbirine en uzak noktalar arasi uzaklik: %f \n",eski_uzaklik);

printf("cember yaricap: %f \n",yaricap); //Cemberin yaricapi yazdiriliyor
printf("Cember merkez koordinat: ( %f , %f )",cembermerkez_x,cembermerkez_y); //Cember merkezinin x ve y koordinati yazdiriliyor

    system("pause");
    return 0;

    }

//BLOK----------------------------------------------------------------------------------------


//DAIRE
//STEP2

float Xstep2;
float Ystep2;
float Rstep2;


Xstep2 = (( (pow(p1x,2)+pow(p1y,2))*(p3y-p2y) + (pow(p2x,2)+pow(p2y,2))*(p1y-p3y) + (pow(p3x,2)+pow(p3y,2))*(p2y-p1y) )/(p1x*(p3y-p2y) + p2x*(p1y-p3y) + p3x*(p2y-p1y)))/2;
Ystep2 = (( (pow(p1x,2)+pow(p1y,2))*(p3x-p2x) + (pow(p2x,2)+pow(p2y,2))*(p1x-p3x) + (pow(p3x,2)+pow(p3y,2))*(p2x-p1x) )/(p1y*(p3x-p2x) + p2y*(p1x-p3x) + p3y*(p2x-p1x)))/2;


Rstep2= sqrt( pow((Xstep2-p1x),2) + pow((Ystep2-p1y),2) );

//STEP1 DEKI ÇIZILEN DAIREYI SILMEK ICIN EKRANDAKI HERSEYI SILDIRIP YENIDEN CIZDIRIYORUZ
//EKRAN
cleardevice();

setbkcolor(RED);
outtextxy(10, 10, "Minimum Covering Circle");
circle(400+Xstep2*yirmi,400-Ystep2*yirmi,6); //MERKEZ
setfillstyle(SOLID_FILL,RED);
floodfill(400+Xstep2*yirmi,400-Ystep2*yirmi,15);
setbkcolor(0);
outtextxy(410+Xstep2*yirmi,390-Ystep2*yirmi,"M" );

circle(400+Xstep2*yirmi,400-Ystep2*yirmi,Rstep2*yirmi);
// *yirmi çemberi ve noktaları büyütmek için 20x20 koordinat oluştu daha büyük koordinat düzlemi için *yirmileri ve x y belirteçlerini silmek yeterli
line(400,0,400,800); //y çizgisi
line(0,400,800,400); //x çizgisi


for(int i=0;800>i;i+=yirmi)//x belirteçleri
line(i,405,i,395);

for(int i=0;800>i;i+=yirmi)//y belirteçleri
line(395,i,405,i);

for(i=0;kordinat_sayisi>i;i++){
circle(400+x[i]*yirmi,400-y[i]*yirmi,6); //noktalari koyma
}


printf("cember yaricap: %f \n",Rstep2);
printf("Cember merkez koordinat: ( %f , %f )",Xstep2,Ystep2);

system("pause"); //çizim ekranını bekletme



	return 0;
}
