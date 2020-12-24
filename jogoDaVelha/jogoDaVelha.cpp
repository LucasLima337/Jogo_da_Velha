#include <iostream>
#include <string>
#include <new>
#include <stdio.h>
#include <stdbool.h>

using namespace std;

void criaTabuleiro(char tabuleiro[3][3], int mascara[3][3]) {
    int indice = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = '*';
            mascara[i][j] = indice;
            indice++;
        }
    }
}

void exibeTabuleiro(char tabuleiro[3][3]) {
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };
    char roxo[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char rosa[] = { 0x1b, '[', '1', ';', '3', '5', 'm', 0 };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == 'X') {
                cout << " | " << roxo << tabuleiro[i][j] << normal;

            }

            else if (tabuleiro[i][j] == 'O') {
                cout << " | " << rosa << tabuleiro[i][j] << normal;
            }

            else {
                cout << " | " << tabuleiro[i][j];
            }
        }
        cout << " |\n";
    }
}

void exibeMascara(int mascara[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " | " << mascara[i][j];
        }
        cout << " |\n";
    }
}

void encontraPosicao(int mascara[3][3], int posicao, int posTabuleiro[2]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (mascara[i][j] == posicao) {
                posTabuleiro[0] = i;
                posTabuleiro[1] = j;
            }
        }
    }
}

void verificaJogada(char tabuleiro[3][3], int *estadoDeJogo) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == 'X' && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) {
            *estadoDeJogo = 1;
        }

        else if (tabuleiro[i][0] == 'O' && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) {
            *estadoDeJogo = 2;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (tabuleiro[0][j] == 'X' && tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j]) {
            *estadoDeJogo = 1;
        }

        else if (tabuleiro[0][j] == 'O' && tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j]) {
            *estadoDeJogo = 2;
        }
    }

    if (tabuleiro[0][0] == 'X' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
        *estadoDeJogo = 1;
    }

    else if (tabuleiro[0][0] == 'O' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
        *estadoDeJogo = 2;
    }

    else if (tabuleiro[2][0] == 'X' && tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2]) {
        *estadoDeJogo = 1;
    }

    else if (tabuleiro[2][0] == 'O' && tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2]) {
        *estadoDeJogo = 2;
    }
}

void jogo(string jogador1, string jogador2, int pontuacao1, int pontuacao2) {
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };
    char roxo[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char rosa[] = { 0x1b, '[', '1', ';', '3', '5', 'm', 0 };
    char vermelho[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
    char tabuleiro[3][3];
    int mascara[3][3], posicao, posTabuleiro[2], reiniciar;
    int turnoJogador = 1, jogadas = 1, estadoDeJogo = 0;
    bool secondLoop = true;
    string jogadorPrincipal = jogador1;

    criaTabuleiro(tabuleiro, mascara);

    while (jogadas <= 9 && estadoDeJogo == 0) {
        cout << "Rodadas restantes: " << 10 - jogadas << "\n\n";

        cout << "============================\n";
        cout << "           Placar\n";
        cout << "============================\n";
        cout << roxo << jogador1 << ": " << pontuacao1 << " pontos \n" << normal;
        cout << rosa << jogador2 << ": " << pontuacao2 << " pontos \n" << normal;
        cout << "============================\n";

        cout << "\nMascara de Posicoes:\n";
        exibeMascara(mascara);
        cout << "\n";

        cout << "Tabuleiro do Jogo:\n";
        exibeTabuleiro(tabuleiro);
        cout << "\n";

        cout << jogadorPrincipal << ", digite uma posicao da mascara: ";
        cin >> posicao;

        system("cls");

        if (posicao > 0 && posicao < 10) {
            encontraPosicao(mascara, posicao, posTabuleiro);

            if (tabuleiro[posTabuleiro[0]][posTabuleiro[1]] != '*') {
                cout << vermelho << "Essa posicao ja foi escolhida!\n\n" << normal;
            }

            else {
                if (turnoJogador == 1) {
                    tabuleiro[posTabuleiro[0]][posTabuleiro[1]] = 'X';
                    turnoJogador = 2;
                    jogadorPrincipal = jogador2;
                    jogadas++;
                }
                else {
                    tabuleiro[posTabuleiro[0]][posTabuleiro[1]] = 'O';
                    turnoJogador = 1;
                    jogadorPrincipal = jogador1;
                    jogadas++;
                }

                verificaJogada(tabuleiro, &estadoDeJogo);
            }
        }

        else {
            cout << vermelho << "Por favor, escolha uma posicao da mascara.\n\n" << normal;
        }
    }

    cout << "Partida encerrada!\n\n";
    exibeTabuleiro(tabuleiro);

    if (estadoDeJogo == 1) {
        cout << "\nO Jogador(a) [ " << roxo << jogador1 << normal << " ] venceu!!\n\n";
        pontuacao1++;
    }

    else if (estadoDeJogo == 2) {
        cout << "\nO Jogador(a) [ " << rosa << jogador2 << normal << " ] venceu!!\n\n";
        pontuacao2++;
    }

    else {
        cout << "\nDeu empate!\n\n";
    }

    cout << "============================\n";
    cout << "           Placar\n";
    cout << "============================\n";
    cout << roxo << jogador1 << ": " << pontuacao1 << " pontos \n" << normal;
    cout << rosa << jogador2 << ": " << pontuacao2 << " pontos \n" << normal;
    cout << "============================\n\n";

    while (secondLoop) {
        cout << "Deseja reiniciar o jogo?\n\n";

        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";
        cout << "[ 1 ] -- SIM" << endl;
        cout << "[ 2 ] -- NAO" << endl;
        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";

        cout << "Sua escolha: ";
        cin >> reiniciar;
        cin.ignore();

        switch (reiniciar) {
            case 1:
                system("cls");
                secondLoop = false;
                jogo(jogador1, jogador2, pontuacao1, pontuacao2);
                break;
            case 2:
                secondLoop = false;
                system("cls");
                break;
            default:
                system("cls");
                cout << "\nPor favor, escolha uma das duas opcoes.\n\n";
                break;
        }
    }
}

void menu() {
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };
    int opcao, opcaoSobre;
    bool mainLoop = true;
    string jogador1, jogador2;

    while (mainLoop) {
        bool thirdLoop = true;
        int pontuacao1 = 0, pontuacao2 = 0;

        cout << normal;
        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";
        cout << " Bem vindo(a) ao Jogo da Velha! :)\n";
        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";
        cout << "[ 1 ] -- Jogar" << endl;
        cout << "[ 2 ] -- Sobre" << endl;
        cout << "[ 3 ] -- Sair" << endl;
        cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";

        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        system("cls");

        switch(opcao) {
            case 1:
                cout << "Digite o nome do primeiro jogador: ";
                getline(cin, jogador1);

                cout << "Digite o nome do segundo jogador: ";
                getline(cin, jogador2);

                system("cls");
                jogo(jogador1, jogador2, pontuacao1, pontuacao2);
                break;

            case 2:
                system("cls");

                while (thirdLoop) {
                    cout << "Jogo da Velha desenvolvido por LUCAS LIMA! :)\n\n";

                    cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";
                    cout << "[ 1 ] -- Voltar" << endl;
                    cout << "[ 2 ] -- Sair" << endl;
                    cout << "=-==-==-==-==-==-==-==-==-==-==-==-=\n";

                    cout << "Escolha uma opcao: ";
                    cin >> opcaoSobre;
                    cin.ignore();

                    switch (opcaoSobre) {
                        case 1:
                            system("cls");
                            thirdLoop = false;
                            break;

                        case 2:
                            system("cls");
                            cout << "Jogo encerrado com sucesso!\n";
                            mainLoop = false;
                            thirdLoop = false;
                            break;

                        default:
                            system("cls");
                            cout << "Por favor, escolha uma das duas opcoes.\n\n";
                            break;
                    }
                }
                break;

            case 3:
                cout << "Jogo encerrado com sucesso!\n";
                mainLoop = false;
                break;

            default:
                cout << "Opcao escolhida invalida, tente novamente.\n\n";
                break;
        }
    }
}

int main() {
    system("cls");
    menu();
    return 0;
}
