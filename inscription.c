#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct etudiants
{
	char nom[10];
	char prenoms[20];
	char date_de_naissance[30];
	char adresse[20];
	char niveau[2];
	int age;
};

void afficher (struct etudiants e[], int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("Entrez votre nom %d:",i+1);
		scanf("%s",e[i].nom);
		printf("Entrez vos prénoms %d:",i+1);
		scanf("%s",e[i].prenoms);
		printf("Entrez votre date de naissance %d:",i+1);
		scanf("%s",e[i].date_de_naissance);
		printf("Entrez votre adresse %d:",i+1);
		scanf("%s",e[i].adresse);
		printf("Entrez votre niveau %d:",i+1);
		scanf("%s",e[i].niveau);
		printf("Entrez votre âge %d:",i+1);
		scanf("%d",&e[i].age);
		printf("\n");
	}
	printf("Résultats affichés dans le fichier: liste.txt\n");
	FILE *liste_etudiants;
	liste_etudiants=fopen("liste.txt","a+");
	if(liste_etudiants==NULL)
	{
		printf("Erreur d'ouverture du fichier\n");
		exit(0);
	}
	for(i=0;i<n;i++)
	{
		fprintf(liste_etudiants,"Le nom de l'étudiant(%d):%s /Prénoms:%s /Date de naissance:%s /Adresse:%s /Niveau:%s /Âge:%d\n",
			i+1,e[i].nom, e[i].prenoms, e[i].date_de_naissance, e[i].adresse, e[i].niveau, e[i].age);
	}
	fclose(liste_etudiants);
}

/* Compare deux etudiants selon le critere choisi :
   critere = 1 -> comparaison par nom (ordre alphabetique)
   critere = 2 -> comparaison par age
   Renvoie : negatif si a vient avant b, 0 si egal, positif si a vient apres b */
int comparer(struct etudiants a, struct etudiants b, int critere)
{
	if(critere == 1)
		return strcmp(a.nom, b.nom);
	else
		return a.age - b.age;
}

/* Tri a bulles generique, utilisable pour n'importe quel critere/type :
   critere = 1 (nom) ou 2 (age)
   type    = 1 (croissant) ou 2 (decroissant) */
void trier(struct etudiants e[], int n, int critere, int type)
{
	int i, j, cmp;
	struct etudiants temp;

	for(i=0; i<n-1; i++)
	{
		for(j=0; j<n-1-i; j++)
		{
			cmp = comparer(e[j], e[j+1], critere);

			/* croissant : on echange si e[j] est plus grand que e[j+1]
			   decroissant : on echange si e[j] est plus petit que e[j+1] */
			if((type==1 && cmp>0) || (type==2 && cmp<0))
			{
				temp = e[j];
				e[j] = e[j+1];
				e[j+1] = temp;
			}
		}
	}
}

void afficher_resultats(struct etudiants e[], int n, const char *titre)
{
	int i;
	printf("\n--- %s ---\n", titre);
	for(i=0;i<n;i++)
	{
		printf("%d) %s %s - age:%d\n", i+1, e[i].nom, e[i].prenoms, e[i].age);
	}
}

/* Affiche toutes les informations d'un etudiant */
void afficher_fiche(struct etudiants e)
{
	printf("\nEtudiants trouvés :\n");
	printf("Nom:%s\n", e.nom);
	printf("Prénoms:%s\n", e.prenoms);
	printf("Date de naissance:%s\n", e.date_de_naissance);
	printf("Adresse:%s\n", e.adresse);
	printf("Niveau:%s\n", e.niveau);
	printf("Âge:%d\n", e.age);
}

/* Recherche generique : l'utilisateur choisit le champ (nom, prenoms, niveau, adresse,
   date de naissance ou age), saisit la valeur connue, et on affiche la fiche complete
   de chaque etudiant correspondant. */
void rechercher(struct etudiants e[], int n, int champ)
{
	char recherche_str[30];
	int recherche_age;
	int i, trouve = 0, correspond;

	if(champ == 6)
	{
		printf("\nEntrez l'âge à rechercher:");
		scanf("%d", &recherche_age);
	}
	else
	{
		printf("\nEntrez la valeur à rechercher:");
		scanf("%s", recherche_str);
	}

	for(i=0; i<n; i++)
	{
		switch(champ)
		{
			case 1: correspond = (strcmp(e[i].nom, recherche_str) == 0); break;
			case 2: correspond = (strcmp(e[i].prenoms, recherche_str) == 0); break;
			case 3: correspond = (strcmp(e[i].niveau, recherche_str) == 0); break;
			case 4: correspond = (strcmp(e[i].adresse, recherche_str) == 0); break;
			case 5: correspond = (strcmp(e[i].date_de_naissance, recherche_str) == 0); break;
			default: correspond = (e[i].age == recherche_age); break;
		}

		if(correspond)
		{
			afficher_fiche(e[i]);
			trouve = 1;
		}
	}

	if(trouve == 0)
	{
		printf("\nAucun étudiant trouvé.\n");
	}
}

/*Recherche un étudiant par son nom et permet de modifier un de ses champs*/
void modif(struct etudiants e[], int n)
{
	char recherche_str[10];
	int i, trouve=0, champ_modif;

	printf("Entrez le nom de l'étudiant à modifier:\n");
	scanf("%s",recherche_str);

	for(i=0;i<n;i++)
	{
		if(strcmp(e[i].nom, recherche_str) == 0)
		{
			trouve = 1;
			printf("Fiche actuelle :\n");
			afficher_fiche(e[i]);

			printf("Quel champ voulez-vous modifier?\n");
			printf("1) Nom\n 2) Prenoms\n 3) Date de naissance\n 4) Adresse\n 5) Niveau\n6 6) Age\n");
			scanf("%d", &champ_modif);

			switch(champ_modif)
			{
				case 1:
					printf("Nouveau nom:\n");
					scanf("%s", e[i].nom);
					break;
				case 2:
					printf("Nouveaux prenoms:\n");
					scanf("%s", e[i].prenoms);
					break;
				case 3:
					printf("Nouvelle date de naissance:\n");
					scanf("%s", e[i].date_de_naissance);
				case 4:
					printf("Nouvelle adresse:\n");
					scanf("%s", e[i].adresse);
					break;
				case 5:
					printf("Nouveau niveau:\n");
					scanf("%s", e[i].niveau);
					break;
				default:
					printf("Nouvel âge:\n");
					scanf("%d", &e[i].age);
					break;
			}
			printf("Modification effectuée. Nouvelle fiche:\n");
			afficher_fiche(e[i]);
		}
	}
	if(trouve == 0)
	{
		printf("Aucun étudiant trouvé avec le nom \"%s\".\n", recherche_str);
	}
}

int main ()
{
	int n, critere, type, choix_recherche, champ, choix_modif;

	printf("Entrez le nombre d'étudiants:");
	scanf("%d",&n);

	struct etudiants e[n];

	afficher(e,n);                  /* saisie des etudiants + ecriture dans le fichier */

	printf("\nSur quel critere voulez-vous trier ?\n");
	printf("1) Nom\n2) Age\n");
	scanf("%d",&critere);

	printf("\nQuel type de tri voulez-vous ?\n");
	printf("1) Croissant\n2) Decroissant\n");
	scanf("%d",&type);

	trier(e,n,critere,type);
	afficher_resultats(e,n,"Liste des étudiants triée");

	printf("\nVoulez-vous rechercher un étudiant ?\n");
	printf("1) Oui\n2) Non\n");
	scanf("%d",&choix_recherche);

	if(choix_recherche == 1)
	{
		printf("\nSur quel champ voulez-vous rechercher ?\n");
		printf("1) Nom\n2) Prénoms\n3) Niveau\n4) Adresse\n5) Date de naissance\n6) Âge\n");
		scanf("%d",&champ);

		rechercher(e,n,champ);
	}

	printf("Y a-t-il des modifications à faire?\n");
	printf("1) oui\n 2) Non\n");
	scanf("%d", &choix_modif);

	if(choix_modif == 1)
	{
		modifier(e,n);
	}

	return 0;
}
