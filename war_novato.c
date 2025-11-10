#include <stdio.h>
#include <string.h>

#define TOTAL_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio mapa[TOTAL_TERRITORIOS];
    int i;

    printf("--- Sistema de Cadastro de Territórios (WAR) ---\n");
    printf("Por favor, cadastre os %d territórios.\n", TOTAL_TERRITORIOS);

    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        
        printf("\n--- Cadastrando Território %d ---\n", i + 1);

        printf("Digite o nome (pode ter espaços): ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor (sem espaços): ");
        scanf("%9s", mapa[i].cor);
        limpar_buffer();

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limpar_buffer();
    }

    printf("\n\n--- Relatório dos Territórios Cadastrados ---\n");
    
    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("------------------------------\n");
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
    }
    printf("------------------------------\n");

    return 0;
}