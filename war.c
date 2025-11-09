/*
 * Bibliotecas necessárias:
 * stdio.h: para funções de entrada e saída (printf, scanf)
 * string.h: para strcpy (copiar a cor do time)
 * stdlib.h: para calloc, free, rand, srand (NOVAS)
 * time.h: para time (seed do rand) (NOVA)
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>   

// --- Constantes Globais ---
#define TOTAL_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

/*
 * ========================================
 *  Definição da struct
 * ========================================
 */
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

/*
 * ========================================
 * Função de Batalha (Modularização)
 * ========================================
 *
 */
void simularAtaque(struct Territorio *mapa, int idAtacante, int idDefensor) {
    // Índices do vetor (usuário digita 1-5, vetor é 0-4)
    int iAtac = idAtacante - 1;
    int iDef = idDefensor - 1;

    printf("\n--- BATALHA: %s (%s) vs %s (%s) ---\n",
           mapa[iAtac].nome, mapa[iAtac].cor,
           mapa[iDef].nome, mapa[iDef].cor);

    // Simulação dos dados com rand()
    int dadoAtacante = (rand() % 6) + 1; // Gera número de 1 a 6
    int dadoDefensor = (rand() % 6) + 1; // Gera número de 1 a 6

    printf("Dados: Atacante [%d] vs Defensor [%d]\n", dadoAtacante, dadoDefensor);

    /*
     * Lógica de Batalha
     * - Se atacante vence -> defensor perde 1 tropa
     * - Se defensor perde todas -> território é conquistado
     * - Empates favorecem o atacante
     */
    if (dadoAtacante >= dadoDefensor) { // Empate favorece o atacante
        printf("Resultado: VITORIA DO ATACANTE!\n");
        mapa[iDef].tropas--; // Defensor perde 1 tropa

        printf("O território %s agora tem %d tropas.\n", mapa[iDef].nome, mapa[iDef].tropas);

        // Lógica de Conquista
        if (mapa[iDef].tropas <= 0) {
            printf(">>> O territorio %s FOI CONQUISTADO! <<<\n", mapa[iDef].nome);
            
            // O território conquistado passa a ser do atacante
            strcpy(mapa[iDef].cor, mapa[iAtac].cor); 
            
            // Regra do jogo: move 1 tropa para o território conquistado
            // (Você pode alterar essa regra depois)
            mapa[iDef].tropas = 1; 
        }

    } else { // dadoDefensor > dadoAtacante
        printf("Resultado: VITORIA DO DEFENSOR!\n");
        // Nenhuma tropa é perdida pelo atacante (conforme imagem)
    }
}


// --- Função Principal ---
int main() {
    /*
     * ========================================
     * MUDANÇA: Alocação Dinâmica com calloc
     * ========================================
     */
    // Antes: struct Territorio mapa[TOTAL_TERRITORIOS];
    
    // Declaração de ponteiro
    struct Territorio *mapa; 
    int i; // Variável de controle do laço

    //  "Semeando" o rand() para que os números sejam diferentes a cada execução
    srand(time(NULL));

    // Alocando a memória dinamicamente com calloc
    // calloc(N_elementos, tamanho_de_cada_elemento)
    mapa = (struct Territorio*) calloc(TOTAL_TERRITORIOS, sizeof(struct Territorio));

    //  Verificar se a alocação funcionou
    if (mapa == NULL) {
        printf("Erro crítico! Falha ao alocar memória.\n");
        return 1; // Retorna 1 para indicar um erro
    }

    // Usabilidade: Título claro para o usuário
    printf("--- Sistema de Cadastro de Territórios (WAR) ---\n");
    printf("Por favor, cadastre os %d territórios.\n", TOTAL_TERRITORIOS);

    /*
     * ========================================
     * Entrada dos dados (Cadastro)
     * ========================================
     */
    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("\n--- Cadastrando Território %d ---\n", i + 1);

        printf("Digite o nome (sem espaços): ");
        scanf("%29s", mapa[i].nome);

        printf("Digite a cor (sem espaços): ");
        scanf("%9s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    /*
     * ========================================
     * Fase de Ataque (Loop Interativo)
     * ========================================
     */
    
    int idAtacante, idDefensor;
    
    // Laço interativo de ataque
    while (1) {
        printf("\n\n--- Fase de Ataque Interativo ---\n");
        printf("--- Mapa Atual ---\n");
        for (i = 0; i < TOTAL_TERRITORIOS; i++) {
             printf("ID %d: %s (Cor: %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        printf("------------------\n");
        
        printf("Digite o ID do território ATACANTE (1-%d) (ou 0 para parar): ", TOTAL_TERRITORIOS);
        scanf("%d", &idAtacante);

        // Condição de parada
        if (idAtacante <= 0 || idAtacante > TOTAL_TERRITORIOS) {
            printf("Encerrando fase de ataque...\n");
            break; // Sai do laço while
        }

        printf("Digite o ID do território DEFENSOR (1-%d): ", TOTAL_TERRITORIOS);
        scanf("%d", &idDefensor);

        // Validação simples
        if (idDefensor <= 0 || idDefensor > TOTAL_TERRITORIOS) {
            printf("ID de defensor inválido. Tente novamente.\n");
            continue; // Pula para a próxima iteração do laço
        }
        
        if (idAtacante == idDefensor) {
            printf("Um território não pode atacar a si mesmo. Tente novamente.\n");
            continue;
        }

        // Validação de Lógica de Jogo
        // (Não se pode atacar um território da mesma cor)
        if (strcmp(mapa[idAtacante - 1].cor, mapa[idDefensor - 1].cor) == 0) {
            printf("Ataque inválido! Você não pode atacar um território que já é seu.\n");
            continue;
        }

        // Chamada da função modularizada
        simularAtaque(mapa, idAtacante, idDefensor);
    }


    /*
     * ========================================
     * Exibição dos dados (Relatório Pós-Batalha)
     * ========================================
     */
    printf("\n\n--- Relatório Final dos Territórios ---\n");

    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("------------------------------\n");
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor); // Pode ter mudado
        printf("  Tropas: %d\n", mapa[i].tropas); // Pode ter mudado
    }
    printf("------------------------------\n");

    // Liberando a memória alocada com calloc
    free(mapa);
    mapa = NULL;

    return 0; // Indica que o programa terminou com sucesso
}