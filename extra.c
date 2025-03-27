#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 8

// Estrutura para representar uma peça
typedef struct {
    char nome[3]; // Nome da peça (ex: "P1", "T1")
    char tipo;    // Tipo da peça ('P' = Peão, 'T' = Torre, etc.)
    int x, y;     // Posição no tabuleiro
    char cor;     // Cor da peça ('B' = Branca, 'P' = Preta)
} Peca;

// Função para inicializar o tabuleiro
void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Peca pecas[]) {
    // Limpar o tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = '.';
        }
    }

    // Colocar as peças no tabuleiro
    for (int i = 0; i < 32; i++) { // 32 peças no total
        if (pecas[i].tipo != '\0') {
            tabuleiro[pecas[i].x][pecas[i].y] = pecas[i].nome[0];
        }
    }
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n   A B C D E F G H\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %c", tabuleiro[i][j]);
        }
        printf(" %d\n", 8 - i);
    }
    printf("   A B C D E F G H\n\n");
}

// Função para validar o movimento de uma peça
int validarMovimento(Peca *peca, int nova_x, int nova_y, Peca pecas[]) {
    // Verificar se a nova posição está dentro do tabuleiro
    if (nova_x < 0 || nova_x >= TAMANHO_TABULEIRO || nova_y < 0 || nova_y >= TAMANHO_TABULEIRO) {
        return 0;
    }

    // Regras específicas para cada tipo de peça
    switch (peca->tipo) {
        case 'P': // Peão
            if (peca->cor == 'B') { // Peão branco
                if (peca->x == 6 && nova_x == 4 && peca->y == nova_y) { // Primeiro movimento do Peão
                    return 1;
                }
                if (nova_x == peca->x - 1 && nova_y == peca->y) { // Movimento normal do Peão
                    return 1;
                }
                if (nova_x == peca->x - 1 && abs(nova_y - peca->y) == 1) { // Captura diagonal
                    return 1;
                }
            } else { // Peão preto
                if (peca->x == 1 && nova_x == 3 && peca->y == nova_y) { // Primeiro movimento do Peão
                    return 1;
                }
                if (nova_x == peca->x + 1 && nova_y == peca->y) { // Movimento normal do Peão
                    return 1;
                }
                if (nova_x == peca->x + 1 && abs(nova_y - peca->y) == 1) { // Captura diagonal
                    return 1;
                }
            }
            break;

        case 'T': // Torre
            if (nova_x == peca->x || nova_y == peca->y) { // Movimento horizontal ou vertical
                return 1;
            }
            break;

        case 'C': // Cavalo
            if ((abs(nova_x - peca->x) == 2 && abs(nova_y - peca->y) == 1) ||
                (abs(nova_x - peca->x) == 1 && abs(nova_y - peca->y) == 2)) {
                return 1;
            }
            break;

        case 'B': // Bispo
            if (abs(nova_x - peca->x) == abs(nova_y - peca->y)) { // Movimento diagonal
                return 1;
            }
            break;

        case 'Q': // Rainha
            if (nova_x == peca->x || nova_y == peca->y || abs(nova_x - peca->x) == abs(nova_y - peca->y)) {
                return 1;
            }
            break;

        case 'K': // Rei
            if (abs(nova_x - peca->x) <= 1 && abs(nova_y - peca->y) <= 1) { // Movimento de uma casa em qualquer direção
                return 1;
            }
            break;

        default:
            return 0;
    }

    return 0;
}

// Função para capturar uma peça
void capturarPeca(Peca pecas[], int nova_x, int nova_y) {
    for (int i = 0; i < 32; i++) {
        if (pecas[i].x == nova_x && pecas[i].y == nova_y) {
            pecas[i].tipo = '\0'; // Remove a peça capturada
            pecas[i].x = -1;
            pecas[i].y = -1;
            break;
        }
    }
}

// Função principal
int main() {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Peca pecas[32];

    // Inicializar as peças
    // Peças brancas
    strcpy(pecas[0].nome, "T1"); pecas[0].tipo = 'T'; pecas[0].x = 7; pecas[0].y = 0; pecas[0].cor = 'B';
    strcpy(pecas[1].nome, "C1"); pecas[1].tipo = 'C'; pecas[1].x = 7; pecas[1].y = 1; pecas[1].cor = 'B';
    strcpy(pecas[2].nome, "B1"); pecas[2].tipo = 'B'; pecas[2].x = 7; pecas[2].y = 2; pecas[2].cor = 'B';
    strcpy(pecas[3].nome, "Q1"); pecas[3].tipo = 'Q'; pecas[3].x = 7; pecas[3].y = 3; pecas[3].cor = 'B';
    strcpy(pecas[4].nome, "K1"); pecas[4].tipo = 'K'; pecas[4].x = 7; pecas[4].y = 4; pecas[4].cor = 'B';
    strcpy(pecas[5].nome, "B2"); pecas[5].tipo = 'B'; pecas[5].x = 7; pecas[5].y = 5; pecas[5].cor = 'B';
    strcpy(pecas[6].nome, "C2"); pecas[6].tipo = 'C'; pecas[6].x = 7; pecas[6].y = 6; pecas[6].cor = 'B';
    strcpy(pecas[7].nome, "T2"); pecas[7].tipo = 'T'; pecas[7].x = 7; pecas[7].y = 7; pecas[7].cor = 'B';
    for (int i = 0; i < 8; i++) {
        sprintf(pecas[8 + i].nome, "P%d", i + 1);
        pecas[8 + i].tipo = 'P';
        pecas[8 + i].x = 6;
        pecas[8 + i].y = i;
        pecas[8 + i].cor = 'B';
    }

    // Peças pretas
    strcpy(pecas[16].nome, "T1"); pecas[16].tipo = 'T'; pecas[16].x = 0; pecas[16].y = 0; pecas[16].cor = 'P';
    strcpy(pecas[17].nome, "C1"); pecas[17].tipo = 'C'; pecas[17].x = 0; pecas[17].y = 1; pecas[17].cor = 'P';
    strcpy(pecas[18].nome, "B1"); pecas[18].tipo = 'B'; pecas[18].x = 0; pecas[18].y = 2; pecas[18].cor = 'P';
    strcpy(pecas[19].nome, "Q1"); pecas[19].tipo = 'Q'; pecas[19].x = 0; pecas[19].y = 3; pecas[19].cor = 'P';
    strcpy(pecas[20].nome, "K1"); pecas[20].tipo = 'K'; pecas[20].x = 0; pecas[20].y = 4; pecas[20].cor = 'P';
    strcpy(pecas[21].nome, "B2"); pecas[21].tipo = 'B'; pecas[21].x = 0; pecas[21].y = 5; pecas[21].cor = 'P';
    strcpy(pecas[22].nome, "C2"); pecas[22].tipo = 'C'; pecas[22].x = 0; pecas[22].y = 6; pecas[22].cor = 'P';
    strcpy(pecas[23].nome, "T2"); pecas[23].tipo = 'T'; pecas[23].x = 0; pecas[23].y = 7; pecas[23].cor = 'P';
    for (int i = 0; i < 8; i++) {
        sprintf(pecas[24 + i].nome, "P%d", i + 1);
        pecas[24 + i].tipo = 'P';
        pecas[24 + i].x = 1;
        pecas[24 + i].y = i;
        pecas[24 + i].cor = 'P';
    }

    // Inicializar o tabuleiro
    inicializarTabuleiro(tabuleiro, pecas);

    // Loop principal do jogo
    while (1) {
        imprimirTabuleiro(tabuleiro);

        // Entrada do usuário
        char nome_peca[3];
        int nova_x, nova_y;
        printf("Digite a peça que deseja mover (ex: P1): ");
        scanf("%s", nome_peca);
        printf("Digite a nova posição (linha coluna): ");
        scanf("%d %d", &nova_x, &nova_y);

        // Encontrar a peça
        Peca *peca_selecionada = NULL;
        for (int i = 0; i < 32; i++) {
            if (strcmp(pecas[i].nome, nome_peca) == 0) {
                peca_selecionada = &pecas[i];
                break;
            }
        }

        if (!peca_selecionada) {
            printf("Peça não encontrada!\n");
            continue;
        }

        // Validar o movimento
        if (!validarMovimento(peca_selecionada, nova_x, nova_y, pecas)) {
            printf("Movimento inválido!\n");
            continue;
        }

        // Verificar se há uma peça na posição de destino
        for (int i = 0; i < 32; i++) {
            if (pecas[i].x == nova_x && pecas[i].y == nova_y && pecas[i].cor != peca_selecionada->cor) {
                capturarPeca(pecas, nova_x, nova_y);
                break;
            }
        }

        // Atualizar a posição da peça
        tabuleiro[peca_selecionada->x][peca_selecionada->y] = '.';
        peca_selecionada->x = nova_x;
        peca_selecionada->y = nova_y;
        tabuleiro[nova_x][nova_y] = peca_selecionada->nome[0];
    }

    return 0;
}