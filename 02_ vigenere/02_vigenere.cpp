#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

string criptografar(string key, string phrase) {
    string newKey;
    int realIndex = 0;
    for (int i = 0; i < phrase.length(); i++) {
        if (phrase[i] >= 'a' && phrase[i] <= 'z') {
            newKey += key[realIndex % key.length()];
            realIndex++;
        } else {
            newKey += phrase[i];
        }
    }

    string criptografado;
    for (int i = 0; i < phrase.length(); i++) {
        if (phrase[i] >= 'a' && phrase[i] <= 'z') {
            int phIdx = (phrase[i] - 0) - 97; // Phrase index
            int kyIdx = (newKey[i] - 0) - 97; // Key index
            int cripIdx = ((phIdx + kyIdx) % 26) + 'a'; // Criptografado index
            /*cout << phrase[i] << "(" << phIdx << ") + ";
            cout << newKey[i] << "(" << kyIdx << ") = ";
            cout << (char)cripIdx << "(" << cripIdx - 'a' << ")" << endl;*/
            criptografado += (char)cripIdx;
        } else {
            criptografado += phrase[i];
        }
    }
    return criptografado;
}

string descriptografar(string key, string criptografado) {
    string newKey;
    int realIndex = 0;
    for (int i = 0; i < criptografado.length(); i++) {
        if (criptografado[i] >= 'a' && criptografado[i] <= 'z') {
            newKey += key[realIndex % key.length()];
            realIndex++;
        } else {
            newKey += criptografado[i];
        }
    }

    string descriptografado;
    for (int i = 0; i < criptografado.length(); i++) {
        if (criptografado[i] >= 'a' && criptografado[i] <= 'z') {
            int crIdx = (criptografado[i] - 0) - 97; // criptografado index
            int kyIdx = (newKey[i] - 0) - 97; // Key index
            int dcripIdx = ((crIdx - kyIdx + 26) % 26) + 'a'; // Criptografado index
            /*cout << criptografado[i] << "(" << crIdx << ") - ";
            cout << newKey[i] << "(" << kyIdx << ") = ";
            cout << (char)dcripIdx << "(" << dcripIdx - 'a' << ")" << endl;*/

            descriptografado += (char)dcripIdx;
        } else {
            descriptografado += criptografado[i];
        }
    }
    return descriptografado;
}

bool quebrou(string descriptografado) {
    string buscar("amor");
    if(descriptografado.find(buscar) != string::npos)
        return true;
    return false;
}

string monta_palavra(int lettersIndex[]) {
    string word;
    for (int i = 0; i < 8; i++) {
        word += (char)(lettersIndex[i] + 97);
    }
    return word;
}

void next_try(int *lettersIndex, int i) {
    if (i == 0 && lettersIndex[i] == 25){
        lettersIndex[i] += 1;
        return;
    }

    if (lettersIndex[i] == 25) {
        next_try(lettersIndex, i - 1);
        //for(int j = i; j < 8; j++)
        lettersIndex[i] = 0;
        return;
    }
    lettersIndex[i] += 1;
}

void quebrar(string criptografado) {
    vector<string> chaves = {};
    vector<string>::iterator it;
    int lettersIndex[8] = {};
    string key;
    string descriptografado;

    int i = 0;
    while(lettersIndex[0] < 26) {
        key = monta_palavra(lettersIndex);
        descriptografado = descriptografar(key, criptografado);

        if(quebrou(descriptografado)) {
            chaves.push_back(key);
        }
        next_try(lettersIndex, 7);

        if (i % 1000000 == 0) {
            for (it = chaves.begin(); it != chaves.end(); it++) {
                cout << *it << ", ";
            }
            cout << endl;
        }
        i++;
    }
}

int main() {
    /*cout << "criptografando..." << endl;
    string criptografado = criptografar("chav", "jordao macedo");
    cout << "descriptografando..." << endl;
    string descriptografado = descriptografar("chav", criptografado);
    cout << descriptografado << endl;*/

    string criptografado;
    FILE *arq;
    arq = fopen("./../atividades_seguranca/02_descriptografar/texto.txt", "r");
    //Ler frase a partir do arquivo
    if(arq == NULL) {
        printf("Erro, nao foi possivel abrir o arquivo\n");
    } else {
        char ch;
        while( (ch=fgetc(arq))!= EOF )
            criptografado += ch;
    }
    fclose(arq);
    quebrar(criptografado);
    return 0;
}
