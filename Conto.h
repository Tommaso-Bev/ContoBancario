//
// Created by tommy on 22/08/2023.
//

#ifndef CONTOBANCA_CONTO_H
#define CONTOBANCA_CONTO_H

#include <iostream>
#include <vector>
#include <memory>

#include "Transazione.h"

using namespace std;

class Conto {
public:
    //costruttore del conto
    Conto(string name, int saldo = 0);

    void depositare(int valoreDeposito, const string &descrizione);

    bool ritirare(int quantitaRitiro, const string &descrizione);

    //metodi getter della classe Conto
    const string &getName() const;

    int getSaldo() const;

    vector<Transazione> transazioniDepositate() const;

    vector<Transazione> transazioniRitirate() const;

    //aggiunte
    vector<Transazione> cercaPerData(const string &data) const;

    int getNumeroTransazioni() const;

    void aggiungiTransazioneDiVecchiaData(Transazione t); //serve unicamente per il testing del cercaPerData

private:
    string name;
    int saldo;
    vector<unique_ptr<Transazione>> transazioniPassate;
};


#endif //CONTOBANCA_CONTO_H
