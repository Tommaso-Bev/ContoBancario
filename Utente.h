//
// Created by tommy on 24/08/2023.
//

#ifndef CONTOBANCA_UTENTE_H
#define CONTOBANCA_UTENTE_H

#include <iostream>
#include <vector>

#include "Conto.h"

using namespace std;

struct DataDiNascita {
    int giorno;
    int mese;
    int anno;
};

class Utente {
public:
    Utente(string nome, string cognome, const DataDiNascita &data);

    void deposita(int contoAttuale, int valoreDeposito, const string &descrizione);

    bool ritira(int contoAttuale, int quantitaRitiro, const string &descrizione);

    void creaConto(const string &nomeConto);

private:
    string nome;
    string cognome;
    DataDiNascita data;
    vector<unique_ptr<Conto>> contiCorrente;
};


#endif //CONTOBANCA_UTENTE_H
