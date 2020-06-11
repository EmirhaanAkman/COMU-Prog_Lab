#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define True 1
#define False 0

// Emirhan Akman 180401068

struct Kart{
    // 0 = Kupa, 1 = Maca, 2 = Karo, 3 = Sinek
    // 0 = Destede, 10 = Bilgisayar, 20 = Oyuncu, 30 = Yer
    // 15 = Bilgisayar kartlari, 25 = Oyuncu kartlari
    int kartTip;
    int kartNo;
    int holder;
};

struct Deste{
    struct Kart tumKartlar[52];
};

struct Yonetici{
    struct Deste tumDeste;
    struct Deste karismisDeste;

    int desteBasi;

    int yerSayisi;
    int* yerKartlari;
    int sonyer;

    int oyuncuKartSayisi;
    int* oyuncuKartlari;
    int oyuncuToplam;
    int* oyuncuToplamKart;
    int oyuncuPistiSayisi;
    int oyuncuValePistiSayisi;

    int cpuKartSayisi;
    int* cpuKartlari;
    int cpuToplam;
    int* cpuToplamKart;
    int cpuPistiSayisi;
    int cpuValePistiSayisi;

    int oyuncununAttigi[52];
    int oyuncununHamle;

    int cpuAttigi[52];
    int cpuHamle;

    int elSayisi;
    int sonlan;

};

void oyunuYukle(struct Yonetici* );
void desteyiYazdir(struct Deste , int , int );
void desteyiKaristir(struct Deste* , int , int );
int desteBasiBul(struct Deste , int );
void kartElDegistir(struct Yonetici* , int , int );
void guncelle(struct Yonetici* );
void printYonetici(struct Yonetici );
void oyuncuHamleBekle(struct Yonetici* );
void ekraniyazdir(struct Yonetici* );
void hamleyiDegerlendir(struct Yonetici* , int , int, int );
void bilgisayarHamleYap(struct Yonetici* );
int kartIndexiBul(struct Yonetici , int , int );
void elsonuBak(struct Yonetici* );
char* kartTipi(int );
void oyunSonuEkrani(struct Yonetici* );

int main()
{
    struct Yonetici yonetici;
    oyunuYukle(&yonetici);

    while (1)
    {
        ekraniyazdir(&yonetici);
        oyuncuHamleBekle(&yonetici);
        bilgisayarHamleYap(&yonetici);
        elsonuBak(&yonetici);

        if (yonetici.sonlan == 1)
            break;
    }
    oyunSonuEkrani(&yonetici);
    return 0;
}

void oyunuYukle(struct Yonetici* yonetici)
{
    int i=0;
    int tip=0, numara=0;
    struct Kart dummy;
    struct Deste yeni;
    for(i=0; i<4*13; i++)
    {
        dummy.kartNo = numara;
        dummy.kartTip = tip;
        dummy.holder = 0;
        yeni.tumKartlar[i] = dummy;
        numara++;
        if (numara%13 == 0){
            numara = 0;
            tip++;
        }
        yonetici->cpuAttigi[i] = 0;
        yonetici->oyuncununAttigi[i] = 0;

    }
    yonetici->tumDeste = yeni;
    yonetici->karismisDeste = yeni;
    yonetici->desteBasi = 0;
    yonetici->sonlan = 0;

    yonetici->cpuHamle = 0;
    yonetici->oyuncununHamle = 0;
    yonetici->oyuncuPistiSayisi  = 0;
    yonetici->cpuPistiSayisi  = 0;
    yonetici->oyuncuValePistiSayisi = 0;
    yonetici->cpuValePistiSayisi = 0;


    desteyiKaristir(&yonetici->karismisDeste, 4, 13);
    kartElDegistir(yonetici, 0, 10);
    kartElDegistir(yonetici, 1, 10);
    kartElDegistir(yonetici, 2, 10);
    kartElDegistir(yonetici, 3, 10);
    kartElDegistir(yonetici, 4, 20);
    kartElDegistir(yonetici, 5, 20);
    kartElDegistir(yonetici, 6, 20);
    kartElDegistir(yonetici, 7, 20);
    yonetici->desteBasi += 8;
    kartElDegistir(yonetici, 8, 30);
    kartElDegistir(yonetici, 9, 30);
    kartElDegistir(yonetici, 10, 30);
    kartElDegistir(yonetici, 11, 30);
    yonetici->cpuToplam = 0;
    yonetici->oyuncuToplam = 0;
    yonetici->desteBasi += 4;
    guncelle(yonetici);
    yonetici->sonyer = 11;
    yonetici->elSayisi = 1;
}

void oyunSonuEkrani(struct Yonetici* yonetici)
{
    int oyuncuPuan = 0;
    int cpuPuan = 0;

    oyuncuPuan += yonetici->oyuncuPistiSayisi*10;
    oyuncuPuan += yonetici->oyuncuValePistiSayisi*20;
    cpuPuan += yonetici->cpuPistiSayisi*10;
    cpuPuan += yonetici->cpuValePistiSayisi*20;

    int i=0;
    for(i=0; i<yonetici->cpuToplam; i++)
    {
        if (yonetici->karismisDeste.tumKartlar[yonetici->cpuToplamKart[i]].kartNo == 1)
        {
            cpuPuan += 1;
        }

        if (yonetici->karismisDeste.tumKartlar[yonetici->cpuToplamKart[i]].kartNo == 11)
        {
            cpuPuan += 1;
        }

        if ( yonetici->karismisDeste.tumKartlar[yonetici->cpuToplamKart[i]].kartTip == 2 &&
                yonetici->karismisDeste.tumKartlar[yonetici->cpuToplamKart[i]].kartNo == 10)
        {
            cpuPuan += 3;
        }

        if ( yonetici->karismisDeste.tumKartlar[yonetici->cpuToplamKart[i]].kartTip == 1 &&
                yonetici->karismisDeste.tumKartlar[yonetici->cpuToplamKart[i]].kartNo == 2)
        {
            cpuPuan += 2;
        }
    }

    for(i=0; i<yonetici->oyuncuToplam; i++)
    {
        if (yonetici->karismisDeste.tumKartlar[yonetici->oyuncuToplamKart[i]].kartNo == 1)
        {
            cpuPuan += 1;
        }

        if (yonetici->karismisDeste.tumKartlar[yonetici->oyuncuToplamKart[i]].kartNo == 11)
        {
            cpuPuan += 1;
        }

        if ( yonetici->karismisDeste.tumKartlar[yonetici->oyuncuToplamKart[i]].kartTip == 2 &&
                yonetici->karismisDeste.tumKartlar[yonetici->oyuncuToplamKart[i]].kartNo == 10)
        {
            cpuPuan += 3;
        }

        if ( yonetici->karismisDeste.tumKartlar[yonetici->oyuncuToplamKart[i]].kartTip == 1 &&
                yonetici->karismisDeste.tumKartlar[yonetici->oyuncuToplamKart[i]].kartNo == 2)
        {
            cpuPuan += 2;
        }
    }

    if (yonetici->cpuToplam > yonetici->oyuncuToplam)
    {
        cpuPuan += 3;
    }
    if (yonetici->oyuncuToplam > yonetici->cpuToplam)
    {
        oyuncuPuan += 3;
    }

    printf("\n");
    printf("|            - Oyun Bitmiþtir.                |\n");
    printf("\n");
    printf("Bilgisayarin Puani: %d\n", cpuPuan);
    printf("Sizin Puaniniz: %d\n", oyuncuPuan);

    if (cpuPuan > oyuncuPuan)
    {
        printf("Bilgisayar Kazandi!");
    }
    if (cpuPuan < oyuncuPuan)
    {
        printf("Tebrikler! Siz Kazandiniz!");
    }
    if (cpuPuan == oyuncuPuan)
    {
        printf("Beraberlik!");
    }
}

void desteyiKaristir(struct Deste* deste, int tip, int numara)
{
    int i=0;
    struct Kart tmp;
    int randomi=0;
    srand(time(NULL));
    for(i=0; i<tip*numara; i++)
    {
        randomi = rand()%(tip*numara);
        tmp = deste->tumKartlar[i];
        deste->tumKartlar[i] = deste->tumKartlar[randomi];
        deste->tumKartlar[randomi] = tmp;
    }
}

void desteyiYazdir(struct Deste deste, int tip, int numara)
{
    int i=0;
    for(i=0; i<tip*numara; i++)
    {
        printf("%d, %d - %d - %d\n", i, deste.tumKartlar[i].kartTip,
               deste.tumKartlar[i].kartNo, deste.tumKartlar[i].holder);
    }
}

int desteBasiBul(struct Deste deste, int miktar)
{
    int i=0;
    for(i=0; i<miktar; i++)
    {
        if (deste.tumKartlar[i].holder == 0)
            return i;
    }
    return i;
}

void kartElDegistir(struct Yonetici* yonetici, int index, int kime)
{
    yonetici->karismisDeste.tumKartlar[index].holder = kime;
}

void guncelle(struct Yonetici* yonetici)
{
    int i=0, yer = 0;
    int cpu=0, oyuncu=0;
    int cpuToplam = 0, oyuncuToplam = 0;
    for(i=0; i<52; i++)
    {
        if (yonetici->karismisDeste.tumKartlar[i].holder == 30)
        {
            yer++;
        }
        if (yonetici->karismisDeste.tumKartlar[i].holder == 10)
        {
            cpu++;
        }
        if (yonetici->karismisDeste.tumKartlar[i].holder == 15)
        {
            cpuToplam++;
        }
        if (yonetici->karismisDeste.tumKartlar[i].holder == 20)
        {
            oyuncu++;
        }
        if (yonetici->karismisDeste.tumKartlar[i].holder == 25)
        {
            oyuncuToplam++;
        }
    }

    int* yerKart = (int*)malloc(sizeof (int)*yer);
    int* cpuKart = (int*)malloc(sizeof (int)*cpu);
    int* oyuncuKart = (int*)malloc(sizeof (int)*oyuncu);
    int* cpuToplamKart = (int*)malloc(sizeof (int)*cpuToplam);
    int* oyuncuToplamKart = (int*)malloc(sizeof (int)*oyuncuToplam);

    int y=0, c=0, o=0;
    int p=0, v=0;
    for(i=0; i<52; i++)
    {
        if (yonetici->karismisDeste.tumKartlar[i].holder == 30)
        {
            yerKart[y] = i;
            y++;
        }
        if (yonetici->karismisDeste.tumKartlar[i].holder == 10)
        {
            cpuKart[c] = i;
            c++;
        }
        if (yonetici->karismisDeste.tumKartlar[i].holder == 15)
        {
            cpuKart[v] = i;
            v++;
        }
        if (yonetici->karismisDeste.tumKartlar[i].holder == 20)
        {
            oyuncuKart[o] = i;
            o++;
        }
        if (yonetici->karismisDeste.tumKartlar[i].holder == 25)
        {
            oyuncuToplamKart[p] = i;
            p++;
        }
    }

    yonetici->yerKartlari = yerKart;
    yonetici->yerSayisi = yer;
    yonetici->cpuKartlari = cpuKart;
    yonetici->cpuKartSayisi = cpu;
    yonetici->oyuncuKartlari = oyuncuKart;
    yonetici->oyuncuKartSayisi = oyuncu;
    yonetici->cpuToplamKart = cpuToplamKart;
    yonetici->oyuncuToplamKart = oyuncuToplamKart;
    yonetici->oyuncuToplam = oyuncuToplam;
    yonetici->cpuToplam = cpuToplam;
}

void printYonetici(struct Yonetici yonetici)
{
    int i = 0;
    for(i=0; i<yonetici.yerSayisi; i++)
    {
        printf("%d\n", yonetici.yerKartlari[i]);
    }
    for(i=0; i<yonetici.cpuKartSayisi; i++)
    {
        printf("%d\n", yonetici.cpuKartlari[i]);
    }
    for(i=0; i<yonetici.oyuncuKartSayisi; i++)
    {
        printf("%d\n", yonetici.oyuncuKartlari[i]);
    }

}

void oyuncuHamleBekle(struct Yonetici* yonetici)
{
    int numara=0, karttip;
    int boz = 0;
    while (boz == 0)
    {
        printf("\n");
        printf("Tip -> 0: Kupa, 1:Maca, 2:Karo, 3:Sinek\n");
        printf("Numara -> 1: A...... 11:J, 12:Q, 13:K\n");
        printf("Ornek: Maca As = 1 1\n");
        printf("Girdi Bekleniyor: ");
        scanf("%d %d", &karttip, &numara);

        int i=0;
        int bulundu = 0;
        for(i=0; i<yonetici->oyuncuKartSayisi; i++)
        {
            if (yonetici->oyuncuKartlari[i] == kartIndexiBul(*yonetici, karttip, numara))
            {
                bulundu = 1;
                boz = 1;
                break;
            }
        }
        if (bulundu == 0)
        {
            printf("Kullanici %s-%d kartina sahip degil. Hareket gecersiz! Tekrar deneyiniz.", kartTipi(karttip), numara);
        }
    }
    printf("\n\n");
    hamleyiDegerlendir(yonetici, 20, karttip, numara);

}

void ekraniyazdir(struct Yonetici* yonetici)
{
    int i=0;
    printf("\n");
    printf("|             Pisti Oyunu - El %d.-  Pencereyi buyutmeniz onerilir!               |\n", yonetici->elSayisi);
    printf("\n");
    printf("|                 Girdi yerinde string karakterler girmeyiniz!                    |\n");
    printf("\n");
    printf("|                  0-> KUPA   1-> MACA    2->KARO    3->SINEK                     |\n");
    printf("\n");
    printf("|                  Ornek Input: Kupa-8 = 0 8,  Sinek-5 = 3 5                       |\n");
    printf("\n");
    // printf("| Yerde Toplanan | Yerdeki Son | Oyuncu Elindeki | CPU Attigi | Oyuncunun Attigi |\n");

    printf("| Yerde Toplanan      | ");
    for(i=0; i<yonetici->yerSayisi; i++)
    {
        int tip = yonetici->karismisDeste.tumKartlar[yonetici->yerKartlari[i]].kartTip;
        int no = yonetici->karismisDeste.tumKartlar[yonetici->yerKartlari[i]].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
        if (yonetici->yerSayisi%8 == 0 && i!=0)
        {
            printf("\n|                     |");
        }
    }
    printf("\n|                     |");
    printf("\n\n");
    printf("| Yerdeki Son         | ");
    if (yonetici->yerSayisi > 0)
    {
        int tip = yonetici->karismisDeste.tumKartlar[yonetici->sonyer].kartTip;
        int no = yonetici->karismisDeste.tumKartlar[yonetici->sonyer].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
    }
    printf("\n");
    printf("|                     |\n");
    printf("\n");
    printf("| Oyuncunun Elinde    | ");
    for(i=0; i<yonetici->oyuncuKartSayisi; i++)
    {
        int tip = yonetici->karismisDeste.tumKartlar[yonetici->oyuncuKartlari[i]].kartTip;
        int no = yonetici->karismisDeste.tumKartlar[yonetici->oyuncuKartlari[i]].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
    }
    printf("\n|                     |");
    printf("\n");
    printf("\n");
    printf("| CPU attigi          | ");
    for(i=0; i<yonetici->cpuHamle; i++)
    {
        int tip = yonetici->karismisDeste.tumKartlar[yonetici->cpuAttigi[i]].kartTip;
        int no =  yonetici->karismisDeste.tumKartlar[yonetici->cpuAttigi[i]].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
    }
    printf("\n|                     |");
    printf("\n");
    printf("\n");
    printf("| Oyuncunun attigi    | ");
    for(i=0; i<yonetici->oyuncununHamle; i++)
    {
        int tip = yonetici->karismisDeste.tumKartlar[yonetici->oyuncununAttigi[i]].kartTip;
        int no = yonetici->karismisDeste.tumKartlar[yonetici->oyuncununAttigi[i]].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
    }
    printf("\n|                     |");
    printf("\n");
    printf("\n");

    /*
    printf("| CPU Kartlari | ");
    for(i=0; i<yonetici->cpuKartSayisi; i++)
    {
        printf("%d-%d | ", yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[i]].kartTip,
                yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[i]].kartNo);
    }
    printf("\n");
    printf("|\n");*/
    printf("Oyuncunun topladigi toplam kart: %d\n", yonetici->oyuncuToplam);
    printf("Bilgisayarin topladigi toplam kart: %d\n", yonetici->cpuToplam);
}

void hamleyiDegerlendir(struct Yonetici* yonetici, int kim, int tip, int numara)
{
    int i=0;
    if (yonetici->karismisDeste.tumKartlar[yonetici->sonyer].kartNo == numara)
    {
        if (yonetici->yerSayisi == 1 && kim == 20)
        {
            printf("Tebrikler Pisti Yaptiniz!\n");
            yonetici->oyuncuPistiSayisi += 1;
        }
        if (yonetici->yerSayisi == 1 && kim ==10)
        {
            printf("Bilgisayar pisti yapti!\n");
            yonetici->cpuPistiSayisi += 1;
        }
        if (kim == 20)
            printf("Tebrikler yerdeki kartlari aldiniz!\n");
        if (kim == 10)
            printf("Bilgisayar yerdeki kartlari aldi!\n");
        for(i=0; i<yonetici->yerSayisi; i++)
        {
            yonetici->karismisDeste.tumKartlar[yonetici->yerKartlari[i]].holder = kim+5;
        }
        yonetici->karismisDeste.tumKartlar[kartIndexiBul(*yonetici, tip, numara)].holder = kim + 5;
        yonetici->yerSayisi = 0;
        yonetici->sonyer = -1;
    }
    else if (numara == 11)
    {
        if (yonetici->yerSayisi == 1 && kim == 20)
        {
            printf("Tebrikler Vale ile Pisti Yaptiniz!\n");
            yonetici->oyuncuValePistiSayisi += 1;
        }
        if (yonetici->yerSayisi == 1 && kim ==10)
        {
            yonetici->cpuValePistiSayisi += 1;
            printf("Bilgisayar Vale ile pisti yapti!\n");
        }
        if (kim == 20)
            printf("Vale ile yerdeki kartlari aldiniz!\n");
        if (kim == 10)
            printf("Bilgisayar Vale ile yerdeki kartlari aldi!\n");
        for(i=0; i<yonetici->yerSayisi; i++)
        {
            yonetici->karismisDeste.tumKartlar[yonetici->yerKartlari[i]].holder = kim+5;
        }
        yonetici->karismisDeste.tumKartlar[kartIndexiBul(*yonetici, tip, numara)].holder = kim + 5;
        yonetici->yerSayisi = 0;
        yonetici->sonyer = -1;
    }
    else {
        yonetici->karismisDeste.tumKartlar[kartIndexiBul(*yonetici, tip, numara)].holder = 30;
        yonetici->yerSayisi++;
        yonetici->sonyer = kartIndexiBul(*yonetici, tip, numara);
    }

    if (kim==10)
    {
        yonetici->cpuAttigi[yonetici->cpuHamle] = kartIndexiBul(*yonetici, tip, numara);
        yonetici->cpuHamle++;
    }
    if (kim==20)
    {
        yonetici->oyuncununAttigi[yonetici->oyuncununHamle] = kartIndexiBul(*yonetici, tip, numara);
        yonetici->oyuncununHamle++;
    }
    guncelle(yonetici);
}

int kartIndexiBul(struct Yonetici yonetici, int tip, int numara)
{
    int i = 0;
    for(i=0; i<52;i++)
    {
        if (yonetici.karismisDeste.tumKartlar[i].kartNo == numara &&
                yonetici.karismisDeste.tumKartlar[i].kartTip == tip)
            return i;
    }
    return i;
}

void bilgisayarHamleYap(struct Yonetici* yonetici)
{
    int i=0;
    int tur = 0;
    for(i=0; i<yonetici->cpuKartSayisi; i++)
    {
        if (yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[i]].kartNo == 11)
        {
            hamleyiDegerlendir(yonetici, 10,
                               yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[i]].kartTip,
                    yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[i]].kartNo);
            tur = 1;
            return;
        }
        else if (yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[i]].kartNo == yonetici->karismisDeste.tumKartlar[yonetici->sonyer].kartNo)
        {
            hamleyiDegerlendir(yonetici, 10,
                               yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[i]].kartTip,
                    yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[i]].kartNo);
            tur = 1;
            return;
        }
        else
        {
            tur = tur*1;
        }
    }
    if (tur==0)
    {
        hamleyiDegerlendir(yonetici, 10,
                           yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[0]].kartTip,
                yonetici->karismisDeste.tumKartlar[yonetici->cpuKartlari[0]].kartNo);
        return;
    }
}

void elsonuBak(struct Yonetici* yonetici)
{
    if (yonetici->cpuKartSayisi == 0)
    {
        yonetici->elSayisi+=1;
        kartElDegistir(yonetici, yonetici->desteBasi, 10);
        kartElDegistir(yonetici, yonetici->desteBasi+1, 10);
        kartElDegistir(yonetici, yonetici->desteBasi+2, 10);
        kartElDegistir(yonetici, yonetici->desteBasi+3, 10);
        kartElDegistir(yonetici, yonetici->desteBasi+4, 20);
        kartElDegistir(yonetici, yonetici->desteBasi+5, 20);
        kartElDegistir(yonetici, yonetici->desteBasi+6, 20);
        kartElDegistir(yonetici, yonetici->desteBasi+7, 20);
        yonetici->desteBasi += 8;
        kartElDegistir(yonetici, yonetici->desteBasi+8, 30);
        kartElDegistir(yonetici, yonetici->desteBasi+9, 30);
        kartElDegistir(yonetici, yonetici->desteBasi+10, 30);
        kartElDegistir(yonetici, yonetici->desteBasi+11, 30);
        yonetici->desteBasi += 4;
        yonetici->sonyer = yonetici->desteBasi-1;
        yonetici->cpuHamle = 0;
        yonetici->oyuncununHamle = 0;
        guncelle(yonetici);
    }

    if (yonetici->desteBasi >= 49 )
    {
        yonetici->sonlan = 1;
    }
}

char* kartTipi(int tip)
{
    char* text = NULL;
    if (tip == 0)
    {
        text = "Kupa";
    }
    if (tip == 1)
    {
        text = "Maca";
    }
    if (tip == 2)
    {
        text = "Karo";
    }
    if (tip == 3)
    {
        text = "Sinek";
    }
    return text;
}
