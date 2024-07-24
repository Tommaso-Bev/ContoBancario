//
// Created by tommy on 24/08/2023.
//

#include "Utente.h"
#include <sstream>
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
    salvaInformazioniUtente();
}

bool Utente::ritira(int contoAttuale, int quantitaRitiro, const string &descrizione) {
    bool val = contiCorrente[contoAttuale]->ritirare(quantitaRitiro, descrizione);
    salvaInformazioniUtente();
    return val;
}

bool
Utente::trasferisci(int contoAttuale, int contoDestinazione, int quantitaTrasferimento, const string &descrizione) {
    bool t = ritira(contoAttuale, quantitaTrasferimento, "TRASFERIMENTO: " + descrizione);
    if (t)
        deposita(contoDestinazione, quantitaTrasferimento, "TRASFERIMENTO: " + descrizione);
    salvaInformazioniUtente();
    return t;
}

void Utente::creaConto(const string &nomeConto) {
    contiCorrente.push_back(std::make_unique<Conto>(nomeConto));
    salvaInformazioniUtente();
}

bool Utente::chiudiConto(const int &nConto) {
    if (contiCorrente.at(nConto)->getSaldo() == 0) {
        contiCorrente.erase(contiCorrente.begin() + nConto);
        salvaInformazioniUtente();
        return true;
    } else {
        cout << "Nel saldo ci sono ancora " << contiCorrente.at(nConto)->getSaldo()
             << " euro, trasferiscili ad un altro conto e poi elimina" << endl;
        return false;
    }

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
        informazioni << "*****FINE CONTO N:" << numeroConto << "*****" << endl;
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

void Utente::leggiInfoUtenteSpecifico(int accountNumber) {
    std::ifstream file("informazioni.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string accountHeader = "*****CONTO N: " + std::to_string(accountNumber + 1) + "*****";
    size_t startPos = buffer.str().find(accountHeader);

    if (startPos == std::string::npos) {
        std::cout << "Conto numero " << accountNumber + 1 << " non trovato." << std::endl;
        return;
    }

    size_t endPos = buffer.str().find(
            "*****FINE CONTO N:" + std::to_string(accountNumber + 1) + "*****" + std::to_string(accountNumber + 1) +
            "*****", startPos + accountHeader.length());
    if (endPos == std::string::npos) {
        endPos = buffer.str().length();
    }

    std::string accountInfo = buffer.str().substr(startPos, endPos - startPos);
    std::cout << accountInfo << std::endl;
}




