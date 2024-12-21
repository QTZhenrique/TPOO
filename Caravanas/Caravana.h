#ifndef TP_CARAVANA_H
#define TP_CARAVANA_H


#include <iostream>

using namespace std;

class Caravana {
private:

    //Caravana
    int id;
    char tipo;
    int velocidade;
    int resistencia;

    //Tripulacao
    int tripulacao,maxTripulacao;

    //Agua
    int agua,maxAgua,gastoAgua;

    //Carga
    int carga,maxCarga;

    //Deslocamento
    int deslocamento,maxDeslocamento;

    //Probabilidade
    int pDestroi;

public:
    //Set

    //Caravana
    void setTipo(char tipo);
    void setVelocidade(int velocidade);
    void setResistencia(int resistencia);

    //Tripulacao
    void setTripulacao(int tripulacao);
    void setMaxTripulacao(int maxTripulacao);

    //Agua
    void setAgua(int agua);
    void setMaxAgua(int maxAgua);

    //Carga
    void setCarga(int carga);
    void setMaxCarga(int maxCarga);

    //Deslocamento
    void setDeslocamento(int deslocamento);
    void setMaxDeslocamento(int maxDeslocamento);

    //Probabilidades
    void setPDestroi(int pDestroi);

    //Get

    //Tripulacao
    int getTripulacao() const;
    int getMaxTripulacao() const;

    //Agua
    int getAgua() const;
    int getMaxAgua() const;
    virtual void consumoAgua() = 0;

    //Carga
    int getCarga() const;
    int getMaxCarga() const;

    //Deslocamento
    int getDeslocamento() const;
    int getMaxDeslocamento() const;

    //Probabilidades
    int getPDestroi() const;
    virtual void Tempestade() = 0;


};

class Militar : public Caravana {
private:
public:
    Militar() {
        setTipo('M');
        setVelocidade(2);
        setResistencia(2);
        setMaxDeslocamento(3);

        setTripulacao(40);
        setMaxTripulacao(40);

        setCarga(0);
        setMaxCarga(5);

        setAgua(400);
        setMaxAgua(400);
    }

    void consumoAgua() override {
        int cosumoAtual = ((getTripulacao() < getMaxTripulacao()) / 2) ? 1:3;
        if(getAgua() > 0) {
            setAgua(getAgua() - cosumoAtual);
        }
    }

    void Tempestade() override {
        int atualizaTripulacao = getTripulacao() * 0.1;
        setTripulacao(getTripulacao() - atualizaTripulacao);
        setPDestroi(25);
    }
};

class Comercio : public Caravana {
private:
public:
    Comercio() {
        setTipo('C');
        setVelocidade(1);
        setResistencia(1);
        setMaxDeslocamento(2);

        setTripulacao(20);
        setMaxTripulacao(40);

        setCarga(0);
        setMaxCarga(40);

        setAgua(400);
        setMaxAgua(400);
    }

    void consumoAgua() override {
        int cosumoAtual = ((getTripulacao() < getMaxTripulacao()) / 2) ? 1:2;
        if(getTripulacao() != 0 && getAgua() > 0) {
            setAgua(getAgua() - cosumoAtual);
        }
    }

    void Tempestade() override {
        int cargaAtual = (getCarga() / getMaxCarga()) * 100;

        if(cargaAtual > 50) {
            setPDestroi(50);
        }
        else {
            setPDestroi(25);
        }
    }
};

class Secreta : public Caravana {
private:
public:
};

class Barbaros : public Caravana {
public:
    Barbaros() {
        setTipo('B');
        setTripulacao(40);
        setMaxDeslocamento(2);
    }

    void Tempestade() override {
        int atualizaTripulacao = getTripulacao() * 0.1;
        setTripulacao(getTripulacao() - atualizaTripulacao);
        setPDestroi(25);
    }

};

#endif //TP_CARAVANA_H
