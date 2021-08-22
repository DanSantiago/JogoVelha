#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//gera o tabuleiro do jogo e define o tempo do turno da máquina
char velha [3][3];
int t=500000;
int mlinha, mcoluna;

//atualiza o tabuleiro do jogo
void tabuleiro()
{
	printf("\n\n %c | %c | %c ", velha[0][0], velha[0][1], velha[0][2]);
	printf("\n---+---+---");
	printf("\n %c | %c | %c ", velha[1][0], velha[1][1], velha[1][2]);
	printf("\n---+---+---");
	printf("\n %c | %c | %c \n", velha[2][0], velha[2][1], velha[2][2]);
}

//limpa o tabuleiro quando termina o jogo
void limpatabuleiro()
{
	int i, j;
	
	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
			velha[i][j] = ' ';
}

//imprime jogo da velha na tela
void jogo()
{
	printf("\n\nJOGO DA VELHA");
	printf("\n===============");
}

//imprime a animação da jogada da maquina
void machine ()
{
		printf("\nVez da Maquina: . ");
		usleep(t);
		system("clear");
		jogo();		
		tabuleiro();		
		printf("\nVez da Maquina: .. ");
		usleep(t);
		system("clear");
		jogo();		
		tabuleiro();		
		printf("\nVez da Maquina: ... ");
		usleep(t);	
		system("clear");
		jogo();		
		tabuleiro();		
}

//checa se alguém ganhou
int win(int x, int y)                                                  
{
		int c=0;

		if(velha[x-1][y-1]!=' ')
		{
			if(velha[x-1][0]==velha[x-1][1] && velha[x-1][0]==velha[x-1][2])
				c++;	
			else if(velha[0][y-1]==velha[1][y-1] && velha[0][y-1]==velha[2][y-1])
				c++;
			else if(x==y)
			{
					 if(velha[0][0]==velha[1][1] && velha[0][0]==velha[2][2])
						c++;
					 else if(((x-1)+(y-1))==2)
								if(velha[0][2]==velha[1][1] && velha[0][2]==velha[2][0])		
									c++;
			}		 		
			else if(((x-1)+(y-1))==2)
					 if(velha[0][2]==velha[1][1] && velha[0][2]==velha[2][0])		
						c++;		
		}		 
		return (c);
}

//checa se deu velha
int dvelha()
{
			int i, j, reset;
			
			for(i=0; i<3; i++)
				for(j=0; j<3; j++)
					if (velha[i][j]=='O' || velha[i][j]=='X')
					reset++;
					
			if(reset==9)
				printf("\nDeu velha");
				
			return (reset);
}

//gera a jogada da maquina (modo simples) até achar um espaço vazio
void turnmachine()
{
			int i;
	
			for(i=0; ; i++)
			{			
				srand(time(NULL));
				mlinha = 1 + rand() % 3;
				usleep(t);
				srand(time(NULL));
				mcoluna = 1 + rand() % 3;
				if(velha[mlinha-1][mcoluna-1]!='O' && velha[mlinha-1][mcoluna-1]!='X')
				{
					velha[mlinha-1][mcoluna-1] = 'X';
					break;
				}	
 			}	
}

//gera o game
int game (int x)
{
	int coluna1 ,linha1, linha2, coluna2 , cond, retorno, reset, i, j, p1, p2, pm;
	char jogador1 = 'O', jogador2 = 'X';

//fecha o programa
		if(x==0)
		{
			cond=0;
			return(cond);
		}	
		
//inicia o programa
  system("clear");
	jogo();
	limpatabuleiro();	
	tabuleiro();

	while(1)
	{
    //gera a jogada do primeiro jogador	
 		while(1)
 		{
			printf("\nJogador 1(Linha e coluna): ");
			scanf("%d%d", &linha1, &coluna1);
		  if(velha[linha1-1][coluna1-1]==' ')
		  {
			 velha[linha1-1][coluna1-1]='O';
			 break;
			} 
			else
				printf("\nMovimento inválido.\n");				
		}
		system("clear");
		jogo();
		tabuleiro();
		
    //checa se o jogador 1 ganhou
		p1 = win(linha1, coluna1);
		
		if(p1)
		{
			printf("\nJogador 1 ganhou.\n");
			break;
		}	
		
    //dar velha		
		reset = dvelha();
		if(reset==9)
			break;
			
//gera a jogada pro jogador 2 se o modo for escolhido				
	  if(x==1)
    {			
   	  //jogada do jogador 2							
 			while(1)
 		  {
				printf("\nJogador 2(Linha e coluna): ");
				scanf("%d%d", &linha2, &coluna2);
		  	if(velha[linha2-1][coluna2-1]==' ')
		  	{
			 		velha[linha2-1][coluna2-1]='X';
			 		break;
				} 
				else
					printf("\nMovimento inválido.\n");				
		  }
		
			system("clear");
			jogo();
			tabuleiro();
		
			//condições para o jogador 2 ganhar
			p2 = win(linha2, coluna2);
			if(p2)
			{
				printf("\nJogador 2 ganhou.\n");
		 		break;	
			} 
		 
			//dar velha					
			reset = dvelha();
			if(reset==9)
				break;		
			}
			
//gera a jogada da maquina simples se o modo for escolhido			
		else if(x==2)
		{
			//imprime a animação de turno da máquina
			machine();

			//gera a jogada da maquina
			turnmachine();
			
			system("clear");
			jogo();
			tabuleiro();
		
			//checa se a máquina ganhou
			pm = win(mlinha, mcoluna);
			if(pm)
			{
				printf("\nMáquina ganhou.\n");
		 		break;
			}	 	
		 
			//checa se deu velha			
			reset = dvelha();
			if(reset==9)
				break;				
 		}
 		
//gera a jogada da maquina complexa caso o modo for escolhido 		
 		else if(x==3)
 		{
			//imprime a animação de turno da máquina
			machine();

			//defesa da máquina nas linhas
				if(velha[0][0]=='O' || velha[0][1]=='O' || velha[0][2]=='O' || velha[1][0]=='O' || velha[1][1]=='O' || velha[1][2]=='O' || velha[2][0]=='O' || velha[2][1]=='O' || velha[2][2]=='O')
				{
					if(velha[0][0]==velha[0][1] && velha[0][2]==' ')
					{
						velha[0][2]='X';
						mlinha=1; mcoluna=3;
					}
					else if(velha[0][0]==velha[0][2] && velha[0][1]==' ')
					{
						velha[0][1]='X';
						mlinha=1; mcoluna=2;
					}
					else if(velha[0][0]==velha[1][0] && velha[2][0]==' ')
					{
						velha[2][0]='X';
						mlinha=3; mcoluna=1;
					}				
					else if(velha[0][0]==velha[2][0] && velha[1][0]==' ')
					{
						velha[1][0]='X';
						mlinha=2; mcoluna=1;
					}
					else if(velha[0][0]==velha[1][1] && velha[2][2]==' ')
					{
						velha[2][2]='X';
						mlinha=3; mcoluna=3;
					}
					else if(velha[0][0]==velha[2][2] && velha[1][1]==' ')
					{
						velha[1][1]='X';
						mlinha=2; mcoluna=2;
					}
					else if(velha[0][1]==velha[0][2] && velha[0][0]==' ')
					{
						velha[0][0]='X';
						mlinha=1; mcoluna=1;
					}
					else if(velha[1][0]==velha[2][0] && velha[0][0]==' ')
					{
						velha[0][0]='X';
						mlinha=1; mcoluna=1;
					}	
					else if(velha[1][1]==velha[2][2] && velha[0][0]==' ')
					{
						velha[0][0]='X';
						mlinha=1; mcoluna=1;
					}	
					else if(velha[1][0]==velha[1][1] && velha[1][2]==' ')
					{
						velha[1][2]='X';
						mlinha=2; mcoluna=3;
					}																																						
					else if(velha[1][0]==velha[1][2] && velha[1][1]==' ')
					{
						velha[1][1]='X';
						mlinha=2; mcoluna=2;
					}	
					else if(velha[1][1]==velha[1][2] && velha[1][0]==' ')
					{
						velha[1][0]='X';
						mlinha=2; mcoluna=1;
					}					
					else if(velha[2][0]==velha[2][1] && velha[2][2]==' ')
					{
						velha[2][2]='X';
						mlinha=3; mcoluna=3;
					}	
					else if(velha[2][0]==velha[2][2] && velha[2][1]==' ')
					{
						velha[2][1]='X';
						mlinha=3; mcoluna=2;
					}	
					else if(velha[2][1]==velha[2][2] && velha[2][0]==' ')
					{
						velha[2][0]='X';
						mlinha=3; mcoluna=1;
					}								
					else if(velha[2][0]==velha[1][1] && velha[0][2]==' ')
					{
						velha[0][2]='X';
						mlinha=1; mcoluna=2;
					}	
					else if(velha[2][0]==velha[0][2] && velha[1][1]==' ')
					{
						velha[1][1]='X';
						mlinha=2; mcoluna=2;
					}	
					else if(velha[1][1]==velha[0][2] && velha[2][0]==' ')
					{
						velha[2][0]='X';
						mlinha=3; mcoluna=1;
					}														
					else if(velha[0][1]==velha[1][1] && velha[2][1]==' ')
					{
						velha[2][1]='X';
						mlinha=3; mcoluna=2;
					}	
					else if(velha[0][1]==velha[2][1] && velha[1][1]==' ')
					{
						velha[1][1]='X';
						mlinha=2; mcoluna=2;
					}	
					else if(velha[1][1]==velha[2][1] && velha[0][1]==' ')
					{
						velha[2][1]='X';
						mlinha=3; mcoluna=2;
					}						
					else if(velha[0][2]==velha[1][2] && velha[2][2]==' ')
					{
						velha[2][2]='X';
						mlinha=3; mcoluna=3;
					}	
					else if(velha[0][2]==velha[2][2] && velha[1][2]==' ')
					{
						velha[1][2]='X';
						mlinha=2; mcoluna=3;
					}	
					else if(velha[1][2]==velha[2][2] && velha[0][2]==' ')
					{
						velha[0][2]='X';
						mlinha=1; mcoluna=3;
					}							
				}															
			//gera o ataque nas linhas
				else if(velha[0][0]=='X' || velha[0][1]=='X' || velha[0][2]=='X' || velha[1][0]=='X' || velha[1][1]=='X' || velha[1][2]=='X' || velha[2][0]=='X' || velha[2][1]=='X' || velha[2][2]=='X')
				{
					if(velha[0][0]==velha[0][1] && velha[0][2]==' ')
					{
						velha[0][2]='X';
						mlinha=1; mcoluna=3;
					}
					else if(velha[0][0]==velha[0][2] && velha[0][1]==' ')
					{
						velha[0][1]='X';
						mlinha=1; mcoluna=2;
					}
					else if(velha[0][0]==velha[1][0] && velha[2][0]==' ')
					{
						velha[2][0]='X';
						mlinha=3; mcoluna=1;
					}				
					else if(velha[0][0]==velha[2][0] && velha[1][0]==' ')
					{
						velha[1][0]='X';
						mlinha=2; mcoluna=1;
					}
					else if(velha[0][0]==velha[1][1] && velha[2][2]==' ')
					{
						velha[2][2]='X';
						mlinha=3; mcoluna=3;
					}
					else if(velha[0][0]==velha[2][2] && velha[1][1]==' ')
					{
						velha[1][1]='X';
						mlinha=2; mcoluna=2;
					}
					else if(velha[0][1]==velha[0][2] && velha[0][0]==' ')
					{
						velha[0][0]='X';
						mlinha=1; mcoluna=1;
					}
					else if(velha[1][0]==velha[2][0] && velha[0][0]==' ')
					{
						velha[0][0]='X';
						mlinha=1; mcoluna=1;
					}	
					else if(velha[1][1]==velha[2][2] && velha[0][0]==' ')
					{
						velha[0][0]='X';
						mlinha=1; mcoluna=1;
					}	
					else if(velha[1][0]==velha[1][1] && velha[1][2]==' ')
					{
						velha[1][2]='X';
						mlinha=2; mcoluna=3;
					}																																						
					else if(velha[1][0]==velha[1][2] && velha[1][1]==' ')
					{
						velha[1][1]='X';
						mlinha=2; mcoluna=2;
					}	
					else if(velha[1][1]==velha[1][2] && velha[1][0]==' ')
					{
						velha[1][0]='X';
						mlinha=2; mcoluna=1;
					}					
					else if(velha[2][0]==velha[2][1] && velha[2][2]==' ')
					{
						velha[2][2]='X';
						mlinha=3; mcoluna=3;
					}	
					else if(velha[2][0]==velha[2][2] && velha[2][1]==' ')
					{
						velha[2][1]='X';
						mlinha=3; mcoluna=2;
					}	
					else if(velha[2][1]==velha[2][2] && velha[2][0]==' ')
					{
						velha[2][0]='X';
						mlinha=3; mcoluna=1;
					}								
					else if(velha[2][0]==velha[1][1] && velha[0][2]==' ')
					{
						velha[0][2]='X';
						mlinha=1; mcoluna=2;
					}	
					else if(velha[2][0]==velha[0][2] && velha[1][1]==' ')
					{
						velha[1][1]='X';
						mlinha=2; mcoluna=2;
					}	
					else if(velha[1][1]==velha[0][2] && velha[2][0]==' ')
					{
						velha[2][0]='X';
						mlinha=3; mcoluna=1;
					}														
					else if(velha[0][1]==velha[1][1] && velha[2][1]==' ')
					{
						velha[2][1]='X';
						mlinha=3; mcoluna=2;
					}	
					else if(velha[0][1]==velha[2][1] && velha[1][1]==' ')
					{
						velha[1][1]='X';
						mlinha=2; mcoluna=2;
					}	
					else if(velha[1][1]==velha[2][1] && velha[0][1]==' ')
					{
						velha[2][1]='X';
						mlinha=3; mcoluna=2;
					}						
					else if(velha[0][2]==velha[1][2] && velha[2][2]==' ')
					{
						velha[2][2]='X';
						mlinha=3; mcoluna=3;
					}	
					else if(velha[0][2]==velha[2][2] && velha[1][2]==' ')
					{
						velha[1][2]='X';
						mlinha=2; mcoluna=3;
					}	
					else if(velha[1][2]==velha[2][2] && velha[0][2]==' ')
					{
						velha[0][2]='X';
						mlinha=1; mcoluna=3;
					}							
				}					
				else
					turnmachine();
	
			system("clear");
			jogo();
			tabuleiro();
		
			//checa se a máquina ganhou
			pm = win(mlinha, mcoluna);
			if(pm)
			{
		 		printf("\nMáquina ganhou.\n");
		 		break;
			}
			//checa se deu velha		
			reset = dvelha();
			if(reset==9)
				break;		
  	}							
  }
//checa se o jogador quer continuar jogando	  
	printf("\nQuer continuar jogando (1 para sim e 0 para não)? ");
	scanf("%d", &retorno);
	if(retorno==1)
		cond = 1;
	else
		cond = 0;
  return (cond);
}  

//menu inicial do game
void main ()
{
	int modo, cond=1;
	char inserir;
		
 	while (cond)
 	{	
 		system("clear");
 		printf("=========================================\nINSTRUÇÕES\nPara jogar basta inserir o número da linha desejada, apertar 'space' (dar espaço) e inserir o número da coluna desejada. Exemplo: 2 2 -> esse comando irá jogar no quadrado do meio (segunda linha e segunda coluna).\n=========================================\n"); 		
		printf("MODOS DE JOGO\t\tCODIGO\nDOIS PLAYERS\t\t 1\nPLAYER VS IA (SIMPLES)\t 2\nPLAYER VS IA (COMPLEXA)  3\n=========================================\n");
		printf("Insira o código que deseja (0 para sair): ");
		scanf("%d", &modo);	
		cond = game(modo);			
	}	
}	

