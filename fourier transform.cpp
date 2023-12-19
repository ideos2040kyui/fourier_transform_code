#include <stdio.h>
#include <math.h>
using namespace std;
#define N (100)
#define a (1)
#define b (2)
#define c (3)
#define arupha (2)
#define beta (10)
#define ganma (M_PI)

struct complex {
    double re;
    double im;
};
void fourier_transform(struct complex x[], char fname_fo[], char fname_fr[]);
void fourier_transform_reverse(struct complex X[], char fname_fr[]);

void fourier_transform(struct complex x[], char fname_fo[], char fname_fr[]){
    
    FILE *fpw;
    fpw = fopen(fname_fo,"w");
    if(fpw == NULL ){
        printf( "%sファイルが開けません¥n", fname_fo);
    }
    fclose(fpw);

    struct complex X[N];
    int i, j, k;
    
    for (k=0; k<N; k++){
        X[k].re = 0;
        X[k].im = 0;

        for (i=0; i<N; i++){
            X[k].re += ((x[i].re)*cos(k*i*2*M_PI/N) + (x[i].im)*sin(k*i*2*M_PI/N))/N;
            X[k].im += (-(x[i].re)*sin(k*i*2*M_PI/N) + (x[i].im)*cos(k*i*2*M_PI/N))/N;
        }
        printf("%d %f %f\n", k, X[k].re, X[k].im);
        FILE *fpa;
        fpa = fopen(fname_fo,"a");
        if(fpa == NULL ){
            printf( "%sファイルが開けません¥n", fname_fo);
        }
        fprintf(fpa, "%f,%f\n", X[k].re, X[k].im);
        fclose(fpa);
    }
    fourier_transform_reverse(X, fname_fr);
}

void fourier_transform_reverse(struct complex X[], char fname_fr[]){
    
    FILE *fpw;
    fpw = fopen(fname_fr,"w");
    if(fpw == NULL ){
        printf( "%sファイルが開けません¥n", fname_fr);
    }
    fclose(fpw);
    struct complex x[N];
    int i, j, k;
    
    for (i=0; i<N; i++){
        x[i].re = 0;
        x[i].im = 0;

        for (k=0; k<N; k++){
            x[i].re += (X[k].re)*cos(i*k*2*M_PI/N) - (X[k].im)*sin(i*k*2*M_PI/N);
            x[i].im += (X[k].re)*sin(i*k*2*M_PI/N) + (X[k].im)*cos(i*k*2*M_PI/N);
        }
        printf("%d %f %f\n", i, x[i].re, x[i].im);
        FILE *fpa;
        fpa = fopen(fname_fr,"a");
        if(fpa == NULL ){
            printf( "%sファイルが開けません¥n", fname_fr );
        }
        fprintf(fpa, "%f,%f\n", x[i].re, x[i].im);
        fclose(fpa);
    }
}

int main(void)
{
    struct complex wave_a[N];
    struct complex wave_b[N];
    struct complex wave_c[N];
    struct complex wave_d[N];
    char fname_a_fo[256] = "wave_a_fouriertransform.csv";
    char fname_a_fr[256] = "wave_a_fouriertransformreverse.csv";
    char fname_b_fo[256] = "wave_b_fouriertransform.csv";
    char fname_b_fr[256] = "wave_b_fouriertransformreverse.csv";
    char fname_c_fo[256] = "wave_c_fouriertransform.csv";
    char fname_c_fr[256] = "wave_c_fouriertransformreverse.csv";
    char fname_d_fo[256] = "wave_d_fouriertransform.csv";
    char fname_d_fr[256] = "wave_d_fouriertransformreverse.csv";

    int n;
    for (n=0; n<N; n++){
        wave_a[n].re = a*sin(arupha*n*2*M_PI/N);
        wave_a[n].im = 0;
        wave_b[n].re = a*sin(arupha*n*2*M_PI/N)+b*cos(beta*n*2*M_PI/N);
        wave_b[n].im = 0;
        wave_c[n].re = c + a*sin(arupha*n*2*M_PI/N)+b*cos(beta*n*2*M_PI/N);
        wave_c[n].im = 0;
        if (n*2*M_PI/N < ganma){
            wave_d[n].re = -a;
        }
        else if (ganma <= n*2*M_PI/N){
            wave_d[n].re = a;
        }
        wave_d[n].im = 0;
    }
    fourier_transform(wave_a, fname_a_fo, fname_a_fr);
    fourier_transform(wave_b, fname_b_fo, fname_b_fr);
    fourier_transform(wave_c, fname_c_fo, fname_c_fr);
    fourier_transform(wave_d, fname_d_fo, fname_d_fr);

    return 0;
}