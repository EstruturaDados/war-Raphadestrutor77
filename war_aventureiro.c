#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

void simularAtaque(struct Territorio *mapa, int idAtacante, int idDefensor) {
    int iAtac = idAtacante - 1;
    int iDef = idDefensor - 1;

    printf("\n--- BATALHA: %s (%s) vs %s (%s) ---\n",
           mapa[iAtac].nome, mapa[iAtac].cor,
           mapa[iDef].nome, mapa[iDef].cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dados: Atacante [%d] vs Defensor [%d]\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        printf("Resultado: VITORIA DO ATACANTE!\n");
        mapa[iDef].tropas--;

        printf("O território %s agora tem %d tropas.\n", mapa[iDef].nome, mapa[iDef].tropas);

        if (mapa[iDef].tropas <= 0) {
            printf(">>> O territorio %s FOI CONQUISTADO! <<<\n", mapa[iDef].nome);
            strcpy(mapa[iDef].cor, mapa[iAtac].cor);
            mapa[iDef].tropas = 1;
        }

    } else {
        printf("Resultado: VITORIA DO DEFENSOR!\n");
    }
}

int main() {
    struct Territorio *mapa;
    int i;
    int c;

    srand(time(NULL));

    mapa = (struct Territorio*) calloc(TOTAL_TERRITORIOS, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro crítico! Falha ao alocar memória.\n");
        return 1;
    }

    printf("--- Sistema de Cadastro de Territórios (WAR) ---\n");
    printf("Por favor, cadastre os %d territórios.\n", TOTAL_TERRITORIOS);

    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("\n--- Cadastrando Território %d ---\n", i + 1);

        /* === MUDANÇA AQUI: Usando fgets para o nome === */
        printf("Digite o nome (pode ter espaços): ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        // Remove o '\n' (Enter) que o fgets captura
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        /* ============================================= */

        printf("Digite a cor (sem espaços): ");
        scanf("%9s", mapa[i].cor);
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        while ((c = getchar()) != '\n' && c != EOF);
    }

    int idAtacante, idDefensor;

    while (1) {
        printf("\n\n--- Fase de Ataque Interativo ---\n");
        printf("--- Mapa Atual ---\n");
        for (i = 0; i < TOTAL_TERRITORIOS; i++) {
             printf("ID %d: %s (Cor: %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        printf("------------------\n");
        
        printf("Digite o ID do território ATACANTE (1-%d) (ou 0 para parar): ", TOTAL_TERRITORIOS);
        scanf("%d", &idAtacante);
        while ((c = getchar()) != '\n' && c != EOF);

        if (idAtacante <= 0 || idAtacante > TOTAL_TERRITORIOS) {
            printf("Encerrando fase de ataque...\n");
            break;
        }

        printf("Digite o ID do território DEFENSOR (1-%d): ", TOTAL_TERRITORIOS);
        scanf("%d", &idDefensor);
        while ((c = getchar()) != '\n' && c != EOF);

        if (idDefensor <= 0 || idDefensor > TOTAL_TERRITORIOS) {
            printf("ID de defensor inválido. Tente novamente.\n");
            continue;
        }
        
        if (idAtacante == idDefensor) {
            printf("Um território não pode atacar a si mesmo. Tente novamente.\n");
            continue;
        }

        if (strcmp(mapa[idAtacante - 1].cor, mapa[idDefensor - 1].cor) == 0) {
            printf("Ataque inválido! Você não pode atacar um território que já é seu.\n");
            continue;
        }

        simularAtaque(mapa, idAtacante, idDefensor);
    }

    printf("\n\n--- Relatório Final dos Territórios ---\n");

    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("------------------------------\n");
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
    }
    printf("------------------------------\n");

    free(mapa);
    mapa = NULL;

    return 0;
}