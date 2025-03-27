#include <stdio.h>

// Desafio de Xadrez - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de movimentação das peças de xadrez.
// O objetivo é utilizar estruturas de repetição e funções para determinar os limites de movimentação dentro do jogo.


int main() {
    // Simulação do movimento da Torre usando FOR
    printf("Movimento da Torre:\n");
    int torre_movimentos = 5; // Número de casas que a Torre irá se mover
    for (int i = 1; i <= torre_movimentos; i++) {
        printf("Direita\n"); // A Torre se move para a direita
    }
    printf("\n");

    // Simulação do movimento do Bispo usando WHILE
    printf("Movimento do Bispo:\n");
    int bispo_movimentos = 5; // Número de casas que o Bispo irá se mover
    int contador_bispo = 1;   // Contador para controlar o loop
    while (contador_bispo <= bispo_movimentos) {
        printf("Cima Direita\n"); // O Bispo se move na diagonal para cima e à direita
        contador_bispo++;
    }
    printf("\n");

    // Simulação do movimento da Rainha usando DO-WHILE
    printf("Movimento da Rainha:\n");
    int rainha_movimentos = 8; // Número de casas que a Rainha irá se mover
    int contador_rainha = 1;   // Contador para controlar o loop
    do {
        printf("Esquerda\n"); // A Rainha se move para a esquerda
        contador_rainha++;
    } while (contador_rainha <= rainha_movimentos);
    printf("\n");

    // Simulação do movimento do Cavalo usando loops aninhados
    printf("Movimento do Cavalo:\n");
    int cavalo_movimentos_vertical = 2; // Número de casas que o Cavalo se move para baixo
    int cavalo_movimentos_horizontal = 1; // Número de casas que o Cavalo se move para a esquerda

    // Loop externo: Movimento vertical (Baixo)
    for (int i = 1; i <= cavalo_movimentos_vertical; i++) {
        printf("Baixo\n"); // O Cavalo se move duas casas para baixo
    }

    // Loop interno: Movimento horizontal (Esquerda)
    int contador_cavalo_horizontal = 1;
    while (contador_cavalo_horizontal <= cavalo_movimentos_horizontal) {
        printf("Esquerda\n"); // O Cavalo se move uma casa para a esquerda
        contador_cavalo_horizontal++;
    }

    return 0;
}