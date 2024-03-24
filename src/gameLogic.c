#include "gameLogic.h"
#include <stdio.h>
#include <stdlib.h>
#include "fila_dinamica.h"
#include <time.h>

int msgIni(){

    // Selecionando o Numero de Jogadores
        int numPlayers = 2;
        do {
            printf(" 1.@                                                                  \n");
            printf(" 1 #@#          .::@@@@-           *+                                 \n");
            printf(" 1  *@@@#-  -=-:    -+# +@+          #@.                              \n");
            printf(" 1    .@@@@@@@@@           :@*         @@-                            \n");
            printf(" 1       *@@@@@@-             #@#+.  :@@@@                            \n");
            printf(" 1      =@  .-##   :*           . @@@@@@@*                            \n");
            printf(" 1   .@-       -#@-             :@@@@@@                               \n");
            printf(" 1  +@      *#       @@@.        @@                                   \n");
            printf(" 1 @@       #         @ +@       @=                                   \n");
            printf(" 1  =@@    ::     :    @@@@     .@#                                   \n");
            printf(" 1    #@.   =     #        .      =@                                  \n");
            printf(" 1     :@.  =     @        =       :@-                                \n");
            printf(" 1       @# :=   =@              +*.:@@#                              \n");
            printf(" 1         -@#=   :#.          *-       @=                            \n");
            printf(" 1           +@@+       :   +:  -@  *@.-@.                            \n");
            printf(" 1             : -*@@@#=:  ##  =  @:  .-@                             \n");
            printf(" 1                       -#@@   :     -@                              \n");
            printf(" 1                          @@@@@@@@@@#                               \n");
            printf("========================================\n");
            if (numPlayers < 2 || numPlayers > 10)
                printf("|           Selecione Novamente        |\n");
            printf("|           Quantos Jogadores?         |\n");
            printf("========================================\n");
            scanf("%i",&numPlayers);
        } while (numPlayers < 2 || numPlayers > 10);
        return numPlayers;
};

void iniGame(Lista* baralhoJogadores[],Pilha* monteCartas, int numPlayers, Lista* pontosJogadores[]){
    // Declaração de Variaveis
            int cartasInicias = 10; /* Numero de Cartas a serem puxadas no Inicio */
            Carta carta;
    // Inicialização do Jogo
            for (int i = 0; i < numPlayers; i++){
                baralhoJogadores[i] = listaCriar();
                pontosJogadores[i] = listaCriar();
            }
            for (int i = 0; i < numPlayers ; i++){
                for (int j = 0; j < cartasInicias; j++){
                    pilhaRemover(monteCartas, &carta);
                    inserirOrdenado(baralhoJogadores[i], carta);
                }
            }
};
void iniMesa(Fila** mesa, Pilha* monteCartas, int numMesa){
        for (int i = 0; i < numMesa; i++)
            mesa[i] = filaCriar();
        Carta *cartaPtr = (Carta*)malloc(sizeof(Carta));
        for (int i = 0; i < numMesa ; i++){
                pilhaRemover(monteCartas, cartaPtr);
                Carta puxada = *cartaPtr;
                filaInserir(mesa[i], puxada);
        }
        free(cartaPtr);
};
void printMesa(struct fila **mesa, int numMesa){
    numMesa = 4;
    for (int i = 0; i < numMesa; i++){
         filaExibir(mesa[i]);
         printf("\n");
    }
    return;
};
void printMao(struct lista** baralhoJogadores){
    printf("Your Colection:\nHand:");
    exibir(baralhoJogadores[0]);
};
void insertMesa(Fila** mesa, Carta* cartaPtr, int numMesa, int isPlayer, Lista* pontosJogadores){
    int insert = -1, selec = 104, tam;
    Carta cartaAux = *cartaPtr;
    for (int i = 0; i < numMesa; i++){
        filaAcessar(mesa[i],cartaPtr);
        int dif = abs(cartaAux.num - cartaPtr->num);
        if(dif < selec && cartaAux.num > cartaPtr->num){
            selec = dif;
            insert = i;
            tam = filaTamanho(mesa[i]);
        }
    }
    if(insert != -1){
        if (tam == 5){
            for(int i = 0; i < tam; i++){
                filaRemover(mesa[insert],cartaPtr);
                inserirOrdenado(pontosJogadores, *cartaPtr);
            }
        }
        if (mesa)
            filaInserir(mesa[insert], cartaAux);
        return;
    }
    if (isPlayer){
    do{
        printf("========================================\n");
        printf("|           Qual Fila puxar  ?         |\n");
        printf("========================================\n");
        scanf("%i",&insert);
    } while (insert < 1|| insert > 4);
    insert--;
    }else{
        insert = (rand() % 4);
    }
    // FALTA AS VERIFICAções
    tam = filaTamanho(mesa[insert]);
    for(int i = 0; i < tam; i++){
        filaRemover(mesa[insert],cartaPtr);
        inserirOrdenado(pontosJogadores, *cartaPtr);
    }
    filaInserir(mesa[insert], cartaAux);
};
void loopGame(Lista** baralhoJogadores, Pilha* monteCartas, Fila** mesa, int numMesa, int numPlayers, Lista** pontosJogadores){
     // Round Logic
    srand(time(NULL));
    int selec, isPlayer;
    Carta *cartaPtr = (Carta*)malloc(sizeof(Carta));
    Lista *ordemCartas = listaCriar();
    for (int i = 0; i < 10; i++){
        isPlayer = 1;
        // Printing
        printMesa(mesa, numMesa);
        printMao(baralhoJogadores);

        // Rounds
            // Player Choice
            selec = 0;
            do{
                printf("\n");
                printf("========================================\n");
                printf("|           Qual carta jogar ?         |\n");
                printf("========================================\n");
                scanf("%i",&selec);
            }while (selec < 1 || selec > 10);
            selec--;
            // Player
                acessarIndice(baralhoJogadores[0],selec,cartaPtr);
                cartaPtr->player = 0;
                removerIndince(baralhoJogadores[0],selec);
                inserirOrdenado(ordemCartas,*cartaPtr);
                insertMesa(mesa,cartaPtr,numMesa,isPlayer,pontosJogadores[0]);
                printf("========================================\n");
                printf("|           Mesa apos jogadas          |\n");
                printf("========================================\n");
            // Bots
                isPlayer = 0;
                for (int i = 1; i < numPlayers; i++){
                        selec = (rand() % 10) + 1 - i;
                        acessarIndice(baralhoJogadores[i],selec,cartaPtr);
                        cartaPtr->player = i;
                        inserirOrdenado(ordemCartas,*cartaPtr);
                        removerIndince(baralhoJogadores[i],selec);
                        insertMesa(mesa,cartaPtr,numMesa,isPlayer,pontosJogadores[i]);
                }

    }
};

void endGame(Lista** pontosJogadores, int numPlayers){
    for (int i = 0; i < numPlayers; i++){
        exibir(pontosJogadores[i]);
    }
}
