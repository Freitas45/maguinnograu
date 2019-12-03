#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char matriz [100][100];
    int linhas;
    int colunas;
    char antes;
}matriz;

typedef struct{
    int vida;
    char tipo;
    int linAtual;
    int colAtual;
    char pos;
}jogadores;


void LeArquivo(matriz mapa[1],FILE* entrada); 
//A funcao escaneia o arquivo,lendo as dimensoes do mapa e o proprio.  
void AbreArquivo(matriz mapa[1]); 
//A funcao abre o arquivo e verifica sua validade, abortando o programa caso o arquivo seja invalido.
void printaMapa(matriz mapa[1],jogadores magos[2]); 
//A funcao printa a matriz mapa, processo que repetimos algumas vezes durante o programa.
int LocaisMagos(matriz mapa[1],jogadores magos[2],int i);
//A funcao printa as informacoes essenciais da rodada, como a posicao atual dos magos e seus respectivos HP's; 
//Alem disso a funcao tambem serve para escanearmos os comandos que serao dados pelos jogadores.Quando escaneados,dentro dessa funcao eh chamada
//A funcao do respectivo comando. 
void identificaPosInicial(matriz mapa[1],jogadores magos[2]);
//A funcao percorre o mapa com intuito de encontrar as coordenadass onde ambos os magos comecaram o jogo. 
void ataque(matriz mapa[1],jogadores magos[2],int i);
//A funcao serve para que os ataques sejam realizados. Dentro dela, sao chamadas outras funcoes correspondentes as interacoes que os 
//ataque de ambos os magos possuem para com o mapa. 
void jogando(matriz mapa[1],jogadores magos[2]);
//A funcao verifica a validade das jogadas e gerencia o jogador da respectiva rodada. 
void interacaoAgua(matriz mapa[1],jogadores magos[2],int linha,int coluna);
//A funcao tem o intuito de modificar o mapa de acordo com as interacoes entre os ataques do mago de agua e os terrenos atingidos por ele. 
void interacaoFogo(matriz mapa[1],jogadores magos[2],int linha,int coluna);
//A funcao tem o intuito de modificar o mapa de acordo com as interacoes entre os ataques do mago de fogo e os terrenos atingidos por ele.
void direita(matriz mapa[1],jogadores magos[2],int i,int mov);
//A funcao serve para que os magos possam se movimentar na direcao que da nome a funcao.
void esquerda(matriz mapa[1],jogadores magos[2],int i,int mov);
//A funcao serve para que os magos possam se movimentar na direcao que da nome a funcao.
void frente(matriz mapa[1],jogadores magos[2],int i,int mov);
//A funcao serve para que os magos possam se movimentar na direcao que da nome a funcao.
void tras(matriz mapa[1],jogadores magos[2],int i,int mov);
//A funcao serve para que os magos possam se movimentar na direcao que da nome a funcao.
void apagaFogo(matriz mapa[1],jogadores magos[2],int i,int linha,int coluna);
//A funcao esta relacionada ao momento onde o mago pode vir a cruzar um terreno com um elemento, onde ele pode perder vida, caso seja
//o elemento do mago adversario, ou não, caso seja o seu elemento. 
void queimaAgua(matriz mapa[1],jogadores magos[2],int i, int linha,int coluna);
//A funcao esta relacionada ao momento onde o mago pode vir a cruzar um terreno com um elemento, onde ele pode perder vida, caso seja
//o elemento do mago adversario, ou não, caso seja o seu elemento.
void ganhador(matriz mapa[1],jogadores magos[2],int i);
//A funcao verifica se ocorreu a vitoria de algum dos jogadores ou o empate de ambos e encerra o jogo caso ocorra.
void parouErrado(matriz mapa[1],jogadores magos[2],int i);
//A funcao verifica tantos as possibilidades dos magos perderem por terminarem a rodada em cima de um terreno fatal
//como tambem verifica as possibilidades do masgos ganharem por terminarem a rodada em cima de sua reliquia. 
void encuralado(matriz mapa[1],jogadores magos[2],int i);
//A funcao verifica a posicao do mago,e em um caso onde ele se encontra incapacitado de fazer movimentos, ele perde. 
void tempo(matriz mapa[1],jogadores magos[2],int i){
    FILE *saida;
    saida = fopen("saida.txt","a");
    int l,k;
    for(l = 0; l < mapa[0].linhas;l++){
        for(k = 0; k < mapa[0].colunas;k++){
            fprintf(saida,"%c",mapa[0].matriz[l][k]);
        }
        fprintf(saida,"\n");
    }
    fprintf(saida,"\n");
    fprintf(saida,"Jogador da vez: %c\n",magos[i].tipo);
    if(magos[1].pos !='.' && magos[1].pos !='f'){
    fprintf(saida,"%c: %c\n",magos[1].tipo,magos[1].pos );
    }else{
        fprintf(saida,"%c: .\n",magos[1].tipo);
    }
    if(magos[0].pos != '.' && magos[0].pos !='a'){
    fprintf(saida,"%c: %c\n",magos[0].tipo,magos[0].pos );
    }else{
        fprintf(saida,"%c: .\n",magos[0].tipo);
    }
    fprintf(saida,"Vida %c: %d\n",magos[1].tipo,magos[1].vida);
    fprintf(saida,"Vida %c: %d\n",magos[0].tipo,magos[0].vida);

    fprintf(saida,"\nComando:\n\n\n");
    fclose(saida);
}
void Ocomando(char comando[],int mov){
    FILE *comandos;
    comandos = fopen("comandos.txt","a");
    int qnt = 0;
    qnt = mov;
    if(qnt == 0){
        fprintf(comandos,"%s\n",comando);
    }else{
        fprintf(comandos,"%s %d\n",comando,qnt);
    }
    fclose(comandos);
}

void saida(matriz mapa[1],jogadores magos[2],int i,char comando[],int mov){
    FILE *all;
    all = fopen("all.txt","a");
    int l,k;
    for(l = 0; l < mapa[0].linhas;l++){
        for(k = 0; k < mapa[0].colunas;k++){
            fprintf(all,"%c",mapa[0].matriz[l][k]);
        }
        fprintf(all,"\n");
    }
    fprintf(all,"\n");
    fprintf(all,"Jogador da vez: %c\n",magos[i].tipo);
    if(magos[1].pos !='.' && magos[1].pos !='f'){
    fprintf(all,"%c: %c\n",magos[1].tipo,magos[1].pos );
    }else{
        fprintf(all,"%c: .\n",magos[1].tipo);
    }
    if(magos[0].pos != '.' && magos[0].pos !='a'){
    fprintf(all,"%c: %c\n",magos[0].tipo,magos[0].pos );
    }else{
        fprintf(all,"%c: .\n",magos[0].tipo);
    }
    fprintf(all,"Vida %c: %d\n",magos[1].tipo,magos[1].vida);
    fprintf(all,"Vida %c: %d\n",magos[0].tipo,magos[0].vida);

    fprintf(all,"\nComando: ");
    int qnt = 0;
    qnt = mov;
    if(qnt == 0){
        fprintf(all,"%s\n\n\n",comando);
    }else{
        fprintf(all,"%s %d\n\n\n",comando,qnt);
    }
    fclose(all);
}


int main(int argc, char** argv){
    matriz mapa[1];
    jogadores magos[2];
    magos[1].tipo = 'f';
    magos[0].tipo = 'a';
    magos[0].vida = 30;
    magos[1].vida = 30;
    magos[0].pos = '.';
    magos[1].pos = '.';
    AbreArquivo(mapa);
    identificaPosInicial(mapa,magos);
    jogando(mapa,magos);
    return 0;
}

//A funcao abre o arquivo e verifica sua validade, abortando o programa caso o arquivo seja invalido.
void AbreArquivo(matriz mapa[1]){
    FILE *entrada;
    entrada = fopen("entrada.txt","r");
    if(entrada != NULL){
       LeArquivo(mapa,entrada);
    }else{
        printf("Problema na abertura do arquivo!\n");
        exit(1);
    }
}

//A funcao escaneia o arquivo,lendo as dimensoes do mapa e o proprio.
void LeArquivo(matriz mapa[1],FILE* entrada){
    int i, k;
    fscanf(entrada,"%d %d\n",&mapa[0].linhas,&mapa[0].colunas);
    for(i = 0; i< mapa[0].linhas;i++){
        fscanf(entrada,"%s",mapa[0].matriz[i]);  
    }
}

//A funcao printa a matriz mapa, processo que repetimos algumas vezes durante o programa.
void printaMapa(matriz mapa[1],jogadores magos[2]){
    int i,k;
    for(i = 0; i < mapa[0].linhas;i++){
        for(k = 0; k < mapa[0].colunas;k++){
            printf("%c",mapa[0].matriz[i][k]);
        }
        printf("\n");
    }
    printf("\n");

}

//A funcao printa as informacoes essenciais da rodada, como a posicao atual dos magos e seus respectivos HP's; 
//Alem disso a funcao tambem serve para escanearmos os comandos que serao dados pelos jogadores.Quando escaneados,dentro dessa funcao eh chamada
//A funcao do respectivo comando.
int LocaisMagos(matriz mapa[1],jogadores magos[2],int i){
    char comando[15];
    int mov = 0;
    int k = 0;
    int l = 0;
    printaMapa(mapa,magos);
    printf("Jogador da vez:%c\n",magos[i].tipo);
    if(magos[1].pos !='.' && magos[1].pos !='f'){
    printf("%c: %c\n",magos[1].tipo,magos[1].pos );
    }else{
        printf("%c: .\n",magos[1].tipo);
    }
    if(magos[0].pos != '.' && magos[0].pos !='a'){
    printf("%c: %c\n",magos[0].tipo,magos[0].pos);
    }else{
        printf("%c: .\n",magos[0].tipo);
    }
    printf("Vida %c: %d\n",magos[1].tipo,magos[1].vida);
    printf("Vida %c: %d\n",magos[0].tipo,magos[0].vida);

    printf("Comando: ");
    
    scanf("%s[^' ']",comando);
    k = strcmp(comando,"ataque");
    if(k == 0){
        Ocomando(comando,mov);
        saida(mapa,magos,i,comando,mov);
        ataque(mapa,magos,i);
        return 0;
    }
    k = strcmp(comando,"direita");
    if(k == 0){
        scanf("%d",&mov);
        saida(mapa,magos,i,comando,mov);
        Ocomando(comando,mov);
        direita(mapa,magos,i,mov);
        return 0;
    }
    k = strcmp(comando,"esquerda");
    if(k == 0){
        scanf("%d",&mov);
        Ocomando(comando,mov);
        saida(mapa,magos,i,comando,mov);
        esquerda(mapa,magos,i,mov);
        return 0;
    }
    k = strcmp(comando,"frente");
    if(k == 0){
        scanf("%d",&mov);
        Ocomando(comando,mov);
        saida(mapa,magos,i,comando,mov);
        frente(mapa,magos,i,mov);
        return 0;
    }
    k = strcmp(comando,"tras");
    if(k == 0){
        scanf("%d",&mov);
        Ocomando(comando,mov);
        saida(mapa,magos,i,comando,mov);
        tras(mapa,magos,i,mov);
        return 0;
    }
    if(k != 0){
        return 3;
    }
    return 0;
}

//A funcao percorre o mapa com intuito de encontrar as coordenadass onde ambos os magos comecaram o jogo.
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

//A funcao serve para que os ataques sejam realizados. Dentro dela, sao chamadas outras funcoes correspondentes as interacoes que os 
//ataque de ambos os magos possuem para com o mapa.
void ataque(matriz mapa[1],jogadores magos[2],int i){
    int linha = magos[i].linAtual;
    int coluna = magos[i].colAtual;
    if(i == 0){
        while(linha >= 0){
            if(mapa[0].matriz[linha][coluna] != '.' && mapa[0].matriz[linha][coluna] != 'f' && mapa[0].matriz[linha][coluna] != '*' && mapa[0].matriz[linha][coluna] != 'F' && mapa[0].matriz[linha][coluna] != '$' && mapa[0].matriz[linha][coluna] != 'a'){
                break;
            }
            apagaFogo(mapa,magos,i,linha,coluna);
            linha--;
        }
        if(mapa[0].matriz[linha][coluna] != 'G'){
            interacaoAgua(mapa,magos,linha,coluna);
        }
        linha = magos[i].linAtual;
        while(linha < mapa[0].linhas){
            if(mapa[0].matriz[linha][coluna] != '.' && mapa[0].matriz[linha][coluna] != 'f' && mapa[0].matriz[linha][coluna] != '*' && mapa[0].matriz[linha][coluna] != 'F' && mapa[0].matriz[linha][coluna] != '$' && mapa[0].matriz[linha][coluna] != 'a'){
                break;
            }
            apagaFogo(mapa,magos,i,linha,coluna);
            linha++;
        }
        if(mapa[0].matriz[linha][coluna] != 'G'){
            interacaoAgua(mapa,magos,linha,coluna);
        }
        linha = magos[i].linAtual;
        coluna = magos[i].colAtual;
        while(coluna >= 0){
            if(mapa[0].matriz[linha][coluna] != '.' && mapa[0].matriz[linha][coluna] != 'f' && mapa[0].matriz[linha][coluna] != '*' && mapa[0].matriz[linha][coluna] != 'F' && mapa[0].matriz[linha][coluna] != '$' && mapa[0].matriz[linha][coluna] != 'a'){
                break;
            }
            apagaFogo(mapa,magos,i,linha,coluna);
            coluna--;
        }
        if(mapa[0].matriz[linha][coluna] != 'G'){
            interacaoAgua(mapa,magos,linha,coluna);
        }
        coluna = magos[i].colAtual;
        while(coluna <= mapa[0].colunas){
            if(mapa[0].matriz[linha][coluna] != '.' && mapa[0].matriz[linha][coluna] != 'f' && mapa[0].matriz[linha][coluna] != '*' && mapa[0].matriz[linha][coluna] != 'F' && mapa[0].matriz[linha][coluna] != '$' && mapa[0].matriz[linha][coluna] != 'a'){
                break;
            }
            apagaFogo(mapa,magos,i,linha,coluna);
            coluna++;
        }
        if(mapa[0].matriz[linha][coluna] != 'G'){
            interacaoAgua(mapa,magos,linha,coluna);
        }
    }
    else{
        while(linha < mapa[0].linhas){
            if(mapa[0].matriz[linha][coluna] != '.' && mapa[0].matriz[linha][coluna] != 'a' && mapa[0].matriz[linha][coluna] != 'F' && mapa[0].matriz[linha][coluna] != '*' && mapa[0].matriz[linha][coluna] != '$' && mapa[0].matriz[linha][coluna] != 'f' && mapa[0].matriz[linha][coluna] != 'A'){
                break;
            }
            queimaAgua(mapa,magos,i,linha,coluna);
            linha++;
        }
        interacaoFogo(mapa,magos,linha,coluna);
        linha = magos[i].linAtual;
        coluna = magos[i].colAtual;
        while(coluna >= 0){
            if(mapa[0].matriz[linha][coluna] != '.' && mapa[0].matriz[linha][coluna] != 'a' && mapa[0].matriz[linha][coluna] != 'F' && mapa[0].matriz[linha][coluna] != '*' && mapa[0].matriz[linha][coluna] != '$' && mapa[0].matriz[linha][coluna] != 'f' && mapa[0].matriz[linha][coluna] != 'A'){
                break;
            }
            queimaAgua(mapa,magos,i,linha,coluna);
            coluna--;
        }
        interacaoFogo(mapa,magos,linha,coluna);
        coluna = magos[i].colAtual;
        while(coluna <= mapa[0].colunas){
            if(mapa[0].matriz[linha][coluna] != '.' && mapa[0].matriz[linha][coluna] != 'a' && mapa[0].matriz[linha][coluna] != 'F' && mapa[0].matriz[linha][coluna] != '*' && mapa[0].matriz[linha][coluna] != '$' && mapa[0].matriz[linha][coluna] != 'f' && mapa[0].matriz[linha][coluna] != 'A'){
                break;
            }
            queimaAgua(mapa,magos,i,linha,coluna);
            coluna++;
        }
        interacaoFogo(mapa,magos,linha,coluna);
        linha = magos[i].linAtual;
        coluna = magos[i].colAtual;
        while(linha >= 0){
            if(mapa[0].matriz[linha][coluna] != '.' && mapa[0].matriz[linha][coluna] != 'a' && mapa[0].matriz[linha][coluna] != 'F' && mapa[0].matriz[linha][coluna] != '*' && mapa[0].matriz[linha][coluna] != '$' && mapa[0].matriz[linha][coluna] != 'f' && mapa[0].matriz[linha][coluna] != 'A'){
                break;
            }
            queimaAgua(mapa,magos,i,linha,coluna);
            linha--;
        }
        interacaoFogo(mapa,magos,linha,coluna);
    }
        
}

void jogando(matriz mapa[1],jogadores magos[2]){
    int i = 1, k = 0;
    int acabou = 0;
    while(acabou != 1){
        tempo(mapa,magos,i);
        acabou = LocaisMagos(mapa,magos,i);
        k++;
        if(acabou == 3){
            k--;
            printf("Jogada Invalida\n");
        }
        if(k%2 == 0){
            i = 1;
        }else{
            i = 0;
        }
        encuralado(mapa,magos,i);
    }
}

//A funcao esta relacionada ao momento onde o mago pode vir a cruzar um terreno com um elemento, onde ele pode perder vida, caso seja
//o elemento do mago adversario, ou não, caso seja o seu elemento. 
void apagaFogo(matriz mapa[1],jogadores magos[2],int i, int linha,int coluna){
    if(mapa[0].matriz[linha][coluna] == 'f'){
                magos[1].vida -= 10;
                if(magos[1].pos == 'F'){
                    magos[1].pos = '.';
                }
            }
            if(mapa[0].matriz[linha][coluna]=='F'){
                mapa[0].matriz[linha][coluna] = '.';
            }
}

//A funcao esta relacionada ao momento onde o mago pode vir a cruzar um terreno com um elemento, onde ele pode perder vida, caso seja
//o elemento do mago adversario, ou não, caso seja o seu elemento.
void queimaAgua(matriz mapa[1],jogadores magos[2],int i,int linha,int coluna){
    if(mapa[0].matriz[linha][coluna] == 'a'){
                magos[0].vida -= 10;
                if(magos[0].pos == 'A'){
                    magos[0].pos = '.';
                }
            }
            if(mapa[0].matriz[linha][coluna]=='A'){
                mapa[0].matriz[linha][coluna] = '.';
            }
}

//A funcao tem o intuito de modificar o mapa de acordo com as interacoes entre os ataques do mago de agua e os terrenos atingidos por ele.
void interacaoAgua(matriz mapa[1],jogadores magos[2],int linha,int coluna){
    int i, k = -1, l = -1, a = 0, f = 0;
    for(k;k<2;k++){
        for(l;l<2;l++){
            if(mapa[0].matriz[linha][coluna] == 'P'){
                if(mapa[0].matriz[linha+k][coluna+l] == '.' || mapa[0].matriz[linha+k][coluna+l] == 'a' || mapa[0].matriz[linha+k][coluna+l] == 'f' && linha + k < mapa[0].linhas && linha + k >= 0 && coluna + l < mapa[0].colunas && coluna + l >= 0){
                    if(mapa[0].matriz[linha+k][coluna+l] == 'f'){
                        if(magos[1].pos == '.'){
                            magos[1].pos = 'P';
                            f++;
                        }     
                    }
                    if(mapa[0].matriz[linha+k][coluna+l] == 'a'){
                        if(magos[0].pos == '.'){
                            magos[0].pos = 'P';
                            a++;
                        }
                    }
                    mapa[0].matriz[linha+k][coluna+l] = 'P'; 
                }
            }
            if(mapa[0].matriz[linha][coluna] == 'A' || mapa[0].matriz[linha][coluna] == 'G' || mapa[0].matriz[linha][coluna] == 'a' ){
                if(mapa[0].matriz[linha+k][coluna+l] == 'a' && linha + k < mapa[0].linhas && linha + k >= 0 && coluna + l < mapa[0].colunas && coluna + l >= 0){
                    if(magos[0].pos == 'A'){
                        i = 1;
                        magos[0].pos = 'G';
                        ganhador(mapa,magos,i);
                    }
                }
                if(mapa[0].matriz[linha+k][coluna+l] == 'A' && linha + k < mapa[0].linhas && linha + k >= 0 && coluna + l < mapa[0].colunas && coluna + l >= 0){
                    mapa[0].matriz[linha+k][coluna+l] = 'G'; 
                }
            }
        }
        l = -1; 
    }
    if(a == 1 && f ==1){
        i = 2;
        ganhador(mapa,magos,i);   
    }else if(a == 1){
        i = 1;
        ganhador(mapa,magos,i);
    }else if(f == 1){
        i = 0;
        ganhador(mapa,magos,i);
    } 
}

//A funcao tem o intuito de modificar o mapa de acordo com as interacoes entre os ataques do mago de fogo e os terrenos atingidos por ele.
void interacaoFogo(matriz mapa[1],jogadores magos[2],int linha,int coluna){
    int i, k = -1, l = -1, f = 0;
    for(k;k<2;k++){
        for(l;l<2;l++){
            if(mapa[0].matriz[linha][coluna] == 'P' || mapa[0].matriz[linha][coluna] == 'F'){
                if(mapa[0].matriz[linha+k][coluna+l] == 'P' && linha + k < mapa[0].linhas && linha + k >= 0 && coluna + l < mapa[0].colunas && coluna + l >= 0){
                    mapa[0].matriz[linha+k][coluna+l] = 'F'; 
                }
            }
            if(mapa[0].matriz[linha][coluna] == 'G' || mapa[0].matriz[linha][coluna] == 'A'){
                if(mapa[0].matriz[linha+k][coluna+l] == 'f'){
                    f++;
                    magos[1].pos = 'A';
                }
                if(mapa[0].matriz[linha+k][coluna+l] == 'a'){
                    magos[0].pos = 'A';
                }
                if(mapa[0].matriz[linha+k][coluna+l] == '.' || mapa[0].matriz[linha+k][coluna+l] == 'G' && linha + k < mapa[0].linhas && linha + k >= 0 && coluna + l < mapa[0].colunas && coluna + l >= 0){
                    mapa[0].matriz[linha+k][coluna+l] = 'A'; 
                }
            }
        }
        l = - 1;
    }
    if(f == 1){
        i = 0;
        ganhador(mapa,magos,i);
    }
}

//A funcao serve para que os magos possam se movimentar na direcao que da nome a funcao.
void direita(matriz mapa[1],jogadores magos[2],int i,int mov){
    int k;
    for(k = 0; k < mov; k++){
        if(i == 0){
            if(magos[i].colAtual + 1 > mapa[0].colunas-1 || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] == 'X' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] == '*' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] == 'G' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] == 'P'){
                break;
            }
        }else{
            if(magos[i].colAtual + 1 > mapa[0].colunas-1 || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] == 'X' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] == '$' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] == 'G' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] == 'P'){
                break;
            }
        }
        mapa[0].antes = magos[i].pos;
        magos[i].pos = mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1];
        mapa[0].matriz[magos[i].linAtual][magos[i].colAtual] = mapa[0].antes;
        mapa[0].matriz[magos[i].linAtual][magos[i].colAtual+1] = magos[i].tipo;
        magos[i].colAtual++;
        if(i == 0 && magos[0].pos == 'F'){
            magos[0].vida -= 10;
        }
        if(i == 1 && magos[1].pos == 'A'){
            magos[1].vida -= 10;
        }
        if(magos[1].vida == 0){
            i = 0;
            ganhador(mapa,magos,i);
        }
        if(magos[0].vida == 0){
            i = 1;
            ganhador(mapa,magos,i);
        }
    }
    parouErrado(mapa,magos,i);
    
}

//A funcao serve para que os magos possam se movimentar na direcao que da nome a funcao.
void esquerda(matriz mapa[1],jogadores magos[2],int i,int mov){
    int k;
    for(k = 0; k < mov; k++){
        if(i == 0){
            if(magos[i].colAtual - 1 < 0 || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] == 'X' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] == '*' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] == 'G' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] == 'P'){
                break;
            }
        }else{
            if(magos[i].colAtual - 1 < 0 || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] == 'X' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] == '$' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] == 'G' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] == 'P'){
                break;
            }
        }
        mapa[0].antes = magos[i].pos;
        magos[i].pos = mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1];
        mapa[0].matriz[magos[i].linAtual][magos[i].colAtual] = mapa[0].antes;
        mapa[0].matriz[magos[i].linAtual][magos[i].colAtual-1] = magos[i].tipo;
        magos[i].colAtual--;
        if(i == 0 && magos[0].pos == 'F'){
            magos[0].vida -= 10;
        }
        if(i == 1 && magos[1].pos == 'A'){
            magos[1].vida -= 10;
        }
        if(magos[1].vida == 0){
            i = 0;
            ganhador(mapa,magos,i);
        }
        if(magos[0].vida == 0){
            i = 1;
            ganhador(mapa,magos,i);
        }
    }
    parouErrado(mapa,magos,i);
}

//A funcao serve para que os magos possam se movimentar na direcao que da nome a funcao.
void frente(matriz mapa[1],jogadores magos[2],int i,int mov){
    int k;
    for(k = 0; k < mov; k++){
        if(i == 0){
            if(magos[i].linAtual - 1 < 0 || mapa[0].matriz[magos[i].linAtual - 1][magos[i].colAtual] == 'X' || mapa[0].matriz[magos[i].linAtual - 1][magos[i].colAtual] == '*' || mapa[0].matriz[magos[i].linAtual - 1][magos[i].colAtual] == 'G' || mapa[0].matriz[magos[i].linAtual - 1][magos[i].colAtual] == 'P'){
                break;
            }
        }else{
            if(magos[i].linAtual - 1 < 0 || mapa[0].matriz[magos[i].linAtual - 1][magos[i].colAtual] == 'X' || mapa[0].matriz[magos[i].linAtual - 1][magos[i].colAtual] == '$' || mapa[0].matriz[magos[i].linAtual - 1][magos[i].colAtual] == 'G' || mapa[0].matriz[magos[i].linAtual - 1][magos[i].colAtual] == 'P'){
                break;
            }
        }
        mapa[0].antes = magos[i].pos;
        magos[i].pos = mapa[0].matriz[magos[i].linAtual-1][magos[i].colAtual];
        mapa[0].matriz[magos[i].linAtual][magos[i].colAtual] = mapa[0].antes;
        mapa[0].matriz[magos[i].linAtual-1][magos[i].colAtual] = magos[i].tipo;
        magos[i].linAtual--;
        if(i == 0 && magos[0].pos == 'F'){
            magos[0].vida -= 10;
        }
        if(i == 1 && magos[1].pos == 'A'){
            magos[1].vida -= 10;
        }
        if(magos[1].vida == 0){
            i = 0;
            ganhador(mapa,magos,i);
        }
        if(magos[0].vida == 0){
            i = 1;
            ganhador(mapa,magos,i);
        }
    }
    parouErrado(mapa,magos,i);
}

//A funcao serve para que os magos possam se movimentar na direcao que da nome a funcao.
void tras(matriz mapa[1],jogadores magos[2],int i,int mov){
    int k;
    for(k = 0; k < mov; k++){
        if(i == 0){
            if(magos[i].linAtual + 1 > mapa[0].colunas - 1 || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'X' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == '*' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'G' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'P'){
                break;
            }
        }else{
            if(magos[i].linAtual + 1 > mapa[0].colunas - 1 || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'X' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == '$' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'G' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'P'){
                break;
            }
        }
        mapa[0].antes = magos[i].pos;
        magos[i].pos = mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual];
        mapa[0].matriz[magos[i].linAtual][magos[i].colAtual] = mapa[0].antes;
        mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] = magos[i].tipo;
        magos[i].linAtual++;
        if(i == 0 && magos[0].pos == 'F'){
            magos[0].vida -= 10;
        }
        if(i == 1 && magos[1].pos == 'A'){
            magos[1].vida -= 10;
        }
        if(magos[1].vida == 0){
            i = 0;
            ganhador(mapa,magos,i);
        }
        if(magos[0].vida == 0){
            i = 1;
            ganhador(mapa,magos,i);
        }
    }
    parouErrado(mapa,magos,i);
}

//A funcao verifica a posicao do mago,e em um caso onde ele se encontra incapacitado de fazer movimentos, ele perde.
void encuralado(matriz mapa[1],jogadores magos[2],int i){
    int impo = 0;
    if(mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'P' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'G' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual] == 'X' || magos[i].linAtual + 1 >= mapa[0].linhas){
        impo++;
    }
    if(mapa[0].matriz[magos[i].linAtual-1][magos[i].colAtual] == 'P' || mapa[0].matriz[magos[i].linAtual-1][magos[i].colAtual] == 'G' || mapa[0].matriz[magos[i].linAtual-1][magos[i].colAtual] == 'X' || magos[i].linAtual -1 < 0){
        impo++;
    }
    if(mapa[0].matriz[magos[i].linAtual][magos[i].colAtual +1] == 'P' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual +1] == 'G' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual +1] == 'X' || magos[i].colAtual +1 >= mapa[0].colunas){
        impo++;
    }
    if(mapa[0].matriz[magos[i].linAtual][magos[i].colAtual - 1] == 'P' || mapa[0].matriz[magos[i].linAtual][magos[i].colAtual - 1] == 'G' || mapa[0].matriz[magos[i].linAtual+1][magos[i].colAtual - 1] == 'X'  || magos[1].colAtual - 1 < 0){
        impo++;
    }
    if(impo == 4){
        if(i == 0){
            i = 1;
            ganhador(mapa,magos,i);
        }else{
            i = 0;
            ganhador(mapa,magos,i);
        }
    }
}

//A funcao verifica tantos as possibilidades dos magos perderem por terminarem a rodada em cima de um terreno fatal
//como tambem verifica as possibilidades do masgos ganharem por terminarem a rodada em cima de sua reliquia.
void parouErrado(matriz mapa[1],jogadores magos[2],int i){
    if(magos[1].pos == 'A'){
        magos[1].vida = 0;
        i = 0;
        ganhador(mapa,magos,i);
    }
    if(magos[0].pos == '$'){
        i = 0;
        ganhador(mapa,magos,i);
    }
    if(magos[1].pos == '*'){
        i = 1;
        ganhador(mapa,magos,i);
    }
    if(magos[0].pos == 'F'){
        magos[0].vida = 0;
        i = 0;
        ganhador(mapa,magos,i);
    }
}

void ganhador(matriz mapa[1],jogadores magos[2],int i){
    printaMapa(mapa,magos);
    printf("Jogador da vez:%c\n",magos[i].tipo);
    if(magos[1].pos !='.' && magos[1].pos !='f'){
    printf("%c: %c\n",magos[1].tipo,magos[1].pos );
    }else{
        printf("%c: .\n",magos[1].tipo);
    }
    if(magos[0].pos != '.' && magos[0].pos !='a'){
    printf("%c: %c\n",magos[0].tipo,magos[0].pos );
    }else{
        printf("%c: .\n",magos[0].tipo);
    }
    printf("Vida %c: %d\n",magos[1].tipo,magos[1].vida);
    printf("Vida %c: %d\n",magos[0].tipo,magos[0].vida);
    if(i == 0){
        printf("O mago da agua venceu!");
    }else if (i == 1){
        printf("O mago do fogo venceu!");
    }else{
        printf("Empate");
    }
    exit(1);
}