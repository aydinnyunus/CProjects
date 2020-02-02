
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n,sayac,tahmin,user_score=0,comp_score=0;
    char secim;

    // Get input from user.
    printf("Sayı tahmin oyununu oynamak istiyor musunuz ? (E/H)");
    scanf("%c",&secim);

    // Check input is 'H' or 'h'
    if(secim=='H' || secim == 'h')
        printf("O zaman programı meşgul etme");

    while(secim=='E' || secim == 'e'){

        // Create random number.
        srand(time(NULL));
        n=rand()%100+1;

        // Get prediction from user.
        printf("\n1 ve 100 arasında sayı tahmin ediniz : ");
        scanf("%d",&tahmin);

        for(int i=1;;i++){

            if(tahmin<n){
                printf("\nDaha buyuk bir sayiyla tekrar tahmin ediniz : %d Hakkınız kaldı",10-i);
                scanf("%d",&tahmin);

                if(i==9){
                    printf("\n\nHakkınız doldu. :(");
                    comp_score = comp_score + 1;
                    printf("Skor : %d - %d ", user_score, comp_score);
                    break;
                }
            }

            else if(tahmin>n){
                printf("\nDaha kucuk bir sayiyla tekrar tahmin ediniz : %d Hakkınız kaldı",10-i);
                scanf("%d",&tahmin);

                if(i==9){
                    printf("\n\nHakkınız doldu. :(");
                    comp_score = comp_score + 1;
                    printf("Skor : %d - %d ", user_score, comp_score);
                    break;
                }
            }

            else if(tahmin==n){
                printf("\nTebrikler %d. Tahmininiz Dogru !!! ",i);
                user_score = user_score + 1;
                printf("Skor : %d - %d ", user_score, comp_score);
                break;
            }
        }

        printf("\n\nTekrar oynamak ister misin ? (E/H)");
        scanf(" %c",&secim);

        }

    printf("%c", secim);
    }
