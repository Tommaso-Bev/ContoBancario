#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Interfaccia.h"

int main() {
    // con l'interfaccia diamo la possibilità all'utente di svolgere qualsivoglia operazione
    Interfaccia i;
    i.selezionareAzioni();

    /*
     * area di testing
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
     */
}
