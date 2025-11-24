#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 15

// Definições para o jogo
#define COR_JOGADOR "Azul"      // O jogador controlará o exército Azul
#define COR_ALVO "Verde"        // Alvo da missão de destruição

// Tipos de Missão
#define MISSAO_DESTRUIR_VERDE 1
#define MISSAO_CONQUISTAR_3 2

struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// --- Protótipos das Funções (Modularização) ---
void inicializarMapa(struct Territorio *mapa);
void exibirMapa(const struct Territorio *mapa);
void simularBatalha(struct Territorio *mapa, int idAtacante, int idDefensor);
void processarAtaque(struct Territorio *mapa);
int sortearMissao();
void exibirMissao(int idMissao);
void verificarMissao(const struct Territorio *mapa, int idMissao);
void limparBuffer();

int main() {
    struct Territorio *mapa;
    int opcao, missaoAtual;

    srand(time(NULL));

    // Alocação dinâmica
    mapa = (struct Territorio*) calloc(TOTAL_TERRITORIOS, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro critico de memoria.\n");
        return 1;
    }

    // 1. Inicialização Automática 
    inicializarMapa(mapa);

    // 2. Sorteio da Missão
    missaoAtual = sortearMissao();

    // Loop do Menu Principal
    do {
        printf("\n=== WAR: NIVEL MESTRE ===\n");
        exibirMissao(missaoAtual);
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao (Status)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                processarAtaque(mapa);
                break;
            case 2:
                verificarMissao(mapa, missaoAtual);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    free(mapa);
    return 0;
}

// --- Implementação das Funções ---

// Inicializa o mapa automaticamente para não perder tempo digitando
void inicializarMapa(struct Territorio *mapa) {
    // Configurando cenário para que as missões sejam possíveis
    // Jogador = Azul. Inimigos = Verde e Vermelho.
    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, COR_JOGADOR);
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Franca");
    strcpy(mapa[1].cor, COR_ALVO); // Verde
    mapa[1].tropas = 3;

    strcpy(mapa[2].nome, "Australia");
    strcpy(mapa[2].cor, "Vermelho");
    mapa[2].tropas = 2;

    strcpy(mapa[3].nome, "Egito");
    strcpy(mapa[3].cor, COR_ALVO); // Verde
    mapa[3].tropas = 4;

    strcpy(mapa[4].nome, "China");
    strcpy(mapa[4].cor, "Vermelho");
    mapa[4].tropas = 3;
    
    printf("\n> Mapa inicializado automaticamente!\n");
}


void exibirMapa(const struct Territorio *mapa) {
    printf("\n--- Mapa Atual ---\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("ID %d: %-10s | Cor: %-8s | Tropas: %d\n", 
            i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("------------------\n");
}

void simularBatalha(struct Territorio *mapa, int idAtacante, int idDefensor) {
    int iAtac = idAtacante - 1;
    int iDef = idDefensor - 1;

    printf("\n>>> BATALHA: %s (%s) vs %s (%s) <<<\n",
           mapa[iAtac].nome, mapa[iAtac].cor,
           mapa[iDef].nome, mapa[iDef].cor);

    int dadoAtac = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dados: Atacante [%d] x [%d] Defensor\n", dadoAtac, dadoDef);

    if (dadoAtac > dadoDef) { // Regra clássica: Empate é da defesa, > é ataque
        printf("VITORIA DO ATACANTE!\n");
        mapa[iDef].tropas--;
        
        if (mapa[iDef].tropas <= 0) {
            printf("--- TERRITORIO CONQUISTADO! ---\n");
            strcpy(mapa[iDef].cor, mapa[iAtac].cor); // Muda a cor
            mapa[iDef].tropas = 1; // Ocupa com 1 tropa
        }
    } else {
        printf("VITORIA DO DEFENSOR!\n");
        // Opcional: Atacante perde tropa na defesa bem sucedida? 
        // No código original não perdia, mantive assim.
    }
}

// Função que gerencia a interação de ataque
void processarAtaque(struct Territorio *mapa) {
    int idAtac, idDef;
    
    exibirMapa(mapa);

    printf("Digite ID do Atacante (Seu cor: %s): ", COR_JOGADOR);
    scanf("%d", &idAtac);
    limparBuffer();

    if (idAtac < 1 || idAtac > TOTAL_TERRITORIOS) {
        printf("ID invalido.\n");
        return;
    }
    
    // Verifica se o jogador está usando o próprio território para atacar
    if (strcmp(mapa[idAtac-1].cor, COR_JOGADOR) != 0) {
        printf("Voce so pode atacar com territorios %s!\n", COR_JOGADOR);
        return;
    }

    printf("Digite ID do Alvo: ");
    scanf("%d", &idDef);
    limparBuffer();

    if (idDef < 1 || idDef > TOTAL_TERRITORIOS || idAtac == idDef) {
        printf("Alvo invalido.\n");
        return;
    }

    if (strcmp(mapa[idAtac-1].cor, mapa[idDef-1].cor) == 0) {
        printf("Voce nao pode atacar aliados!\n");
        return;
    }

    simularBatalha(mapa, idAtac, idDef);
}

int sortearMissao() {
    // Retorna 1 ou 2
    return (rand() % 2) + 1;
}

void exibirMissao(int idMissao) {
    printf("\n[ MISSAO ATUAL ]: ");
    if (idMissao == MISSAO_DESTRUIR_VERDE) {
        printf("Destruir totalmente o exercito VERDE.\n");
    } else {
        printf("Conquistar 3 territorios.\n");
    }
}

void verificarMissao(const struct Territorio *mapa, int idMissao) {
    int contVerde = 0;
    int contJogador = 0;
    int vitoria = 0;

    // Varredura única para contar status
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        if (strcmp(mapa[i].cor, COR_ALVO) == 0) {
            contVerde++;
        }
        if (strcmp(mapa[i].cor, COR_JOGADOR) == 0) {
            contJogador++;
        }
    }

    printf("\n--- Status da Missao ---\n");
    
    if (idMissao == MISSAO_DESTRUIR_VERDE) {
        printf("Territorios Verdes restantes: %d\n", contVerde);
        if (contVerde == 0) vitoria = 1;
    } else {
        printf("Territorios %s conquistados: %d / 3\n", COR_JOGADOR, contJogador);
        if (contJogador >= 3) vitoria = 1;
    }

    if (vitoria) {
        printf("\n**********************************\n");
        printf(" PARABENS! MISSAO CUMPRIDA! \n");
        printf("**********************************\n");
        // Opcional: Encerrar jogo ou continuar
    } else {
        printf("A missao ainda nao foi concluida.\n");
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}