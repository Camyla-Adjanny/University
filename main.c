#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define VALOR_NAVIO 3
#define AGUA 0
#define ACERTO -1

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Exibe o tabuleiro com símbolos
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            char simbolo;
            if (tabuleiro[i][j] == AGUA)
                simbolo = '~';
            else if (tabuleiro[i][j] == VALOR_NAVIO)
                simbolo = 'N';
            else if (tabuleiro[i][j] == ACERTO)
                simbolo = 'X';
            else
                simbolo = '?';
            printf("%c ", simbolo);
        }
        printf("\n");
    }
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

// Função de ataque
int atacar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO)
        return -1; // Fora dos limites
    if (tabuleiro[linha][coluna] == VALOR_NAVIO) {
        tabuleiro[linha][coluna] = ACERTO;
        return 1; // Acertou
    }
    return 0; // Errou
}

// Verifica se todos os navios foram atingidos
int verificarVitoria(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == VALOR_NAVIO)
                return 0; // Ainda há navios
        }
    }
    return 1; // Todos os navios foram atingidos
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

    // Loop de ataque
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
        else
            printf("❌ Coordenadas inválidas!\n");
    }

    printf("🎉 Todos os navios foram destruídos! Fim de jogo.\n");
    return 0;
}

