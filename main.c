#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define VALOR_NAVIO 3
#define AGUA 0
#define ACERTO -1
#define TIRO_ERRADO -2

// Inicializa o tabuleiro com água (~)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Exibe o tabuleiro com símbolos e índices
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n    ");
    for (int j = 0; j < TAM_TABULEIRO; j++)
        printf("%d ", j);  // Índice das colunas
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d |", i);  // Índice das linhas
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            char simbolo;
            if (tabuleiro[i][j] == AGUA)
                simbolo = '~';          // Água
            else if (tabuleiro[i][j] == VALOR_NAVIO)
                simbolo = '~';          // Esconde navio
            else if (tabuleiro[i][j] == ACERTO)
                simbolo = 'X';          // Acertou navio
            else if (tabuleiro[i][j] == TIRO_ERRADO)
                simbolo = '.';          // Tiro na água
            else
                simbolo = '?';          // Desconhecido
            printf(" %c", simbolo);
        }
        printf("\n");
    }
    printf("\n");
}

// Posiciona navio horizontal
int posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (coluna + TAM_NAVIO > TAM_TABULEIRO)
        return 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA)
            return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = VALOR_NAVIO;
    }
    return 1;
}

// Posiciona navio vertical
int posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM_TABULEIRO)
        return 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA)
            return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = VALOR_NAVIO;
    }
    return 1;
}

// Ataca uma posição do tabuleiro
int atacar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO)
        return -1; // Coordenadas inválidas

    if (tabuleiro[linha][coluna] == VALOR_NAVIO) {
        tabuleiro[linha][coluna] = ACERTO;
        return 1; // Acertou
    } else if (tabuleiro[linha][coluna] == AGUA) {
        tabuleiro[linha][coluna] = TIRO_ERRADO;
        return 0; // Errou
    }

    return 2; // Já atacou essa posição antes
}

// Verifica se todos os navios foram destruídos
int verificarVitoria(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == VALOR_NAVIO)
                return 0; // Ainda há navios
        }
    }
    return 1; // Vitória!
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    if (!posicionarNavioHorizontal(tabuleiro, 2, 4)) {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }
    if (!posicionarNavioVertical(tabuleiro, 5, 1)) {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }

    // Loop de ataques
    int linha, coluna;
    while (!verificarVitoria(tabuleiro)) {
        exibirTabuleiro(tabuleiro);
        printf("Digite linha e coluna para atacar (0 a 9): ");
        scanf("%d %d", &linha, &coluna);

        int resultado = atacar(tabuleiro, linha, coluna);
        if (resultado == 1)
            printf("💥 Acertou!\n");
        else if (resultado == 0)
            printf("🌊 Errou!\n");
        else if (resultado == 2)
            printf("⚠️ Já atacou essa posição.\n");
        else
            printf("❌ Coordenadas inválidas!\n");
    }

    exibirTabuleiro(tabuleiro); // Exibe o tabuleiro final
    printf("🎉 Todos os navios foram destruídos! Fim de jogo.\n");
    return 0;
}
