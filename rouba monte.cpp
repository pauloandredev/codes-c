#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//definir a estrutura da carta
struct Carta {
    int numero;
    int naipe; //tem que ser definido porém não é utilizado nas regras fornecidas pelo prof. Edwaldo
};

// Estrutura para representar um monte de um jogador
struct Monte {
    struct Carta cartas[52]; // Assumindo que um monte pode ter no máximo 52 cartas
    int quantidadeCartas;
};

// Estrutura para representar a área de descarte
struct AreaDescarte {
    struct Carta cartas[52]; // Assumindo que a área de descarte pode ter no máximo 52 cartas
    int quantidadeCartas;
};

// Estrutura para representar o estado do jogo
struct EstadoJogo {
    struct Carta baralho[52];
    int quantidadeCartasBaralho;

    struct Monte montesJogadores[4]; // Assumindo 4 jogadores
    struct AreaDescarte areaDescarte;
    int jogadorAtual; // Índice do jogador que está jogando
};
// Função para inicializar o estado do jogo de forma completa
void inicializarJogo(struct EstadoJogo *jogo, int quantidadeJogadores) {
    // Inicializar o baralho
    jogo->quantidadeCartasBaralho = 52;
    for (int i = 0; i < jogo->quantidadeCartasBaralho; i++) {
        jogo->baralho[i].numero = i % 13 + 1; // Números de 1 a 13
        jogo->baralho[i].naipe = i / 13;
    }
    
// Embaralhar o baralho
    srand(time(NULL));
    for (int i = jogo->quantidadeCartasBaralho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Carta temp = jogo->baralho[i];
        jogo->baralho[i] = jogo->baralho[j];
        jogo->baralho[j] = temp;
    }

// Inicializar os montes dos jogadores
    for (int i = 0; i < quantidadeJogadores; i++) {
        jogo->montesJogadores[i].quantidadeCartas = 0;
    }


    // Inicializar a área de descarte
    jogo->areaDescarte.quantidadeCartas = 0;
    
    // Definir o jogador inicial
    jogo->jogadorAtual = 0;
}


// Função para imprimir as cartas no console
void imprimirCartasNoConsole(struct Carta *cartas, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Carta %d: Numero = %d, Naipe = %d\n", i + 1, cartas[i].numero, cartas[i].naipe);
    }
}

// Função para imprimir o estado atual do jogo
void imprimirEstadoJogo(struct EstadoJogo *jogo) {
    printf("\n--- Estado Atual do Jogo ---\n");
    printf("Cartas no Baralho: %d\n", jogo->quantidadeCartasBaralho);
    printf("Área de Descarte:\n");
    imprimirCartasNoConsole(jogo->areaDescarte.cartas, jogo->areaDescarte.quantidadeCartas);
    
    for (int i = 0; i < 4; i++) {
        printf("Monte do Jogador %d:\n", i + 1);
        imprimirCartasNoConsole(jogo->montesJogadores[i].cartas, jogo->montesJogadores[i].quantidadeCartas);
    }

    printf("-----------------------------\n");
}

// Função para realizar uma jogada
void realizarJogada(struct EstadoJogo *jogo) {
    // Verificar se a área de descarte não está vazia
    if (jogo->areaDescarte.quantidadeCartas > 0) {
        // Lógica para verificar se a carta da vez combina com alguma carta na área de descarte
        // Se combinar, mover a carta da área de descarte para o monte do jogador atual
        // Caso contrário, adicionar a carta da vez à área de descarte

        // Exemplo: Verificar se a carta da vez combina com a última carta na área de descarte
        struct Carta cartaDaVez = jogo->baralho[jogo->quantidadeCartasBaralho - 1];
        struct Carta ultimaCartaDescarte = jogo->areaDescarte.cartas[jogo->areaDescarte.quantidadeCartas - 1];

        if (cartaDaVez.numero == ultimaCartaDescarte.numero) {
            // A carta da vez combina com a última carta na área de descarte
            // Mover ambas as cartas para o monte do jogador atual
            jogo->montesJogadores[jogo->jogadorAtual].cartas[jogo->montesJogadores[jogo->jogadorAtual].quantidadeCartas] = ultimaCartaDescarte;
            jogo->montesJogadores[jogo->jogadorAtual].quantidadeCartas++;

            jogo->montesJogadores[jogo->jogadorAtual].cartas[jogo->montesJogadores[jogo->jogadorAtual].quantidadeCartas] = cartaDaVez;
            jogo->montesJogadores[jogo->jogadorAtual].quantidadeCartas++;

            // Reduzir a quantidade de cartas na área de descarte
            jogo->areaDescarte.quantidadeCartas--;
        } else {
            // A carta da vez não combina com a última carta na área de descarte
            // Adicionar a carta da vez à área de descarte
            jogo->areaDescarte.cartas[jogo->areaDescarte.quantidadeCartas] = cartaDaVez;
            jogo->areaDescarte.quantidadeCartas--;

            // Se a carta da vez combinar com alguma carta no topo dos montes dos outros jogadores
            for (int i = 0; i < 4; i++) {
                if (i != jogo->jogadorAtual &&
                    jogo->montesJogadores[i].quantidadeCartas > 0 &&
                    jogo->montesJogadores[i].cartas[jogo->montesJogadores[i].quantidadeCartas - 1].numero == cartaDaVez.numero) {
                    // "Roubar" o monte do jogador
                    for (int j = 0; j < jogo->montesJogadores[i].quantidadeCartas; j++) {
                        jogo->montesJogadores[jogo->jogadorAtual].cartas[jogo->montesJogadores[jogo->jogadorAtual].quantidadeCartas] =
                            jogo->montesJogadores[i].cartas[j];
                        jogo->montesJogadores[jogo->jogadorAtual].quantidadeCartas++;
                    }

                    // Zerar o monte do jogador roubado
                    jogo->montesJogadores[i].quantidadeCartas = 0;

                    // Reduzir a quantidade de cartas na área de descarte
                    jogo->areaDescarte.quantidadeCartas--;
                }
            }
        }
    }

    // Reduzir a quantidade de cartas no baralho
    jogo->quantidadeCartasBaralho--;

    // Mudar para o próximo jogador
    jogo->jogadorAtual = (jogo->jogadorAtual + 1) % 4;
}

// Função principal para jogar o Rouba-Monte
void jogarRoubaMonte(struct EstadoJogo *jogo, int quantidadeJogadores) {
    while (jogo->quantidadeCartasBaralho > 0) {
        // Exemplo: Realizar a jogada atual
        realizarJogada(jogo);

        // Exemplo: Imprimir o estado atual do jogo
        imprimirEstadoJogo(jogo);

        // Exemplo: Mudar para o próximo jogador
        jogo->jogadorAtual = (jogo->jogadorAtual + 1) % quantidadeJogadores;
    }

// Função para determinar o vencedor
int determinarVencedor(struct EstadoJogo *jogo) {
    int indiceVencedor = 0;
    int maiorQuantidadeCartas = jogo->montesJogadores[0].quantidadeCartas;

    for (int i = 1; i < 4; i++) {
        if (jogo->montesJogadores[i].quantidadeCartas > maiorQuantidadeCartas) {
            maiorQuantidadeCartas = jogo->montesJogadores[i].quantidadeCartas;
            indiceVencedor = i;
        } else if (jogo->montesJogadores[i].quantidadeCartas == maiorQuantidadeCartas) {
            // Empate
            return -1;
        }
    }
    return indiceVencedor;
}

    // Exemplo: Imprimir o estado final do jogo
    printf("\n--- Fim do Jogo ---\n");
    imprimirEstadoJogo(jogo);
}


// Função para exibir os resultados do jogo
void exibirResultados(struct EstadoJogo *jogo) {
    printf("\n--- Resultados do Jogo ---\n");

    // Determinar o vencedor
    int vencedor = determinarVencedor(jogo);

    if (vencedor == -1) {
        printf("Empate!\n");
    } else {
        printf("Jogador %d venceu!\n", vencedor + 1);
    }

    // Exibir a quantidade de cartas em mãos de cada jogador
    for (int i = 0; i < 4; i++) {
        printf("Jogador %d: %d cartas\n", i + 1, jogo->montesJogadores[i].quantidadeCartas);
    }

    // Exibir o ranking dos jogadores
    printf("\nRanking dos Jogadores:\n");
    for (int i = 0; i < 4; i++) {
        int posicao = i + 1;
        printf("Posição %d: Jogador %d com %d cartas\n", posicao, i + 1, jogo->montesJogadores[i].quantidadeCartas);
    }

    printf("---------------------------\n");
}

int main() {
    // Inicializar o estado do jogo com 4 jogadores
    struct EstadoJogo jogo;
    inicializarJogo(&jogo, 4);

    // Loop para simular o jogo (você pode ajustar conforme necessário)
    while (jogo.quantidadeCartasBaralho > 0) {
        // Realizar uma jogada
        realizarJogada(&jogo);

        // Imprimir o estado atual do jogo
        imprimirEstadoJogo(&jogo);
    }

    // Após o término do jogo, exibir os resultados
    exibirResultados(&jogo);

    return 0;
}
