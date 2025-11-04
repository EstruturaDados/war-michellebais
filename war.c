#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definindo Constantes e bibliotecas Globais
#define TAM_NOME 30
#define TAM_COR 10

// Variáveis globais de controle
int numTerrit = 0;  //numero dado a cada tropa
int qtdterritorios; //numero de equipes (territorios) escolhido pelo usuario

// Definindo o Territorio (Struct) - jogador
typedef struct {
    char nome[TAM_NOME];   // Nome do território
    char cor[TAM_COR];     // Cor do exército (identifica o jogador)
    int ntropas;           // Quantidade de tropas no território
    char *missao;          // Missão do jogador (texto alocado dinamicamente)
    int tipoMissao;        // Tipo da missão (usado para verificação)
    char alvo[TAM_COR];    // Cor alvo (usada em missões do tipo "eliminar")
} Territorio;

// Definindo Missão (Struct)
typedef struct {
    char descricao[100];   // Texto descritivo da missão
    int tipo;              // Número de identificação de cada missão
    char alvo[TAM_COR];    // Usado para um inimigo especifico
    int qtdObjetivo;       // Usado para missões com metas numéricas
} Missao;

//Definindo as missoes do jogo
Missao missoes[] = {
    {"Você deve ELIMINAR UM EXÉRCITO INTEIRO. Escolha a cor", 1, "", 0},  
    {"VOCÊ DEVE ADQUIRIR 10 TROPAS NOVAS", 2, "", 10}, 
    {"Você deve DOMINAR TODOS OS TERRITÓRIOS DO MAPA", 3, "", 0}, 
    {"VOCÊ DEVE MANTER AO MENOS 10 TROPAS", 4, "", 10},  
    {"VOCÊ DEVE CONQUISTAR A MAIOR PARTE DE TERRITÓRIOS DO JOGO", 5, "", 0}
};
int totalMissoes = 5;


// Função principal (main)
int main() {

    void limparBufferEntrada();
    void liberarMemoria(Territorio *t);
    int dados();
    void cadTropas(Territorio *t, int qtdterritorios);
    void exibirMapa(Territorio *t, int qtdterritorios);
    void batalha(Territorio *t, int qtdterritorios);
    void atribuirMissao(Territorio *jogador, Missao *missoes, int totalMissoes);
    int verificarMissao(Territorio *jogador, Territorio *mapa, int tamanho);

    int escolha, menu = 1;
    srand(time(NULL)); // inicializa o gerador de números aleatórios

    printf("* * * * * * * *   W A R   * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * *\n");
    printf("Vamos começar definindo os Territórios...\n");
    printf("Quantos Territórios teremos?  ");
    if (scanf("%d", &qtdterritorios) != 1) {    //número total de territórios definido pelo usuário
        printf("Entrada inválida! Inicie o jogo novamente.\n");
        exit(1);
    }

    limparBufferEntrada();

    // Alocando memoria de acordo com a qtd indicada pelo usuario, para a struct Territorios, que corresponde ao ponteiro 't'
    Territorio *t = malloc(qtdterritorios * sizeof(Territorio));
    if (!t) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadTropas(t, qtdterritorios); // Cadastro inicial de territórios

    printf("=== Lista de Missões ===\n");
    for (int i = 0; i < totalMissoes; i++) {
        printf("[%d] %s\n", missoes[i].tipo, missoes[i].descricao);
    }
/*
    printf("\nMissão configurada:\n");
    printf("Descrição: %s\n", missoes[0].descricao);
    printf("Alvo: %s\n", missoes[0].alvo);
    printf("Quantidade objetivo: %d\n", missoes[0].qtdObjetivo);*/

    // Atribuindo uma missão para cada jogador 't'
    for (int i = 0; i < qtdterritorios; i++) {
        atribuirMissao(&t[i], missoes, totalMissoes);
    }

    exibirMapa(t, qtdterritorios); // Exibe o mapa inicial

    printf("\nIniciando as batalhas! \nATENÇÃO: O exército que ganha, adquire a quantidade de tropa que o adversário enviou para batalha!\n");

    // Loop principal do jogo
    while (menu) {
        printf("\nO que você escolhe agora?\n");
        printf("1 - Batalhar (continuar)\n");
        printf("2 - Mostrar mapa\n");
        printf("0 - Sair do jogo\n");
        printf("Digite sua opção:  ");
        scanf("%d", &escolha);
        limparBufferEntrada();

        switch (escolha) {
            case 1:
                batalha(t, qtdterritorios);
                
                for (int i = 0; i < qtdterritorios; i++) {      // Após cada batalha, verificar se alguém venceu
                    if (verificarMissao(&t[i], t, qtdterritorios)) {
                        printf("\n🏆 O jogador do exército %s cumpriu sua missão!\n", t[i].cor);
                        printf("Missão: %s\n", t[i].missao);
                        menu = 0;
                        break;
                    }
                }
                break;

            case 2:
                exibirMapa(t, qtdterritorios);
                break;

            case 0:
                printf("\nOk! espero te ver em breve!\n");
                menu = 0;
                break;

            default:
                printf("Opção inválida!\n");
        }
    };

    liberarMemoria(t);

    return 0;
}

// Função limpar o buffer, evitando sobrecarregar
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Liberando a memória alocada dinamicamente
void liberarMemoria(Territorio *t) {
    for (int i = 0; i < qtdterritorios; i++) {
        free(t[i].missao);
    }
    free(t);
    printf("\nMemória liberada. Fim de jogo!\n");
};

// Função que simula o lançamento de um dado (1 a 6)
int dados() {
    return (rand() % 6) + 1;
}

// Função para cadastrar todos os territórios/jogadores
void cadTropas(Territorio *t, int qtdterritorios) {
    printf("\n...Pressione ENTER pra continuar...\n\n");
    
    fgets(t->nome, TAM_NOME, stdin);
    for (int i = 0; i < qtdterritorios; i++) {
        printf("--- Cadastrando Território %d ---\n", i + 1);

        printf("Qual o nome deste Território? ");
        fgets(t[i].nome, TAM_NOME, stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Qual a cor do seu exército? ");
        fgets(t[i].cor, TAM_COR, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        printf("Quantas tropas ele tem? ");
        scanf("%d", &t[i].ntropas);
        limparBufferEntrada();
        printf("\n");
    }
}

// Exibe todos os territórios, tropas e missões
void exibirMapa(Territorio *t, int qtdterritorios) {
    printf("* * * * * * * *  W A R  * * * * * * * *\n");
    printf("* * * * * MAPA DE TERRITORIOS * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * *\n");
    for (int i = 0; i < qtdterritorios; i++) {
        printf("%d. %s, de cor %s,", i + 1, t[i].nome, t[i].cor);
        if (t[i].ntropas <=0) {
            printf("Territorio %s já era! Foi dominado! Ele tinha", t[i].nome);
        } else {
        printf("possui %d tropas", t[i].ntropas);
        };    
        printf(">> Missão: %s\n", t[i].missao);
    }
}

// Função que executa uma batalha entre dois territórios
void batalha(Territorio *t, int qtdterritorios) {
    int trAtaq, trDef, dado1, dado2;

    // Escolha dos participantes
    printf("Escolha o território Atacante (1-%d): ", qtdterritorios);
    scanf("%d", &trAtaq);
    printf("Escolha o território que deve se Defender (1-%d): ", qtdterritorios);
    scanf("%d", &trDef);
    limparBufferEntrada();

    // Validação das escolhas
    if (trAtaq == trDef || trAtaq < 1 || trDef < 1 ||
        trAtaq > qtdterritorios || trDef > qtdterritorios) {
        printf("Escolha inválida!\n");
        return;
    }

    // Ponteiros facilitam a manipulação direta dos territórios
    Territorio *pAtaque = &t[trAtaq - 1];
    Territorio *pDefesa = &t[trDef - 1];

    // Sorteio dos dados
    printf("\n Que rolem os dados!\n");
    dado1 = dados();
    dado2 = dados();

    printf("%s (%s) atacou com %d  VS  %s (%s) defendeu com %d\n",
        pAtaque->nome, pAtaque->cor, dado1, pDefesa->nome, pDefesa->cor, dado2);

    // Resultado da batalha
    if (dado1 > dado2) {
        pAtaque->ntropas += dado2;
        pDefesa->ntropas -= dado2;
        printf("Vitória para o exército %s!\n", pAtaque->cor);
    } else if (dado2 > dado1) {
        pDefesa->ntropas += dado1;
        pAtaque->ntropas -= dado1;
        printf("Vitória para o exército %s!\n", pDefesa->cor);
    } else {
        printf("Empate! Ninguem ganhou, ninguem perdeu!\n");
    }
}

// Função que sorteia e atribui uma missão personalizada
void atribuirMissao(Territorio *jogador, Missao *missoes, int totalMissoes) {
    int sorteio = rand() % totalMissoes; //sorteia (aleatorio) as missoes, da função missão

    // Alocação dinâmica para armazenar o texto da missão do jogador
    jogador->missao = malloc(120 * sizeof(char));
    strcpy(jogador->missao, missoes[sorteio].descricao);
    jogador->tipoMissao = missoes[sorteio].tipo;
    strcpy(jogador->alvo, missoes[sorteio].alvo);
}

// Função que verifica se o jogador cumpriu sua missão
int verificarMissao(Territorio *jogador, Territorio *mapa, int tamanho) {
    switch (jogador->tipoMissao) {

        // Tipo 1: eliminar um exército inimigo
        case 1:
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i].cor, jogador->alvo) == 0 && mapa[i].ntropas > 0)
                    return 0; // ainda existe inimigo
            }
            return 1; // missão cumprida

        // Tipo 2: dominar todos os territórios
        case 2:
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i].cor, jogador->cor) != 0)
                    return 0; // ainda há territórios de outras cores
            }
            return 1;

        // Tipo 3: proteger todos os seus territórios com pelo menos 10 tropas
        case 3:
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i].cor, jogador->cor) == 0 && mapa[i].ntropas < 10)
                    return 0;
            }
            return 1;

        // Tipo 4: conquistar X territórios (definido em qtdObjetivo)
        case 4: {
            int conta = 0;
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i].cor, jogador->cor) == 0)
                    conta++;
            }
            if (conta >= jogador->tipoMissao)
                return 1;
            return 0;
        }

        default:
            return 0;
    }
}
