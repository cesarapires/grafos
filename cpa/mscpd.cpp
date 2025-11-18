
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;

void lerArquivoEntrada(const string& nomeArquivo, int*& vetor, int& tamanho) {
    ifstream in(nomeArquivo);

    if (!in) {
        return;
    }

    in >> tamanho;

    if (!in || tamanho <= 0) {
        return;
    }

    vetor = new int[tamanho];
    for (int i = 0; i < tamanho; ++i) {
        in >> vetor[i];
        if (!in) {
            delete[] vetor;
            vetor = nullptr;
            tamanho = 0;
            return;
        }
    }

    return;
}

int msc(int linha, int coluna, int tamanhoVetor, const int* vetor,
    vector<vector<int>>& matrizCusto, vector<vector<int>>& matrizRastreio) {
    int indiceColuna = coluna - 1;

    if (coluna > tamanhoVetor) {
        if (linha >= 0 && linha <= tamanhoVetor && indiceColuna >= 0 && indiceColuna <= tamanhoVetor)
            matrizCusto[linha][indiceColuna] = 0;
        return 0;
    }

    if (matrizCusto[linha][indiceColuna] != -1) return matrizCusto[linha][indiceColuna];

    int vLinha = (linha == 0) ? INT_MIN : vetor[linha - 1];
    int vColuna = vetor[coluna - 1];

    int pular = msc(linha, coluna + 1, tamanhoVetor, vetor, matrizCusto, matrizRastreio);
    int valor;
    if (vColuna <= vLinha) {
        matrizRastreio[linha][indiceColuna] = 0;
        valor = pular;
    } else {
        int pegar = 1 + msc(coluna, coluna + 1, tamanhoVetor, vetor, matrizCusto, matrizRastreio);
        if (pegar > pular) {
            matrizRastreio[linha][indiceColuna] = 1;
            valor = pegar;
        } else {
            matrizRastreio[linha][indiceColuna] = 0;
            valor = pular;
        }
    }

    matrizCusto[linha][indiceColuna] = valor;
    return valor;
}

void processarMsc(int* vetor, int tamanho, vector<vector<int>>& matrizCusto, vector<vector<int>>& matrizRastreio) {
    if (tamanho <= 0) return;

    for (int i = 0; i <= tamanho; ++i) {
        for (int j = 0; j <= tamanho; ++j) {
            matrizCusto[i][j] = -1;
            matrizRastreio[i][j] = 0;
        }
    }

    for (int i = 0; i <= tamanho; ++i) {
        for (int col = 0; col <= i - 1; ++col) {
            matrizCusto[i][col] = 0;
            matrizRastreio[i][col] = 0;
        }
    }

    for (int i = 0; i <= tamanho; ++i) {
        msc(i, i + 1, tamanho, vetor, matrizCusto, matrizRastreio);
    }
}

void escreverArquivoSaida(const string& nomeArquivo, const int* vetor, int tamanho, const vector<vector<int>>& matrizCusto, const vector<vector<int>>& matrizRastreio) {
    ofstream out(nomeArquivo);

    if (!out) {
        cerr << "Erro ao abrir " << nomeArquivo << "\n";
        return;
    }

    out << tamanho << endl;

    for (int i = 0; i < tamanho; ++i) {
        out << vetor[i];
        if (i + 1 < tamanho) out << ' ';
    }

    out << endl;

    for (size_t i = 0; i < matrizCusto.size(); ++i) {
        for (size_t j = 0; j < matrizCusto[i].size(); ++j) {
            out << matrizCusto[i][j];
            if (j + 1 < matrizCusto[i].size()) out << ' ';
        }
        out << endl;
    }

    for (size_t i = 0; i < matrizRastreio.size(); ++i) {
        for (size_t j = 0; j < matrizRastreio[i].size(); ++j) {
            out << matrizRastreio[i][j];
            if (j + 1 < matrizRastreio[i].size()) out << ' ';
        }
        out << endl;
    }
}

int main(int argc, char* argv[]) {
    vector<string> entradas = {"entrada1.txt", "entrada2.txt", "entrada3.txt"};

    for (size_t i = 0; i < entradas.size(); ++i) {
        int tamanhoEntrada = 0;
        int* vetor = nullptr;

        lerArquivoEntrada(entradas[i], vetor, tamanhoEntrada);

        if (vetor == nullptr || tamanhoEntrada <= 0) {
            cerr << "Falha ao ler " << entradas[i] << " ou arquivo vazio/inválido. Pulando.\n";
            continue;
        }

        vector<vector<int>> matrizCusto(tamanhoEntrada + 1, vector<int>(tamanhoEntrada + 1, 0));

        vector<vector<int>> matrizRastreio(tamanhoEntrada + 1, vector<int>(tamanhoEntrada + 1, 0));

        processarMsc(vetor, tamanhoEntrada, matrizCusto, matrizRastreio);

        string saida = "saida" + to_string(i + 1) + ".txt";

        escreverArquivoSaida(saida, vetor, tamanhoEntrada, matrizCusto, matrizRastreio);

        delete[] vetor;
    }

    return 0;
}
