//rouba monte
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//definir a estrutura da carta
struct Carta {
    int numero;
    int naipe; //tem que ser definido por�m n�o � utilizado nas regras fornecidas pelo prof. Edwaldo
};

//iniciar o baralho

void inicializarBaralho(struct Carta *baralho, int quantidadeCartas) {
    // Inicializar vari�veis
    int indiceCarta = 0;

    // Preencher o baralho
    for (int naipe = 0; naipe < 4; naipe++) { // Loop para cada naipe (0 a 3)
        for (int numero = 1; numero <= 13; numero++) { // Loop para cada n�mero (1 a 13)
            // Verificar se ainda h� espa�o no baralho
            if (indiceCarta < quantidadeCartas) {
                // Preencher a carta no baralho
                baralho[indiceCarta].numero = numero;
                baralho[indiceCarta].naipe = naipe;
                indiceCarta++;
            } else {
                // Se o baralho estiver cheio, interromper o loop
                break;
            }
        }
    }
}


// fun��o embaralhar o baralho

void embaralharBaralho(struct Carta *baralho, int quantidadeCartas) {
    srand(time(NULL)); // Inicializar a semente aleat�ria

    for (int i = quantidadeCartas - 1; i > 0; i--) {
        // Gerar um �ndice aleat�rio entre 0 e i (inclusive)
        int j = rand() % (i + 1);

        // Trocar as cartas nas posi��es i e j
        struct Carta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp;
    }
}


int main() {
    // Definir o tamanho do baralho
    int quantidadeCartas = 52;

    // Criar um array para representar o baralho
    struct Carta baralho[quantidadeCartas];

    // Chamar a fun��o para inicializar o baralho
    inicializarBaralho(baralho, quantidadeCartas);

// Imprimir as cartas do baralho antes de embaralhar (apenas para verificar)
    printf("Baralho antes de embaralhar:\n");
    for (int i = 0; i < quantidadeCartas; i++) {
        printf("Carta %d: Numero = %d, Naipe = %d\n", i + 1, baralho[i].numero, baralho[i].naipe);
    }

    // Chamar a fun��o para embaralhar o baralho
    embaralharBaralho(baralho, quantidadeCartas);

    // Imprimir as cartas do baralho depois de embaralhar
    printf("\nBaralho depois de embaralhar:\n");
    for (int i = 0; i < quantidadeCartas; i++) {
        printf("Carta %d: Numero = %d, Naipe = %d\n", i + 1, baralho[i].numero, baralho[i].naipe);
    }

    return 0;
}


//mostrar as cartas na tela

//implementar a l�gica do jogo

//exibir resultados
