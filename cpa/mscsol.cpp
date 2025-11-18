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

int main(int argc, char* argv[]) {
    vector<string> saidas = {"saida1.txt", "saida2.txt", "saida3.txt"};
    for (size_t idx = 0; idx < saidas.size(); ++idx) {
        const string& nome = saidas[idx];
        ifstream in(nome);
        if (!in) {
            cerr << "Nao foi possivel abrir " << nome << "\n";
            continue;
        }

        int n;
        in >> n;
        if (!in || n <= 0) {
            cerr << "Formato invalido em " << nome << " (n)\n";
            continue;
        }

        vector<int> vetor(n);
        for (int i = 0; i < n; ++i) in >> vetor[i];

        int linhas = n + 1;
        int colunas = n + 1;

        vector<int> dadosCusto = lerMatrizInt(in, linhas, colunas);

        vector<int> dadosRastreio = lerMatrizInt(in, linhas, colunas);

        vector<int> sol;
        int i = 0;
        int j = 1;
        while (j <= n) {
            int col = j - 1;
            int mark = dadosRastreio[i * colunas + col];
            if (mark == 1) {
                sol.push_back(vetor[j - 1]);
                i = j;
                j = j + 1;
            } else {
                j = j + 1;
            }
        }

        string outName = "sol" + to_string(idx + 1) + ".txt";
        ofstream out(outName);
        if (!out) {
            cerr << "Nao foi possivel criar " << outName << "\n";
            continue;
        }

        for (size_t k = 0; k < sol.size(); ++k) {
            out << sol[k];
            if (k + 1 < sol.size()) out << ' ';
        }
        out << '\n';
    }
    
    return 0;
}
