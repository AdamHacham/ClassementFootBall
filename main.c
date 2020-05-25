#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include "biba.h"


//_____________________________________________________________________________
// les structures utilisées sont
/*
typedef struct championnat championnat;
typedef struct equipe equipe;
typedef struct joueur joueur;

struct joueur{
  char nom[256];
  char nationalite[256];
  char club[256];
  unsigned short age;
  unsigned short taille;
  unsigned short poids;
  unsigned short numero;
  unsigned short nbr_buts;
  unsigned short nbr_passes;
};

struct equipe{
  char nom[256];
  char pays[256];
  char entraineur[256];
  char president[256];
  char stade[256];
  unsigned short AnneeCreation;
  unsigned short nbr_points;
  unsigned short buts_pour;
  unsigned short buts_contre;
  unsigned short matchs_gagnes;
  unsigned short matchs_perdus;
  unsigned short matchs_nuls;
  joueur joueurs[nbr_joueurs_equipe];
};

struct championnat{
  char nom[256];
  char pays[256];
  unsigned short saison;
  equipe equipes[nbr_equipes_championnat];
  equipe classement[nbr_equipes_championnat];
  joueur buteurs[nbr_joueurs_championnat];
  joueur passeeurs[nbr_joueurs_championnat];
};
*/

//-------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-------------------------------------------------------------------------------------

//_______________________________________________________________________________________________________

int main(void){
  int i1,i2;
  unsigned short x=5;
  char *nom,kh[100];
  joueur j;
  equipe e,ea, e1,e2;
  resultat r;
  championnat ch, cha;
  FILE *fc , *fe , *fj ;
  

  fc = fe = fj = NULL;
  
  ch=GenererChampionnatA();
  InitJournee(&ch, 0);
  InitJournee(&ch, 1);
  Journee(&ch);
  Journee(&ch);
  Journee(&ch);
  Journee(&ch);
  Journee(&ch);
  /*
  e1 = AjouterEquipe("ang");
  DetailEquipe(e1);
  e2 = AjouterEquipe("ang");
  DetailEquipe(e2);
  r = MatchA(&e1, &e2);
  printf("\n Resultat est %hu - %hu    !!\n",r.ed,r.ev);
  DetailEquipe(e1);
  DetailEquipe(e2);
  */
  /*
 
  //  DetailChampionnat(ch);
  Buteurs(ch, ch.buteurs);
  Passeurs(ch, ch.passeurs);
  classement(ch.equipes);
  for (i1=0; i1<nbr_joueurs_championnat-400; i1++){
    DetailJoueur(ch.buteurs[i1]);
  }
  //  DetailChampionnat(ch);
  */
  goto fin;
  fc = fopen("./fichiers/championnat.txt", "a+");
  fe = fopen("./fichiers/equipes.txt", "a+");
  fj = fopen("./fichiers/joueurs.txt", "a+");
  StockerChampionnatF(ch, fc);
  for (i1=0; i1<nbr_equipes_championnat; i1++){
    StockerEquipesF(ch.equipes[i1], fe);
    for (i2=0; i2<nbr_joueurs_equipe; i2++){
      StockerJoueursF(ch.equipes[i1].joueurs[i2], fj);
    }
    fprintf(fj, "!\0");
    fputc('\n', fj);
  }
  fprintf(fe, "!\0");
  fputc('\n', fe);
  rewind(fc);
  AfficherFichier(fc);
  rewind(fc);
  rewind(fe);
  rewind(fj);
  maligne;
  RecupererChampionnatF(&cha, fc);
  RecupererJoueursF(&j, fj);
  maligne;
  AfficherFichier(fc);
  DetailChampionnat(cha);
  DetailJoueur(j);
  fclose(fj);
  fclose(fe);
  fclose(fc);
  printf("\nFIN\n");

 fin:
  return 0;

}


/*
gdb ./a.out 
run
where
--
*/
