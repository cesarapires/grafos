#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include<functional>

using namespace std;

struct No {
  char caractere;
  int frequencia;
  No *esquerda, *direita;

  No(char c, int f) : caractere(c), frequencia(f), esquerda(nullptr), direita(nullptr) {}
};

struct Comparar {
  bool operator()(No* esquerda, No* direita) {
    return esquerda->frequencia > direita->frequencia;
  }
};

No* construirArvoreHuffman(map<char, int>& frequencias) {
  priority_queue<No*, vector<No*>, Comparar> filaPrioridade;

  for (auto& par : frequencias) {
    filaPrioridade.push(new No(par.first, par.second));
  }

  while (filaPrioridade.size() > 1) {
    No* esquerda = filaPrioridade.top(); filaPrioridade.pop();
    No* direita = filaPrioridade.top(); filaPrioridade.pop();

    No* combinado = new No('\0', esquerda->frequencia + direita->frequencia);
    combinado->esquerda = esquerda;
    combinado->direita = direita;

    filaPrioridade.push(combinado);
  }

  return filaPrioridade.top();
}

void gerarCodigos(No* raiz, string codigo, map<char, string>& codigosHuffman) {
  if (!raiz) return;

  if (raiz->caractere != '\0') {
    codigosHuffman[raiz->caractere] = codigo;
  }

  gerarCodigos(raiz->esquerda, codigo + "0", codigosHuffman);
  gerarCodigos(raiz->direita, codigo + "1", codigosHuffman);
}

map<char, int> obterFrequenciasCaracteres(const string& nomeArquivo) {
  map<char, int> frequencias;
  ifstream arquivo(nomeArquivo);
  char caractere;

  while (arquivo.get(caractere)) {
    frequencias[caractere]++;
  }

  arquivo.close();
  return frequencias;
}

void escreverCodigosHuffman(const string& nomeArquivo, map<char, string>& codigosHuffman) {
  ofstream arquivo(nomeArquivo);

  for (auto& par : codigosHuffman) {
    arquivo << par.first << " " << par.second << endl;
  }

  arquivo.close();
}

int main() {
  vector<pair<string, string>> arquivos = {
    {"doc1.txt", "doc1_saida.txt"},
    {"doc2.txt", "doc2_saida.txt"}
  };

  for (auto& parArquivos : arquivos) {
    string arquivoEntrada = parArquivos.first;
    string arquivoSaida = parArquivos.second;

    map<char, int> frequencias = obterFrequenciasCaracteres(arquivoEntrada);
    No* raiz = construirArvoreHuffman(frequencias);

    map<char, string> codigosHuffman;
    gerarCodigos(raiz, "", codigosHuffman);

    escreverCodigosHuffman(arquivoSaida, codigosHuffman);
  }

  return 0;
}
