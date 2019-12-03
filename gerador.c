#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int aux,tam,foguinho=0,aguinha=0,relifogo=0,reliagua=0,tam1; 
    printf("Qual o tamanho do mapa que deseja criar?\n"); 
    scanf("%d %d",&tam,&tam1); 
    char mat[tam][tam1]; 
    FILE* arq; 
    arq = fopen("entrada.txt","w"); 
    srand(time(NULL));
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam1;j++){
            aux = rand()%100; 
            if(aux >= 0 && aux < 5 && foguinho < 1){
                mat[i][j] = 'f'; 
                foguinho++; 
            }else if(aux >= 5 && aux < 10 && aguinha < 1){
                mat[i][j] = 'a'; 
                aguinha++; 
            }else if(aux >= 10 && aux < 15 && relifogo < 1){
                mat[i][j] = '*';
                relifogo++;  
            }else if(aux >= 15 && aux < 20 && reliagua < 1){
                mat[i][j] = '$'; 
                reliagua++; 
            }else if(aux >= 20 && aux < 28){
                mat[i][j] = 'G'; 
            }else if(aux >= 28  && aux < 36){
                mat[i][j] = 'X'; 
            }else if(aux >= 36 && aux < 44){
                mat[i][j] = 'P'; 
            }else{
                mat[i][j] = '.'; 
            }
        }
    }
        fprintf(arq,"%d %d\n",tam,tam1);
        for(int i=0;i<tam;i++){
            for(int j=0;j<tam1;j++){
            fprintf(arq,"%c",mat[i][j]); 
            }

            fprintf(arq,"\n"); 
        }
        fclose(arq); 
}