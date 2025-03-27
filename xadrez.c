#include <stdio.h>

// Desafio de Xadrez - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de movimentação das peças de xadrez.
// O objetivo é utilizar estruturas de repetição e funções para determinar os limites de movimentação dentro do jogo.


// Função recursiva para o movimento da Torre
void moverTorre(int casasRestantes) {
    if (casasRestantes <= 0) {
        return; // Condição de parada
    }
    printf("Direita\n"); // Movimento da Torre para a direita
    moverTorre(casasRestantes - 1); // Chamada recursiva
}

// Função recursiva para o movimento do Bispo
void moverBispo(int casasRestantes) {
    if (casasRestantes <= 0) {
        return; // Condição de parada
    }
    printf("Cima Direita\n"); // Movimento diagonal do Bispo
    moverBispo(casasRestantes - 1); // Chamada recursiva
}

// Função recursiva para o movimento da Rainha
void moverRainha(int casasRestantes) {
    if (casasRestantes <= 0) {
        return; // Condição de parada
    }
    printf("Esquerda\n"); // Movimento da Rainha para a esquerda
    moverRainha(casasRestantes - 1); // Chamada recursiva
}

int main() {
    // Movimento da Torre usando recursividade
    printf("Movimento da Torre:\n");
    int torre_movimentos = 5; // Número de casas que a Torre irá se mover
    moverTorre(torre_movimentos);
    printf("\n");

    // Movimento do Bispo usando recursividade e loops aninhados
    printf("Movimento do Bispo:\n");
    int bispo_movimentos = 5; // Número de casas que o Bispo irá se mover
    for (int i = 1; i <= bispo_movimentos; i++) { // Loop externo: vertical
        for (int j = 1; j <= bispo_movimentos; j++) { // Loop interno: horizontal
            if (i == j) { // Garante que o movimento seja diagonal
                printf("Cima Direita\n");
            }
        }
    }
    printf("\n");

    // Movimento da Rainha usando recursividade
    printf("Movimento da Rainha:\n");
    int rainha_movimentos = 8; // Número de casas que a Rainha irá se mover
    moverRainha(rainha_movimentos);
    printf("\n");

    // Movimento do Cavalo usando loops aninhados complexos
    printf("Movimento do Cavalo:\n");
    int cavalo_movimentos_vertical = 2; // Número de casas para cima
    int cavalo_movimentos_horizontal = 1; // Número de casas para a direita

    for (int i = 1; i <= cavalo_movimentos_vertical; i++) {
        if (i > cavalo_movimentos_vertical) break; // Condição de parada
        printf("Cima\n"); // Movimento do Cavalo para cima
    }

    for (int j = 1; j <= cavalo_movimentos_horizontal; j++) {
        if (j > cavalo_movimentos_horizontal) break; // Condição de parada
        printf("Direita\n"); // Movimento do Cavalo para a direita
    }
    printf("\n");

    return 0;
}