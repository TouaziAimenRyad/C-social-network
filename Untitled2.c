#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "dos.h"
#include "conio.h"
#include "conio2.h"
#include <time.h>
#include "GRAPHIQUE.h"


int menu_oui_non() // Affiche le menu principal et donne le choix de l'utilisateur
{
        char *t [] = {  "1-  OUI ",
                     "2-  NON ",
        };

    int n = 2 ; // TAILLE DU TABLEAU DE CHAINE
    int i , j , quite = 1, quite2 , y = 20  , x= 55 , y1= n+4 , x1 =  strlen(t[0])+6 , choix ;
    char c1,c2 ,c3 , c4 ;
    debut :

    textattr(15);

    textattr(255);

    printf("\n");
    textcolor(15);

    for( i = 0 ; i< n ; i++)
    {
        if (i==0) textbackground(7);
        else textbackground(0);
        gotoxy(x,y+i);
        printf("%s\n",t[i]);
    }
    i=0;
    while( quite)
    {
        c1 = getch();
        if( c1 == 13 || c1 == 27 )
        {
            if ( c1 == 27 )
            {
                quite2 = 1 ;
                choix = 1 ;
                gotoxy(1,y);
                textattr(0);
                system("cls");
                textattr(204);
                for (i=1 ; i<= 46  ; i++)
                {
                    for ( j=1 ; j<= 4 ; j++)
                    {
                        gotoxy(x+13+i,y-3+j);
                        printf("%c",219);
                    }

                }
                textattr(207);
                gotoxy(x+15,y);
                printf("ETES VOUS SURE DE VOULOIR QUITTER ?!  (Y%cN) ",92);
                gotoxy(109,y);
                textattr(143);
                printf("O");
                while(quite2)
                {
                    c3 = getch();
                    if ( c3 == 13) quite2 = 0 ;
                    else if ( c3 == -32)
                    {
                        c4 = getch();
                        if (c4 == 77 && choix == 1 )
                        {
                            gotoxy(111,y);
                            textattr(143);
                            printf("N");
                            gotoxy(109,y);
                            textattr(207);
                            printf("O");
                            choix -- ;
                        }
                        if (c4 == 75 && choix == 0)
                        {
                            gotoxy(109,y);
                            textattr(143);
                            printf("O");
                            gotoxy(111,y);
                            textattr(207);
                            printf("N");
                            choix ++ ;
                        }
                    }

                }

                textattr(15);
                if ( choix == 1)
                {
                    i = -1 ;
                    quite = 0 ;
                }
                else  goto debut ;
            }
            else quite = 0 ;
        }

        else if( c1 == -32 )
        {
            c2 = getch();
            if (c2 == 72 )
            {
                if(i > 0)
                {
                    gotoxy(x,i-1+y);
                    textbackground(1);
                    printf("%s\n",t[i-1]);
                    textbackground(0);
                    gotoxy(x,i+y);
                    printf("%s\n",t[i]);
                    i--;
                }
                else
                {
                    gotoxy(x,y+n-1);
                    textbackground(1);
                    printf("%s\n",t[n-1]);
                    gotoxy(x,y);
                    textbackground(0);
                    printf("%s\n",t[0]);
                    i=n-1;
                }
            }
            else if (c2 == 80)
            {
                if( i < n-1)
                {
                    gotoxy(x,y+i+1);
                    textbackground(1);
                    printf("%s\n",t[i+1]);
                    textbackground(0);
                    gotoxy(x,y+i);
                    printf("%s\n",t[i]);
                    i++;
                }
                else
                {
                    gotoxy(x,y);
                    textbackground(1);
                    printf("%s\n",t[0]);
                    gotoxy(x,y+i);
                    textbackground(0);
                    printf("%s\n",t[i]);
                    i=0 ;
                }
            }
        }
    }
    return i+1;
}

int maino()
{   char mot[20],kk[20];
    FILE *fichier;
printf("%d",menu_oui_non());
    fichier=fopen("C:/Users/kara bernou/desktop/TP ALSDD/fichierdetp.txt","r");
    fscanf(fichier,"%s",kk);
       fscanf(fichier,"%s",mot);
    fclose(fichier);
printf("%s\n",kk);
printf("%s",mot);
return 0;
}

