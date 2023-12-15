#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TAMPILHA 1000 //definição do baralho de até mil cartas

//criacao da estrutura
typedef struct {
    int topo;
    int cartas[TAMPILHA];
} PILHA;


void push(PILHA *ps, int x)
{
    if (ps->topo > TAMPILHA) {
        printf("%s\n", "Pilha Cheia");
        system("pause");
        exit(1);
    } else
        ps->cartas[ps->topo++] = x;
}


int pop(PILHA *ps)
{
    if (ps->topo <= 0) {
        printf("%s\n", "Pilha vazia");
        system("pause");
        exit(1);
    } else
        return ps->cartas[--ps->topo];
}


void pegarMonte(PILHA *ps)
{
    ps->topo = 0;
}


int getTopItem(PILHA *ps)
{
    if(ps->topo > 0)
    {
        return ps->cartas[ps->topo-1];
    }
    return -1;
}


int getTopo(PILHA *ps)
{
	return ps->topo;
}

void setTopo(PILHA *ps)
{
    ps->topo = 0;
}

//--------------------declaração de funções----------------------------------------------------------
void sair();
void criarArq();
int inicio();
void clear();
void pause();
void menu();
void creditos();
int carta(void);
int outrosMontes(int, PILHA *, int, int);
int meuMonte(PILHA *, int, int);
int noDescarte(int *, PILHA *, int, int);
int prox(int, int *, int, int, PILHA *, int);
int vencedor(int, PILHA *);
//--------------------função para pausar a execução e aguardar a tecla Enter---------------------------

void pause()
{
    fflush(stdin);
    printf("\n\nPressione enter para continuar");
    scanf("%*c");
}
//-------------------------------------------------------------------------------------------
void menu()
{
    clear();
    printf("0 - Regras do Jogo;\n");
	printf("1 - Iniciar partida;\n");
	printf("2 - Gerar novo arquivo rouba-monte.txt;\n");
	printf("3 - Creditos;\n");
	printf("4 - SAIR;\n");
}
//-------------------------------------------------------------------------------------------
void regras()
{
	clear();
	printf("--- R E G R A S --- \n \n ");
	printf("O jogo utiliza um ou mais baralhos normais e tem regras muito simples. \n Cartas são distinguidas apenas pelo valor (ás, dois, três, . . .), \n ou seja, os naipes das cartas não são considerados \n (por exemplo, ás de paus e ás de ouro têm o mesmo valor).\n");
	printf("Inicialmente as cartas são embaralhadas e colocadas em uma pilha na mesa de \n jogo,chamada de pilha de compra, com face voltada para baixo.\n");
	printf("Durante o jogo, cada jogador mantém um monte de cartas, com face voltada para cima;\n em um dado momento o monte de um jogador pode conter zero ou mais cartas.\n");
	printf("No início do jogo, todos os montes dos jogadores têm zero cartas. Ao lado da pilha de compras encontra-se \n uma área denominada de área de descarte, inicialmente vazia, e todas as cartas colocadas na área de descarte \n são colocadas lado a lado com a face para cima (ou seja, não são empilhadas).\n");
	printf("\n \n \n J O G A B I L I D A D E \n \n" );
	printf("O jogador que tem a vez de jogar retira a carta de cima da pilha de compras e a mostra aos outros jogadores; vamos chamar essa carta de carta da vez.\n");
	printf("Se a carta da vez for igual a alguma carta presente na área de descarte, o jogador retira essa carta da área de descarte colocando-a,\n juntamente com a carta da vez, no topo de seu monte, com as faces voltada para cima, e continua a jogada\n");
	printf("Se a carta da vez for igual à carta de cima de um monte de um outro jogador, o jogador rouba esse monte\n, empilhando-o em seu próprio monte, coloca a carta da vez no topo do seu monte, face para cima, e continua a jogada.\n");
	printf("Se a carta da vez for igual à carta no topo de seu próprio monte, o jogador coloca a carta da vez no topo de seu próprio monte, com a face para cima, e continua a jogada.\n");
	printf("Se a carta da vez for diferente das cartas da área de descarte e das cartas nos topos dos montes, o jogador a coloca na área de descarte,\n face para cima, e a jogada se encerra (ou seja, o próximo jogador efetua a sua jogada).\n Note que esse é o único caso em que o jogador não continua a jogada.\n");
	printf("O jogo termina quando não há mais cartas na pilha de compras. O jogador que tiver o maior monte (o monte contendo o maior número de cartas) ganha o jogo.\n Se houver empate, todos os jogadores com o monte contendo o maior número de cartas ganham o jogo.\n");
}

//-------------------------------------------------------------------------------------------
void creditos()
{
    clear();
    printf("Paulo André de Oliveira Félix - paulo.1694451@discente.uemg.br;\n");
    printf("Prof. Edwaldo Soares Rodrigues - Prof. da disciplina Algoritmos e  Estrutura de Dados II ;\n");
    printf("Universidade do Estado de Minas Gerais - UEMG - Campus Divinópolis;\n");
    printf("Ao Cruzeiro por não ter caído para a série B e conquistado a vaga pra Sula;\n");
    printf("A minha mãe por ter feito um café mais que especial nos dias de programação desse trabalho;\n");
    printf("A Deus por nunca ter me abandonado;\n");
}
//------------------------------função para manipular o monte dos outros jogadores-------------------------------
int outrosMontes(int qtdJogadores, PILHA *jogador, int mao, int jAtual)
{
    int j;
	for(j = 0; j < qtdJogadores; j++)
	{
		if(jAtual != j)
		{
			if(mao == getTopItem(&jogador[j]))
			{
				pegarMonte(&jogador[j]);
				push(&jogador[jAtual], mao);
				return 1;
				break;
			}
		}
	}
	return 0;
}
//--------------------manipula o monte do jogador atual--------------------------------------
int meuMonte(PILHA *jogador, int mao, int jAtual)
{
	if(mao == getTopItem(&jogador[jAtual]))
	{
		push(&jogador[jAtual], mao);
		return 1;
	}
	return 0;
}
//------------------verifica e manipula a pilha de descarte-------------------------------------
int noDescarte(int *descarte, PILHA *jogador, int mao, int jAtual)
{
    int j;
	for(j = 1; j <= descarte[0]; j++)
	{
		if(mao == descarte[j])
		{
			push(&jogador[jAtual], mao);
			descarte[j] = 0;
			return 1;
			break;
		}
	}
	return 0;
}
//------------------determina o próximo jogador com base nas regras-------------------------------------
int prox(int achou, int *descarte, int mao, int qtdJogadores, PILHA *monte, int jAtual)
{
    if(achou == 0)
    {
        descarte[descarte[0]+1] = mao;
        descarte[0] = descarte[0] + 1;
        if(getTopo(monte) != 0)
        {
            if(jAtual >= qtdJogadores-1)
                jAtual = 0;
            else
                jAtual++;
        }
    }
    else
    {
        if(getTopo(monte) != 0)
        {
            jAtual=jAtual;
        }
    }
    return jAtual;
}
//-------------------função para determinar o vencedor do jogo---------------------------------
int vencedor(int qtdJogadores, PILHA * jogador)
{
    int ganhador = 0, i, count=0;
    for(i=0; i < qtdJogadores; i++)
    {
        if(getTopo(&jogador[ganhador]) > getTopo(&jogador[i]))
            count++;
        if(getTopo(&jogador[ganhador]) < getTopo(&jogador[i]))
        {
            ganhador = i;
            count++;
        }


    }

    if(count == 0)
        return -1;
    return ganhador;
}
//---------------------gerar valores aleatorios representando uma carta------------------------------------------

int carta(void)
{
    int carta = rand() % 14;
    if(carta == 0)
        carta++;
    return carta;
}
//-----------------------função que inicia o jogo de rouba montes---------------------------
int inicio()
{
    clear();
    int cartas,
        qtdJogadores,
        itens[TAMPILHA],
        i,
        j,
        k,
        mao,
        achou,
        descarte[TAMPILHA+1],
        repet = 1,
        jAtual = 0,
        opt,
        jCampeao;
    FILE * Arquivo;
    PILHA monte;

    Arquivo = fopen ("roubaMonte.txt","r"); 

    if (Arquivo==NULL) 
    {
        printf("Arquivo roubaMonte.txt nao encontrado!!!\n");
        printf("Acesse o menu 2 para gerar um arquivo aleatorio.\n");
        return 0;
    }

    fscanf (Arquivo, "%d", &cartas); 
    fscanf (Arquivo, "%d", &qtdJogadores); 
    printf("Nr de jogadores: %d\n", qtdJogadores);
    printf("Nr de cartas: %d\n", cartas);
    printf("---------------------\n");

    PILHA jogador[qtdJogadores];

    for(i=0; i<TAMPILHA+1; i++) 
        descarte[i] = 0;

    setTopo(&monte); 

    for(i=0; i<cartas; i++) 
        fscanf(Arquivo, "%d", &itens[i]);

    fclose(Arquivo);

    for(i=0; i<qtdJogadores; i++)
        setTopo(&jogador[i]);

    for(i=cartas-1; i>=0; i--)
        push(&monte, itens[i]);

    for(i=0; i<cartas; i++) 
        printf(" %d ", itens[i] );

    printf("\n---------------------\n");

    while(repet)
    {
        mao = pop(&monte);
        achou = 0;
        achou = outrosMontes(qtdJogadores, jogador, mao, jAtual);
        if(achou != 1) 
            achou = meuMonte(jogador, mao, jAtual);
        if(achou != 1) 
            achou = noDescarte(descarte, jogador, mao, jAtual);
        jAtual = prox(achou, descarte, mao, qtdJogadores, &monte, jAtual);
        if(getTopo(&monte) == 0)
            repet = 0;
    }

    jCampeao = vencedor(qtdJogadores, jogador);
    if(jCampeao != -1)
        printf("Ganhador jogador %d, cartas %d.", jCampeao+1, getTopo(&jogador[jCampeao]));
    else
    {
        for(; qtdJogadores > 0; qtdJogadores-- )
            printf("Ganhador jogador %d, cartas %d;\n", qtdJogadores, getTopo(&jogador[qtdJogadores-1]));
    }
    printf("\n---------------------\n");
}
//------------------cria um arquivo de configuração-----------------------------------------
void criarArq()
{
    int qtdPlays,
        qtdCarts;
    FILE * Arquivo;

    clear();
    printf("Informe a quantidade de jogadores: ");
    scanf("%d", &qtdPlays);
    printf("Informe a quantidade de cartas: ");
    scanf("%d", &qtdCarts);

    Arquivo = fopen ("roubaMonte.txt","w"); 
    fprintf (Arquivo, "%d %d\n", qtdCarts, qtdPlays);
    for( ; qtdCarts > 0; qtdCarts--)
        fprintf (Arquivo, "%d ", carta());
    fclose (Arquivo);

    printf("Arquivo roubaMonte.txt gerado com sucesso!!!");
}
//-------------------------------------------------------------------------------------------
void sair()
{
    clear();
    printf("Saindo!!!");
}
//-------------------------------------------------------------------------------------------
void clear()
{
    system("cls||clear");
}
//-------------------------------------------------------------------------------------------
int main()
{
    srand ( time(NULL) );
    int opt;

    do
    {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opt);

        switch(opt)
        {
        	case 0: regras(); pause(); break;
            case 1: inicio();   pause();    break;
            case 2: criarArq(); pause();    break;
            case 3: creditos(); pause();    break;
            case 4: sair();                 break;
        }
    }
    while(opt != 4);

    //system("pause");
    return 0;
}
