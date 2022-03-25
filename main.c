//Sylvain PERGAUD
//Lahcen EL OUARDI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define BUFSIZE 1024
/* structure joueur
	attributs: l, c, nbmurs, (!)tableau des murs placés dans le plateau
	fonctions:initialiser(joueur j, int tour), deplacer(struct joueur j,int x), (!)dep_valide(..),(!)placer_mur(..)
*/
struct mur{
	int l;
	int c;
	char pos;


};

struct joueur{
	int l;	
	int c;	
	int tour;
	int dl;
	struct mur** plateau;
	int nbmurs;
	int ms;
	
};


void init(struct joueur* j,int tour){
	if(tour==0){
		j->l=0;
		j->c=4;
		j->tour=0;
		j->dl = 1;
	}else{
		j->l=8;
		j->c=4;
		j->tour=-1;
		j->dl=-1;
	}
	
	j->plateau=(struct mur**)malloc(20*sizeof(struct mur*));
	for(int i=0;i<20;i++){
		j->plateau[i]=malloc(sizeof(struct mur));
		j->plateau[i]->l=-1;
		j->plateau[i]->c=-1;
		j->plateau[i]->pos='n';
	}

	j->nbmurs=0;
	j->ms = 10;

}

/*Ajouter un mur dans le plateau,memorise les murs placé*/

void ajouterMur(struct joueur *j, int l, int c, char e){
	 
	 j->plateau[j->nbmurs]->l=l;
	 j->plateau[j->nbmurs]->c=c;
	 j->plateau[j->nbmurs]->pos=e;
	 j->nbmurs++;

	 j->ms++;
}

/*Mouvement Impossible*/
/*
h: mur: l,c | l,c -> l+1,c | l,c+1 -> l+1,c+1 | l+1,c -> l,c | l+1,c+1 -> l,c+1
v:  l,c -> l,c+1  | l+1,c -> l+1,c+1  |  l,c+1 -> l,c  |  l+1,c+1  -> l+1,c
*/

int verifierMurs(struct joueur* j, int x, char type){
	if(x==1 && type=='H')
		j->l+=j->dl;
	for(int i=0;i<j->nbmurs;i++){
		//Murs Horizontaux
		if(j->plateau[i]->pos=='H'&& type=='H'){
			if((j->l+j->tour) == j->plateau[i]->l){
				int testMursVD = verifierMurs(j,x,'V');
				if(j->c == j->plateau[i]->c && testMursVD==1){
					j->c--;
					printf("%d\n%d\n",j->l,j->c);
					return 1;
				}else if(j->c == (j->plateau[i]->c+1) || testMursVD==0){
					j->c++;
					printf("%d\n%d\n",j->l,j->c);
					return 1;

				}
			}
		//Murs verticaux
		}else if(j->plateau[i]->pos=='V' && type=='V'){
			if(((j->l-1)==j->plateau[i]->l || j->l==j->plateau[i]->l) &&
			(j->c-1) == j->plateau[i]->c)
				return 0;
		}
		
	}
	if(type=='H'){
		j->l+=j->dl;
		printf("%d\n%d\n",j->l,j->c);
	}
	return 1;

}
void deplacer(struct joueur* j, int x){

	if(x<2){
		//DEPLACEMENT
		puts("MOVE");
		verifierMurs(j,x,'H');

	}else {
		//Place un mur horizontal 
		puts("WALL H");
		if(j->tour==0){
			//place mur horizontal derriere lui, si joueur A
			printf("%d\n%d\n",j->l-1,j->c);
			ajouterMur(j,j->l-1,j->c,'H');
			
		}else{
			//place mur horizontal derriere lui, si joueur B
			printf("%d\n%d\n",j->l,j->c);
			ajouterMur(j,j->l,j->c,'H');
		}
		
	}
		
}


int main() {
	setbuf(stdout, NULL);
	char buf[BUFSIZE];
	// get the letter of the player
	fgets(buf, BUFSIZE, stdin);
	int turn = (buf[0] == 'A') ? 0 : 1;
	struct joueur *j;
	if(buf[0]=='A')
	init(j,0);
	else
	init(j,1);

	// initialize the state of the game
	int l=-1,c=-1;char e='n';

	for (;;) {
		if (turn == 0) {
		 // my turn
		// compute the action and the coord
		if(l==3 && c==4 && j->tour==0){
			puts("WALL V");
			printf("%d\n%d\n",3,3);
			ajouterMur(j,3,3,'V');
		}
		if((j->l+j->dl) == l && j->c == c)
		deplacer(j,1);
		else if((j->l+j->dl+j->dl)==l && j->c == c){
		deplacer(j,2);
		}
		else
		deplacer(j,0);
		
		
		fgets(buf, BUFSIZE, stdin);
	
		if (strcmp(buf, "WIN\n") == 0|| strcmp(buf, "LOSE\n") == 0) {
			break;
		}
		} else {
			 // other player’s turn
			 fgets(buf, BUFSIZE, stdin);
			 if (strcmp(buf, "WIN\n") == 0|| strcmp(buf, "LOSE\n") == 0) {
			 	break;
			 }
			 if(strcmp(buf,"WALL H\n")==0){
			 	e = 'H';
			 } 
			 if(strcmp(buf,"WALL V\n")==0){
			 	e = 'V';
			 }
			 fgets(buf, BUFSIZE, stdin);
			 l = atoi(buf);
			 fgets(buf, BUFSIZE, stdin);
			 c = atoi(buf);
			if(e=='H' || e=='V'){
				ajouterMur(j,l,c,e);
			 	e='n';
			}
			 // update the state of the game
		}
		turn = 1 - turn;
		
	}
	
	return 0;
}	
	
	
	
	
	
	
	
	
	
	

	
	
