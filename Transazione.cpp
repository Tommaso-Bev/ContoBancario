//
// Created by tommy on 22/08/2023.
//

#include "Transazione.h"

#include <utility>

Transazione::Transazione(int valoreTransazione, string data, pair<int, int> ora, string descrizione,
                         string tipoTransazione)
        : valoreTransazione(valoreTransazione), data(std::move(data)), orario(std::move(ora)),
          descrizione(std::move(descrizione)), tipoTransazione(std::move(tipoTransazione)) {

}

int Transazione::getValoreTransazione() const {
    return valoreTransazione;
}

const string &Transazione::getData() const {
    return data;
}

const pair<int, int> &Transazione::getOra() const {
    return orario;
}

const string &Transazione::getDescrizione() const {
    return descrizione;
}

const string &Transazione::getTipoTransazione() const {
    return tipoTransazione;
}
