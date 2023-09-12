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
    int giorno;
    string mese;
    int anno;

    DataDiNascita(int g, string m, int a) {
        giorno = g;
        mese = std::move(m);
        anno = a;
    }

    DataDiNascita() {}

};

class Utente {
public:

    Utente(string nome, string cognome, DataDiNascita data);

    //distruttore
    virtual ~Utente();

    //metodi attivi della classe utente
    void deposita(int contoAttuale, int valoreDeposito, const string &descrizione);

    bool ritira(int contoAttuale, int quantitaRitiro, const string &descrizione);

    bool trasferisci(int contoAttuale, int contoDestinazione, int quantitaTrasferimento, const string &descrizione);

    void creaConto(const string &nomeConto);

    void salvaInformazioniUtente();

    void leggiInfoUtente();

    //metodi getter per nome e cognome (utilizzati nell'interfaccia)

    const string &getNome() const;

    const string &getCognome() const;

    unique_ptr<Conto> &getConto(int numeroConto);

    unsigned long long getNumeroConti();

private:
    string nome;
    string cognome;
    DataDiNascita data;
    vector<unique_ptr<Conto>> contiCorrente;
};


#endif //CONTOBANCA_UTENTE_H
