#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* textFile;
char* ArananKelime;
int tekrarSayisi=0;

void TerminaleYaz()
{
    if (tekrarSayisi == 0)
    {
        printf("*** Kelime Bulunamadi! ***\n");
    }
    else
    {
        printf("*** %s Kelimesi, %s Dosyasinda Toplamda %d kez Tekrar Edilmistir ***\n",ArananKelime,textFile,tekrarSayisi);
    }
}

void BaslikYaz()
{
    FILE* fp=fopen("OutputFile.txt","a");   
    if(fp==NULL)
    {
        printf("*** Output Dosyasi Acma Hatasi! ***\n");
        exit(-1);
    }
    else
    {       
        if (tekrarSayisi != 0)
        {
            fprintf(fp,"\n' %s ' kelimesinin %s dosyasinda bulundugu satirlar = ",ArananKelime,textFile);
        }  
    }
}

void SatirNoYaz(int No)
{
    FILE* fp=fopen("OutputFile.txt","a");   
    if(fp==NULL)
    {
        printf("*** Output Dosyasi Acma Hatasi! ***\n");
        exit(-1);
    }
    else
    {   
        fprintf(fp,"%d; ",No);
    }
}

void DosyayiOku()
{
    FILE* fp=fopen(textFile,"r");   
    if(fp==NULL)
    {
        printf("*** Dosya Okuma Hatasi! ***\n");
        printf("*** %s Dosyasi Bulunamadi! ***\n",textFile);
        exit(-1);
    }
    else
    {     
        char c;
        char bosluk = ' ';
        char altSatir = '\n';
        char tab = '\t';
        char son = '\0';
        int satirNo = 1;  
        int kelimeUzunluk = 0;      
        char* OkunanKarakterler = (char*)malloc(200*sizeof(char));
        char* ilkKarakter = OkunanKarakterler;
        char* sonKarakter = OkunanKarakterler;

        while(!feof(fp)) 
        {
            c = fgetc(fp);
            
            if(c == altSatir || c == bosluk || c==tab)
            {           
                char* kelime = (char*)malloc(kelimeUzunluk*sizeof(char));
                char* kelimeIlk = kelime;

                for (int j = 0; j < kelimeUzunluk; j++)
                {                      
                    *kelimeIlk = *ilkKarakter;
                    ilkKarakter++;
                    kelimeIlk++;
                }
                                          
                if(strcmp(kelime,ArananKelime)==0)
                {   
                    tekrarSayisi++;
                    SatirNoYaz(satirNo);
                }               
                
                free(kelime);

                kelimeUzunluk=0;
                if (c == altSatir)
                {
                    satirNo++;
                }    
            }        
            else
            {   
                *sonKarakter = c;
                sonKarakter++;
                kelimeUzunluk++;
            }
        }
        fclose(fp);
        free(OkunanKarakterler);
    }        
}

int main(int argc, char * argv[]) 
{   
    if (argv[1]==NULL)
    {
        printf("*** Uzerinde Arama Yapilacak Dosya Adini Ve Aranacak Kelimeyi Giriniz! ***\n");
        printf("Ornek calistirma icin ./grepFile.c -h ya da ./grepFile.c -help komutunu kullanin\n");
        exit(-1);
    }
    else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0)
    {
        printf("USAGE: ./grepFile testFile.txt lorem (<program adi> <dosya> <aranacak kelime>)\n");
        exit(-1);
    }
    if (argv[2]==NULL)
    {      
        printf("*** Aranacak Kelimeyi Giriniz! ***\n");
        printf("Ornek calistirma icin ./grepFile.c -h ya da ./grepFile.c -help komutunu kullanin\n");
        exit(-1);
    }
    else
    {
        if(argv[3]!=NULL)
        {
            printf("*** Yalnizca 2 Parametre Giriniz! ***\n");
            printf("Ornek calistirma icin ./grepFile.c -h ya da ./grepFile.c -help komutunu kullanin\n");
            exit(-1);
        }
        else
        {    
            textFile = argv[1];
            ArananKelime = argv[2];

            DosyayiOku(); 
            BaslikYaz();
            TerminaleYaz();          
        }
    }
    return 0;
}