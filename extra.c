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
    int movida;   // Indica se a peça já foi movida (para roque e en passant)
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

// Função para verificar se o Rei está em xeque
int estaEmXeque(Peca pecas[], char corRei) {
    int rei_x = -1, rei_y = -1;

    // Encontrar a posição do Rei
    for (int i = 0; i < 32; i++) {
        if (pecas[i].tipo == 'K' && pecas[i].cor == corRei) {
            rei_x = pecas[i].x;
            rei_y = pecas[i].y;
            break;
        }
    }

    // Verificar se alguma peça adversária pode atacar o Rei
    for (int i = 0; i < 32; i++) {
        if (pecas[i].tipo != '\0' && pecas[i].cor != corRei) {
            if (validarMovimento(&pecas[i], rei_x, rei_y, pecas)) {
                return 1; // O Rei está em xeque
            }
        }
    }

    return 0; // O Rei não está em xeque
}

// Função para verificar xeque-mate
int estaEmXequeMate(Peca pecas[], char corRei) {
    if (!estaEmXeque(pecas, corRei)) {
        return 0; // Não está em xeque, então não é xeque-mate
    }

    // Tentar todos os movimentos possíveis para sair do xeque
    for (int i = 0; i < 32; i++) {
        if (pecas[i].tipo != '\0' && pecas[i].cor == corRei) {
            for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
                for (int y = 0; y < TAMANHO_TABULEIRO; y++) {
                    if (validarMovimento(&pecas[i], x, y, pecas)) {
                        // Simular o movimento
                        int antiga_x = pecas[i].x;
                        int antiga_y = pecas[i].y;
                        pecas[i].x = x;
                        pecas[i].y = y;

                        // Verificar se o Rei ainda está em xeque
                        if (!estaEmXeque(pecas, corRei)) {
                            // Desfazer o movimento simulado
                            pecas[i].x = antiga_x;
                            pecas[i].y = antiga_y;
                            return 0; // Há um movimento legal para sair do xeque
                        }

                        // Desfazer o movimento simulado
                        pecas[i].x = antiga_x;
                        pecas[i].y = antiga_y;
                    }
                }
            }
        }
    }

    return 1; // Xeque-mate
}

// Função para realizar o roque
int realizarRoque(Peca *rei, Peca *torre, Peca pecas[], char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    if (rei->movida || torre->movida) {
        return 0; // O Rei ou a Torre já se moveram
    }

    int direcao = (torre->y > rei->y) ? 1 : -1;
    int nova_y_rei = rei->y + 2 * direcao;

    // Verificar se há peças entre o Rei e a Torre
    for (int y = rei->y + direcao; y != torre->y; y += direcao) {
        if (tabuleiro[rei->x][y] != '.') {
            return 0; // Há uma peça no caminho
        }
    }

    // Verificar se o Rei passará por casas atacadas
    for (int y = rei->y; y != nova_y_rei; y += direcao) {
        if (estaEmXeque(pecas, rei->cor)) {
            return 0; // O Rei está em xeque ou passará por uma casa atacada
        }
    }

    // Realizar o roque
    tabuleiro[rei->x][rei->y] = '.';
    rei->y = nova_y_rei;
    tabuleiro[rei->x][rei->y] = rei->nome[0];

    tabuleiro[torre->x][torre->y] = '.';
    torre->y = rei->y - direcao;
    tabuleiro[torre->x][torre->y] = torre->nome[0];

    rei->movida = 1;
    torre->movida = 1;

    return 1;
}

// Função principal
int main() {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Peca pecas[32];

    // Inicializar as peças
    // Peças brancas
    strcpy(pecas[0].nome, "T1"); pecas[0].tipo = 'T'; pecas[0].x = 7; pecas[0].y = 0; pecas[0].cor = 'B'; pecas[0].movida = 0;
    strcpy(pecas[1].nome, "C1"); pecas[1].tipo = 'C'; pecas[1].x = 7; pecas[1].y = 1; pecas[1].cor = 'B'; pecas[1].movida = 0;
    strcpy(pecas[2].nome, "B1"); pecas[2].tipo = 'B'; pecas[2].x = 7; pecas[2].y = 2; pecas[2].cor = 'B'; pecas[2].movida = 0;
    strcpy(pecas[3].nome, "Q1"); pecas[3].tipo = 'Q'; pecas[3].x = 7; pecas[3].y = 3; pecas[3].cor = 'B'; pecas[3].movida = 0;
    strcpy(pecas[4].nome, "K1"); pecas[4].tipo = 'K'; pecas[4].x = 7; pecas[4].y = 4; pecas[4].cor = 'B'; pecas[4].movida = 0;
    strcpy(pecas[5].nome, "B2"); pecas[5].tipo = 'B'; pecas[5].x = 7; pecas[5].y = 5; pecas[5].cor = 'B'; pecas[5].movida = 0;
    strcpy(pecas[6].nome, "C2"); pecas[6].tipo = 'C'; pecas[6].x = 7; pecas[6].y = 6; pecas[6].cor = 'B'; pecas[6].movida = 0;
    strcpy(pecas[7].nome, "T2"); pecas[7].tipo = 'T'; pecas[7].x = 7; pecas[7].y = 7; pecas[7].cor = 'B'; pecas[7].movida = 0;
    for (int i = 0; i < 8; i++) {
        sprintf(pecas[8 + i].nome, "P%d", i + 1);
        pecas[8 + i].tipo = 'P';
        pecas[8 + i].x = 6;
        pecas[8 + i].y = i;
        pecas[8 + i].cor = 'B';
        pecas[8 + i].movida = 0;
    }

    // Peças pretas
    strcpy(pecas[16].nome, "T1"); pecas[16].tipo = 'T'; pecas[16].x = 0; pecas[16].y = 0; pecas[16].cor = 'P'; pecas[16].movida = 0;
    strcpy(pecas[17].nome, "C1"); pecas[17].tipo = 'C'; pecas[17].x = 0; pecas[17].y = 1; pecas[17].cor = 'P'; pecas[17].movida = 0;
    strcpy(pecas[18].nome, "B1"); pecas[18].tipo = 'B'; pecas[18].x = 0; pecas[18].y = 2; pecas[18].cor = 'P'; pecas[18].movida = 0;
    strcpy(pecas[19].nome, "Q1"); pecas[19].tipo = 'Q'; pecas[19].x = 0; pecas[19].y = 3; pecas[19].cor = 'P'; pecas[19].movida = 0;
    strcpy(pecas[20].nome, "K1"); pecas[20].tipo = 'K'; pecas[20].x = 0; pecas[20].y = 4; pecas[20].cor = 'P'; pecas[20].movida = 0;
    strcpy(pecas[21].nome, "B2"); pecas[21].tipo = 'B'; pecas[21].x = 0; pecas[21].y = 5; pecas[21].cor = 'P'; pecas[21].movida = 0;
    strcpy(pecas[22].nome, "C2"); pecas[22].tipo = 'C'; pecas[22].x = 0; pecas[22].y = 6; pecas[22].cor = 'P'; pecas[22].movida = 0;
    strcpy(pecas[23].nome, "T2"); pecas[23].tipo = 'T'; pecas[23].x = 0; pecas[23].y = 7; pecas[23].cor = 'P'; pecas[23].movida = 0;
    for (int i = 0; i < 8; i++) {
        sprintf(pecas[24 + i].nome, "P%d", i + 1);
        pecas[24 + i].tipo = 'P';
        pecas[24 + i].x = 1;
        pecas[24 + i].y = i;
        pecas[24 + i].cor = 'P';
        pecas[24 + i].movida = 0;
    }

    // Inicializar o tabuleiro
    inicializarTabuleiro(tabuleiro, pecas);

    // Loop principal do jogo
    char vez = 'B'; // Começa com as brancas
    while (1) {
        imprimirTabuleiro(tabuleiro);

        // Verificar xeque e xeque-mate
        if (estaEmXeque(pecas, vez)) {
            printf("XEQUE! O Rei %s está em perigo!\n", vez == 'B' ? "branco" : "preto");
            if (estaEmXequeMate(pecas, vez)) {
                printf("XEQUE-MATE! O jogador %s venceu!\n", vez == 'B' ? "preto" : "branco");
                break;
            }
        }

        // Entrada do usuário
        char entrada[10];
        printf("Jogador %s, digite o movimento (ex: e2 e4): ", vez == 'B' ? "branco" : "preto");
        scanf("%s", entrada);

        // Converter entrada para coordenadas
        int origem_x = 8 - (entrada[1] - '0');
        int origem_y = entrada[0] - 'a';
        int destino_x = 8 - (entrada[4] - '0');
        int destino_y = entrada[3] - 'a';

        // Encontrar a peça
        Peca *peca_selecionada = NULL;
        for (int i = 0; i < 32; i++) {
            if (pecas[i].x == origem_x && pecas[i].y == origem_y && pecas[i].cor == vez) {
                peca_selecionada = &pecas[i];
                break;
            }
        }

        if (!peca_selecionada) {
            printf("Movimento inválido! Tente novamente.\n");
            continue;
        }

        // Validar o movimento
        if (!validarMovimento(peca_selecionada, destino_x, destino_y, pecas)) {
            printf("Movimento inválido! Tente novamente.\n");
            continue;
        }

        // Verificar se há uma peça na posição de destino
        for (int i = 0; i < 32; i++) {
            if (pecas[i].x == destino_x && pecas[i].y == destino_y && pecas[i].cor != peca_selecionada->cor) {
                capturarPeca(pecas, destino_x, destino_y);
                break;
            }
        }

        // Atualizar a posição da peça
        tabuleiro[peca_selecionada->x][peca_selecionada->y] = '.';
        peca_selecionada->x = destino_x;
        peca_selecionada->y = destino_y;
        tabuleiro[destino_x][destino_y] = peca_selecionada->nome[0];
        peca_selecionada->movida = 1;

        // Alternar a vez
        vez = (vez == 'B') ? 'P' : 'B';
    }

    return 0;
}