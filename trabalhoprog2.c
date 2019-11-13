#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char matriz [100][100];
    int linhas;
    int colunas;
}matriz;

typedef struct{
    int vida;
    char tipo[10];
    int linAtual;
    int colAtual;
}jogadores;


void LeArquivo(matriz mapa[1],FILE* entrada);
void AbreArquivo(matriz mapa[1]);
void printaMapa(matriz mapa[1],jogadores magos[2]);
void LocaisMagos(matriz mapa[1],jogadores magos[2]);
void identificaPosInicial(matriz mapa[1],jogadores magos[2]);
void confereFora(matriz)

int main(int argc, char** argv){
    matriz mapa[1];
    jogadores magos[2];
    strcpy(magos[0].tipo, "agua");
    strcpy(magos[1].tipo, "fogo"); 
    magos[0].vida = 30;
    magos[1].vida = 30;
    AbreArquivo(mapa);
    identificaPosInicial(mapa,magos);
    LocaisMagos(mapa,magos);
    return 0;
}

void AbreArquivo(matriz mapa[1]){
    FILE *entrada;
    entrada = fopen("entrada.txt","r");
    if(entrada != NULL){
       LeArquivo(mapa,entrada);
    }else{
        printf("Arquivo vazio");
        exit(1);
    }
}

void LeArquivo(matriz mapa[1],FILE* entrada){
    int i, k;
    fscanf(entrada,"%d %d\n",&mapa[0].linhas,&mapa[0].colunas);
    for(i = 0; i< mapa[0].linhas;i++){
        fscanf(entrada,"%s",mapa[0].matriz[i]);  
    }
}

void printaMapa(matriz mapa[1],jogadores magos[2]){
    int i,k;
    for(i = 0; i < mapa[0].linhas;i++){
        for(k = 0; k < mapa[0].colunas;k++){
            printf("%c ",mapa[0].matriz[i][k]);
        }
        printf("\n");
    }
    printf("\n");

}

void LocaisMagos(matriz mapa[1],jogadores magos[2]){
    printaMapa(mapa,magos);
    printf("Jogador da vez:%s\n",magos[1].tipo);
    if(mapa[0].matriz[magos[1].linAtual][magos[1].colAtual]!='.' && mapa[0].matriz[magos[1].linAtual][magos[1].colAtual]!='f'){
    printf("%s: %c\n",magos[1].tipo,mapa[0].matriz[magos[1].linAtual][magos[1].colAtual]);
    }else{
        printf("%s: .\n",magos[1].tipo);
    }
    if(mapa[0].matriz[magos[0].linAtual][magos[0].colAtual]!='.'&&mapa[0].matriz[magos[0].linAtual][magos[0].colAtual]!='a'){
    printf("%s: %c\n",magos[0].tipo,mapa[0].matriz[magos[0].linAtual][magos[0].colAtual]);
    }else{
        printf("%s: .\n",magos[0].tipo);
    }
    printf("Vida %s: %d\n",magos[1].tipo,magos[1].vida);
    printf("Vida %s: %d\n",magos[0].tipo,magos[0].vida);

    printf("Comando: ");
    //scanf()
}

void identificaPosInicial(matriz mapa[1],jogadores magos[2]){
    int i,k;
    for(i = 0; i < mapa[0].linhas;i++){
        for(k = 0; k < mapa[0].colunas;k++){
            if(mapa[0].matriz[i][k] == 'f'){
                magos[1].linAtual = i;
                magos[1].colAtual = k;
            }
            if(mapa[0].matriz[i][k] == 'a'){
                magos[0].linAtual = i;
                magos[0].colAtual = k;
            }
        }
    }
}