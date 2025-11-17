
#include <iostream>
#include <fstream>
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

int msc(int linha, int coluna, int tamanhoVetor, const int* vetor) {
    if (coluna > tamanhoVetor) return 0;
    
    if (vetor[coluna] <= vetor[linha]) {
        return 1 + msc(coluna, coluna + 1, tamanhoVetor, vetor);
    } 
    int opcao1 = msc(linha, coluna + 1, tamanhoVetor, vetor);
    int opcao2 = msc(coluna, coluna + 1, tamanhoVetor, vetor);
    
    return max(opcao1, opcao2);
}

void processarMsc(int* vetor, int tamanho, vector<vector<int>>& matrizCusto, vector<vector<int>>& matrizRastreio) {
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
