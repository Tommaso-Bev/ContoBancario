//
// Created by tommy on 26/08/2023.
//

#ifndef CONTOBANCA_INTERFACCIA_H
#define CONTOBANCA_INTERFACCIA_H

#include <iostream>
#include <sstream>
#include <limits>
#include <cstring>

#include "Utente.h"

using namespace std;

class Interfaccia {
public:
    //creazione di utenti e di conti secondo imput cliente
    void creareUtente();

    void creareConto();

    //metodo generale che faccia fare all'utente le proprie scelte
    void selezionareAzioni();

    //codici di utilità per non fare codice duplicato

    void stampaScelte();

    void interfacciaAreaPersonale();

    void interfacciaAreaConto();

    void stampaScelteConto();

    string controlloInputStringhe(int numeroMinimoCaratteri, int numeroMassimoCaratteri);

    DataDiNascita controlloInputData();

    int controlloInputConto();

    int controlloInputQuant();

private:
    unique_ptr<Utente> utente;
    std::vector<std::string> mesiValidi = {
            "gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno",
            "luglio", "agosto", "settembre", "ottobre", "novembre", "dicembre"
    };
};


#endif //CONTOBANCA_INTERFACCIA_H
