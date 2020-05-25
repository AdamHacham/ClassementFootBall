#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "biba.h"

// ----------------------------------------------------------------------------------------

//la fonction retourne une chaine de n caractere(s) aleatoirement
void GenererNom (char *nom, short n){
  short i;
  clock_t t;

  if (n <= 0);
  for (i=0;i<n;i++){
    t=clock();
    nom[i]=(char) ( (clock() + t) % 26 + 65);
  }
  nom[i]='\0';
}
//_________________________________________________________________________________________

//la fonction retourne un entier compris en n1 et n2 qui sont positifs sinon -1
short GenererNumero (short n1, short n2){
  clock_t t=clock();
  if ((n1<0)||(n2<0)||((n1==0)&&(n2==0))) return -1;
  if (n1<n2) return (clock()+t) % (n2-n1) + n1;
  if (n1>n2) return clock() % (n1-n2) + n2;
  return n1;
}
//___________________________________________________________________________________________

// la fonction ajoute un joueur avec les information le concernant de façon aléatoire
// et retourne une structure de type joueur définie dans "biba.h"
joueur AjouterJoueurA(char *SonEquipe){
  joueur s;
  char *nom;
  nom=malloc(10*sizeof(*nom));
  GenererNom(nom,10);
  strcpy( s.nom, nom);
  free(nom);
  nom=malloc(15*sizeof(*nom));
  GenererNom(nom,15);
  strcpy( s.nationalite, nom);
  free(nom);
  strcpy( s.club , SonEquipe);
  s.age = GenererNumero(17,40);
  s.taille = GenererNumero(155,210);
  s.poids = GenererNumero(51,110);
  s.numero = GenererNumero(1,100);
  s.nbr_buts = GenererNumero(40,0);
  s.nbr_passes = GenererNumero(40,0);

  return s;
}
//_____________________________________________________________________________

// la fonction prend en entrée une structure de type joueur et l'initialise
// le modifie c'est un joueur qui n'a rien
void InitialiseJoueur(joueur *s){
  strcpy( s->nom, "rien");
  strcpy( s->nationalite, "rien");
  strcpy( s->club, "rien");
  s->age = GenererNumero(0,-2);
  s->taille = GenererNumero(0,-2);
  s->poids = GenererNumero(0,-2);
  s->numero = GenererNumero(-2,0);
  s->nbr_buts = GenererNumero(-2,0);
  s->nbr_passes = GenererNumero(-2,0);
}
//___________________________________________________________________________________________

// la fonction affiche les details d'un joueur
void DetailJoueur(joueur j){
  printf("\n-------------------------------------------\n");
  printf("  Nom : %s.\n",j.nom);
  printf("  Nationalite : %s.\n",j.nationalite);
  printf("  Club : %s.\n",j.club);
  printf("  age : %hd ans.\n",j.age);
  printf("  taille : %hd cm.\n",j.taille);
  printf("  poids : %hd kg.\n",j.poids);
  printf("  Numero : %hd.\n",j.numero);
  printf("  But(s) marqué(s) : %hd.\n",j.nbr_buts);
  printf("  Passe(s) décisive(s) : %hd.",j.nbr_passes);
  printf("\n-------------------------------------------\n");
}
//_____________________________________________________________________________

// la fonction ajoute une equipe avec les information la concernant de façon aléatoire
// et retourne une structure de type equipe définie dans "biba.h"
equipe AjouterEquipeA(char *SonPays){
  equipe s;
  int i;
  char *nom;
  nom=malloc(13*sizeof(*nom));
  GenererNom(nom,13);
  strcpy( s.nom, nom);
  free(nom);
  strcpy( s.pays, SonPays);
  nom=malloc(13*sizeof(*nom));
  GenererNom(nom,13);
  strcpy(s.entraineur, nom);
  free(nom);
  nom=malloc(10*sizeof(*nom));
  GenererNom(nom,10);
  strcpy( s.president, nom);
  free(nom);
  nom=malloc(11*sizeof(*nom));
  GenererNom(nom,11);
  strcpy( s.stade, nom);
  free(nom);
  s.AnneeCreation = GenererNumero(1870,1970);
  s.nbr_points = GenererNumero(1,100);
  s.buts_pour = GenererNumero(1,100);
  s.buts_contre = GenererNumero(1,100);
  s.matchs_gagnes = GenererNumero(1,15);
  s.matchs_perdus = GenererNumero(1,15);
  s.matchs_nuls = GenererNumero(1,8);
  for(i=0; i<nbr_joueurs_equipe; i++){
    s.joueurs[i] = AjouterJoueurA(s.nom);
  }

  return s;
}
//_____________________________________________________________________________

// la fonction affiche les details d'une equipe
void DetailEquipe(equipe e){
  unsigned short i;
  printf("\n-------------------------------------------\n");
  printf("  Nom : %s.\n",e.nom);
  printf("  Pays : %s.\n",e.pays);
  printf("  Entraineur : %s.\n",e.entraineur);
  printf("  President : %s.\n",e.president);
  printf("  Stade : %s.\n",e.stade);
  printf("  Fondation : %hd.\n",e.AnneeCreation);
  printf(" Points : %hd.\n",e.nbr_points);
  printf(" buts_pour : %hd.\n",e.buts_pour);
  printf(" buts_contre : %hd.\n",e.buts_contre);
  printf(" matchs_gagnes : %hd.\n",e.matchs_gagnes);
  printf(" matchs_perdus : %hd.\n",e.matchs_perdus);
  printf(" matchs_nuls : %hd.\n",e.matchs_nuls);
  printf("\n-------------------------------------------\n");
  printf("  Voulez vous afficher les details des joueurs de l'equipe");
  if (OuiNon() != 0){
    for(i=0; i<nbr_joueurs_equipe; i++){
      printf("  Joueur %d !",i+1);
      DetailJoueur(e.joueurs[i]);  
    }
  }

  printf("\n________________________________________________________\n");
}
//_____________________________________________________________________________

// la fonction prend en entrée un tableau de structure de type "equipe"
// et trie le tableau pour avoir un classement de championnat de football
void classement(equipe *ch){
  unsigned short ti,tj;
  equipe tmp;
for ( ti = 0 ; ti < nbr_equipes_championnat ; ti++ ){
  for ( tj = 0 ; tj < nbr_equipes_championnat-1 ; tj++ ){
    if ( ch[tj].nbr_points < ch[tj+1].nbr_points ){ // on intervertit
      tmp = ch[tj];
      ch[tj] = ch[tj+1];
      ch[tj+1] = tmp;
    }
    else if ( ch[tj].nbr_points == ch[tj+1].nbr_points ){ // on regarde la diff. de buts
      if ( ch[tj].buts_pour - ch[tj].buts_contre < ch[tj+1].buts_pour - ch[tj+1].buts_contre ){ // on intervertit
	tmp = ch[tj];
	ch[tj] = ch[tj+1];
	ch[tj+1] = tmp;
      }
      else if (  ch[tj].buts_pour - ch[tj].buts_contre == ch[tj+1].buts_pour - ch[tj+1].buts_contre ){ // on regarde l'attaque
	if ( ch[tj].buts_pour < ch[tj+1].buts_pour ){ // on intervertit
	  tmp = ch[tj];
	  ch[tj] = ch[tj+1];
	  ch[tj+1] = tmp;
	}
	else if ( ch[tj].buts_pour == ch[tj+1].buts_pour ){ // on regarde les les matchs gagnés
	  if ( ch[tj].matchs_gagnes < ch[tj+1].matchs_gagnes ){ // on intervertit
	    tmp = ch[tj];
	    ch[tj] = ch[tj+1];
	    ch[tj+1] = tmp;
	  }
	} // Sinon il y a égalité parfaite, on ne change rien
      } // Fin attaque
    }// Fin différence de buts
  }// Fin boucle tj
 }// Fin boucle ti
}
//_____________________________________________________________________________

// la fonction ajoute un championnat avec les information le concernant de façon aléatoire
// et retourne une structure de type championnat définie dans "biba.h"
championnat GenererChampionnatA (){
  unsigned short i;
  championnat ch;
  char *nom;

  nom=malloc(20*sizeof(*nom));
  GenererNom(nom,19);
  strcpy( ch.nom, nom);
  free(nom);
  nom=malloc(13*sizeof(*nom));
  GenererNom(nom,13);
  strcpy( ch.pays, nom);
  free(nom);
  ch.saison = GenererNumero(2015, 1880);
  for(i=0; i<nbr_equipes_championnat; i++){
    ch.equipes[i] = AjouterEquipeA(ch.pays);
  }
  //  equipe classement[nbr_equipes_championnat];
  //  joueur buteurs[nbr_joueurs_championnat];
  //  joueur passeeurs[nbr_joueurs_championnat];

  return ch;
}
//_____________________________________________________________________________

// la fonction affiche les details d'un championnat
void DetailChampionnat (championnat ch){
  unsigned short i;
  printf("\n________________________________________________________\n");
  printf("  Nom : %s.\n",ch.nom);
  printf("  Pays : %s.\n",ch.pays);
  printf("  Saison : %hd-%hd\n",ch.saison, ch.saison+1);
  printf("  Voulez vous afficher les details des equipes du championnat");
  if (OuiNon() != 0){
    for(i=0; i<nbr_equipes_championnat; i++){
      printf("  Equipe %d !\n",i+1);
      DetailEquipe(ch.equipes[i]);
    }
  }
  printf("\n________________________________________________________\n");
}
//_________________________________________________________________________________
//--------------------------------------------------------------------------------------------------------------------

//fonctions pour fichiers
//_________________________________________________________________________________


void AfficherFichier(FILE *f){
  char c='\n';
  printf("\n---------------------------------------");
  if (f != NULL){
    while (c != EOF){
      printf("%c",c);
      c = fgetc(f);
    }
  }
  printf("\n---------------------------------------\n");
}
//_________________________________________________________________________________

void StockerChampionnatF (championnat ch, FILE *f){
  if (f != NULL){
    fprintf(f, "%s %s %hd\0", ch.nom, ch.pays, ch.saison);
    fprintf(f, "\n");
  }
}
//_________________________________________________________________________________

void RecupererChampionnatF (championnat *ch, FILE *f){
  char s[5];
  if (f!=NULL){
    fscanf(f,"%s %s %s", ch->nom, ch->pays, s);
    ch->saison = atoi(s);
    s[0] = fgetc(f); // pour passer a la ligne suivante pour la prochaine fois
    while ((s[0] != '\n') & (s[0] != EOF)){
      s[0] = fgetc(f);
    } 
  }
}
//_________________________________________________________________________________

void StockerEquipesF (equipe e, FILE *f){
  if (f!=NULL){
    fprintf(f, "%s %s %s %s %s %hd %hd %hd %hd %hd %hd %hd %hd\0", e.nom, e.pays, e.entraineur, e.president, e.stade, e.AnneeCreation, e.nbr_points, e.buts_pour, e.buts_contre, e.matchs_gagnes, e.matchs_perdus, e.matchs_nuls, nbr_joueurs_equipe);
    fprintf(f, "\n");
  }
}
//_________________________________________________________________________________

void RecupererEquipesF (equipe *e, FILE *f){
  char s[7][5];
  if (f != NULL){
    fscanf(f, "%s %s %s %s %s %s %s %s %s %s %s %s", e->nom,e->pays,e->entraineur,e->president,e->stade,s[0],s[1],s[2],s[3],s[4],s[5],s[6]);
    e->AnneeCreation = atoi(s[0]);
    e->nbr_points = atoi(s[1]);
    e->buts_pour = atoi(s[2]);
    e->buts_contre = atoi(s[3]);
    e->matchs_gagnes = atoi(s[4]);
    e->matchs_perdus = atoi(s[5]);
    e->matchs_nuls = atoi(s[6]);
    s[0][0] = fgetc(f); // pour passer a la ligne suivante pour la prochaine fois qu'on utilisera le fichier pointé par f
    while ((s[0][0] != '\n') & (s[0][0] != EOF)){
      s[0][0] = fgetc(f);
    }
  }
}
//_________________________________________________________________________________

void StockerJoueursF (joueur j, FILE *f){
  if (f != NULL){
    fprintf(f, "%s %s %s %hd %hd %hd %hd %hd %hd\0", j.nom, j.nationalite, j.club, j.age, j.taille, j.poids, j.numero, j.nbr_buts, j.nbr_passes);
    fprintf(f, "\n");
  }
}
//_________________________________________________________________________________

void RecupererJoueursF (joueur *j, FILE *f){
  char s[6][4];
  if (f != NULL){
    fscanf(f, "%s %s %s %s %s %s %s %s %s", j->nom, j->nationalite, j->club, s[0], s[1], s[2], s[3], s[4], s[5]);
    j->age = atoi(s[0]);
    j->taille = atoi(s[1]);
    j->poids = atoi(s[2]);
    j->numero = atoi(s[3]);
    j->nbr_buts = atoi(s[4]);
    j->nbr_passes = atoi(s[5]);
    s[0][0] = fgetc(f); // pour passer a la ligne suivante pour la prochaine fois qu'on utilisera le fichier pointé par f
    while ((s[0][0] != '\n') & (s[0][0] != EOF)){
      s[0][0] = fgetc(f);
    }
  }
}
//_________________________________________________________________________________

joueur AjouterJoueur(char *SonClub){
  joueur s;

  printf("\n Vous allez ajouter un joueur, merci de suivre les instructions\n");

  printf("\n Entrez le nom du joueur : ");
  scanf("%s", s.nom);

  printf("\n Entrez la nationalite du joueur : ");
  scanf("%s", s.nationalite);

  if (strlen(SonClub) == 0){
    printf("\n Entrez le nom de l'equipe du joueur : ");
    scanf("%s", s.club);
  }
  else {
    strcpy(s.club, SonClub);
  }

  printf("\n Entrez l'age du joueur : ");
  scanf("%hd", &s.age);

  printf("\n Entrez la taille du joueur : ");
  scanf("%hd", &s.taille);

  printf("\n Entrez le poids du joueur : ");
  scanf("%hd", &s.poids);

  printf("\n Entrez le numero du joueur : ");
  scanf("%hd", &s.numero);

  printf("\n Entrez le nombre de but(s) marque(s) par le joueur : ");
  scanf("%hd", &s.nbr_buts);

  printf("\n Entrez le nombre de passe(s) faite(s) par le joueur : ");
  scanf("%hd", &s.nbr_passes);

  printf("\n     -------------------------------     \n");

  return s;
}
//_________________________________________________________________________________

equipe AjouterEquipe(char *SonPays){
  equipe s;
  int i;

  printf("\n Vous allez ajouter une equipe, merci de suivre les instructions\n");

  printf("\n Entrez le nom de l'equipe : ");
  scanf("%s", s.nom);

  if (strlen(SonPays) == 0){
    printf("\n Entrez le pays de l'equipe  : ");
    scanf("%s", s.pays);
  }
  else {
    strcpy(s.pays, SonPays);
  }

  printf("\n Entrez le nom de l'entraineur de l'equipe : ");
  scanf("%s", s.entraineur);

  printf("\n Entrez le nom du president de l'equipe : ");
  scanf("%s", s.president);

  printf("\n Entrez le nom du stade de l'equipe : ");
  scanf("%s", s.stade);

  printf("\n Entrez l'annee de creation de l'equipe : ");
  scanf("%hd", &s.AnneeCreation);

  printf("\n Entrez le nombre de points de l'equipe : ");
  scanf("%hd", &s.nbr_points);

  printf("\n Entrez le nombre de but(s)-pour pour l'equipe : ");
  scanf("%hd", &s.buts_pour);

  printf("\n Entrez le nombre de but(s)-contre pour l'equipe : ");
  scanf("%hd", &s.buts_contre);

  printf("\n Entrez le nombre de match(s)-gagne(s) de l'equipe : ");
  scanf("%hd", &s.matchs_gagnes);

  printf("\n Entrez le nombre de match(s)-perdus(s) de l'equipe : ");
  scanf("%hd", &s.matchs_perdus);

  printf("\n Entrez le nombre de match(s)-nul(s) de l'equipe : ");
  scanf("%hd", &s.matchs_nuls);

  for(i=0; i<nbr_joueurs_equipe; i++){
    s.joueurs[i] = AjouterJoueurA(s.nom);
  }

  return s;
}
//_________________________________________________________________________________

unsigned short OuiNon (){
  char c='a';
  unsigned short x = 1;

  printf("\n pour oui tapez 'o' , pour non tapez 'n'\n");
  while ((c!='o')&(c!='O')&(c!='n')&(c!='N')){
    printf("   : ");
    c = getchar();
  }
  if ((c=='n')|(c=='N')){
    x = 0;
  }
  return x;
}
//_________________________________________________________________________________

resultat MatchA (equipe *ed, equipe *ev){
  unsigned short bed, bev, jb,jp;
  int i;
  resultat r;
  bed = GenererNumero(0,6);
  bev = GenererNumero(0,4);
  for (i=0; i<bed; i++){ // pour chaque but marqué on incrémente le nombre de buts pour le buteur, et le nombre de passes pour le passeur pour l'equipe qui reçoit
    jb = GenererNumero(0,nbr_joueurs_equipe);  
    ed->joueurs[jb].nbr_buts ++;
    do{
      jp = GenererNumero(0,nbr_joueurs_equipe);
    } while (jp == jb);
    ed->joueurs[jp].nbr_passes ++;
  }
  for (i=0; i<bev; i++){  // pour chaque but marqué on incrémente le nombre de buts pour le buteur, et le nombre de passes pour le passeur pour l'equipe visiteur
    jb = GenererNumero(0,nbr_joueurs_equipe);
    ev->joueurs[jb].nbr_buts ++;
    do{
      jp = GenererNumero(0,nbr_joueurs_equipe);
    } while (jp == jb);
    ev->joueurs[jp].nbr_passes ++;
  }

  if (bed > bev) {
    ed->nbr_points = ed->nbr_points + 3;
    ed->matchs_gagnes = ed->matchs_gagnes + 1;
    ev->matchs_perdus = ev->matchs_perdus + 1;
  }
  else if (bev>bed) {
    ev->nbr_points = ev->nbr_points + 3;
    ev->matchs_gagnes = ev->matchs_gagnes + 1;
    ed->matchs_perdus = ed->matchs_perdus + 1;
  }
  else {
    ed->nbr_points = ed->nbr_points + 1;
    ev->nbr_points = ev->nbr_points + 1;
    ed->matchs_nuls = ed->matchs_nuls +1;
    ev->matchs_nuls = ev->matchs_nuls +1;
  }
  ed->buts_pour = ed->buts_pour + bed;
  ed->buts_contre = ed->buts_contre + bev;
  ev->buts_pour = ev->buts_pour + bev;
  ev->buts_contre = ev->buts_contre + bed;

  r.ed = bed;
  r.ev = bev;

  return r;
}
//_________________________________________________________________________________

void Buteurs (championnat ch, joueur *b){
  unsigned short i, j, k=0 ;
  for (i=0; i<nbr_equipes_championnat; i++){  // on met tous les joueurs des equipes dans un tableau pour faire le classement des buteurs
    for (j=0; j<nbr_joueurs_equipe; j++){
      b[k] = ch.equipes[i].joueurs[j];
      k++;
    }
  }
  for (i=0; i<nbr_joueurs_championnat; i++){
    for (j=0; j<nbr_joueurs_championnat-1; j++){
      if (b[j].nbr_buts < b[j+1].nbr_buts){
	k = b[j].nbr_buts;
	b[j].nbr_buts = b[j+1].nbr_buts;
	b[j+1].nbr_buts = k;
      }
    }
  }
}
//_________________________________________________________________________________

void Passeurs (championnat ch, joueur *b){
  unsigned short i, j, k=0 ;
  for (i=0; i<nbr_equipes_championnat; i++){  // on met tous les joueurs des equipes dans un tableau pour faire le classement des passeurs
    for (j=0; j<nbr_joueurs_equipe; j++){
      b[k] = ch.equipes[i].joueurs[j];
      k++;
    }
  }
  for (i=0; i<nbr_joueurs_championnat; i++){
    for (j=0; j<nbr_joueurs_championnat-1; j++){
      if (b[j].nbr_passes < b[j+1].nbr_passes){
	k = b[j].nbr_passes;
	b[j].nbr_passes = b[j+1].nbr_passes;
	b[j+1].nbr_passes = k;
      }
    }
  }
}
//_________________________________________________________________________________

int RetInd (char *s, int ar, adversaire a[ar][nbr_equipes_championnat-1]){ //retourne l'indice de l'equipe s dans le tableau adversaire selon la phase aller (ar==0) et retour(ar==1)
  int i;
  for (i=0; i<nbr_equipes_championnat-1; i++){
    if (strcmp(s,a[ar][i].nom)==0) return i;
  }
  return -1;
}
//_________________________________________________________________________________

void InitJournee(championnat *ch, int ar){ //ça initialise toutes les journées
  int m,i,k;
  for (m=0; m<nbr_equipes_championnat; m++){
    for (i=0,k=0; i<nbr_equipes_championnat; i++){
      if (strcmp(ch->equipes[m].nom, ch->equipes[i].nom)!= 0){
	strcpy(ch->equipes[m].adversaires[ar][k].nom, ch->equipes[i].nom);
	ch->equipes[m].adversaires[ar][k].m = 0;
	ch->equipes[m].jour = 0;
	k++;
      }
    }
  }
}
//_________________________________________________________________________________

void Journee (championnat *ch){ // on generer une phase aller ou retour ou une seule journée
  int i,k,j,ind,c=0,m;
  resultat r;
  unsigned short choix, ar=0;

  m = ch->equipes[0].jour;
  printf("\n Pour generer une phase (aller ou retour) tapez 'o'");
  printf("\n Pour generer une seule journee tapez 'n'");
  choix = OuiNon();
  if (choix == 1){
  printf("\n Pour la phase aller tapez 'n' , pour la phase retour tapez 'o'");
  ar = OuiNon();
  }
  else{
    printf("\n si c'est aller tapez 'n', si c'est retour tapez 'o'");
    ar = OuiNon();
  }
     for (i=0; i<nbr_equipes_championnat; i++){  // boucle pour la 1ere equipe
       for (j=0; j<nbr_equipes_championnat; j++){ //boucle pour la 2eme equipe
	 if (strcmp(ch->equipes[i].nom, ch->equipes[j].nom) != 0){ // on choisit une equipe differente de la 1ere equipe
	   for(k=0; k<nbr_equipes_championnat-1; k++){  // boucle pour les adversaires de la 1ere equipe
	     if (strcmp(ch->equipes[i].adversaires[ar][k].nom, ch->equipes[j].nom) == 0 ){ //on recupere la 2eme equipe dans le tableau adversaire
	       if (ch->equipes[i].adversaires[ar][k].m == 0){ // on verifie si on a pas deja joué contre
		 if (choix == 1){ // aller retour
		   if (ar == 0){ // phase aller
		   ch->equipes[i].jour++;
		   ch->equipes[j].jour++;
		   ch->equipes[i].adversaires[ar][k].m = 1;
		   r= MatchA(&ch->equipes[i], &ch->equipes[j]);
		   c++;
		   printf("\n e[%d] : %s  %hu - %hu  e[%d] : %s  --> %d  ... %d %d",i,ch->equipes[i].nom,r.ed,r.ev,j,ch->equipes[j].nom,c,ch->equipes[i].jour,ch->equipes[j].jour);
		   ind = RetInd(ch->equipes[i].nom, ar, ch->equipes[j].adversaires);
		   printf("\n  ind ---> %d",ind);
		   ch->equipes[j].adversaires[ar][ind].m = 1; 
		   }
		   else{ // phase retour
		   ch->equipes[i].jour++;
		   ch->equipes[j].jour++;
		   ch->equipes[i].adversaires[ar][k].m = 1;
		   r= MatchA(&ch->equipes[i], &ch->equipes[j]);
		   c++;
		   printf("\n e[%d] : %s  %hu - %hu  e[%d] : %s  --> %d  ... %d %d",i,ch->equipes[i].nom,r.ed,r.ev,j,ch->equipes[j].nom,c,ch->equipes[i].jour,ch->equipes[j].jour);
		   ind = RetInd(ch->equipes[i].nom, ar, ch->equipes[j].adversaires);
		   printf("\n  ind ---> %d",ind);
		   ch->equipes[j].adversaires[ar][ind].m = 1; 
		   }
		 }
		 else{ // une seule journée
		   if ((ch->equipes[i].jour == m) && (ch->equipes[j].jour == m)){ // on verifie si elle sont en meme journée
		   ch->equipes[i].jour++;
		   ch->equipes[j].jour++;
		   ch->equipes[i].adversaires[ar][k].m = 1;
		   r= MatchA(&ch->equipes[i], &ch->equipes[j]);
		   c++;
		   printf("\n e[%d] : %s  %hu - %hu  e[%d] : %s  --> %d  ... %d %d",i,ch->equipes[i].nom,r.ed,r.ev,j,ch->equipes[j].nom,c,ch->equipes[i].jour,ch->equipes[j].jour);
		   ind = RetInd(ch->equipes[i].nom, ar, ch->equipes[j].adversaires);
		   printf("\n  ind ---> %d",ind);
		   ch->equipes[j].adversaires[ar][ind].m = 1;  
		   }
		 }
	       }
	     }   
	   }
	 }
       }
     }

  printf("\n\n");
}
//_________________________________________________________________________________

//_________________________________________________________________________________

//_________________________________________________________________________________

//_________________________________________________________________________________

//_________________________________________________________________________________

//_________________________________________________________________________________


