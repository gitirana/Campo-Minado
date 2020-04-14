#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

void localBomba(int local[100]);

void printarMapa(int local[100], int mapaAberto[100])
{
    int i;

    system("cls");

    for (i = 1; i <= 100; i++)
    {
        if (mapaAberto[i - 1] == 1) // verifica se o local do mapa ja foi aberto ou nao
        {
            printf("%d | ", local[i - 1]);
        }
        if (mapaAberto[i - 1] == 0) // mantem o mapa fechado, sem mostrar posicao das bombas
        {
            printf("* | ");
        }
        //interface tabuleiro
        if (i % 10 == 0)
        {
            printf("\n");
            printf("---------------------------------------\n");
        }
        if (i == 100)
        {
            printf("\n");
        }
    }
}

int main(void)
{
    int local[100] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // vetor pra colocar as bombas (so eh mostrada pro usuario depois que a posicao for selecionada)
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int mapaAberto[100] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // vetor pra colocar as jogadas e checar se a posicao ja foi aberta ou nao
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int count = 0, i = 0;
    char playagain;
    int jogada = 0, vez = 0, k = 0;
    int lose = 0, win = 0, player1 = 0, player2 = 0;
    do
    {
        count = 1;
        lose = 0;
        win = 0;
        vez = 0;

        for (k = 0; k < 100; k++) //zera o vetor depois de comecar um novo jogo
        {
            mapaAberto[k] = 0;
            local[k] = 0;
        }

        localBomba(local);

        do
        {
            printarMapa(local, mapaAberto);

            if (vez % 2 == 0) //pede e memoriza a jogada do 1 jogador
            {
                printf("Vez do jogador 1: \n");
                printf("Digite sua jogada (1 - 100)\n");
                scanf("%d", &jogada);
            }
            else
            {
                printf("Vez do jogador 2: \n"); //pede e memoriza a jogada do 2 jogador
                printf("Digite sua jogada (1 - 100)\n");
                scanf("%d", &jogada);
            }

            //jogadas invalidas
            if (jogada < 1 || jogada > 100) //se passar o tamanho do vetor
            {
                system("cls");

                printf("Jogada invalida. Coloque um numero entre 1 e 100\n");

                Sleep(2000);
            }
            else
            {
                if (mapaAberto[jogada - 1] != 0) //se tentar selecionar uma posicao aberta
                {
                    system("cls");

                    printf("Jogada invalida. Escolha um campo fechado\n");

                    Sleep(2000);
                }
                else
                {
                    mapaAberto[jogada - 1] = 1;

                    if (local[jogada - 1] == 1) //condicao de derrota
                    {
                        lose = 1; //perde e sai do loop

                        if (vez % 2 == 0)
                        {
                            player1 = 1;
                        }
                        else
                        {
                            player2 = 1;
                        }
                    }

                    if(count == 80 && lose == 0)
                    {
                        win = 1;

                        if (vez % 2 == 0)
                        {
                            player1 = 1;
                        }
                        else
                        {
                            player2 = 1;
                        }
                    }

                    printarMapa(local, mapaAberto);

                    count++; //qntd de rodadas
                    vez++;
                }
            }

        }while(lose == 0 && win == 0);

        if (lose == 1)
        {
            if (player1 == 1)
            {
                printf("Jogador 1 perdeu!\n");
            }
            else
            {
                printf("Jogador 2 perdeu!\n");
            }
        }
        
        if(win == 1)
        {
            if (player1 == 1)
            {
                printf("Jogador 1 ganhou!\n");
            }
            else
            {
                printf("Jogador 2 ganhou!\n");
            }
        }

        printf("Deseja jogar novamente?\n");
        scanf("%s", &playagain);

    } while (playagain == 's');

    return 0;
}

void localBomba(int local[100]) //funcao para gerar as bombas
{
    int j = 0;
    int numBomba = 0;

    srand(time(NULL));

    while (numBomba < 20)
    {
        j = rand() % 100; //gera em posicoes aleatorias

        if (local[j] != 1)
        {
            local[j] = 1;
            numBomba++;
        }
    }
}
