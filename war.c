/*
 * Bibliotecas necessárias:
 * stdio.h: para funções de entrada e saída (printf, scanf)
 * string.h: solicitada (embora não seja essencial para esta
 * implementação específica com scanf, seria para fgets)
 */
#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
// Manutenibilidade: Usar constantes torna fácil alterar o tamanho depois
#define TOTAL_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

/*
 * ========================================
 * 1. Definição da struct
 * ========================================
 */
struct Territorio {
    char nome[TAM_NOME];   // Nome do território (ex: "Brasil")
    char cor[TAM_COR];     // Cor do exército (ex: "Verde")
    int tropas;            // Quantidade de tropas
};

// --- Função Principal ---
int main() {
    /*
     * 2. Declaração de vetor de structs
     */
    struct Territorio mapa[TOTAL_TERRITORIOS];
    int i; // Variável de controle do laço (Manutenibilidade)

    // Usabilidade: Título claro para o usuário
    printf("--- Sistema de Cadastro de Territórios (WAR) ---\n");
    printf("Por favor, cadastre os %d territórios.\n", TOTAL_TERRITORIOS);

    /*
     * ========================================
     * 3. Entrada dos dados
     * ========================================
     */
    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        
        printf("\n--- Cadastrando Território %d ---\n", i + 1);

        // Usabilidade: Mensagem clara sobre o que digitar
        printf("Digite o nome (sem espaços): ");
        /*
         * Limitação: scanf("%s") para de ler no primeiro espaço.
         */
        scanf("%29s", mapa[i].nome);

        // Usabilidade: Mensagem clara
        printf("Digite a cor (sem espaços): ");
        // Lendo a cor com a mesma técnica de segurança "%9s"
        scanf("%9s", mapa[i].cor);

        // Usabilidade: Mensagem clara
        printf("Digite a quantidade de tropas: ");

        scanf("%d", &mapa[i].tropas);
    }

    /*
     * ========================================
     * 4. Exibição dos dados
     * ========================================
     */
    printf("\n\n--- Relatório dos Territórios Cadastrados ---\n");
    
    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("------------------------------\n");
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
    }
    printf("------------------------------\n");

    return 0; // Indica que o programa terminou com sucesso
}