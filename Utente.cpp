//
// Created by tommy on 24/08/2023.
//

#include "Utente.h"

#include <utility>

Utente::Utente(string nome, string cognome, DataDiNascita data) : nome(std::move(nome)),
                                                                  cognome(std::move(cognome)),
                                                                  data(std::move(data)) {}

Utente::~Utente() {
    salvaInformazioniUtente();
    //la prossima istruzione la si può mettere per vedere le informazioni degli utenti al momento della distruzione dell'oggetto
    //leggiInfoUtente();
}

void Utente::deposita(int contoAttuale, int valoreDeposito, const string &descrizione) {
    if (valoreDeposito > 0)
        contiCorrente[contoAttuale]->depositare(valoreDeposito, descrizione);
}

bool Utente::ritira(int contoAttuale, int quantitaRitiro, const string &descrizione) {
    return contiCorrente[contoAttuale]->ritirare(quantitaRitiro, descrizione);
}

bool
Utente::trasferisci(int contoAttuale, int contoDestinazione, int quantitaTrasferimento, const string &descrizione) {
    bool t = ritira(contoAttuale, quantitaTrasferimento, "TRASFERIMENTO: " + descrizione);
    if (t)
        deposita(contoDestinazione, quantitaTrasferimento, "TRASFERIMENTO: " + descrizione);
    return t;
}

void Utente::creaConto(const string &nomeConto) {
    contiCorrente.push_back(std::make_unique<Conto>(nomeConto));
}

void Utente::salvaInformazioniUtente() {
    ofstream informazioni("informazioni.txt");
    informazioni << "INFORMAZIONI RELATIVE ALL'UTENTE: " << nome << " " << cognome << endl;
    informazioni << "NOME: " << nome << endl;
    informazioni << "COGNOME: " << cognome << endl;
    informazioni << "DATA DI NASCITA: " << data.giorno << " " << data.mese << " " << data.anno << endl;
    informazioni << "******CRONOLOGIA SALDO******" << endl;
    int numeroConto = 1;
    for (auto &i: contiCorrente) {
        informazioni << "*****CONTO N: " << numeroConto << "*****" << endl;
        informazioni << "NOME DEL CONTO: " << contiCorrente[numeroConto - 1]->getName() << endl;
        informazioni << "SALDO: " << contiCorrente[numeroConto - 1]->getSaldo() << endl;
        informazioni << "***TRANSAZIONI DEPOSITO***: " << endl;
        for (auto &transazioniDeposito: contiCorrente[numeroConto - 1]->transazioniDepositate()) {
            informazioni << "Deposito avvenuto il: " << transazioniDeposito.getData() << " ";
            informazioni << " alle ore: " << transazioniDeposito.getOra().first << " "
                         << transazioniDeposito.getOra().second << endl;
            informazioni << "di: " << transazioniDeposito.getValoreTransazione() << " euro" << endl;
            informazioni << "Motivazioni: " << transazioniDeposito.getDescrizione() << endl;
        }
        informazioni << "***TRANSAZIONI RITIRO***: " << endl;
        for (auto &transazioniRitiro: contiCorrente[numeroConto - 1]->transazioniRitirate()) {
            informazioni << "Ritiro avvenuto il: " << transazioniRitiro.getData() << " ";
            informazioni << " alle ore: " << transazioniRitiro.getOra().first << " "
                         << transazioniRitiro.getOra().second << endl;
            informazioni << "di: " << transazioniRitiro.getValoreTransazione() << " euro" << endl;
            informazioni << "Motivazioni: " << transazioniRitiro.getDescrizione() << endl;
        }
        numeroConto++;
    }
}

void Utente::leggiInfoUtente() {
    ifstream informazioni("informazioni.txt");
    string info;
    if (informazioni.is_open()) {
        while (getline(informazioni, info)) {
            cout << info << endl;
        }
        informazioni.close();
    }

}

const string &Utente::getNome() const {
    return nome;
}

const string &Utente::getCognome() const {
    return cognome;
}

unique_ptr<Conto> &Utente::getConto(int numeroConto) {
    if (numeroConto >= 0 && numeroConto < contiCorrente.size()) {
        return contiCorrente[numeroConto];
    } else {
        // Restituisci un riferimento nullo se il numeroConto non è valido.
        static unique_ptr<Conto> null_conto;
        return null_conto;
    }
}

unsigned long long Utente::getNumeroConti() {
    return contiCorrente.size();
}




