#ifndef TP_UI_H
#define TP_UI_H

#include "../Simulador/Simulador.h"
#include "../Buffer/Buffer.h"
#include <iostream>
#include <sstream>

using namespace std;

class UI {
private:
    Simulador& simulador;
    Buffer* buffer;
    bool simuladorEmExecucao;

public:
    UI(Simulador& sim) : simulador(sim), simuladorEmExecucao(false){
        buffer = new Buffer(1, 1);// Inicializa o buffer com dimensões padrão (serão ajustadas após 'config')
    }

    ~UI() {
        delete buffer;
    }

    void executa() {
        string cmd;
        while (true) {
            cout << ">> ";
            getline(cin, cmd);

            if (cmd.empty()) continue;

            istringstream iss(cmd);
            string acao, parametro1, parametro2;
            int p1, p2, p3;

            iss >> acao;

            // Fase de configuração (menu inicial)
            if (!simuladorEmExecucao) {
                if (acao == "config") {
                    iss >> parametro1;
                    if (simulador.initMap(parametro1)) {
                        // Redimensiona o buffer de acordo com as dimensões do mapa
                        delete buffer;
                        buffer = new Buffer(simulador.getLinhas(), simulador.getColunas());

                        cout << "Mapa carregado com sucesso!" << endl;
                        simulador.renderMap(*buffer);
                        buffer->print(); // Mostra o mapa no buffer
                        simuladorEmExecucao = true; // Inicia a fase de execução
                    } else {
                        cout << "Erro ao carregar mapa." << endl;
                    }
                } else if (acao == "sair") {
                    break;
                } else {
                    cout << "Comando invalido! Use 'config' para iniciar ou 'sair' para terminar." << endl;
                }
            }
            // Fase de execução (simulação)
            else {
                if (acao == "moedas") {
                    iss >> p1;
                    simulador.adicionaMoedas(p1);
                } else if (acao == "exec") {
                    iss >> parametro1;
                    // TODO: Implementar lógica de executar comandos de ficheiro
                    cout << "DEBUG: Comando 'exec' chamado com " << parametro1 << endl;
                } else if (acao == "prox") {
                    iss >> p1;
                    // TODO: Implementar lógica de avancar turnos
                    cout << "DEBUG: Comando 'prox' chamado para avancar " << p1 << " turnos." << endl;
                } else if (acao == "comprac") {
                    iss >> parametro1 >> parametro2;
                    // TODO: Implementar lógica de compra de caravana
                    cout << "DEBUG: Comando 'comprac' chamado para cidade " << parametro1 << " e tipo " << parametro2
                         << endl;
                } else if (acao == "precos") {
                    simulador.exibirTabela();
                    cout << "DEBUG: Comando 'precos' chamado." << endl;
                } else if (acao == "cidade") {
                    iss >> parametro1;
                    // TODO: Implementar lógica de listar cidade
                    cout << "DEBUG: Comando 'cidade' chamado para cidade " << parametro1 << endl;
                } else if (acao == "caravana") {
                    iss >> parametro1;
                    // TODO: Implementar lógica de listar caravana
                    cout << "DEBUG: Comando 'caravana' chamado para caravana " << parametro1 << endl;
                } else if (acao == "compra") {
                    iss >> p1 >> p2;
                    // TODO: Implementar lógica de compra de mercadorias
                    cout << "DEBUG: Comando 'compra' chamado para caravana " << p1 << " com " << p2 << " toneladas."
                         << endl;
                } else if (acao == "vende") {
                    iss >> p1;
                    // TODO: Implementar lógica de venda de mercadorias
                    cout << "DEBUG: Comando 'vende' chamado para caravana " << p1 << endl;
                } else if (acao == "move") {
                    iss >> p1 >> parametro1;
                    // TODO: Implementar lógica de movimento de caravanas
                    cout << "DEBUG: Comando 'move' chamado para caravana " << p1 << " na direcao " << parametro1
                         << endl;
                } else if (acao == "auto") {
                    iss >> p1;
                    // TODO: Implementar lógica de ativar modo automatico
                    cout << "DEBUG: Comando 'auto' chamado para caravana " << p1 << endl;
                } else if (acao == "stop") {
                    iss >> p1;
                    // TODO: Implementar lógica de parar comportamento automatico
                    cout << "DEBUG: Comando 'stop' chamado para caravana " << p1 << endl;
                } else if (acao == "barbaro") {
                    iss >> p1 >> p2;
                    // TODO: Implementar lógica de criar barbaros
                    cout << "DEBUG: Comando 'barbaro' chamado para posicao (" << p1 << ", " << p2 << ")" << endl;
                } else if (acao == "areia") {
                    iss >> p1 >> p2 >> p3;
                    // TODO: Implementar lógica de tempestades de areia
                    cout << "DEBUG: Comando 'areia' chamado para posicao (" << p1 << ", " << p2 << ") com raio " << p3
                         << endl;
                } else if (acao == "saves") {
                    iss >> parametro1;
                    buffer->saveState(parametro1);
                    cout << "DEBUG: Estado salvo com o nome: " << parametro1 << endl;
                } else if (acao == "loads") {
                    iss >> parametro1;
                    if (buffer->loadState(parametro1)) {
                        cout << "DEBUG: Estado carregado: " << parametro1 << endl;
                        buffer->print(); // Mostra o estado carregado
                    } else {
                        cout << "Erro: Estado nao encontrado." << endl;
                    }
                } else if (acao == "lists") {
                    cout << "DEBUG: Estados guardados:" << endl;
                    buffer->listStates();
                } else if (acao == "dels") {
                    iss >> parametro1;
                    if (buffer->deleteState(parametro1)) {
                        cout << "DEBUG: Estado apagado: " << parametro1 << endl;
                    } else {
                        cout << "Erro: Estado nao encontrado." << endl;
                    }
                } else if (acao == "terminar") {
                    simulador.terminarSimulacao();
                    simuladorEmExecucao = false;
                } else {
                    cout << "Comando invalido!" << endl;
                }
            }
        }
    }
};

#endif //TP_UI_H
