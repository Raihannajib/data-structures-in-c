#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int host1;
  int host2;
}Connexion;

typedef struct {
    int nombreHostes;         //les noeuds
    int nombreConnexion;      //enter les noeuds
    char **hostsNames;
    Connexion *nConnexion;        //tableau des reseaux(sommets := laison entre h1 et h2)
}Reseau;

Reseau* chargementReseau(char* fileName){

    char host[100];
    FILE* file = fopen(fileName,"rt");
    if(file == NULL){
        puts("file not fount\n");
        exit(1);
    }
    Reseau* intranet = (Reseau*)malloc(sizeof(Reseau));

    fscanf(file,"%d",&intranet->nombreHostes);
    fscanf(file,"%d",&intranet->nombreConnexion);

    intranet->hostsNames = (char**)malloc(intranet->nombreHostes*sizeof(char*));
    for (int i = 0; i <intranet->nombreHostes ; ++i) {
        fscanf(file,"%s",host);
        intranet->hostsNames[i] = (char*)malloc((strlen(host)+1)* sizeof(char));
        strcpy(intranet->hostsNames[i], host);
    }

    intranet->nConnexion = (Connexion*)malloc(intranet->nombreConnexion*(sizeof(Connexion)));
    for (int j = 0; j < intranet->nombreConnexion; ++j) {
        fscanf(file,"%d %d",&intranet->nConnexion[j].host1,&intranet->nConnexion[j].host2);
    }


    fclose(file);
    return intranet;
}


void enregistrerreseau(char* fileName , Reseau *intranet){

    FILE* file = fopen(fileName,"wt");

    fprintf(file,"%d\n", intranet->nombreHostes);
    fprintf(file,"%d\n",intranet->nombreConnexion);
    for (int i = 0; i <intranet->nombreHostes ; ++i) {
        fprintf(file,"%s\n",intranet->hostsNames[i]);
    }
    for (int j = 0; j <intranet->nombreConnexion ; ++j) {
        fprintf(file,"%d %d\n",intranet->nConnexion->host1,intranet->nConnexion->host2);
    }

    fclose(file);
}

int isConnected(Reseau* intranet , int h1 , int h2){
    for (int i = 0; i <intranet->nombreConnexion ; ++i) {
        if((intranet->nConnexion[i].host1 == h1) && (intranet->nConnexion[i].host2 == h2)){
            return 1;
        }
        return 0;
    }

}

int areConnected(Reseau* intranet , const int* tabHots){
    for (int i = 0; i <intranet->nombreConnexion ; ++i) {
        if((intranet->nConnexion[i].host1 == tabHots[i]) && (intranet->nConnexion[i].host2 == tabHots[i+1])){
            return 1;
        }
        return 0;
    }

}



int main() {

    char file[10]="file.txt";
    char file2[10] ="file2.txt";
    Reseau* reseau = NULL;
    reseau = chargementReseau(file);
    enregistrerreseau(file2,reseau);


    return 0;
}