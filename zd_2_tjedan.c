#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max_string 1024

double convert_dec(char *hex){
    char *pointer=hex;
    char temp='0';
   double *bin;
   double dec=0.0;
   int znamenka;
   double temp_for;
   int tempnum,n=0,b;


    bin=malloc(sizeof(double));

    while(strlen(pointer)>0){
        if(sscanf(pointer,"%c %n",&temp, &b)==1){
            if(temp>='A' && temp<='F'){
                n++;
                if(n>1){
                    bin=realloc(bin,(n)*sizeof(double));
                }

                switch (temp){
                    case 'A':
                        tempnum=10;
                        break;

                    case 'B':
                        tempnum=11;
                        break;

                    case 'C':
                        tempnum=12;
                        break;

                    case 'D':
                        tempnum=13;
                        break;

                    case 'E':
                        tempnum=14;
                        break;

                    case 'F':
                        tempnum=15;
                        break;

                    default:
                        printf("kriva znamenka");
                        return -1;

                }

                bin[n]=(double)(tempnum);
                printf("%d,%f\n",n, bin[n]);
                pointer+=b;
            }
        }
            if(sscanf(pointer,"%d %n",&tempnum, &b)==1){

                while(tempnum){
                n++;
                if(n>1){
                    bin=realloc(bin,n*sizeof(double));
                }

                znamenka=tempnum%10;
                tempnum/=10;
                bin[n]=(double)(znamenka);

                pointer+=b;

                }
            }

        }

    for(int i=0;i<n;i++){
        printf("%.0f\n",bin[i]);
    }

    for(int i=1;i<n+1;i++){
        double exponent=n*1.0-i*1.0;
        printf("%f,exponent ",exponent);
        dec+=bin[i]*pow(16.0,exponent);
        printf("bin %f,dec %f, pow :%f \n",bin[i],dec,pow(16.0,(double)(exponent)));
    }

    return dec;
}

int main()
{
   double decimal=0.0;
    char hex[max_string]={'0'};

    printf("unesite heksadecimalni broj ");
    scanf("%s",hex);

    decimal=convert_dec(hex);


    printf("dec %.0f ",decimal);
    return 0;


    printf("nije hexadecimnalni broj");

}
