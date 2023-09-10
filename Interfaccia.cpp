//
// Created by tommy on 26/08/2023.
//

#include "Interfaccia.h"

void Interfaccia::creareUtente() {
    cout << "Benvenuto nella creazione del profilo" << endl;
    string inputN;
    string inputC;
    cout << "Inserire il proprio nome: " << endl;
    inputN = controlloInputStringhe(0, 30);
    cout << "Inserire il proprio cognome: " << endl;
    inputC = controlloInputStringhe(0, 40);
    cout << "Inserire la propria data di nascita: " << endl;
    DataDiNascita d = controlloInputData();
    utente = make_unique<Utente>(inputN, inputC, d);
}

void Interfaccia::creareConto() {
    string nomeConto;
    cout << "Hai scelto di creare un nuovo conto" << endl;
    cout << "Scegli un nome da affidare al conto:" << endl;
    getline(std::cin, nomeConto);
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
    bool loop = true;
    while (loop) {
        cout << "Selezionare il conto in cui fare transazioni:";
        int numeroConto = controlloInputConto();
        stampaScelte();
        std::string input;
        int scelta;
        getline(cin, input);
        std::istringstream iss(input);
        if (iss >> scelta) {
            switch (scelta) {
                case 1: {
                    cout << "immetere la quantità di denaro da depositare sul conto: " << endl;
                    int quant = controlloInputQuant();
                    string causale;
                    cout << "scrivere eventuali motivazioni della transazione: " << endl;
                    getline(std::cin, causale);

                    utente->deposita(numeroConto, quant, causale);
                    break;
                }
                case 2: {
                    cout << "immettere la quantità di denaro da ritirare dal conto: " << endl;
                    int quant = controlloInputQuant();
                    string causale;
                    cout << "scrivere eventuali motivazioni della transazione: " << endl;
                    getline(std::cin, causale);
                    utente->ritira(numeroConto, quant, causale);
                    break;
                }
                case 3: {
                    cout << utente->getNumeroConti() << endl;
                    if (utente->getNumeroConti() > 1) {
                        cout << "selezionare a quale conto trasferire il denaro: " << endl;
                        int destinazione = numeroConto;
                        while (destinazione == numeroConto) {
                            destinazione = controlloInputConto();
                        }
                        cout << "immettere la quantita' di denaro da trasferire al secondo conto: " << endl;
                        int quant = controlloInputQuant();
                        string causale;
                        cout << "scrivere eventuali motivazioni della transazione: " << endl;
                        getline(std::cin, causale);
                        utente->trasferisci(numeroConto, destinazione, quant, causale);
                        break;
                    } else {
                        cout
                                << "Non sei in possesso di piu' di due conti, quindi non e' possibile effettuare alcun trasferimento, siamo spiacenti."
                                << endl;
                        cout << "Torna appena avrai creato un nuovo conto" << endl;
                        break;
                    }
                }
                case 4: {
                    cout << "Stai per creare un nuovo conto: " << endl;
                    creareConto();
                    break;
                }
                case 5: {
                    utente->salvaInformazioniUtente();
                    utente->leggiInfoUtente();
                    break;
                }
                case 6: {
                    loop = false;
                    cout << "Arrivederci." << endl;
                    break;
                }
            }


        } else {
            cout << "Sono accettati solo numeri!!!" << endl;
            std::cin.clear();
        }
    }
}

string Interfaccia::controlloInputStringhe(int numeroMinimoCaratteri, int numeroMassimoCaratteri) {
    string input = "default";
    try {
        getline(std::cin, input);
        if (input.length() > numeroMassimoCaratteri or input.length() < numeroMinimoCaratteri)
            throw out_of_range("string inserita non valida");
        return input;
    }
    catch (const out_of_range &e) {
        cerr << e.what() << endl;
        return "NO";
    }

}

DataDiNascita Interfaccia::controlloInputData() {
    DataDiNascita input(-1, "-1", -1);
    while (true) {
        cout << "anno: " << endl;
        input.anno = controlloInputQuant();
        if (input.anno < 0 || input.anno > 2099) {
            cout << "Hai inserito una data non valida, riprova!" << endl;
            cin.clear();
        } else
            break;
    }
    bool loop = true;
    while (loop) {
        cout << "mese: " << endl;
        input.mese = controlloInputStringhe(0, 30);
        for (const auto &a: mesiValidi) {
            if (input.mese == a) {
                loop = false;
            }
        }
        cin.clear();
    }

    while (true) {
        cout << "giorno: " << endl;
        input.giorno = controlloInputQuant();
        if (input.mese == "settembre" || input.mese == "novembre" || input.mese == "aprile" || input.mese == "giugno") {
            if (input.giorno < 0 or input.giorno > 30) {
                cout << "Data non valida, riprova!" << endl;
                cin.clear();
            } else break;
        } else if (input.mese == "febbraio") {
            if (input.giorno < 0 or input.giorno > 28) {
                cout << "Data non valida, riprova!" << endl;
                cin.clear();
            } else break;
        } else {
            if (input.giorno < 0 or input.giorno > 31) {
                cout << "Data non valida, riprovare!" << endl;
                cin.clear();
            } else break;
        }
    }


    return input;
}

int Interfaccia::controlloInputConto() {
    while (true) {
        int controllo;
        string input;
        getline(cin, input);
        std::istringstream iss(input);
        if (iss >> controllo) {
            if (utente->getConto(controllo))
                return controllo;
            else {
                cout << "Il conto da lei selezionato non esiste!" << endl;
                std::cin.clear();
            }
        } else {
            cout << "Sono accettati solo numeri!!!" << endl;
            std::cin.clear();
        }
    }

}

int Interfaccia::controlloInputQuant() {
    while (true) {
        int controllo;
        string input;
        getline(cin, input);
        std::istringstream iss(input);
        if (iss >> controllo and controllo > 0) {
            return controllo;
        } else {
            cout << "Sono accettati unicamente numeri (e positivi)" << endl;
            cin.clear();
        }
    }
}


