//
// Created by tommy on 22/08/2023.
//

#ifndef CONTOBANCA_TRANSAZIONE_H
#define CONTOBANCA_TRANSAZIONE_H

#include <iostream>

using namespace std;

class Transazione {
public:
    //costruttore della transazione
    Transazione(int valoreTransazione, string data, pair<int, int> ora, string descrizione, string tipoTransazione);

    //metodi getter della classe Transazione

    int getValoreTransazione() const;

    const string &getData() const;

    const pair<int, int> &getOra() const;

    const string &getDescrizione() const;

    const string &getTipoTransazione() const;

private:
    int valoreTransazione;
    string data;
    pair<int, int> orario;
    string descrizione;
    string tipoTransazione; //se è stato un ritiro o un deposito
};


#endif //CONTOBANCA_TRANSAZIONE_H
