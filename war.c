/*NOVATO: WAR
STRUCT - Territorio: Nome, cor do exercito, nº de tropas
ARRAY - Tabuleiro: 5 espaços, e em cada um deles o molde do tabuleiro criado (em forma de relatorio)

1º  cadastra cada territorio
2º relatorio completo do mundo criado com os territórios*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //biblioteca que tem funções para manipular strings . Para strcspn()

// Definindo Constantes e bibliotecas Globais
#define TAM_NOME 30
#define TAM_COR 10
#define MAX_TERRITORIOS 5

// Definindo o Territorio (Struct)
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int ntropas;
};

// Função limpar o buffer, evitando sobrecarregar
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c!= EOF); 
};

// Função Principal (main)
int main() {
    struct Territorio biblioteca[MAX_TERRITORIOS];
    int numTerrit = 0;

    printf("* * * *  W A R * * * *\n");
    printf("Vamos começar definindo os Territórios?\n");


    for (int i = 1; i <= MAX_TERRITORIOS; i++) { // Loop até o total dee territorios. 
        printf("--- Cadastrando Territorio %d ---\n", (numTerrit+1));
        printf("Qual nome deste Territorio? ");
        fgets(biblioteca[numTerrit].nome, TAM_NOME, stdin);

        printf("Qual a cor do seu exército? ");
        fgets(biblioteca[numTerrit].cor, TAM_COR, stdin);

        biblioteca[numTerrit].nome[strcspn(biblioteca[numTerrit].nome, "\n")] = '\0';
        biblioteca[numTerrit].cor[strcspn(biblioteca[numTerrit].cor, "\n")] = '\0';

        printf("Quantas tropas ele tem? ");
        scanf("%d", &biblioteca[numTerrit].ntropas);
        printf("\n");

        numTerrit++;

        limparBufferEntrada();
    }

    printf("\n\n\n");
        
    //Relatório dos territorios
    printf("* * * * *  W A R  * * * * *\n");
    printf("* * MAPA DE TERRITORIOS * *\n");
    printf("* * * * *  * * *  * * * * *\n");

    for (int i = 0; i < numTerrit; i++) {
        printf("TERRITÓRIO %d\n", i+1);
        printf("+ Denominado: %s\n", biblioteca[i].nome);
        printf("+ Conhecido por ser o Exército %s\n", biblioteca[i].cor);
        printf("+ Iniciará com %d tropas\n\n", biblioteca[i].ntropas);
    }
    printf("Etapa finalizada!\n");

    return 0;
}