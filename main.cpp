#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Interfaccia.h"

int main() {
    // con l'interfaccia diamo la possibilità all'utente di svolgere qualsivoglia operazione
    /*
    Interfaccia i;
    i.selezionareAzioni();


     * area di testing
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
     */

    Conto c("uno", 10);
    c.depositare(20, "sis");
    c.ritirare(10, "sis");
    c.depositare(100, "test ricerca per data");
    c.depositare(101, " ");
    c.aggiungiTransazioneDiVecchiaData(Transazione(10, "20241010", make_pair(13, 50), "prova", "ritiro"));
    vector<Transazione> v = c.cercaPerData("20241110");
    cout << c.getNumeroTransazioni() << endl;
}
