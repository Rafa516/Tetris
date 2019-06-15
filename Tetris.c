
/*Descricao: < Programa de Jogo Tetris em C >*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void limpa(char game[][20])
{
	/* funçao que ler  a matriz game, onde sao recebidas as  sequencias
	e preenchimento com espacos em branco para limpa-la*/
	int i, j;
	for(i = 0; i < 6; i++) /*percorre o vetor de  linhas*/
	{
		for(j = 0; j < 20; j++) /*percorre o vetor de  colunas*/
		{
			game[i][j] = ' ';
		}
	}
}

void clear()
{
	/*limpa a tela*/
	system("clear || cls");
}

void roda(char game[][20], char *seq, int *vertical, int *coluna)
{
	/*funcao que roda a sequencia apresentada(peca) na tela, e  a verificacao dela
	para nao ultrapassar os limites determinados da matriz(colisao)*/
	int tam = strlen(seq);
	int i;
	if(*vertical) /*verifica se a sequencia esta na posicao vertical*/
	{
		if(((*coluna) + tam) <= 20) /*verifica se a sequencia nao estoura o vetor*/
		{
			limpa(game);
			for(i = 0; i < tam; i++)
			{
				game[0][*coluna + i] = seq[i];/*atribui a matriz game ao vetor da sequencia apresentada ao passo que vai girando
                                                se ela nao estourar o vetor e colocando-a na posicao horizontal*/
			}
			if(*vertical == 1) *vertical = 0;
			else *vertical = 1;
		}
	}
	else    /*Esse else so ocorre caso a sequencia(peca) esteja na posicao horizontal*/
	{
		limpa(game);/*Executa a limpeza da matriz game*/
		for(i = 0; i < tam; i++)
		{
			game[i][*coluna] = seq[i];/*faz o mesmo que o primeiro for, porem, gira da posicao horizontal para a vertical*/
		}
		if(*vertical == 1) *vertical = 0;
		else *vertical = 1;
	}
}

void cair(char game[][20], char *seq, int vertical, int *coluna)
{
	/*funcao que derruba o elemento(peca) da sequencia apresentada, verificando tambem a existencia
	de algum outro elemento(peca) da sequencia na posicao na qual foi derrubado*/
	int i, tam = strlen(seq), flag = 0, j;
	if(vertical)
	{
		j = 6;
		while(j < 15)
		{
			if(game[j][*coluna] != ' ') /*verifica a existencia de outro elemento(peca) na posicao na qual foi derrubada*/
			{
				flag = j;
				break;
			}
			j++;
		}
		for(i = 0; i < tam; i++)
		{
			game[j - i - 1][*coluna] = seq[i];/*Derruba o elemento(peca) verticalmente e com o auxilio da verificacao
			da existencia de outro elemento(peca), derruba no espaco que esteja vazio ou acima de um espaco ja ocupado*/
		}
	}
	else
	{
		j = 6;
		flag = 0;
		while(j < 15)
		{
			for(i = 0; i < tam; i++)
			{
				if (game[j][*coluna + i] != ' ') /*verifica tambem a existencia de outro elemento(peca) na posicao*/
				{
					flag = j;
				}
			}
			if(flag != 0)
			{
				break;
			}
			j++;
		}
		for(i = 0; i < tam; i++)
		{
			game[j - 1][*coluna + i] = seq[i];/*Derruba o elemento(peca) horizontalmente e com o auxilio da verificacao
			da existencia de outro elemento(peca), derruba no espaco que esteja vazio ou acima de um espaco ja ocupado*/
		}
	}
}

void esquerda(char game[][20], char *seq, int vertical, int *coluna)
{
	/*Funcao que movimenta o elemento(peca) da sequencia para a esquerda*/
	int tam = strlen(seq);
	int i;
	if(*coluna > 0)
	{
		/*Verifica se a posicao do elemento(peca) da sequencia nao esta na posicao maxima a esquerda
		                para nao estourar a matriz(colisao)*/
		limpa(game);
		*coluna = *coluna - 1;
		if(vertical)
		{
			for(i = 0; i < tam; i++)
			{
				game[i][*coluna] = seq[i];/*Movimenta verticalmente o elemento(peca) para a esquerda*/
			}
		}
		else
		{
			for(i = 0; i < tam; i++)
			{
				game[0][(*coluna) + i] = seq[i];/*Movimenta horizontalmente o elemento(peca)  para a esquerda*/
			}
		}
	}
}

void direita(char game[][20], char *seq, int vertical, int *coluna)
{
	/*Movimenta verticalmente o elemento(peca) para a direita*/
	int tam = strlen(seq);
	int i;
	if(*coluna < 19) /*Verifica se o elemento(peca) da sequencia nao se encontra na posicao maxima a direita*/
	{
		if(vertical)
		{
			*coluna = *coluna + 1;
			limpa(game);
			for(i = 0; i < tam; i++)
			{
				game[i][*coluna] = seq[i]; /*Atribui o valor para a matriz game, movimentando o elemento (peca)para a direita verticalmente*/
			}
		}
		else
		{
			*coluna = *coluna + 1;
			if(((*coluna) + tam) <= 20) /*Verifica se o elemento(peca) nao estoura a matriz na posicao maxima horizontal a direita*/
			{
				limpa(game);
				for(i = 0; i < tam; i++)
				{
					game[0][(*coluna) + i] = seq[i]; /*Atribui o valor para a matriz game, movimentando o elemento(peca) para a direita horizontalmente*/
				}
			}
			else
			{
				*coluna = *coluna - 1; /*Evita a contagem desnecessaria para a direita depois de alcancar a posicao maxima a direita,
                                        impedindo o elemento(peca) de ultrapassar para a proxima linha sem autorizacao(bug)*/
			}
		}
	}
}

int lerSeq(char *seq, char game[][20])
{
	/*Realiza a leitura de cada elemento(peca) da sequencia do jogo*/
	int i, tam = strlen(seq);
	for(i = 0; i < tam; i++)
	{
		game[i][9] = seq[i];/*Atribui o valor para a matriz game*/
	}
	return 1;
}
void imprimir(char game[][20], int tot_pontos)
{
	/*Imprime na tela o ambiente do jogo com a pontuacao e instrucoes*/
	printf("\n\n");
	clear();
	int i, j;
	printf("  +--------------------+ PONTUACAO: %d\n", tot_pontos);
	for (i = 0; i < 15; i++)
	{
		if (i == 6)
			printf("=>+");
		else
			printf("  |");
		for (j = 0; j < 20; j++)
			printf("%c", game[i][j]);
		if (i == 6) printf("+<=\n");
		else printf("|\n");
	}
	printf("  +--------------------+\n");
	printf("R-rotar D-direita E-esquerda C-cair\n");/*Instrucoes para a realizacao das acoes no jogo*/
	printf("ACAO: ");
}

void verifica_linha(char game[][20], int *pontos)
{
	/*Funcao que verifica a existencia de linhas completas no Tetris para a sua exclusao da tela
	e contagem dos respectivos pontos*/
	int i, j, cont, k;
	for (i = 6; i < 15; i++)
	{
		cont = 0;
		for (j = 0; j < 20; j++)
		{
			if (game[i][j] == ' ')
			{
				cont++;
			}
		}
		if (cont == 0)
		{
			break;
		}
	}
	if(cont == 0)
	{
		for(j = 0; j < 20; j++)
		{
			game[i][j] = 'X';/*Atribui a linha completa uma linha de X para mostrar que esta completa e sumir posteriormente(obs: com a funcao fflush(stdout) seu aparecimento nao e perceptivel) */
		}
		*pontos = *pontos + 100;/*Adiciona os respectivos pontos a cada linha completa*/
		limpa(game);
		imprimir(game, *pontos);
		getchar();
		k = i;
		while(k > 6)
		{
			for(j = 0; j < 20; j++)
			{
				game[k][j] = game[k - 1][j];/*Derruba os elementos(pecas) que restaram na tela do jogo apos a remocao da linha completa*/
			}
			k--;
		}
	}
	imprimir(game, *pontos);
	getchar();
}

void fimDoJogo(int fim, int pontos)
{
	/*funcao que eh executada apos a verificacao da funcao terminaJogo() para printar na tela
	o respectivo resultado */
	int i, j;
	char game[15][20];
	if(fim)
	{
		clear();
		for(i = 0; i < 15; i++)
		{
			for(j = 0; j < 20; j++)
			{
				game[i][j] = 'X';/*Preenche toda a tela de X para indicar o fim do jogo*/
			}
		}
		imprimir(game, pontos);
		printf("*** YOU LOSE!!!Tecle <enter> para sair");/*Mensagem que eh executada quando o jogador ultrapassa o limite da linha-seta
                                                            da tela do jogo*/
		getchar();
		getchar();
	}
	else
	{
		clear();
		printf("*** PARABENS!!! VOCE CHEGOU AO FIM DO JOGO COM %d PONTOS!!!\nTecle <enter> para sair\n", pontos);/*Mensagem mostrada quando o usuario termina o jogo com sucesso*/
		getchar();
	}
}

int terminaJogo(char game[][20], int pontos)
{
	/*Funcao que verifica se o jogador ultrapassou o limite da linha-seta do jogo e finaliza o jogo em caso positivo*/
	int i;
	for(i = 0; i < 20; i++)
	{
		if(game[6][i] != ' ')
		{
			fimDoJogo(1, pontos);
			return 0;
		}
	}
	return 1;
}

int main()
{
	FILE *fp;
	char game[15][20], seq[70][7], op;
	int i = 0, vertical, coluna, pontos = 0, j;
	fp = fopen("sequencia.txt", "r");
	while(fscanf(fp, "%s", seq[i] ) > 0)  /*realiza a leitura da sequencia(pecas),atraves da leitura do arquivo de texto.*/
	{
		i++;
	}
	for(i = 0; i < 15; i++)
	{
		for(j = 0; j < 20; j++)
		{
			game[i][j] = ' ';
		}
	}
	imprimir(game, pontos);
	i = 0;
	while(i < 70 && lerSeq(seq[i], game))
	{
		vertical = 1;
		coluna = 9;
		imprimir(game, pontos);
		do
		{
			scanf("%c", &op);
			fflush(stdout);/*limpa o buffer prevenindo problemas que possam atrapalhar a execucao, gerando mais praticidade no jogo.*/
			switch(op)
			{
				/*Switch responsavel pelos movimentos do jogo*/
			case 'r':
				roda(game, seq[i], &vertical, &coluna);
				imprimir(game, pontos);
				break;
			case 'd':
				direita(game, seq[i], vertical, &coluna);
				imprimir(game, pontos);
				break;
			case 'e':
				esquerda(game, seq[i], vertical, &coluna);
				imprimir(game, pontos);
				break;
			default:
				break;
			}
		}
		while(op != 'c');
		cair(game, seq[i], vertical, &coluna);
		limpa(game);
		if(terminaJogo(game, pontos)) /*chamada da verificacao da funcao que determina se executa o fim do jogo*/
		{
			imprimir(game, pontos);
			verifica_linha(game, &pontos);
			imprimir(game, pontos);
			limpa(game);
			i++;
		}
		else
		{
			return 0;/*finaliza o jogo caso o jogador perca*/
		}
	}
	fimDoJogo(0, pontos); /*funcao que executa o fim do jogo no caso de terminadas as sequencias*/
	return 0;
}
