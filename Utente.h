//
// Created by tommy on 24/08/2023.
//

#ifndef CONTOBANCA_UTENTE_H
#define CONTOBANCA_UTENTE_H

#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

#include "Conto.h"

using namespace std;

struct DataDiNascita {
    string giorno;
    string mese;
    string anno;

    DataDiNascita(string g, string m, string a) {
        giorno = std::move(g);
        mese = std::move(m);
        anno = std::move(a);
    }
};

class Utente {
public:

    Utente(string nome, string cognome, const DataDiNascita &data);

    //distruttore
    virtual ~Utente();

    //metodi attivi della classe utente
    void deposita(int contoAttuale, int valoreDeposito, const string &descrizione);

    bool ritira(int contoAttuale, int quantitaRitiro, const string &descrizione);

    void creaConto(const string &nomeConto);

    void salvaInformazioniUtente();

private:
    string nome;
    string cognome;
    DataDiNascita data;
    vector<unique_ptr<Conto>> contiCorrente;
};


#endif //CONTOBANCA_UTENTE_H
