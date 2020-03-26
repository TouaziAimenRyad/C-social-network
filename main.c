#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <unistd.h>
#include <conio.h>
#include "conio2.h"
#include "GRAPHIQUE.h"
//Pour l'affichage
#define selected_color 9
#define selected_background 7
#define not_selected_color 15
#define not_selected_background 0
//Pour l'affichage
#define selected_color 9
#define selected_background 7
#define not_selected_color 15
#define not_selected_background 0
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef struct follower *point_follow;
typedef struct user *point_suiv;

struct follower
{
    char nom_follow[20];
    int commun;
    point_suiv info;
    point_follow folllow;
};

struct user
{
    char nom[20];
    char ville[20];
    long intret;
    point_follow tete_follow;
    point_suiv suiv;
};
point_suiv tab[26];

//la machine abstrait 01
point_suiv allouer_user()
{
    return(struct user *)malloc(sizeof(struct user));
}

point_suiv suivant_user(point_suiv p)
{
    return(p->suiv);
}

void aff_suiv(point_suiv p , point_suiv q)
{
    p->suiv=q;
}

void aff_nom_user(point_suiv p , char arg[])
{
    strncpy(p->nom,arg,20);
}

void aff_ville(point_suiv p,char arg[])
{
    strncpy(p->ville,arg,20);
}

void aff_intret(point_suiv p, int v)
{
    p->intret=v;
}

void aff_tete_follow(point_suiv p, point_follow q)
{
    p->tete_follow=q;
}

char* nom_user(point_suiv p)
{
    return(p->nom);
}

char* ville_user(point_suiv p)
{
    return(p->ville);
}

long interet_user(point_suiv p)
{
    return(p->intret);
}

void liberer_user(point_suiv p)
{
    free(p);
}

//la machine abstraite 02

void aff_follow(point_follow p, point_follow q)
{
    p->folllow=q;
}

point_follow suivant_follow(point_follow p)
{
    return(p->folllow);
}

point_follow adr_tete_follow(point_suiv p)
{
    return(p->tete_follow);
}

point_follow allouer_follower()
{
    return(struct follower *)malloc(sizeof (struct follower));
}

char* nom_follower(point_follow p)
{
    return(p->nom_follow);
}

void aff_nom_follower(point_follow p ,char arg[])
{
    strncpy(p->nom_follow,arg,20);
}

void aff_info(point_follow p, point_suiv q)
{
    p->info=q;
}

void liberer_follower(point_follow p)
{
    free(p);
}
//---------------------------------------------------------------------------
void color(int t,int f) /* Fonction pour changer les couleurs ( Texte / Arrière plan) */
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(H,f*16+t);
}



int lire_string(char string[])
{
    scanf("%s",string);
return 0;
}


point_suiv existe(  char arg[]) //dir la recheerche 3la hssab el harf lowal en plus exist tatik address ta3 li yexisti
{int c;
     point_suiv p;
     point_suiv i;
     c=(int)arg[0];
     if(c<97)
     {p=tab[c-65];}
     else {p=tab[c-97];}

     i=NULL;
    if (p==NULL)
    {
        i=NULL;
    }
    else
    {

        while ((p != NULL) && (i==NULL))
        {
            if (strncasecmp(nom_user(p),arg,20)==0)
            {
                i=p;
            }
            else
            {
                i=NULL;
            }
            p=suivant_user(p);
        }

    }
    return i;
}



void follow_someone(point_suiv m ,char arg[]) //pointeur est pour le person qui veut faire un follow et char arg est pour le person qu'on veut le suivre
{
    point_follow q , d ; point_follow n;point_suiv k; int trouv;
    k=existe(arg);
    if (k==NULL)
    {
        printf("ce person n'existe pas ");

    }
    else
    {
        q=adr_tete_follow(m);
        if (q==NULL)
        {
            n=allouer_follower();
            aff_nom_follower(n,arg);
            aff_info(n,k);
            aff_follow(n,NULL);
            aff_tete_follow(m,n);
        }
        else
        {
             trouv=0;

        d=NULL;

        while ((q!=NULL)&&(trouv==0))
        {

            if (strncasecmp(arg,nom_follower(q),20)==-1)
            {
                trouv=1;

            }
            else
            {
                d=q;
                q=suivant_follow(q);
            }
        }
        n=allouer_follower();
        aff_nom_follower(n,arg);
            aff_info(n,k);
            aff_follow(n,q);


        if (d!=NULL)
        {
            aff_follow(d,n);
        }
        else
        {
              aff_tete_follow(m,n);
        }



        }
    }
}

void supprimer_follow(point_suiv p,char arg[])
{ point_follow q,pred;  int trouv=0;
q=adr_tete_follow(p);
if(q!=NULL)
{
 if (strncasecmp(arg,nom_follower(q),20)==0)
 {  aff_tete_follow(p,suivant_follow(q));
    liberer_follower(q);
 }else {
      pred=q;
q=suivant_follow(q);
while (q != NULL && trouv==0)
{
if (strncasecmp(arg,nom_follower(q),20)==0)
{    aff_follow(pred,suivant_follow(q));
     liberer_follower(q);
     trouv=1;
}
 pred=q;
q=suivant_follow(q);
}
 }
}
}

void change_nom_follow(char arg_old[],char arg_new[] ,point_suiv new_name_pointer)
{ point_follow q ;  int trouv=0 , i ; point_suiv p;

for (i=0;i<26;i++)
{   p=tab[i];
    while (p != NULL)
{q=adr_tete_follow(p);
while (q != NULL && trouv==0)
{
if (strncasecmp(arg_old,nom_follower(q),20)==0)
{   aff_nom_follower(q,arg_new);
    aff_info(q,new_name_pointer);
     trouv=1;
}
q=suivant_follow(q);
}
p=suivant_user(p);
}
}
}

point_suiv insert_maillon(char mot1[],char mot2[],int interet)
{  int a=interet ,c;
 int trouv; point_suiv p; point_suiv q; point_suiv n;
    c=(int)mot1[0];
     if(c<90)
     {c=c-65;}
     else {c=c-97;}

    if (tab[c]==NULL)
    {   n=allouer_user();
        tab[c]=n;
        aff_intret(tab[c],a);
        aff_nom_user(tab[c],mot1);
        aff_ville(tab[c],mot2);
        aff_suiv(tab[c],NULL);
        aff_tete_follow(tab[c],NULL);
        //khassk el following

    }
    else
    {
        trouv=0;
        p=tab[c];
        q=NULL;

        while ((p!=NULL)&&(trouv==0))
        {

            if (strncasecmp(mot1,nom_user(p),20)==-1)
            {
                trouv=1;

            }
            else
            {
                q=p;
                p=suivant_user(p);
            }
        }
        n=allouer_user();
        aff_nom_user(n,mot1);
        aff_intret(n,a);
        aff_ville(n,mot2);
        aff_suiv(n,p);
        aff_tete_follow(n,NULL);
        if (q!=NULL)
        {
            aff_suiv(q,n);
        }
        else
        {
            tab[c]=n;
        }

    }
return n;
}

void sauvegarder(FILE *fichier)
{  int i,l;
point_suiv p;  point_follow k;
 for(i=0;i<26;i++)
    {
        p=tab[i];
        while (p!=NULL)
        { fprintf(fichier," %s  %s  %ld \n",nom_user(p),ville_user(p),interet_user(p));

        p=suivant_user(p);
        }

}
fprintf(fichier,"\n finale ");
for (l=0;l<26;l++)
{
    p=tab[l];
    while (p!=NULL)
    {    fprintf(fichier," %s ",nom_user(p));
         k=adr_tete_follow(p);
       while (k!=NULL)
       {
           fprintf(fichier," %s ",nom_follower(k));
           k=suivant_follow(k);
       }
       fprintf(fichier," fin \n");
       p=suivant_user(p);
    }
}
fprintf(fichier," finale ");
printf("votre travail est sauvegarde");
}

void restaurer(FILE *fichier)
{    char nom[20],ville[20] , follow[20];point_suiv n;
     int b , finale=0 , fin;
     while (finale==0)
     {    fin=0;
          fscanf(fichier,"%s",nom);
     if (strncasecmp(nom,"finale",20)!=0)
     {
         fscanf(fichier,"%s",ville);
         fscanf(fichier,"%d",&b);
         n=insert_maillon(nom,ville,b);

     }
     else
     {
         finale=1;
     }

     }
     finale=0;
 while (finale==0)
     {    fin=0;
          fscanf(fichier,"%s",nom);
     if (strncasecmp(nom,"finale",20)!=0)
     {
         n=existe(nom);
         while (fin==0)
         {   fscanf(fichier,"%s",follow);
            if (strncasecmp(follow,"fin",20)!=0)
            {
                follow_someone(n,follow);
            }
             else
             {
                 fin=1;
             }
         }

     }
     else
     {
         finale=1;
     }

}
printf("l'operation est termine");
}

void insertion()
 {
    long a; int b,y;     point_suiv n; char mot1[20]; char mot2[20];
nom:
    printf("\n\ndonnez moi votre nom :");
    lire_string(mot1);
    if (existe(mot1)!=NULL){printf("ce nom existe deja .veuillez le changer \n\n");goto nom;}
    a=0;
    printf("\n\n\ndonnez moi le nom de votre ville :");
    lire_string(mot2);

printf("\n\n maintenant je vais vous poser des question sur vos centres d'interets\n\nsport\n ");y=wherey()-2;
            b=menu_oui_non();
            a=a+b*10000000;
            gotoxy(20,y);
            printf("cinema\n ");
             gotoxy(20,y+1);
            b=menu_oui_non();
            a=a+b*1000000;
            gotoxy(40,y);
            printf("art\n ");
            gotoxy(40,y+1);
            b=menu_oui_non();
            a=a+b*100000;
            gotoxy(60,y);
            printf("sante\n ");
             gotoxy(60,y+1);
            b=menu_oui_non();
            a=a+b*10000;
            gotoxy(80,y);
            printf("tech\n ");
            gotoxy(80,y+1);
           b=menu_oui_non();
            a=a+b*1000;
            gotoxy(100,y);
            printf("DIY\n ");
            gotoxy(100,y+1);
            b=menu_oui_non();
            a=a+b*100;
            gotoxy(120,y);
            printf("cuisine\n ");
             gotoxy(120,y+1);
           b=menu_oui_non();
            a=a+b*10;
            gotoxy(140,y);
            printf("voyage\n ");
             gotoxy(140,y+1);
          b=menu_oui_non();
            a=a+b;

   n=insert_maillon(mot1,mot2,a);
    gotoxy(0,y+5);
    suivre:
        printf("voulez vous suivre quelqun  \n");
     b=menu_oui_non();
    if (b==0)
    {
        printf("\n\n on a termine vous etes incrit dans notre reseau");

    }
    else
    {
        printf("\n\n donnez moi le nom de l'utilisateur que vous voulez suivre\nle nom:");
        lire_string(mot2);
        follow_someone(n,mot2);
        goto suivre;
    }

}

void supprimer_user(char arg[])
{
    int a; int trouv=0; point_suiv p ; point_suiv pred;

    a=(int)arg[0];
     if(a<90)
     {a=a-65;}
     else {a=a-97;}
     p=tab[a];
    if (p==NULL)
    {
        printf("utilisateur non trouve");
    }
    else
    {   if (strncasecmp(arg,nom_user(p),20)==0)
    {   tab[a]=suivant_user(p);
        liberer_user(p);
        printf("utilisateur supprime");
        trouv=1;
    }
    else
        {
        trouv=0;
        pred=p;p=suivant_user(p);
        while ((p!=NULL)&&(trouv==0))
        {
            if (strncasecmp(arg,nom_user(p),20)==0)
            {
                aff_suiv(pred,suivant_user(p));
                liberer_user(p);
                printf("utilisateur supprime");
                trouv=1;
            }

           pred=p;
           p=suivant_user(p);
        }

    } if(trouv==0){printf("utilisateur non trouve");}
    else
    {
         for (a=0;a<26;a++)
              {
                  p=tab[a];
                  while (p != NULL)
                  {
                    supprimer_follow(p,arg);
                    p=suivant_user(p);
                  }
              }
    }

    }
}

void affichage_interet(int c)
{color(11,0);
if (div(c,10).rem==1){printf(" voyage -");}
c=div(c,10).quot;
if (div(c,10).rem==1){printf(" cuisine -");}
c=div(c,10).quot;
if (div(c,10).rem==1){printf(" DIY -");}
c=div(c,10).quot;
if (div(c,10).rem==1){printf(" technologie -");}
c=div(c,10).quot;
if (div(c,10).rem==1){printf(" sante -");}
c=div(c,10).quot;
if (div(c,10).rem==1){printf(" art -");}
c=div(c,10).quot;
if (div(c,10).rem==1){printf(" cinema -");}
c=div(c,10).quot;
if (div(c,10).rem==1){printf(" sport -");}
c=div(c,10).quot;
}

void recherche_nom(char arg[])
{
    point_suiv p;
     p=existe(arg);
    if (p==NULL)
    {
        printf("utilisateur non trouvé");
    }
    else
    {

        printf("utilisateur trouve\nnom: ");
        color(11,0);
        printf("%s    ",nom_user(p));
        color(15,0);
        printf("ville: ");
        color(11,0);
        printf("%s  ",ville_user(p));
        color(15,0);
        printf("interet:");
        affichage_interet(p->intret);
        color(15,0);
    }
}


void recherche_ville(char arg[])
{
    point_suiv p; int i;int c;c=0;
    for(i=0;i<26;i++)
    {
        p=tab[i];
        while (p!=NULL)
        {
            if (strncasecmp(arg,ville_user(p),20)==0)
            {


        printf("nom: ");
        color(11,0);
        printf("%s    ",nom_user(p));
        color(15,0);
        printf("ville: ");
        color(11,0);
        printf("%s  ",ville_user(p));
        color(15,0);
        printf("interet:");
        affichage_interet(p->intret);
        color(15,0);

                printf("\n\n");
                c=2;
            }
            p=suivant_user(p);
        }
    }if (c==0){printf("utilisateur non trouve");}
}

void affichage_follow(char arg[])//le nom d'utlisateur qu'oon veut afficher les gens qu'il suive
{
    point_suiv p ;point_follow q; int c;
     p=existe(arg);
    if (p==NULL)
    {
        printf("utilisateur non trouvé");
    }
    else
    {

        q=adr_tete_follow(p);
        if (q== NULL)
        {
            printf("pas de contact a afficher");
        }
        else
        { c=1;
            printf("\n\nles contacts suivis sont: \n");
            while (q!=NULL)
            {
               printf("%d-nom: ",c);
        color(11,0);
        printf("%s    ",nom_follower(q));
        color(15,0);
        printf("ville: ");
        color(11,0);
        printf("%s  ",ville_user(q->info));
        color(15,0);
        printf("interet:");
        affichage_interet(q->info->intret);
        color(15,0);

                printf("\n\n");
                q=suivant_follow(q);
                 c=c+1;
            }
        }
    }

}




void modifier_user(char arg[])
{
    point_suiv p , n ;char mot5[20]; long a ;int b,y; int x;int z;
    a=0;
    p=existe(arg);
    if (p==NULL)
    {
        printf("utilisateur non trouve");
    }
    else
    {   modif:
        printf("\n\nvoulez vous modifier :\n");
        x=menu_modif();
        printf("\n\n\n");
        if (x==1)
        {   printf("tapez le nouveau nom :");
            lire_string(mot5);
            n=insert_maillon(mot5,ville_user(p),interet_user(p));
            aff_tete_follow(n,adr_tete_follow(p));
            change_nom_follow(arg,mot5,n);
            supprimer_user(arg);
            gotoxy(0,wherey()-1);
            printf("                                        ");
            printf("\n\nmodification termine");
        }

        if (x==2)
        {   printf("tapez le nouveau nom de la ville :");
            lire_string(mot5);
            aff_ville(p,mot5);
            printf("\n\nmodification termine");
        }

        if (x==3)
        {
            printf("\n\n maintenant je vais vous poser des question sur vos centres d'interets\n\nsport\n ");y=wherey()-2;
            b=menu_oui_non();
            a=a+b*10000000;
            gotoxy(20,y);
            printf("cinema\n ");
             gotoxy(20,y+1);
            b=menu_oui_non();
            a=a+b*1000000;
            gotoxy(40,y);
            printf("art\n ");
            gotoxy(40,y+1);
            b=menu_oui_non();
            a=a+b*100000;
            gotoxy(60,y);
            printf("sante\n ");
             gotoxy(60,y+1);
            b=menu_oui_non();
            a=a+b*10000;
            gotoxy(80,y);
            printf("tech\n ");
            gotoxy(80,y+1);
           b=menu_oui_non();
            a=a+b*1000;
            gotoxy(100,y);
            printf("DIY\n ");
            gotoxy(100,y+1);
            b=menu_oui_non();
            a=a+b*100;
            gotoxy(120,y);
            printf("cuisine\n ");
             gotoxy(120,y+1);
           b=menu_oui_non();
            a=a+b*10;
            gotoxy(140,y);
            printf("voyage\n ");
             gotoxy(140,y+1);
          b=menu_oui_non();
            a=a+b;

            aff_intret(p,a);
            printf("\n\nmodification termine");
        } if (x==4){
       mod_suivre:
           printf("\nvoulez vous suivre quel qu'un d'autre?\n");
       z=menu_oui_non();
        if (z==1)
        {
            printf("\n\ndonnez moi le nom d'utilisateur que vous voulez suivre\nle nom :");
            lire_string(mot5);
            follow_someone(p,mot5);
            printf("\n\nmodification termine");
            goto mod_suivre;
        }else
        { mod_sup:
             printf("\n\nvoulez vous supprimer un contact suivis?\n");
             z=menu_oui_non();
             if(z==1)
                {printf("\n\ntapez le nom du contact :");
                 lire_string(mot5);
                 supprimer_follow(p,mot5);
                 printf("\n\nce contact n'est pas dans ta liste de followings maintenant");
                 goto mod_sup;
                    }
             else{goto quiter;}

        }}
        if(x==5){goto quiter;}else{goto modif; }
    }

quiter : Sleep(10);

}

typedef struct{point_suiv p;int commun;} int_commun;
int_commun tabb[5];

int existe_in_tab(int_commun t[5],point_suiv q)
{   int trouv,i;

trouv=0 ;i=0;
    while(trouv==0 && i<5 )
    {
        if(t[i].p==q)
        {
            trouv=1;
        }i=i+1;
    }
  return trouv;
}

int plus_grand(int_commun t[5],int k)
{  int c=k+1,max=k;

while(c<5)
{  if(t[c].commun>t[max].commun)
    {
       max=c;
    }
    c=c+1;
}
 return max;
}

void permute(int_commun t[5],int x,int y)
{ int_commun r;
r.p=t[x].p;
r.commun=t[x].commun;
t[x].p=t[y].p;
t[x].commun=t[y].commun;
t[y].p=r.p;
t[y].commun=r.commun;
}

void tri_int_commun(int_commun t[5])
{  int c=0,i;
while (c<4)
{
    i=plus_grand(t,c);
    permute(t,c,i);
    c=c+1;
}
}

void amis_commun(char arg[])
{   point_suiv p;
p=existe(arg);
if(p==NULL)
{
    printf("utilisateur non trouve");
}
else
{

int c,r;
c=0;
while (c<5)
{
    tabb[c].p=NULL;
    tabb[c].commun=0;
    c=c+1;
}c=0;
    point_follow q,k,i,z; int cpt,trouv;
    q=p->tete_follow;
    if(q== NULL)
    {
    printf("pas de contact en commun a suggester\n");
    }
    else
    {while (suivant_follow(q)!= NULL)
    {k=q->info->tete_follow;
     while (k != NULL )
     {if(existe_in_tab(tabb,k->info)==0)
     {
   i=suivant_follow(q);
     cpt=1;
     while(i!=NULL )
     {z=i->info->tete_follow;
     trouv=0;
     while (z!=NULL && trouv==0)
     {
         if(z->info==k->info)
         {
             cpt=cpt+1;
             trouv=1;
         }
         z=suivant_follow(z);
     }
     i=suivant_follow(i);
     }
     if (c<5)
              {
                  tabb[c].p=k->info;
              tabb[c].commun=cpt;
              c=c+1;
              }
              else
              {r=0;trouv=0;
                  while (r<5 && trouv==0)
                  {
                      if (cpt>tabb[r].commun)
                      {tabb[r].p=k->info;
                       tabb[r].commun=cpt;
                       trouv=1;
                      }r=r+1;
                  }
              }
     }
     k=suivant_follow(k);
     }q=suivant_follow(q);
    }
if(tabb[0].p==NULL)
{
    printf("pas de contact en commun a suggester\n");
}else{tri_int_commun(tabb);
 printf("les utilisateur suggeste sont :\n ");
   c=0;int y=0;
   while(c<5 && y==0)
   {   if (tabb[c].p!=NULL){

        printf("%d-nom: ",c+1);
        color(11,0);
        printf("%s    ",nom_user(tabb[c].p));
        color(15,0);
        printf("ville: ");
        color(11,0);
        printf("%s    ",ville_user(tabb[c].p));
        color(15,0);
        printf("followers en commun: ");
        color(11,0);
        printf("%d\n",tabb[c].commun);
        color(15,0);
       }
        else{y=1;}
        c=c+1;
        }}}}}


int comp(long a,long b)
{int i,s=a,n=b;
i=0;

    while (s != 0 || n!=0)
    {   if(div(s,10).rem==div(n,10).rem)
    {
        i=i+1;
    }
    s=div(s,10).quot;
    n=div(n,10).quot;
    }
    return i;
}

void interet_commun(char arg[])
{ point_suiv p;
p=existe(arg);
if(p==NULL)
{
    printf("utilisateur non trouvé");
}
else
{
    point_suiv q;
int i,s,c,z,trouv;
c=0;i=0;

 while (c<5)
{
    tabb[c].p=NULL;
    tabb[c].commun=0;
    c=c+1;
}c=0;
    while(i<26)
    {
        q=tab[i];
        while (q != NULL )
        {
            if (q != p)
            {
              s=comp(q->intret,p->intret);
              if (c<5)
              {tabb[c].p=q;
              tabb[c].commun=s;
              c=c+1;
              }
              else
              {z=0;trouv=0;
                  while (z<5 && trouv==0)
                  {
                      if (s>tabb[z].commun)
                      {tabb[z].p=q;
                       tabb[z].commun=s;
                       trouv=1;
                      }z=z+1;
                  }
              }
            }q=suivant_user(q);
        }i=i+1;
    }
    if(tabb[0].p==NULL)
{
    printf("pas d'utilisateur a suggester\n");
}else{tri_int_commun(tabb);
   printf("les utilisateur suggesté sont :\n ");
   c=0;
   int y;
   y=0;
   while(c<5 && y==0)
   {    if (tabb[c].p!=NULL){

        printf("%d-nom: ",c+1);
        color(11,0);
        printf("%s    ",nom_user(tabb[c].p));
        color(15,0);
        printf("ville: ");
        color(11,0);
        printf("%s    ",ville_user(tabb[c].p));
        color(15,0);
        printf("interet en commun: ");
        color(11,0);
        printf("%d\n",tabb[c].commun);
        color(15,0);
       }
      else{y=1;}
       c=c+1;
   }}
}}

COORD coord ={0,0};     /* Fonction pour changer la position d'ecriture */
void gotoxy(int x, int y )
{ coord.X=x;
  coord.Y=y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
/*------------------------------------------------------------------------------------------------------------------------*/

void affichage()
{
color(15,0);
printf("\n *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   \n");
color(10,0);
printf("               _");
printf("                                                            \n");
printf("              ");
printf("|_|");
printf("                                                           \n");
printf("              ");
printf("/_/");
printf("                                                             \n");
printf("     ");
printf("___  ___ _");
printf("                                                              \n");
printf("    ");
printf("/ _ \\/ __| |");
printf("                                                            \n");
printf("   ");
printf("|  __/\\__ \\ |");
printf("           \n");
printf("    ");
printf("\\___||___/_|");
printf("             \n");
printf("    ");
printf("\t\t");
printf("E");
Sleep(200);
color(15,0);
printf("C");
Sleep(200);
printf("O");
Sleep(200);
printf("L");
Sleep(200);
printf("E");
Sleep(200);
printf(" ");
Sleep(200);
color(10,0);
printf("N");
color(15,0);
Sleep(200);
printf("A");
Sleep(200);
printf("T");
Sleep(200);
printf("I");
Sleep(200);
printf("O");
Sleep(200);
printf("N");
Sleep(200);
printf("A");
Sleep(200);
printf("L");
Sleep(200);
printf("E");
Sleep(200);
printf(" ");
Sleep(200);
color(10,0);
printf("S");
color(15,0);
Sleep(200);
printf("U");
Sleep(200);
printf("P");
Sleep(200);
printf("E");
Sleep(200);
printf("R");
Sleep(200);
printf("I");
Sleep(200);
printf("E");
Sleep(200);
printf("U");
Sleep(200);
printf("R");
Sleep(200);
printf("E");
Sleep(200);
printf(" ");
Sleep(200);
color(10,0);
printf("D");
Sleep(200);
printf("'");
Sleep(200);
printf("I");
Sleep(200);
color(15,0);
printf("N");
Sleep(200);
printf("F");
Sleep(200);
printf("O");
Sleep(200);
printf("R");
Sleep(200);
printf("M");
Sleep(200);
printf("A");
Sleep(200);
printf("T");
Sleep(200);
printf("I");
Sleep(200);
printf("Q");
Sleep(200);
printf("U");
Sleep(200);
printf("E");
Sleep(200);
printf("\n\n\t\t     ALGORITHME ET STRUCTURES DES DONNEES DYNAMIQUES\n");
printf("\t\t\t\t      * ALSDD * \n");
printf("\n");
color(10,0);
printf("\n    -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- \n") ;
color(15,0);
printf("\n\t\t\t\tTravail Pratique N :1 ");
printf("\n\n\t\t         gestion des abonnées d'un reseau social");
printf("\n\n");
color(10,0);
printf("\t\t\t\t   Realise par :");
printf("\n\n");
color(15,0);
printf("\t\t    TOUAZI AIMEN RYAD ");
color(10,0);
printf(" &  ");
color(15,0);
printf("KARABERNOU MOHAMAD ISLAM ");
printf("\n\n\t\t\t\t    Groupe : 5");
printf("\n\n\t\t\t      Encadre Par :  ");
Sleep(400);
color(10,0);
printf("D");
Sleep(200);
printf("r");
Sleep(200);
printf(" ");

Sleep(200);
printf("C");
color(15,0);
Sleep(200);
printf("H");
Sleep(200);
printf("A");
Sleep(200);
printf("R");
Sleep(200);
printf("A");
Sleep(200);
printf("B");
Sleep(200);
printf("I");
Sleep(200);
printf(" ");
Sleep(200);
color(10,0);
printf("L");
Sleep(200);
color(15,0);
printf("I");
Sleep(200);
printf("L");
Sleep(200);
printf("A");
Sleep(200);
printf("\n\n\t\t\t\t\t     Annee Universitaire : 2018 / 2019 ");
printf("\n\n");
color(10,0);
printf("    -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- \n") ;
printf("\n");
color(15,0);
printf("\n *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *");
printf("\n\t\t    ");

system("pause");
}
/*------------------------------------------------------------------------------------------------------------------------*/

void choixMenu()
{   char s[20];
    int choix ,b  ;
    int quite = 0  ;
    FILE *fichier;
    while ( quite==0) // Tanque la variable quite n'ai pas a vrai le programme continue
    {

        choix = menu(); // La variable choix reçoit le choix de l'utilisateur
        textattr(0);
        system("cls");
        switch(choix)
        {
        case 1: // Si choix = 1 ,
            textattr(15);
            insertion();

           printf("\n\t\t\t\t\t");
           textattr(10);
            retourMenu(); // Retourner au Menu


        break ;
        case 2: // Si choix = 2 ,
            textattr(15);
                printf("donnez moi le nom d'utilisateur a supprimer\n le nom:");
                lire_string(s);
                supprimer_user(s);
            printf("\n\t\t\t\t\t");
           textattr(10);
                retourMenu();

        break;

            case 3:
            textattr(15);
                printf("donnez moi le nom d'utilisateur à modifier\n le nom:");
                lire_string(s);
                modifier_user(s);


                       printf("\n\t\t\t\t\t");
           textattr(10);
                retourMenu();
                break;
        case 4:
//
            textattr(15);
                printf("donnez moi le nom d'utilisateur pour afficher ces contacts suivis\n le nom:");
                lire_string(s);
                affichage_follow(s);
          printf("\n\t\t\t\t\t");
           textattr(10);

                retourMenu();



        break;
        case 5: // si choix= 5

            textattr(15);
                printf("quel type de recherche voulez vous ?\n");
                        b=menu_RECHERCHE();
                        printf("\n\n");
                        if(b==1)
                        {   printf("tapez le nom d'utilisateur :");
                            lire_string(s);
                            recherche_nom(s);
                        }
                        else
                        {   printf("tapez le nom de la ville :");
                            lire_string(s);
                            recherche_ville(s);
                        }
                         printf("\n\t\t\t\t\t");
           textattr(10);

                retourMenu();


        break ;
        case 6: // Si choix = 6
            textattr(15);
                             printf("quel type de suggestion voulez vous ?\n");
                             b=menu_suggestion();
                             printf("\n\ntapez le nom d'utilisateur :");
                             lire_string(s);
                             if (b==1)
                             {
                                interet_commun(s);
                             }else
                             {
                                amis_commun(s) ;
                             }



                          printf("\n\t\t\t\t\t");
           textattr(10);

                retourMenu();

        break;
        case 7: // Si choix = 7
           textattr(15);
           fichier=fopen("C:/Users/kara bernou/desktop/TP ALSDD/fichierdetp.txt","r");
           restaurer(fichier);
           fclose(fichier);
           printf("\n\t\t\t\t\t");
           textattr(10);

                retourMenu();

        break;
        case 8:
            textattr(15);
           fichier=fopen("C:/Users/kara bernou/desktop/TP ALSDD/fichierdetp.txt","w");
           sauvegarder(fichier);
           fclose(fichier);
           printf("\n\t\t\t\t\t");
           textattr(10);

                retourMenu();
        break;
        case 9:
            quite = 1 ;
            textattr(10);
            cadre_aff(50,5,65,17);
            gotoxy(72,19);
            textattr(15);
            printf("MERCI D'AVOIR UTILISE CE PROGRAMME");
            gotoxy(70,24);
            textattr(15);
            system("pause");

         break;

        }
        textattr(15);
        system("cls");
    }
}
int main()
{

    system("cls");
color(15,0);
     int i;
     for(i=0;i<26;i++)
     {
         tab[i]=NULL;
     }


    textattr(15);
    affichage();
      system("mode con LINES=550 COLS=189");
    textattr(15);
    system("cls");
    choixMenu();
return 0;
}




