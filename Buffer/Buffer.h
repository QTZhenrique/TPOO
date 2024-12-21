#ifndef TP_BUFFER_H
#define TP_BUFFER_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Buffer {
private:
    char** data;                  // Buffer bidimensional
    int rows, cols;               // Dimensões do buffer
    int cursorRow, cursorCol;     // Posição atual do cursor
    map<string, char**> savedStates; // Estados salvos do buffer

    void deleteBuffer(char** buffer) {
        for (int i = 0; i < rows; ++i) {
            delete[] buffer[i];
        }
        delete[] buffer;
    }

public:
    // Construtor: inicializa o buffer com espaços em branco
    Buffer(int r, int c) : rows(r), cols(c), cursorRow(0), cursorCol(0) {
        data = new char*[rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new char[cols];
        clear();
    }

    // Destrutor: libera memória alocada e limpa estados salvos
    ~Buffer() {
        deleteBuffer(data);
        for (auto& [name, buffer] : savedStates) {
            deleteBuffer(buffer);
        }
    }

    // Limpar o buffer (preencher com espaços)
    void clear() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = ' ';
            }
        }
    }

    // Transcrever o buffer para a consola
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j];
            }
            cout << '\n';
        }
    }

    // Mover o cursor para uma posição específica
    void moveCursor(int row, int col) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            cursorRow = row;
            cursorCol = col;
        }
    }

    // Inserir um carácter na posição atual do cursor
    void putChar(char ch) {
        if (cursorRow >= 0 && cursorRow < rows && cursorCol >= 0 && cursorCol < cols) {
            data[cursorRow][cursorCol] = ch;
        }
        cursorCol++;
        if (cursorCol >= cols) {
            cursorCol = 0;
            cursorRow++;
        }
    }

    // Inserir uma string na posição atual do cursor
    void putString(const string& str) {
        for (char ch : str) {
            putChar(ch);
        }
    }

    // Guardar o estado atual do buffer
    void saveState(const string& name) {
        char** savedBuffer = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            savedBuffer[i] = new char[cols];
            for (int j = 0; j < cols; ++j) {
                savedBuffer[i][j] = data[i][j];
            }
        }
        savedStates[name] = savedBuffer;
    }

    // Carregar um estado salvo do buffer
    bool loadState(const string& name) {
        if (savedStates.find(name) != savedStates.end()) {
            clear(); // Limpa o buffer atual
            char** savedBuffer = savedStates[name];
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    data[i][j] = savedBuffer[i][j];
                }
            }
            return true;
        }
        return false;
    }

    // Listar todos os estados salvos
    void listStates() const {
        for (const auto& [name, _] : savedStates) {
            cout << name << endl;
        }
    }

    // Apagar um estado salvo
    bool deleteState(const string& name) {
        if (savedStates.find(name) != savedStates.end()) {
            deleteBuffer(savedStates[name]);
            savedStates.erase(name);
            return true;
        }
        return false;
    }
};

#endif //TP_BUFFER_H
