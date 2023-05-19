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

struct ComandoProff
{
    void naoPisca();
    void reposicionaCursor();
    void cor_texto(int fonte, int fundo = 0);
};

struct Principal
{
    void functionMenu();
};

struct Jogador
{
    string nome;
    int passos;
    char ultimoMovimento;

    void escolheNome()
    {
        cout << "Escolha seu nome" << endl;
        cin >> nome;
    }

    void conferePosicoesRanking(string nome, int passos, string nomeRanking[3], int passosRanking[3]);

    void leRanking(string nomeRanking[3], int passosRanking[3]);

    void escreveRanking(string nome, int passos);
};

struct Personagem
{
    char boneco;
    void movimento(char tecla, char m[10][15], int &x, int &y, bool &sair, int &passos, char &ultimoMovimento);

    void registroMovimentos(char ultimoMovimento);
};

struct Mapa
{
    void menuEscolheMapa(int &x, int &y, char m[10][15], int &numeroCaixas);

    void imprimeMapaPersonagem(char m[10][15], int x, int y);

    void imprimeTrocado(char m[10][15]);

    void escolheMapa(string &escolha, char m[10][15], int &x, int &y,int &numeroDeCaixas);

    void imprimeNumeroPassos(int &passos);

    void executaMovimentos(char tecla, char m[10][15], int &x, int &y, bool &sair, int &passos, char &ultimoMovimento);

    void lerMapaGrupo(char m[10][15], string mapa, int &x, int &y, int &numeroCaixa);
};

void ComandoProff::naoPisca()
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

void ComandoProff::reposicionaCursor()
{
    // IN CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ComandoProff::cor_texto(int fonte, int fundo)
{
    fundo = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(fonte | fundo << 4));
}

void Jogador::conferePosicoesRanking(string nome, int passos, string nomeRanking[3], int passosRanking[3])
{

    for (int i = 0; i < 3; i++)
    {
        if (passosRanking[i] > passos)
        {
            if (i == 0 || i == 1)
            {
                nomeRanking[i + 1] = nomeRanking[i];
                passosRanking[i + 1] = passosRanking[i];
                nomeRanking[i] = nome;
                passosRanking[i] = passos;
            }
            else
            {
                nomeRanking[i] = nome;
                passosRanking[i] = passos;
            }
            break;
        }
    }
}

void Jogador::leRanking(string nomeRanking[3], int passosRanking[3])
{
    int i = 0;
    string linha;
    ifstream arquivo;
    arquivo.open("ranking.txt");
    if (arquivo.is_open())
    {
        while (i < 3 && arquivo >> nomeRanking[i] >> passosRanking[i])
        {
            i++;
        }
        arquivo.close();
    }
    else
    {
        cout << "O arquivo não pode ser aberto";
    }
}

void Jogador::escreveRanking(string nome, int passos)
{
    Jogador rank;
    string nomeRanking[3];
    int passosRanking[3];
    int i = 0;
    rank.leRanking(nomeRanking, passosRanking);
    rank.conferePosicoesRanking(nome, passos, nomeRanking, passosRanking);
    ofstream arquivo;
    arquivo.open("ranking.txt");
    if (arquivo.is_open())
    {
        while (i < 3)
        {
            arquivo << nomeRanking[i] << " " << passosRanking[i] << endl;
            i++;
        }
        arquivo.close();
    }
    else
    {
        cout << "O arquivo não pode ser aberto";
    }
}

void Personagem::registroMovimentos(char ultimoMovimento)
{
    ofstream arquivo;
    arquivo.open("movimentos.txt", std::ios::app);
    if (arquivo.is_open())
    {
        arquivo << ultimoMovimento << " ";

        arquivo.close();
    }
    else
    {
        cout << "O arquivo não pode ser aberto";
    }
}

void Personagem::movimento(char tecla, char m[10][15], int &x, int &y, bool &sair, int &passos, char &ultimoMovimento)
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
    case 'l': /// sair
        modificadorX = 0;
        modificadorY = 0;
        sair = true;
        break;
    }

    switch (m[x + modificadorX][y + modificadorY])
    {
    case 0:
        if (modificadorX != 0)
        {
            x += modificadorX;
            passos++;
            if (modificadorX == 1)
            {
                ultimoMovimento = 's';
                registroMovimentos(ultimoMovimento);
            }
            else
            {
                ultimoMovimento = 'w';
                registroMovimentos(ultimoMovimento);
            }
        }
        if (modificadorY != 0)
        {
            y += modificadorY;
            passos++;
            if (modificadorY == 1)
            {
                ultimoMovimento = 'd';
                registroMovimentos(ultimoMovimento);
            }
            else
            {
                ultimoMovimento = 'a';
                registroMovimentos(ultimoMovimento);
            }
        }
        break;

    case 2:
        switch (m[x + modificadorX * 2][y + modificadorY * 2]) // acima da caixa
        {
        case 0:
            m[x + modificadorX][y + modificadorY] = 0;
            m[x + modificadorX * 2][y + modificadorY * 2] = 2;
            if (modificadorX != 0)
            {
                x += modificadorX;
                passos++;
                if (modificadorX == 1)
                {
                    ultimoMovimento = 's';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'w';
                    registroMovimentos(ultimoMovimento);
                }
            }
            if (modificadorY != 0)
            {
                y += modificadorY;
                passos++;
                if (modificadorY == 1)
                {
                    ultimoMovimento = 'd';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'a';
                    registroMovimentos(ultimoMovimento);
                }
            }
            break;

        case 3:
            m[x + modificadorX][y + modificadorY] = 0;
            m[x + modificadorX * 2][y + modificadorY * 2] = 4;
            if (modificadorX != 0)
            {
                x += modificadorX;
                passos++;
                if (modificadorX == 1)
                {
                    ultimoMovimento = 's';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'w';
                    registroMovimentos(ultimoMovimento);
                }
            }
            if (modificadorY != 0)
            {
                y += modificadorY;
                passos++;
                if (modificadorY == 1)
                {
                    ultimoMovimento = 'd';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'a';
                    registroMovimentos(ultimoMovimento);
                }
            }
            break;
        }
        break;

    case 3:
        if (modificadorX != 0)
        {
            x += modificadorX;
            passos++;
            if (modificadorX == 1)
            {
                ultimoMovimento = 's';
                registroMovimentos(ultimoMovimento);
            }
            else
            {
                ultimoMovimento = 'w';
                registroMovimentos(ultimoMovimento);
            }
        }
        if (modificadorY != 0)
        {
            y += modificadorY;
            passos++;
            if (modificadorY == 1)
            {
                ultimoMovimento = 'd';
                registroMovimentos(ultimoMovimento);
            }
            else
            {
                ultimoMovimento = 'a';
                registroMovimentos(ultimoMovimento);
            }
        }
        break;

    case 4:
        switch (m[x + modificadorX * 2][y + modificadorY * 2])
        {
        case 0:
            m[x + modificadorX][y + modificadorY] = 3;
            m[x + modificadorX * 2][y + modificadorY * 2] = 2;
            if (modificadorX != 0)
            {
                x += modificadorX;
                passos++;
                if (modificadorX == 1)
                {
                    ultimoMovimento = 's';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'w';
                    registroMovimentos(ultimoMovimento);
                }
            }
            if (modificadorY != 0)
            {
                y += modificadorY;
                passos++;
                if (modificadorY == 1)
                {
                    ultimoMovimento = 'd';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'a';
                    registroMovimentos(ultimoMovimento);
                }
            }
            break;

        case 3:
            m[x + modificadorX][y + modificadorY] = 3;
            m[x + modificadorX * 2][y + modificadorY * 2] = 4;
            if (modificadorX != 0)
            {
                x += modificadorX;
                passos++;
                if (modificadorX == 1)
                {
                    ultimoMovimento = 's';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'w';
                    registroMovimentos(ultimoMovimento);
                }
            }
            if (modificadorY != 0)
            {
                y += modificadorY;
                passos++;
                if (modificadorY == 1)
                {
                    ultimoMovimento = 'd';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'a';
                    registroMovimentos(ultimoMovimento);
                }
            }
            break;
        }
        break;
    }
}

bool retornaGanhou(int &numeroCaixas, char m[10][15])
{
    int caixasCorretas = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (m[i][j] == 4)
            {
                caixasCorretas++;
            }
        }
    }

    if (caixasCorretas == numeroCaixas)
    {
        return true;
    }
    return false;
}

void Mapa::lerMapaGrupo(char m[10][15], string mapa, int &x, int &y, int &numeroCaixa)
{
    ifstream carregamento(mapa);

    if (carregamento.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                char c;
                carregamento.get(c);

                switch (c)
                {
                case 9:
                    m[i][j] = char(24);
                    x = i;
                    y = j;
                    break;
                case 1:
                    m[i][j] = char(219);
                    break;
                case 3:
                    m[i][j] = char(176);
                    numeroCaixa++;
                    break;
                case 4:
                    m[i][j] = char(169);
                    break;
                case 5:
                    m[i][j] = char(178);
                    numeroCaixa++;
                    break;
                case 0:
                    m[i][j] = ' ';
                    break;
                }
            }
            carregamento.ignore('\n');
        }
    }
}


void Mapa::escolheMapa(string& escolha, char m[10][15], int& x, int& y, int& numeroCaixas)
{
    string mapa;

    if (escolha.length() > 1)
    {
        mapa = escolha + ".txt";
    }
    else
    {
        int escolhaInt = stoi(escolha);

        switch (escolhaInt)
        {
        case 1:
            mapa = "mapa1.txt";
            break;
        case 2:
            mapa = "mapa2.txt";
            break;
        case 3:
            mapa = "mapa3.txt";
            break;
        }
    }

    lerMapaGrupo(m, mapa, x, y, numeroCaixas);
}


void Mapa::menuEscolheMapa(int &x, int &y, char m[10][15], int &numeroCaixas)
{
    char mapa[10][15];
    int escolha;
    string mapaString;


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
    cout << "[1] - MicroBanIv : 1\n[2] - Aruba 5 : 1\n[3] - TBox 2 : 1\n[4] - Digite o nome do mapa\nDigite o mapa que voce quer jogar: ";
    cin >> escolha;
    if (escolha == 4)
    {
        cout << "\nDigite o nome do mapa: ";
        
        cin >> mapaString;
        escolheMapa(mapaString, m, x, y, numeroCaixas);
    }
    else if (escolha == 1)
    {   
        mapaString = "mapa1";
        escolheMapa(mapaString, m, x, y, numeroCaixas);
    } else if(escolha == 2){
        mapaString = "mapa2";
        escolheMapa(mapaString, m, x, y, numeroCaixas);
    } else if(escolha == 3){
        mapaString = "mapa3";
        escolheMapa(mapaString, m, x, y, numeroCaixas);
    }
    else
    {
        mapaString = "mapa1";
        escolheMapa(mapaString, m, x, y, numeroCaixas);
    }
}

void Mapa::imprimeNumeroPassos(int &passos)
{
    cout << "numero de passos " << passos << endl;
}

void Mapa::imprimeMapaPersonagem(char m[10][15], int x, int y)
{
    ComandoProff corzinha; 
    /// Imprime o jogo: mapa e personagem.
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (i == x && j == y)
            {
                corzinha.cor_texto(15, 0);
                cout << char(2); // personagem
            }
            else
            {
                switch (m[i][j])
                {
                case 0:
                    corzinha.cor_texto(7, 0);
                    cout << " "; // caminho
                    break;
                case 1:
                    corzinha.cor_texto(11, 0);
                    cout << char(219); // parede
                    break;
                case 2:
                    corzinha.cor_texto(6, 0);
                    cout << char(176); // caixa
                    break;
                case 3:
                    corzinha.cor_texto(10, 0);
                    cout << char(169); // posicao final
                    break;
                case 4:
                    corzinha.cor_texto(4, 0);
                    cout << char(178); // caixa na posicao final
                    break;
                } // fim switch
                corzinha.cor_texto(7, 0);
            }
        }
        cout << "\n";
    } // fim for mapa
}

void Mapa::executaMovimentos(char tecla, char m[10][15], int &x, int &y, bool &sair, int &passos, char &ultimoMovimento)
{
    Personagem movimentacao;
    if (_kbhit())
    {
        tecla = getch();
        movimentacao.movimento(tecla, m, x, y, sair, passos, ultimoMovimento);
    } // fim do if
}

void Principal::functionMenu()
{
    Jogador player;
    Jogador rank;
    ComandoProff comando;
    Mapa mapaJogado;
    int escolhaMenu = 0, escolhaMapa = 1, numeroCaixas = 0, jogar = 1;
    bool menu = false, ganhou = false, sair = false;
    char m[10][15];
    int x = 1;
    int y = 4;

    char tecla;

    player.ultimoMovimento = 'c';

    do
    {
        system("cls");
        cout << "Bem vindo a Sokoban Master Ultra 3000" << endl;
        cout << "[1] - Jogar" << endl;
        cout << "[2] - Sobre" << endl;
        cout << "[3] - Sair" << endl;
        cout << "Digite sua escolha: ";
        cin >> escolhaMenu;

        switch (escolhaMenu)
        {
        case 1:
            system("cls");

            if (sair)
            {
                cout << "[1] - Novo jogo" << endl;
                cout << "[2] - Continuar" << endl;
                cout << "Digite sua escolha: ";
                cin >> jogar;
            }

            if (jogar == 1)
            {
                comando.naoPisca();
                sair = false;
                ganhou = false;
                player.escolheNome(); // chamada de metodo struct
                player.passos = 0;
                mapaJogado.menuEscolheMapa(x, y, m, numeroCaixas);
                system("cls");
            }
            else
            {
                comando.naoPisca();
                system("cls");
                sair = false;
                ganhou = false;
                jogar = 1;
            }

            while (!sair && !ganhou)
            {
                /// Posiciona a escrita no início do console
                comando.reposicionaCursor();
                cout << "para sair presione [L]" << endl;
                mapaJogado.imprimeMapaPersonagem(m, x, y);
                mapaJogado.imprimeNumeroPassos(player.passos);
                mapaJogado.executaMovimentos(tecla, m, x, y, sair, player.passos, player.ultimoMovimento);
                ganhou = retornaGanhou(numeroCaixas, m);
                if (ganhou == true)
                {

                    system("cls");
                    mapaJogado.imprimeMapaPersonagem(m, x, y);
                    mapaJogado.imprimeNumeroPassos(player.passos);
                    rank.escreveRanking(player.nome, player.passos);
                    cout << "Parabens, " << player.nome << " voce ganhou o joguinho... " << endl;
                    cout << "Pressione qualquer tecla pra voltar ao menu" << endl;
                    system("pause");
                }
            }
            break;
        case 2:
            escolhaMenu = 0;
            system("cls");
            cout << "Sokoban eh um jogo de movimentacao de caixas onde o objetivo eh \n"
                    "alocar as caixas no local certo usando estrategia e logica.\n\n"
                    "Esse jogo foi desenvolvido pelos alunos do curso de Ciencias da computacao\n"
                    "da universidade do vale do Itajai(UNIVALI), para materia de algoritmos e programacao 2\n"
                    "lecionada pelo professor Thiago Felski.\n"
                    "Alunos: Vinicius Grisa, Gabriel Turman, Marco Antonio Martins Akerman\n"
                    "Data: Marco 2022"
                 << endl;
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            cout << "Obrigado por jogar Sokoban Mater Ultra 3000" << endl;
        }
        if (escolhaMenu == 3)
            break;
    } while (true);
}
