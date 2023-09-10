//
// Created by tommy on 22/08/2023.
//

#include "Conto.h"

#include <utility>

Conto::Conto(string name, int saldo) : name(std::move(name)), saldo(saldo) {}

const string &Conto::getName() const {
    return name;
}

int Conto::getSaldo() const {
    return saldo;
}

void Conto::depositare(int valoreDeposito, const string &descrizione) {
    saldo += valoreDeposito;
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);
    string data =
            to_string(localTime->tm_year + 1900) + to_string(localTime->tm_mon + 1) + to_string(localTime->tm_mday);

    transazioniPassate.push_back(
            make_unique<Transazione>(valoreDeposito, data, make_pair(localTime->tm_hour, localTime->tm_min),
                                     descrizione, "deposito"));
}

bool Conto::ritirare(int quantitaRitiro, const string &descrizione) {
    if (saldo >= quantitaRitiro) {
        saldo -= quantitaRitiro;
        time_t now = time(nullptr);
        tm *localTime = localtime(&now);
        string data =
                to_string(localTime->tm_year + 1900) + to_string(localTime->tm_mon + 1) + to_string(localTime->tm_mday);
        transazioniPassate.push_back(
                make_unique<Transazione>(quantitaRitiro, data, make_pair(localTime->tm_hour, localTime->tm_min),
                                         descrizione, "ritiro"));
        return true;
    } else {
        throw (runtime_error("Siamo dispiaciuti, ma la quantità di denaro richiesta non è presente nel conto"));
    }
}

vector<Transazione> Conto::transazioniDepositate() {
    std::vector<Transazione> transazioniDeposito;
    for (const auto &it: transazioniPassate) {
        if (it->getTipoTransazione() == "deposito")
            transazioniDeposito.push_back(*it);
    }
    return transazioniDeposito;
}

vector<Transazione> Conto::transazioniRitirate() {
    std::vector<Transazione> transazioniRitiro;
    for (const auto &it: transazioniPassate) {
        if (it->getTipoTransazione() == "ritiro")
            transazioniRitiro.push_back(*it);
    }
    return transazioniRitiro;
}

