#include <iostream>
#include <string>

using namespace std;

// Não vai ter W
char tabela[5][5];

void init_table() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tabela[i][j] = ' ';
        }
    }
}

pair<int, int> buscar(char a) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (tabela[i][j] == a){
                return make_pair(i, j);
            }
        }
    }
    return make_pair(0, 0);
}

bool exists(char a) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (tabela[i][j] == a)
                return true;
        }
    }
    return false;
}

void insere_char(char a) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (tabela[i][j] == ' ') {
                tabela[i][j] = a;
                return;
            }
        }
    }
}

void montar_tabela(string key) {
    init_table();
    for (int i = 0; i < key.size(); i++) {
        if (!exists(key[i])) {
            insere_char(key[i]);
        }
    }

    for (int i = 97; i <= 122; i++) {
        if ((char)i != 'w' && !exists((char)i)) {
            insere_char((char)i);
        }
    }
}

string criptografar(string frase) {
    string pares = "";
    string criptografado = "";
    int size = frase.size();
    for (int i = 0; i < size; i++) {
        if(frase[i] == ' ' || frase[i] - 0 < 97 || frase[i] - 0 > 122)
            continue;
        if (i + 1 < size) {
            int iCur = i;
            int iNext = i + 1;
            while(frase[iNext] == ' ') {
                iNext++;
                i++;
            }
            if (frase[iCur] == frase[iNext]) {
                pares.insert(pares.size(), 1, frase[i]);
                if (frase[iNext] == 'x') {
                    pares.insert(pares.size(), 1, 'z');
                } else {
                    pares.insert(pares.size(), 1, 'x');
                }
            } else {
                pares.insert(pares.size(), 1, frase[iCur]);
                pares.insert(pares.size(), 1, frase[iNext]);
                i++;
            }
        } else {
            pares.insert(pares.size(), 1, frase[i]);
            if (frase[i] == 'x') {
                pares.insert(pares.size(), 1, 'z');
            } else {
                pares.insert(pares.size(), 1, 'x');
            }
        }
    }

    for (int i = 0; i < pares.size(); i+=2) {
        pair<int, int> posA = buscar(pares[i]);
        pair<int, int> posB = buscar(pares[i + 1]);

        int x, y;
        if (posA.first == posB.first) {
            //mesma linha
            x = posA.first;
            y = (posA.second + 1) % 5;
            criptografado.insert(criptografado.size(), 1, tabela[x][y]);

            x = posB.first;
            y = (posB.second + 1) % 5;
            criptografado.insert(criptografado.size(), 1, tabela[x][y]);
        } else if (posA.second == posB.second) {
            // mesma coluna
            x = (posA.first + 1) % 5;
            y = posA.second;
            criptografado.insert(criptografado.size(), 1, tabela[x][y]);

            x = (posB.first + 1) % 5;
            y = posB.second;
            criptografado.insert(criptografado.size(), 1, tabela[x][y]);
        } else {
            x = posA.first;
            y = posB.second;
            criptografado.insert(criptografado.size(), 1, tabela[x][y]);

            x = posB.first;
            y = posA.second;
            criptografado.insert(criptografado.size(), 1, tabela[x][y]);
        }
    }
    return criptografado;
    /* for (int i = 0; i < criptografado.size(); i+=2) {
        cout << "[" << pares[i] << pares[i+1] << "] => ";
        cout << "[" << criptografado[i] << criptografado[i+1] << "]" << endl;
    } */
}

string descriptografar(string frase_criptog) {
    string descriptografado = "";
    for (int i = 0; i < frase_criptog.size(); i+= 2) {
        pair<int, int> posA = buscar(frase_criptog[i]);
        pair<int, int> posB = buscar(frase_criptog[i + 1]);

        int x, y;
        if (posA.first == posB.first) {
            //mesma linha
            x = posA.first;
            y = (posA.second - 1) < 0 ? 4 : (posA.second - 1);
            cout << "aqui X=" << x << " Y=" << y << endl;
            descriptografado.insert(descriptografado.size(), 1, tabela[x][y]);

            x = posB.first;
            y = (posB.second - 1) < 0 ? 4 : (posB.second - 1);
            descriptografado.insert(descriptografado.size(), 1, tabela[x][y]);
        } else if (posA.second == posB.second) {
            // mesma coluna
            y = (posA.first - 1) < 0 ? 4 : (posA.first - 1);
            y = posA.second;
            descriptografado.insert(descriptografado.size(), 1, tabela[x][y]);

            y = (posB.first - 1) < 0 ? 4 : (posB.first - 1);
            y = posB.second;
            descriptografado.insert(descriptografado.size(), 1, tabela[x][y]);
        } else {
            x = posA.first;
            y = posB.second;
            descriptografado.insert(descriptografado.size(), 1, tabela[x][y]);

            x = posB.first;
            y = posA.second;
            descriptografado.insert(descriptografado.size(), 1, tabela[x][y]);
        }
    }
    return descriptografado;
}

int main(int argc, char *argv[])
{
    string key, frase;
    cout << "[KEY]: ";
    getline(cin, key);
    cout << "Frase: ";
    getline(cin, frase);

    montar_tabela(key);

    string frase_criptogr = criptografar(frase);
    cout << "Frase criptografada: " << frase_criptogr << endl;

    string descriptografado = descriptografar(frase_criptogr);
    cout << "Frase descriptografada: " << descriptografado << endl;


    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << tabela[i][j];
        }
        cout << endl;
    }

    return 0;
}
