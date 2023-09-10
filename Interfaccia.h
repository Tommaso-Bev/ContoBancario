//
// Created by tommy on 26/08/2023.
//

#ifndef CONTOBANCA_INTERFACCIA_H
#define CONTOBANCA_INTERFACCIA_H

#include <iostream>
#include <sstream>
#include <limits>

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

    string controlloInputStringhe(int numeroMinimoCaratteri, int numeroMassimoCaratteri);

    DataDiNascita controlloInputData();

    int controlloInputConto();

    int controlloInputQuant();

private:
    unique_ptr<Utente> utente;
};


#endif //CONTOBANCA_INTERFACCIA_H
