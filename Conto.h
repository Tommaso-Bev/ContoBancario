//
// Created by tommy on 22/08/2023.
//

#ifndef CONTOBANCA_CONTO_H
#define CONTOBANCA_CONTO_H

#include <iostream>
#include <vector>
#include <memory>
#include <ctime>

#include "Transazione.h"

using namespace std;

class Conto {
public:
    //costruttore del conto
    Conto(string name, int saldo);

    void depositare(int valoreDeposito, string &descrizione);

    bool ritirare(int quantitaRitiro, string &descrizione);

    //metodi getter della classe Conto
    const string &getName() const;

    int getSaldo() const;

    vector<Transazione> transazioniDepositate();

    vector<Transazione> transazioniRitirate();

private:
    string name;
    int saldo;
    vector<unique_ptr<Transazione>> transazioniPassate;
};


#endif //CONTOBANCA_CONTO_H
