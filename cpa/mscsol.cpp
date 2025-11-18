#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> lerMatrizInt(ifstream &in, int linhas, int colunas) {
    vector<int> dados;

    dados.reserve(linhas * colunas);
    
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int x;
            in >> x;
            dados.push_back(x);
        }
    }
    
    return dados;
}

bool escreverSolucao(const string& outName, const vector<int>& sol) {
    ofstream out(outName);
    
    if (!out) {
        cerr << "Nao foi possivel criar " << outName << endl;
        return false;
    }

    for (size_t k = 0; k < sol.size(); ++k) {
        out << sol[k];
        if (k + 1 < sol.size()) out << ' ';
    }
    
    return true;
}

vector<int> construirSolucao(const vector<int>& vetor, int n, int colunas, const vector<int>& dadosRastreio) {
    vector<int> sol;
    
    int i = 0;
    int j = 1;

    while (j <= n) {
        int col = j - 1;
        int mark = dadosRastreio[i * colunas + col];
        if (mark == 1) {
            sol.push_back(vetor[j - 1]);
            i = j;
            ++j;
        } else {
            ++j;
        }
    }
    
    return sol;
}

int main(int argc, char* argv[]) {
    vector<string> saidas = {"saida1.txt", "saida2.txt", "saida3.txt"};
    for (size_t idx = 0; idx < saidas.size(); ++idx) {
        const string& nome = saidas[idx];
        ifstream in(nome);
        if (!in) {
            cerr << "Nao foi possivel abrir " << nome << endl;
            continue;
        }

        int n;
        in >> n;
        if (!in || n <= 0) {
            cerr << "Formato invalido em " << nome << " (n)" << endl;
            continue;
        }

        vector<int> vetor(n);
        for (int i = 0; i < n; ++i) in >> vetor[i];

        int linhas = n + 1;
        int colunas = n + 1;

        vector<int> dadosCusto = lerMatrizInt(in, linhas, colunas);

        vector<int> dadosRastreio = lerMatrizInt(in, linhas, colunas);

        vector<int> sol = construirSolucao(vetor, n, colunas, dadosRastreio);

        string outName = "sol" + to_string(idx + 1) + ".txt";
        
        if (!escreverSolucao(outName, sol)) continue;
    }
    
    return 0;
}