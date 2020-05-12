#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<stdbool.h>

typedef struct Lista{
    int heuristica;
    int **matriz;
    struct Lista *prox;
}Lista;



int **criaMatrizSolucao(int **MS){ //Cria a matriz final, ou seja, a matriz a qual o programa deve chegar
    MS=(int**)malloc(3* sizeof(int*)); //alocando memoria para  a matriz solucao
    int x,y,cont;
    cont=0;
    for(x=0;x<3;x++){//Criando matriz
        MS[x]=(int*)malloc(3*sizeof(int)); //alocando memoria para  a matriz solucao
    }
    for(x=0;x<3;x++){ //Inserindo valores na matriz

        for(y=0;y<3;y++){
            MS[x][y]=cont;
            cont++; //cont mudando de valor ate 8, para chegar a matriz desejada
        }
    }
    return MS; //retornando a matriz
}


void imprimeMatriz(int **C){//imprime matriz
    printf("\n \n");
    int x,y;
    for(x=0;x<3;x++){//x  linha
        for(y=0;y<3;y++){//y coluna
            printf("%d ", C[x][y]);//print numero que esta nessa posicao
        }
        printf("\n");
    }
}

int verifica(int num, int **M){//Verifica se o numero ja existe na matriz
    int x, y;
   for(x = 0; x < 3; x++){
        for(y = 0; y < 3; y++){ //percorrendo os valores da matriz
            if(num == M[x][y]){
               return 0; //caso encontre o valor na matriz, retorna 0
            }
        }
    }
    return 1; // caso nao encontre o valor na matriz, retorna 1
}

int **criaMatrizRandom(int **M){//Gera matriz randomica(Matriz a ser solucionada)
    M=(int**)malloc(3* sizeof(int*)); //alocando espaço de memoria na matriz
    int x,y,z=0; // variaveis utilizadas para percorrer a matriz
    for(x=0;x<3;x++){
        M[x]=(int*)malloc(3*sizeof(int)); //alocando espaço de memoria na matriz
    }

    int num,num2 ;
    srand(time(NULL)); //função para a raiz nunca ser igual

    for(x=0;x<3;x++){
        for(y=0;y<3;y++){
            num = rand()%8;  //gerando um numero aleatorio de 0 a 8
            while(verifica(num,M) == 0 ){//Chama a funcao verifica, para saber se o numero ja existe, se existir,gera outro numero
                num = rand()%10;

               
            }   
             // atribui o numero aleatorio na matriz
            M[x][y] = num;
        }
    }

    for(x=0;x<3;x++){
        for(y=0;y<3;y++){
            if(M[x][y] == 9){
                M[x][y] = 0;

            }
        }
    }


    return M; // retorna a matriz randomica
}

int calcAestrela(int **MR, int **MS){ //Calcula a distancia da peca para sua posicao final em linha reta
    int x,y,z=0;
    int manhattan = 0,g=0,soma=0,i,j,k,l;

    
    while(z != 9){
        for(x=0;x<3;x++){
            for(y=0;y<3;y++){//Pega as coordenadas da peca na matriz a ser solucionada
                if(MR[x][y] == z){
                    i = x; //guarda a posica x em i
                    j = y; // guarda a posicao y em j
                }
            }
        }
   
        for(x=0;x<3;x++){
            for(y=0;y<3;y++){//Pega as coordenadas da peca na matriz solucao
                if(MS[x][y] == z){
                    k = x; //guarda a posicao x em k
                    l = y; //guarda a posica y em l
                }
            }
        }   
        manhattan = fabs(k-i)+ fabs(l-j);
        if(manhattan != 0){
            g++;
        }
        soma += manhattan;
        //printf(" numero %d Valor da dist %d \n",z,manhattan); 
        z++;
    }
    
    soma += g;
     //Calcula a distancia da peca em linha reta, pegando a coordenada x da matriz solucao e randomica
                                // e pegando a coordenada y da matriz soluca e randomica, elevando ao quadrado as duas
                                // pela funcao "fabs" e assim gerando a distancia
    
    return soma; // retornando a distancia

}

Lista *insereInicio(int heuristicaEstrela, Lista *L, int **M){
   if(L == NULL){
       L = (Lista*) malloc(sizeof(Lista));
       L->heuristica = heuristicaEstrela;
       L->matriz = M;
       L->prox =NULL;
       return L;
    }else{
        Lista *novo;
        novo = (Lista*) malloc(sizeof(Lista));
        novo->heuristica = heuristicaEstrela;
        novo->matriz;
        novo->prox = L;
        return novo;
    }
}


void imprime(Lista *L){
    Lista *aux =L;
    Lista *aux2 = L;
    while(aux != NULL){
        imprimeMatriz(aux->matriz);
        aux = aux->prox;
    }
    aux = aux2;
}

int procuraListaAbertos(Lista *Abertos){
    
}

int **move(int **MR, Lista *Fechados){
    int i=0,j=0,x=0,y=0,auxX = 0,auxY = 0;

    for(i = 0; i<3;i++){
        for(j=0;j<3;j++){
            if(MR[i][j] == 0){
                x = i;
                y = j;
            }
        }
    }

    if(x == 0 && y == 0 ){
        int **NM1, **NM2;   //NM = New matriz 

        for(i=0;i<3;i++){
            NM1[i] = (int*) malloc(3*sizeof(int)); //alocando uma matriz
            NM2[i] = (int*) malloc(3*sizeof(int));//alocando uma matriz
        }

        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                NM1[i][j] = MR[i][j]; //deixando a matriz alocada com mesmo valor de M
                NM2[i][j] = MR[i][j];
            }
        }
        auxX = NM1[x][y];
        NM1[x][y] = NM1[x+1][j];
        NM1[x+1][j] = auxX;

        auxY=NM1[x][y];
        NM2[x][y] = NM1[x][j+1];
        NM1[x][j+1] = auxY;

    }
}

int main(){
    int **MS;
    int **MR;
    int **MT;
    int x=0;
    MS = criaMatrizSolucao(MS);
    MR =  criaMatrizRandom(MR);
    
    imprimeMatriz(MR);
    imprimeMatriz(MS);

    MT = (int**)malloc(3*sizeof(int*));
    for(x=0;x<3;x++){
        MT[x]=(int*)malloc(3*sizeof(int)); //alocando espaço de memoria na matriz
    }

    Lista *Abertos = NULL; 
    Lista *Fechados = NULL;

    Abertos = insereInicio(calcAestrela(MR,MS),Abertos,MT);
    imprime(Abertos);
    printf("cabo");

}