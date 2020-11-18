#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
// Her nokta icin Xve y noktalarý olusturdum

struct Point // int olarak noktalarin koordinatlari
{
    double X;
    double Y;
};

// Yaricap koordinatlari
struct Radius // float olarak yaricap koordinatlari
{
    struct Point r_koor; // merkez icin
    double R_length; // cap uzunlugu
};

double spline_x[1000]; // spline in x degerlerini depolamak icin
double spline_y[1000]; // spline in y degerlerini depolamak icin
int olcek=13; // olcek
int spline_uzunlugu=0; // spline uzunlugu

// a ve b ,noktalari temsil eder,ornegin ;array icindeki 10 noktadan 2 si gibi.
double mesafeBul(struct Point a, struct Point b)   // 2 nokta arasi mesafe,bunu kullanarak cap bulunacak(for dongusuyle)
{
    return sqrt(pow(a.X-b.X,2) + pow(a.Y-b.Y,2));
}

Radius merkeziBul(struct Point a,struct Point b) // herhangi iki nokta arasi uzaklik capa esitse,o noktalarin orta noktasi ,capin koordinatlarina esit olur
{
    // 2 tane nokta icin orta noktayi kabul eder
    Radius R; // R struct

    R.r_koor.X = (a.X+b.X)/2.0; // orta nokta metodu ile yaricap noktalari elde ettim
    R.r_koor.Y = (a.Y+b.Y)/2.0; // orta nokta metodu ile yaricap noktalari elde ettim
    R.R_length=(mesafeBul(a,b)/2.0);
    return R;

}// 2 nokta icin

Point ucNoktaIcinMerkezNok(double bx,double by,double cx,double cy)
{
    // 3 noktadan cember elde etmeye yardimci fonk.
    double B = bx * bx + by * by;
    double C = cx * cx + cy * cy;
    double D = bx * cy - by * cx;
    struct Point sample;
    sample.X=((cy*B-by*C)/(2*D)); // yari cap koordinat
    sample.Y = ((bx*C-cx*B)/(2*D)); //
    return sample;
    // 3 tane nokta icin ortak bir nokta olusturur(merkez gibi)
    // daha sonra degistirilir
}

Radius merkeziBul2(struct Point a,struct Point b,struct Point c)
{
    // ucNoktaIcinMerkezNok elde edilen nokta genisletilip,cember daraltilir
    struct Point last = ucNoktaIcinMerkezNok(b.X-a.X,b.Y-a.Y,c.X-a.X,c.Y-a.Y);
    last.X += a.X; // cember daha da kucultmek icin ek nokta eklenir
    last.Y += a.Y;
    struct Radius r;
    r.r_koor=last;
    r.R_length=mesafeBul(last,a);
    return r; // 3 nokta verildiginde bir cember olusturma

}

// orta nokta metodu ile yaricap noktalari elde ettim

void noktaGoster(struct Point *p,int N)
{
    settextstyle(3,3,3);
    setcolor(LIGHTBLUE);
    //setlinestyle(4,0,1);
    for(int i=0; i<N; i++)
    {
        outtextxy((320+p[i].X*olcek),(235-p[i].Y*olcek),"*"); // (320,250) baslangic noktasi, => (320+p.X,250-p.Y) yapilmali.
        //line((320+p[i].X*13),(240-p[i].Y*13),);
    } // her noktayi olceklendirdim (*6)
}

void merkeziGoster(struct Radius r)  // ayni sekilde baslangic noktasidnan (320,250) baslayip gosterilir
{
    setcolor(CYAN);
    outtextxy((320+r.r_koor.X*olcek),(240-r.r_koor.Y*olcek),"R");
}

void sayiAralik()
{
    setcolor(WHITE);
    settextstyle(2,3,4);
    char msg[50]; // gerekli degerleri atmak icin array
    for(int i=0; i<25; i++) // sayi araliklari 5 er 5 er olacak
    {
        itoa(i,msg,10); // i degerini arraya 10 tabaninda atar.
        outtextxy((320+i*olcek),(240),msg);// yon verme
    }
    char msg2[80];
    for(int i=0; i<25; i++)
    {
        itoa(i,msg2,10);
        outtextxy((320),(240-i*olcek),msg2);// yon verme,6 kat buyutup verilir
    }

    char msg3[80];
    for(int i=0; i<25; i++)
    {
        itoa(-i,msg3,10);
        outtextxy((320),(240+i*olcek),msg3); // yon verme,6 kat buyutup verilir
    }
    char msg4[80];
    for(int i=0; i<25; i++)
    {
        itoa(-i,msg4,10);
        outtextxy((320-i*olcek),(240),msg4); // yon verme,6 kat buyutup verilir
    }

}

void koordinatCiz()
{
    setcolor(2);
    line(20,240,640,240); // baslangic noktalari (320,250)
    line(320,20,320,640);
}

void daireCiz(struct Radius R,double yaricap)
{
    setcolor(YELLOW);
    circle(320+R.r_koor.X*olcek,240-R.r_koor.Y*olcek,yaricap*olcek); // 6 kat buyutup verilir
}

int icindeMi(struct Radius c,struct Point p)
{
// yaricap koordinati ve bir noktanın arasi uzakliginin yaricap tan ufak olmasi gerek
    if (mesafeBul(c.r_koor,p) <= c.R_length)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int gecerli_mi(struct Radius r,struct Point *points,int N)
{
    for(int i=0; i<N; i++) // points arrayi icindeki noktlarin ,gecerliliginin kontrolu
    {
        if (!icindeMi(r,points[i]))
        {
            return 0;
        }
    }
    return 1;
}
// 3 nokta icin cember olusturma fonksiyonu
struct Radius ucNoktaIleCember(struct Point *points,struct Radius radius,int N)
{
    // baslangic olarak verilen degerler

    for(int i=0; i<N; i++) // tüm noktalara ulasım
    {
        for(int j=i+1; j<N; j++)
        {
            for(int c=j+1; c<N; c++)
            {
                // 3 nokta icin gecici cember olusturma daha sonra giderek ufaltma(gecici olacak)
                struct Radius gecici=merkeziBul2(points[i],points[j],points[c]);
                if (gecici.R_length<radius.R_length && gecerli_mi(gecici,points,N))
                {
                    radius=gecici;
                }
            }
        }
    }
    return radius;
};
// minimum en closing circcle bulunur,genel olarak
// tum cift noktalar ve uclu noktalar kullanilacak ve cember elde edilecek
struct Radius enKucukKapsayanCember(struct Point *points,struct Radius radius,int N)
{
    radius.r_koor.X=0;
    radius.r_koor.Y=0;
    radius.R_length=10000; // sonsuz r ye sahip cember,gitgide ufalacak

    if (N==0)
    {
        radius.r_koor.X=0;
        radius.r_koor.Y=0;
        radius.R_length=0;
        return radius;
    }
    if (N==1)
    {
        radius.r_koor = points[0];
        radius.R_length=0;
        return radius;
    }
    for(int i=0; i<N; i++)
    {
        for(int j=i+1; j<N; j++) // i ile j karsilasmasin diye
        {
            // 2 nokta icin merkezi bulduk,geciciye atadik,giderek ufalttik
            struct Radius gecici = merkeziBul(points[i],points[j]);
            if (gecici.R_length<radius.R_length && gecerli_mi(gecici,points,N))
            {
                radius=gecici;
            }
        }
    }
    // en sonunda 3 noktali durum icinde islem yaptik
   if (N>2){
     radius = ucNoktaIleCember(points,radius,N);
   }
    return radius;
};

void b_spline_uygulama(struct Point p1,struct Point p2,struct Point p3,struct Point p4,int n)
{

    double a[5]; // atanma islemi icin arrayler
    double b[5];
    // matristen cevirip , a ve b arraylerine atama islemi yaptım
    a[0] = (-(p1.X*olcek) + 3 * (p2.X*olcek) - 3 * (p3.X*olcek) + (p4.X*olcek)) / 6.0;
    a[1] = (3 * (p1.X*olcek) - 6 * (p2.X*olcek) + 3 * p3.X*olcek) / 6.0;
    a[2] = (-3 * (p1.X*olcek) + 3 * (p3.X*olcek)) / 6.0;
    a[3] = ((p1.X*olcek) + 4 * (p2.X*olcek) + (p3.X*olcek)) / 6.0;
    b[0] = (-(p1.Y*olcek) + 3 * (p2.Y*olcek) - 3 * (p3.Y*olcek) + (p4.Y*olcek)) / 6.0;
    b[1] = (3 * (p1.Y*olcek) - 6 * (p2.Y*olcek) + 3 * (p3.Y*olcek)) / 6.0;
    b[2] = (-3 * (p1.Y*olcek) + 3 * (p3.Y*olcek)) / 6.0;
    b[3] = ((p1.Y*olcek) + 4 * (p2.Y*olcek) + (p3.Y*olcek)) / 6.0;

    // belirlenen mesafe icin spline ayarlamasi yapiliyor
    for(int i=0; i<=n-1; i++)
    {
        float x = float(i);
        float y = float(n);
        float t = x/y;
        spline_x[spline_uzunlugu] = (a[2] + t * (a[1] + t * a[0]))*t+a[3];
        spline_y[spline_uzunlugu] = (b[2] + t * (b[1] + t * b[0]))*t+b[3];
        spline_uzunlugu++;
    }
}

void spline_egrisi_cizdir(struct Point *points,int N)
{
    struct Point gecici; // noktalari siralamak icin
    double M; // mesafe
    for(int i=0; i<N; i++) // x degerlerini sıralamak icin(daha duzgun bir sekil icin)
    {
        for(int j=i+1; i<N; i++)
        {
            if (points[i].X>points[j].X)
            {
                gecici = points[i];
                points[i] = points[j];
                points[j] = gecici;
                // kucukten buyuge dogru siralama
            }
        }
    }

    for(int i = 0; i<N-2; i++)
    {
        //gonderdigimiz 2 nokta arasindaki uzaklik
        M = mesafeBul(points[i],points[i+3]);
        int n = int(M); // mesafeyi inte cevirdik
        // kubik oldugu icin 4 nokta gonderdim
        b_spline_uygulama(points[i],points[i+1],points[i+2],points[i+3],n);
        // iki nokta arasina line , b-spline olusuyor
        for(int j=1; j<spline_uzunlugu; j++)
        {
            int x = int(spline_x[j]);
            int y = int(spline_y[j]);
            int x1 = int(spline_x[j-1]);
            int y1 = int(spline_y[j-1]);

            setcolor(LIGHTMAGENTA);

            line(320+x,240-y,320+x1,240-y1);
            // iki nokta arsina cizgi cekerek b - spline olustuduk
        }
    }
    line(spline_x[0]+320,240-spline_y[0],points[0].X*olcek+320,240-points[0].Y*olcek); // ilk elemandan spline cizgi
    line(spline_x[spline_uzunlugu-1]+320,240-spline_y[spline_uzunlugu-1],points[N-1].X*olcek+320,240-points[N-1].Y*olcek); // son elemandan cizgi
// en kucuk ve en buyuk noktalari ekledik
}
int main()
{
    int N;
    printf("\nLutfen , points.txt dosyasina kac adet nokta girdiginizi yazin \n");
    scanf("%d",&N);
    struct Point *points = (Point*)malloc(20 * sizeof *points); // N tane nokta icin array tanimladim
    /** --- section of reading file --**/
    FILE *fp = fopen("points.txt","r");
    if (fp==NULL)
    {
        printf("Dosya okunurken bir sorun olustu\n");
        exit(1);
    }
    int i=0;
    while(i<N && fscanf(fp,"%lf %lf",&points[i].X,&points[i].Y)==2)
    {
        i++;
    }
    fclose(fp);
    printf("\nGirilen noktalar : \nx\ty\n");
    printf("------------------------\n");
    for(i=0; i<N; i++)
    {
        printf("%lf\t%lf\n",points[i].X,points[i].Y);
    }

    struct Radius radius = enKucukKapsayanCember(points,radius,N); // yaricap koordinatlari icin struct
    //printf("%f",mesafeBul(points[2],points[0]));
    double yaricap = radius.R_length;
    printf("Yaricap = %f\nMerkezi Koordinatlar (%lf,%lf)",yaricap,radius.r_koor.X,radius.r_koor.Y);
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    koordinatCiz();
    daireCiz(radius,yaricap);
    merkeziGoster(radius);
    noktaGoster(points,N);
    sayiAralik();
    spline_egrisi_cizdir(points,N);
    getch();
    closegraph();
    return 0;
}




