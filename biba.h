#define nbr_equipes_championnat 20
#define nbr_joueurs_equipe 22
#define nbr_joueurs_championnat nbr_joueurs_equipe*nbr_equipes_championnat
#define maligne printf("\nici %d ??\n",__LINE__)

typedef struct championnat championnat;
typedef struct equipe equipe;
typedef struct joueur joueur;
typedef struct resultat resultat;
typedef struct adversaire adversaire;

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

struct adversaire{
  char nom[256];
  unsigned short m;
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
  adversaire adversaires[2][nbr_equipes_championnat-1];
  unsigned short jour;
};

struct championnat{
  char nom[256];
  char pays[256];
  unsigned short saison;
  equipe equipes[nbr_equipes_championnat];
  equipe classement[nbr_equipes_championnat];
  joueur buteurs[nbr_joueurs_championnat];
  joueur passeurs[nbr_joueurs_championnat];
};

struct resultat{
  unsigned short ed;
  unsigned short ev;
};

//---------------------------------------------------------------------------------------

void GenererNom (char *nom, short n);

short GenererNumero (short n1, short n2);

joueur AjouterJoueurA(char *SonEquipe);

void InitialiseJoueur(joueur *s);

void DetailJoueur(joueur j);

equipe AjouterEquipeA();

void DetailEquipe(equipe e);

void classement(equipe *ch);

championnat GenererChampionnatA ();

void DetailChampionnat (championnat ch);
//--------------------------------------------------------------------------------------------------------------------

//fonctions pour fichiers

void AfficherFichier(FILE *f);

void StockerChampionnatF (championnat ch, FILE *f);

void RecupererChampionnatF (championnat *ch, FILE *f);

void StockerEquipesF (equipe e, FILE *f);

void RecupererEquipesF (equipe *e, FILE *f);

void StockerJoueursF (joueur j, FILE *f);

void RecupererJoueursF (joueur *j, FILE *f);
//----------------------------------------------------

joueur AjouterJoueur(char *SonClub);

equipe AjouterEquipe(char *SonPays);

unsigned short OuiNon ();

resultat MatchA (equipe *ed, equipe *ev);

void Buteurs (championnat ch, joueur *b);

void Passeurs (championnat ch, joueur *b);

int RetInd (char *s, int ar, adversaire a[ar][nbr_equipes_championnat-1]);

void InitJournee(championnat *ch, int ar);

void Journee (championnat *ch);
