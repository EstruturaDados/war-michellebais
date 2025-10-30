// Definindo Constantes e bibliotecas Globais
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TAM_NOME 30
#define TAM_COR 10
#define MAX_TERRITORIOS 10

int numTerrit = 0;  //numero dado a cada tropa
int qtdterritorios; //numero de equipes (territorios) escolhido pelo usuario

// Função limpar o buffer, evitando sobrecarregar
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c!= EOF); 
};

// Definindo o Territorio (Struct)
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int ntropas;
} Territorio;

//Função Jogar Dados (numero aleatorio de 1 a 6)
int dados() {
    return (rand() % 6) + 1;
};

//Função cadastrar tropas
void cadTropas(Territorio *t, int qtdterritorios){    
    printf("\n...Pressione ENTER pra continuar...\n\n");
    fgets(t ->nome, TAM_NOME, stdin);           //chamar o fgets antes do for pra ler o primeiro loop
    for (int i = 0; i < qtdterritorios; i++) {  // Loop até o total de territorios escolhido pelo usuario
        printf("--- Cadastrando Territorio %d ---\n", (numTerrit+1));
        printf("Qual o nome deste Territorio? ");
        fgets(t[i].nome, TAM_NOME, stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0'; //procura \n na string e substitui pelo nulo (\0) 

        printf("Qual a cor do seu exército? ");
        fgets(t[i].cor, TAM_COR, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        t ->nome[strcspn(t ->nome, "\n")] = '\0';
        t ->cor[strcspn(t ->cor, "\n")] = '\0';

        printf("Quantas tropas ele tem? ");
        scanf("%d", &t[i].ntropas);
        printf("\n");

        ++numTerrit; //incrementa o numero dado a cada tropa

        limparBufferEntrada();
    };
};

//Função exibir Mapa
void exibirMapa(Territorio *t, int qtdterritorios) { //'exibirMapa' recebe como argumento a struct denominada '*t' do tipo 'Territorio' e a variavel 'qtdterritorios' (valor vem do usuário)
    printf("* * * * * * * *  W A R  * * * * * * * *\n");
    printf("* * * * * MAPA DE TERRITORIOS * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * *\n");

    for (int i = 0; i < qtdterritorios; i++) {
        printf("TERRITÓRIO %d\n", i + 1);
        printf("  Denominado: %s\n", t[i].nome);
        printf("  Conhecido por ser o Exército %s\n", t[i].cor);
        if (t[i].ntropas <=0) {
            printf("  Territorio %s já era! Foi dominado!\n\n", t[i].nome);
        } else {
        printf("  Possui %d tropas\n\n", t[i].ntropas);
        };
    };
};

//Função Ataque x Defesa
void batalha(Territorio *t, int qtdterritorios) {
    int trAtaq;         //tropa ataque
    int trDef;          //tropa defesa
    int dado1, dado2;   //resultado dos dados ataque (1) e defesa (2)
    int atcTotal, defTotal; //soma de tropas

    printf("Escolha o territorio Atacante: (de 1 a %d) ", qtdterritorios);
    scanf("%d", &trAtaq);
    printf("Escolha o territorio que deve se Defender: (de 1 a %d) ", qtdterritorios);
    scanf("%d", &trDef);

    if (trAtaq == trDef || trAtaq < 1 || trDef < 1 || trAtaq > qtdterritorios || trDef > qtdterritorios) {
        printf("Escolha inválida!\n");
        return;
    };

    Territorio *pAtaque = &t[trAtaq - 1];  //criando ponteiro para ataque e defesa, pra conseguir identificar pelo nome depois
    Territorio *pDefesa = &t[trDef - 1];

    printf("\nQue rolem os dados...  e que a Sorte esteja com vocês!!!\n");
    dado1 = dados();
    dado2 = dados();

    printf("\n\n\nUau! O Exército %s (%s) enviou %d tropas enquanto o %s (%s) enviou %d tropas!\n\n", pAtaque -> cor, pAtaque -> nome, dado1, pDefesa -> cor, pDefesa -> nome, dado2); //t[trAtaq - 1 - 1].nome imprime o nome ao invés do número. t[trAtaq - 1 - 1] acessa o território que o jogador escolheu (- 1, porque começa do zero)

    if (dado1 == dado2) {
        printf("Belo acordo de paz! Mas uma GUERRA nao é feita de EMPATES...!\n");
        return;
    } else if (dado1 > dado2) {
        printf("Parabéns! O Exército %s (%s) atacou e ganhou mais pessoal pro seu exército!\n", pAtaque -> cor, pAtaque -> nome);

        // Atualiza as tropas de ambos
        pAtaque -> ntropas += dado2;
        pDefesa -> ntropas -= dado2;

        printf("Agora o Exército %s ja tem %d tropas...\n", pAtaque -> cor, pAtaque -> ntropas);
    } else {
        printf("Owl! O Exército %s vai precisar se recuperar dessa: perdeu %d soldados para seu adversário...\n", pAtaque -> cor, dado1);

        // Atualiza as tropas de ambos
        pDefesa -> ntropas += dado1;
        pAtaque -> ntropas -= dado1;

        printf("... enquanto o Exército  %d tem %d tropas...\n", pDefesa -> cor, pDefesa -> ntropas);
    }      
    limparBufferEntrada();
};

// Função Principal (main)
int main() {
    int escolha;
    srand(time(NULL));

    printf("* * * * * * * *   W A R   * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * *\n");
    printf("Vamos começar definindo os Territórios...\n");
    printf("Quantos Territórios teremos?  ");
    if (scanf("%d", &qtdterritorios) != 1) {
        printf("Entrada inválida! Inicie o jgo novamente.\n");
        exit(1);
    };
    limparBufferEntrada();
    
    Territorio *t = malloc(qtdterritorios*sizeof(Territorio)); //alocação de memoria de acordo com a qtd indicada pelo usuario, para a struct Territorios, que corresponde ao ponteiro 't'
    if (!t) {
        printf("Erro ao alocar memória!\n");
        return 1;
    };

    cadTropas(t, qtdterritorios);
    printf("\n");
    exibirMapa(t, qtdterritorios);
           
    //Iniciando as jogadas
    printf("Iniciando o modo caos... que comecem as batalhas!!!\n\n");
    batalha(t, qtdterritorios);
    
    int menu = 1;
    while (menu) {
        printf("\nO que você escolhe agora?\n");
        printf("1 - Continuar\n");
        printf("2 - Mostrar mapa\n");
        printf("0 - Sair do jogo\n");
        printf("Digite sua opção:  ");
        scanf("%d", &escolha);
        limparBufferEntrada();

        switch (escolha) {
            case 1:
                batalha(t, qtdterritorios);
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
                break;
        };
    };

    //Liberando o espaço alocado

    free(t);

    printf("\n...Memoria liberada!!!\n");

    printf("\nEtapa finalizada!\n");

    return 0;
};
