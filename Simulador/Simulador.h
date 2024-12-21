#ifndef TP_SIMULADOR_H
#define TP_SIMULADOR_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include "../Buffer/Buffer.h"
#include "../Caravanas/Caravana.h"

using namespace std;

class Simulador {
private:
    // Mapa
    vector<string> mapa;
    int linhas, colunas;

    // Parâmetros do jogo
    int moedas;

    // Itens
    int moedasPorItem;           // Valor das moedas por item
    int spawnTimeItens;          // Tempo de surgimento de itens
    int duracaoItens;            // Duração dos itens no mapa
    int maxItens;                // Máximo de itens no mapa

    // Valores de compra/venda
    int precoVendaMercadorias;   // Preço de venda de mercadorias
    int precoCompraMercadorias;  // Preço de compra de mercadorias
    int precoCaravana;           // Preço de compra de uma caravana

    // Bárbaros
    int spawnTimeBarbaros;       // Tempo de surgimento dos bárbaros
    int duracaoBarbaros;         // Duração dos bárbaros no mapa

    // Contadores do mapa
    int numCidades;              // Número de cidades
    int numCaravanas;            // Número de caravanas no mapa
    int numBarbaros;             // Número de bárbaros
    int numMontanhas;            // Número de montanhas
    int numDesertos;             // Número de células deserto

    // Estatísticas gerais
    int instantesPassados;       // Contagem de turnos
    int combatesVencidos;        // Contagem de combates vencidos

    // Vetor para itens ativos
    vector<shared_ptr<class Item>> itensAtivos;

public:
    Simulador()
            : linhas(0), colunas(0), moedas(0), moedasPorItem(0), spawnTimeItens(0), duracaoItens(0), maxItens(0),
              precoVendaMercadorias(0), precoCompraMercadorias(0), precoCaravana(0), spawnTimeBarbaros(0), duracaoBarbaros(0),
              numCidades(0), numCaravanas(0), numBarbaros(0), numMontanhas(0), numDesertos(0),
              instantesPassados(0), combatesVencidos(0) {}

    // Getters e Setters
    int getMoedas() const { return moedas; }
    void setMoedas(int moedas) { this->moedas = moedas; }

    int getSpawnTimeItens() const { return spawnTimeItens; }
    void setSpawnTimeItens(int valor) { spawnTimeItens = valor; }

    int getDuracaoItens() const { return duracaoItens; }
    void setDuracaoItens(int valor) { duracaoItens = valor; }

    int getMaxItens() const { return maxItens; }
    void setMaxItens(int valor) { maxItens = valor; }

    int getPrecoVendaMercadorias() const { return precoVendaMercadorias; }
    void setPrecoVendaMercadorias(int valor) { precoVendaMercadorias = valor; }

    int getPrecoCompraMercadorias() const { return precoCompraMercadorias; }
    void setPrecoCompraMercadorias(int valor) { precoCompraMercadorias = valor; }

    int getPrecoCaravana() const { return precoCaravana; }
    void setPrecoCaravana(int valor) { precoCaravana = valor; }

    int getSpawnTimeBarbaros() const { return spawnTimeBarbaros; }
    void setSpawnTimeBarbaros(int valor) { spawnTimeBarbaros = valor; }

    int getDuracaoBarbaros() const { return duracaoBarbaros; }
    void setDuracaoBarbaros(int valor) { duracaoBarbaros = valor; }

    // Retorna o número de linhas do mapa
    int getLinhas() const { return linhas; }

    // Retorna o número de colunas do mapa
    int getColunas() const { return colunas; }

    // Função para inicializar o mapa e os parâmetros do jogo
    bool initMap(const string& fileName) {
        ifstream f(fileName);
        if (!f) {
            cout << "Erro ao abrir ficheiro: " << fileName << endl;
            return false;
        }

        string nome_config;

        // Ler dimensões do mapa
        f >> nome_config >> linhas;
        f >> nome_config >> colunas;

        mapa.resize(linhas);
        f.ignore();

        // Ler o mapa
        for (int i = 0; i < linhas; ++i) {
            getline(f, mapa[i]);
            if (mapa[i].length() != static_cast<size_t>(colunas)) {
                cout << "Erro: Linha " << i + 1 << " com tamanho incorreto!" << endl;
                return false;
            }
        }

        // Analisar o mapa
        for (const auto& linha : mapa) {
            for (char celula : linha) {
                if (celula == '.') numDesertos++;
                else if (celula == '+') numMontanhas++;
                else if (celula >= 'a' && celula <= 'z') numCidades++;
                else if (celula >= '0' && celula <= '9') numCaravanas++;
                else if (celula == '!') numBarbaros++;
            }
        }

        // Ler as moedas iniciais
        f >> nome_config >> moedas;

        // Ler os itens
        f >> nome_config >> spawnTimeItens;
        f >> nome_config >> duracaoItens;
        f >> nome_config >> maxItens;

        // Ler os valores de compra e venda
        f >> nome_config >> precoVendaMercadorias;
        f >> nome_config >> precoCompraMercadorias;
        f >> nome_config >> precoCaravana;

        // Ler os bárbaros
        f >> nome_config >> spawnTimeBarbaros;
        f >> nome_config >> duracaoBarbaros;

        f.close();

        // Debug: Exibir informações carregadas
        cout << "DEBUG: Mapa carregado com " << linhas << " linhas e " << colunas << " colunas." << endl;
        cout << "DEBUG: Contadores do mapa: " << endl;
        cout << "  Desertos: " << numDesertos << ", Montanhas: " << numMontanhas
                  << ", Cidades: " << numCidades << ", Caravanas: " << numCaravanas
                  << ", Barbaros: " << numBarbaros << endl;
        cout << "DEBUG: Parametros do jogo: " << endl;
        cout << "  Moedas iniciais: " << moedas << endl;
        cout << "  Preco venda mercadorias: " << precoVendaMercadorias
                  << ", Preco compra mercadorias: " << precoCompraMercadorias
                  << ", Preco caravana: " << precoCaravana << endl;
        cout << "  Itens -> Spawn time: " << spawnTimeItens << ", Duracao: " << duracaoItens
                  << ", Maximo: " << maxItens << endl;
        cout << "  Barbaros -> Spawn time: " << spawnTimeBarbaros << ", Duracao: " << duracaoBarbaros << endl;

        return true;
    }

    // Renderizar o mapa no buffer
    void renderMap(Buffer& buffer) const {
        buffer.clear();
        for (int i = 0; i < linhas; ++i) {
            buffer.moveCursor(i, 0);
            buffer.putString(mapa[i]);
        }
    }

    // Adicionar moedas ao jogador
    void adicionaMoedas(int valor) {
        moedas += valor;
        cout << "DEBUG: Moedas agora: " << moedas << endl;
    }

    // Incrementar turnos
    void incrementarTurnos(int n) {
        instantesPassados += n;
    }

    // Registrar combate vencido
    void registrarCombateVencido() {
        combatesVencidos++;
    }

    // Terminar a simulação
    void terminarSimulacao() {
        // Exibe a pontuação final
        cout << "\n=== Pontuacao Final ===" << endl;
        cout << "Instantes passados: " << instantesPassados << endl;
        cout << "Combates vencidos: " << combatesVencidos << endl;
        cout << "Moedas restantes: " << moedas << endl;

        // Limpa os dados do simulador
        mapa.clear();
        linhas = colunas = 0;
        moedas = 0;
        numCidades = numCaravanas = numBarbaros = numMontanhas = numDesertos = 0;
        instantesPassados = 0;
        combatesVencidos = 0;
    }

    void exibirTabela() {
        cout << "          Tabela de Preços          " << endl;
        cout << "-----------------------------------" << endl;
        cout << "Item                Preço (Moedas)" << endl;
        cout << "-----------------------------------" << endl;
        cout << "Caravana           " << precoCaravana << endl;
        cout << "Compra             " << precoCompraMercadorias << endl;
        cout << "Venda              " << precoVendaMercadorias << endl;
    }

    // Classe base para itens
    class Item {
    public:
        string nome;
        int tempo;
        int x,y;

        Item(const string& n) : nome(n) {}
        virtual void efeito(Simulador& simulador) = 0;
        virtual ~Item() = default;
    };

    class CaixaDePandora : public Item {
    public:
        CaixaDePandora() : Item("Caixa de Pandora") {}
        void efeito(Simulador& simulador) override {
            cout << "20% da tripulação foi perdida!\n";
            // Implementação do efeito
        }
    };

    class ArcaDoTesouro : public Item {
    public:
        ArcaDoTesouro() : Item("Arca do Tesouro") {}
        void efeito(Simulador& simulador) override {
            int aumento = simulador.getMoedas() / 10;
            simulador.adicionaMoedas(aumento);
        }
    };

    class Jaula : public Item {
    public:
        Jaula() : Item("Jaula") {}
        void efeito(Simulador& simulador) override {
            int prisioneiros = 10;
            while ()
        }
    };

    class Mina : public Item {
    public:
        Mina() : Item("Mina") {}
        void efeito(Simulador& simulador) override {
            cout << "A caravana foi destruída!\n";
        }
    };

    class Surpresa : public Item {
    public:
        Surpresa() : Item("Surpresa") {}
        void efeito(Simulador& simulador) override {
            cout << "Um evento inesperado ocorreu!\n";
        }
    };

    /*void gerarItem() {
        if (itensAtivos.size() >= static_cast<size_t>(maxItens)) return;

        int tipo = rand() % 5;
        shared_ptr<Item> novoItem;

        switch (tipo) {
            case 0: novoItem = make_shared<CaixaDePandora>(); break;
            case 1: novoItem = make_shared<ArcaDoTesouro>(); break;
            case 2: novoItem = make_shared<Jaula>(); break;
            case 3: novoItem = make_shared<Mina>(); break;
            case 4: novoItem = make_shared<Surpresa>(); break;
        }

        itensAtivos.push_back(novoItem);
        cout << "Um novo item apareceu no deserto: " << novoItem->nome << endl;
    }*/
};

#endif //TP_SIMULADOR_H
