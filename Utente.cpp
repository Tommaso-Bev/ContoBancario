//
// Created by tommy on 24/08/2023.
//

#include "Utente.h"

#include <utility>

Utente::Utente(string nome, string cognome, const DataDiNascita &data) : nome(std::move(nome)),
                                                                         cognome(std::move(cognome)),
                                                                         data(data) {}

void Utente::deposita(int contoAttuale, int valoreDeposito, const string &descrizione) {
    contiCorrente[contoAttuale]->depositare(valoreDeposito, descrizione);
}

bool Utente::ritira(int contoAttuale, int quantitaRitiro, const string &descrizione) {
    try {
        contiCorrente[contoAttuale]->ritirare(quantitaRitiro, descrizione);
    }
    catch (runtime_error &errore) {
        cerr << errore.what() << endl;
        return false;
    }
    return true;
}

void Utente::creaConto(const string &nomeConto) {
    contiCorrente.push_back(make_unique<Conto>(nomeConto));
}
