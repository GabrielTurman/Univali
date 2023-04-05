#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTAQUA 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTYELLOW 14
#define BRIGHTWHITE 15

void cor_texto(int fonte, int fundo = 0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(fonte | fundo << 4));
}

void imprimeTrocado(char m[10][15])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{

			switch (m[i][j])
			{
			case 0:
				cor_texto(7, 0);
				cout << " ";
				break; // caminho
			case 1:
				cor_texto(11, 0);
				cout << char(219);
				break; // parede
			case 3:
				cor_texto(6, 0);
				cout << char(176);
				break; // caixa
			case 4:
				cor_texto(10, 0);
				cout << char(169);
				break; // posicao final
			case 5:
				cor_texto(4, 0);
				cout << char(178);
				break; // caixa na posicao final
					   // default: cout<<"-"; //erro
			}		   // fim switch
			cor_texto(7, 0);
		}
		cout << "\n";
	}
}

void imprimeMapa(char m[10][15])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			cout << m[i][j];
		}
		cout << endl;
	}
}

void escolheMapa(int escolha, char m[10][15], int &x, int &y)
{
	// MicroBan IV -> 1 personagem x=4 y=1
	char m1[10][15] = {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
					   1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 0, 3, 5, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
					   1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// Aruba 5 -> 1 personagem x=4 y=3
	char m2[10][15] = {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0,
					   1, 0, 1, 3, 1, 0, 1, 1, 1, 0, 4, 0, 0, 1, 0,
					   1, 0, 3, 0, 3, 0, 0, 0, 0, 4, 0, 4, 0, 1, 0,
					   1, 0, 1, 3, 1, 0, 1, 1, 1, 0, 4, 0, 0, 1, 0,
					   1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0,
					   1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// TBox -> 2 personagem x=5 y=2
	char m3[10][15] = {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 0, 3, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 1, 0, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 0, 0, 5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	switch (escolha)
	{
	case 1:
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				m[i][j] = m1[i][j];
			}
		}
		x = 4;
		y = 1;
		break;
	case 2:
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				m[i][j] = m2[i][j];
			}
		}
		x = 4;
		y = 3;
		break;
	case 3:
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				m[i][j] = m3[i][j];
			}
		}
		x = 5;
		y = 2;
		break;
	}
}

void menuEscolheMapa(int &x, int &y, char m[10][15], int &numeroCaixas)
{
	char mapa[10][15];
	int escolha;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			mapa[i][j] = 0;
		}
	}

	system("cls");
	cout << "Escolha seu mapa:\n"
		 << endl;
	for (int i = 1; i < 4; i++)
	{
		switch (i)
		{
		case 1:
			cout << "[1] - MicroBanIv : 1\n" << endl;
			numeroCaixas = 2;
			break;
		case 2:
			cout << "[2] - Aruba 5 : 1\n" << endl;
			numeroCaixas = 4;
			break;
		case 3:
			cout << "[3] - TBox 2 : 1\n" << endl;
			numeroCaixas = 3;
			break;
		default:
			break;
		}
		escolheMapa(i, mapa, x, y);
		imprimeTrocado(mapa);
		cout << endl;
	}
	cout << "Digite o mapa que voce quer: ";
	cin >> escolha;
	escolheMapa(escolha, m, x, y);
}

void naoPisca()
{
	/// ALERTA: N O MODIFICAR O TRECHO DE C DIGO, A SEGUIR.
	// INICIO: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
	// FIM: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
}

void reposicionaCursor()
{
	// IN CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
	short int CX = 0, CY = 0;
	COORD coord;
	coord.X = CX;
	coord.Y = CY;
	// FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void imprimeMapaPersonagem(char m[10][15], int x, int y)
{
	/// Imprime o jogo: mapa e personagem.
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i == x && j == y)
			{
				cor_texto(15, 0);
				cout << char(2); // personagem
			}
			else
			{
				switch (m[i][j])
				{
				case 0:
					cor_texto(7, 0);
					cout << " ";
					break; // caminho
				case 1:
					cor_texto(11, 0);
					cout << char(219);
					break; // parede
				case 3:
					cor_texto(6, 0);
					cout << char(176);
					break; // caixa
				case 4:
					cor_texto(10, 0);
					cout << char(169);
					break; // posicao final
				case 5:
					cor_texto(4, 0);
					cout << char(178);
					break; // caixa na posicao final
						   // default: cout<<"-"; //erro
				}		   // fim switch
				cor_texto(7, 0);
			}
		}
		cout << "\n";
	} // fim for mapa
}

void movimento(char tecla, char m[10][15], int &x, int &y)
{
	int modificadorX, modificadorY;
	switch (tecla)
	{
	case 72:
	case 'w': /// cima
		modificadorX = -1;
		modificadorY = 0;
		break;
	case 80:
	case 's': /// baixo
		modificadorX = 1;
		modificadorY = 0;
		break;
	case 75:
	case 'a': /// esquerda
		modificadorX = 0;
		modificadorY = -1;
		break;
	case 77:
	case 'd': /// direita
		modificadorX = 0;
		modificadorY = 1;
		break;
	}

	switch (m[x + modificadorX][y + modificadorY])
	{
	case 0:
		if (modificadorX != 0)
			x += modificadorX;
		if (modificadorY != 0)
			y += modificadorY;
		break;

	case 3:
		switch (m[x + modificadorX * 2][y + modificadorY * 2]) // acima da caixa
		{
		case 0:
			m[x + modificadorX][y + modificadorY] = 0;
			m[x + modificadorX * 2][y + modificadorY * 2] = 3;
			if (modificadorX != 0)
				x += modificadorX;
			if (modificadorY != 0)
				y += modificadorY;
			break;

		case 4:
			m[x + modificadorX][y + modificadorY] = 0;
			m[x + modificadorX * 2][y + modificadorY * 2] = 5;
			if (modificadorX != 0)
				char tecla;
			x += modificadorX;
			if (modificadorY != 0)
				y += modificadorY;
			break;
		}
		break;

	case 4:
		if (modificadorX != 0)
			x += modificadorX;
		if (modificadorY != 0)
			y += modificadorY;
		break;

	case 5:
		switch (m[x + modificadorX * 2][y + modificadorY * 2])
		{
		case 0:
			m[x + modificadorX][y + modificadorY] = 4;
			m[x + modificadorX * 2][y + modificadorY * 2] = 3;
			if (modificadorX != 0)
				x += modificadorX;
			if (modificadorY != 0)
				y += modificadorY;
			break;

		case 4:
			m[x + modificadorX][y + modificadorY] = 4;
			m[x + modificadorX * 2][y + modificadorY * 2] = 5;
			if (modificadorX != 0)
				x += modificadorX;
			if (modificadorY != 0)
				y += modificadorY;
			break;
		}
		break;
	}
}

void executaMovimentos(char tecla, char m[10][15], int &x, int &y)
{
	if (_kbhit())
	{
		tecla = getch();
		movimento(tecla, m, x, y);
	} // fim do if
}

/*void funcaoWhile(int m[10][10], int x, int y)
{
	while (true)
	{
		/// Posiciona a escrita no início do console
		reposicionaCursor();

		/// Imprime o jogo: mapa e personagem.
		imprimeMapaPersonagem(m, x, y);

		executaMovimentos(m, x, y);

	} // fim main
}*/

void functionMenu()
{
	int escolhaMenu = 0, escolhaMapa = 1, numeroCaixas = 0;
	bool case2 = true, menu = false;
	char m[10][15] = {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
					  1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
					  1, 0, 0, 3, 5, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0,
					  1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
					  1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
					  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int x = 1;
	int y = 4;

	char tecla;

	do
	{
		cout << "Bem vindo a Sokoban Master Ultra 3000" << endl;
		cout << "(1) para jogar" << endl;
		cout << "(2) para ler sobre" << endl;
		cout << "(3) para sair" << endl;
		cout << "Digite sua escolha:";
		cin >> escolhaMenu;

		switch (escolhaMenu)
		{
		case 1:
			system("cls");
			// Posi  o inicial do personagem no console
			// Vari vel para tecla precionada

			naoPisca();
			menuEscolheMapa(x, y, m, numeroCaixas);
			system("cls");
			imprimeMapa(m);

			while (true)
			{
				/// Posiciona a escrita no início do console
				reposicionaCursor();
				imprimeMapaPersonagem(m, x, y);
				executaMovimentos(tecla, m, x, y);
			}
			break;
		case 2:
			escolhaMenu = 0;
			system("cls");
			cout << "Sokoban eh um jogo de movimentacao de caixas onde o objetivo eh \n"
					"alocar as caixas no local certo usando estrategia e logica.\n\n"
					"Esse jogo foi desenvolvido pelos alunos do curso de Ciencias da computacao\n"
					"da universidade do vale do Itajai(UNIVALI), para materia de algoritmos e programacao 2\n"
					"lecianada pelo professor Thiago Felski.\n"
				"Alunos responsaveis: Gabriel Turman, Vinicius Grisa, Marco Antonio Martins Akerman\n"
				 << endl;
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			cout << "Obrigado por jogar Sokoban Mater Ultra 3000" << endl;
			menu = true;
		}
	} while (menu);
}
void salvarJogo(char mapaAtual[10][15], int x, int y){
	ofstream salvamento("jogoSalvo.txt");
	if(salvamento.is_open()){
		salvamento << x << " " << y << endl;
	   
	    for(int i = 0; i < 10; i++){
			for(int  j = 0; j < 15; j++){
				salvamento << mapaAtual[i][j];
			}
		}
	}

	
}

void carregarOJogo(char &mapa, char &posicaoPersonagem, char &posicaoCaixa){
    ifstream salvamento("jogoSalvo.txt");
}
