//
// Created by tommy on 26/08/2023.
//

#include "Interfaccia.h"

void Interfaccia::creareUtente() {
    cout << "Benvenuto nella creazione del profilo" << endl;
    string inputN;
    string inputC;
    cout << "Inserire il proprio nome: ";
    inputN = controlloInputStringhe(0, 30);
    cout << "Inserire il proprio cognome: ";
    inputC = controlloInputStringhe(0, 40);
    cout << "Inserire la propria data di nascita: ";
    DataDiNascita d = controlloInputData();
    utente = make_unique<Utente>(inputN, inputC, d);
}

void Interfaccia::creareConto() {
    string nomeConto;
    cout << "Hai scelto di creare un nuovo conto" << endl;
    cout << "Scegli un nome da affidare al conto: " << endl;
    cin >> nomeConto;
    utente->creaConto(nomeConto);
}

void Interfaccia::stampaScelte() {
    cout << "BENVENUTO: " << utente->getNome() << " " << utente->getCognome() << endl;
    cout << "premere [1] per depositare" << endl;
    cout << "premere [2] per ritirare" << endl;
    cout << "premere [3] per trasferire ad un altro tuo conto" << endl;
    cout << "premere [4] per creare un nuovo conto" << endl;
    cout << "premere [5] per vedere tutte le tue informazioni" << endl;
    cout << "premere [6] per uscire" << endl;
}

void Interfaccia::selezionareAzioni() {
    cout << "Benvenuto nell'interfaccia cliente" << endl;
    if (utente == nullptr) {
        cout << "Per iniziare creare un profilo:" << endl;
        creareUtente();
    }
    if (utente->getConto(0) == nullptr) {
        cout << "Per iniziare a fare transazioni devi possedere almeno un conto." << endl;
        creareConto();
    }
    while (true) {
        cout << "Selezionare il conto in cui fare transazioni:";
        int numeroConto = controlloInputConto();
        stampaScelte();
        int scelta;
        cin >> scelta;
        if (scelta == 6) {
            cout << "Arrivederci.";
            break;
        } else {
            switch (scelta) {
                case 1: {
                    cout << "immetere la quantità di denaro da depositare sul conto: ";
                    int quant;
                    cin >> quant;
                    string causale;
                    cout << "scrivere eventuali motivazioni della transazione: ";
                    cin >> causale;
                    utente->deposita(numeroConto, quant, causale);
                    break;
                }
                case 2: {
                    cout << "immettere la quantità di denaro da ritirare dal conto: ";
                    int quant;
                    cin >> quant;
                    string causale;
                    cout << "scrivere eventuali motivazioni della transazione: ";
                    cin >> causale;
                    utente->ritira(numeroConto, quant, causale);
                    break;
                }
                case 3: {
                    cout << "selezionare a quale conto trasferire il denaro: ";
                    int destinazione = -1;
                    while (destinazione == numeroConto) {
                        destinazione = controlloInputConto();
                    }
                    cout << "immettere la quantità di denaro da trasferire al secondo conto: ";
                    int quant;
                    cin >> quant;
                    string causale;
                    cout << "scrivere eventuali motivazioni della transazione: ";
                    cin >> causale;
                    utente->trasferisci(numeroConto, destinazione, quant, causale);
                    break;
                }
                case 4: {
                    cout << "Stai per creare un nuovo conto: ";
                    creareConto();
                    break;
                }
                case 5: {
                    utente->leggiInfoUtente();
                    break;
                }
            }
        }

    }
}

string Interfaccia::controlloInputStringhe(int numeroMinimoCaratteri, int numeroMassimoCaratteri) {
    string input;
    try {
        cin >> input;
        getline(cin, input);
        if (input.length() > numeroMassimoCaratteri or input.length() < numeroMinimoCaratteri)
            throw out_of_range("string inserita non valida");
    }
    catch (const out_of_range &e) {
        cerr << e.what() << endl;
    }
    return input;
}

DataDiNascita Interfaccia::controlloInputData() {
    DataDiNascita input("-1", "-1", "-1");
    try {
        //TODO per ora non faccio alcun tipo di controllo in questo metodo, chiedo solamente di fare l'input delle informazioni
        cout << "giorno: ";
        cin >> input.giorno;
        cout << " mese: ";
        cin >> input.mese;
        cout << " anno: ";
        cin >> input.anno;
    }
    catch (exception &e) {}
    return input;
}

int Interfaccia::controlloInputConto() {
    int controllo;
    while (true) {
        cin >> controllo;
        if (utente->getConto(controllo))
            return controllo;
        else
            cerr << "Il conto da lei selezionato non esiste!" << endl;
    }
}


