#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> lerMatrizInt(ifstream &arquivoEntrada, int totalLinhas, int totalColunas) {
    vector<int> matriz;
    matriz.reserve(totalLinhas * totalColunas);

    for (int linha = 0; linha < totalLinhas; ++linha) {
        for (int coluna = 0; coluna < totalColunas; ++coluna) {
            int valor;
            arquivoEntrada >> valor;
            matriz.push_back(valor);
        }
    }
    return matriz;
}

bool escreverSolucao(const string& nomeArquivoSaida, const vector<int>& solucao) {
    ofstream arquivoSaida(nomeArquivoSaida);

    if (!arquivoSaida) {
        cerr << "Não foi possível criar " << nomeArquivoSaida << endl;
        return false;
    }

    for (size_t index = 0; index < solucao.size(); ++index) {
        arquivoSaida << solucao[index];
        if (index + 1 < solucao.size()) {
            arquivoSaida << ' ';
        }
    }

    return true;
}

vector<int> construirSolucao(const vector<int>& dadosVetorOriginal,
                             int tamanhoVetor,
                             int totalColunas,
                             const vector<int>& matrizRastreio) 
{
    vector<int> solucao;

    int linhaAtual = 0;
    int elementoAtual = 1;

    while (elementoAtual <= tamanhoVetor) {
        int colunaIndex = elementoAtual - 1;
        int marcaRastreio = matrizRastreio[linhaAtual * totalColunas + colunaIndex];

        if (marcaRastreio == 1) {
            solucao.push_back(dadosVetorOriginal[elementoAtual - 1]);
            linhaAtual = elementoAtual;
        }

        ++elementoAtual;
    }

    return solucao;
}

int main(int argc, char* argv[]) {
    vector<string> arquivosEntrada = {"saida1.txt", "saida2.txt", "saida3.txt"};

    for (size_t indiceArquivo = 0; indiceArquivo < arquivosEntrada.size(); ++indiceArquivo) {
        const string& nomeArquivoEntrada = arquivosEntrada[indiceArquivo];
        ifstream arquivoEntrada(nomeArquivoEntrada);

        if (!arquivoEntrada) {
            cerr << "Não foi possível abrir " << nomeArquivoEntrada << endl;
            continue;
        }

        int tamanhoVetor;
        arquivoEntrada >> tamanhoVetor;

        if (!arquivoEntrada || tamanhoVetor <= 0) {
            cerr << "Formato inválido em " << nomeArquivoEntrada << " (tamanhoVetor)" << endl;
            continue;
        }

        vector<int> vetorOriginal(tamanhoVetor);
        for (int i = 0; i < tamanhoVetor; ++i) {
            arquivoEntrada >> vetorOriginal[i];
        }

        int totalLinhas = tamanhoVetor + 1;
        int totalColunas = tamanhoVetor + 1;

        vector<int> matrizCusto = lerMatrizInt(arquivoEntrada, totalLinhas, totalColunas);
        vector<int> matrizRastreio = lerMatrizInt(arquivoEntrada, totalLinhas, totalColunas);

        vector<int> solucao = construirSolucao(vetorOriginal, tamanhoVetor, totalColunas, matrizRastreio);

        string nomeArquivoSaida = "sol" + to_string(indiceArquivo + 1) + ".txt";

        escreverSolucao(nomeArquivoSaida, solucao);
    }

    return 0;
}