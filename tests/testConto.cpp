//
// Created by tommy on 12/09/2023.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Utente.h"

using testing::Eq;
using namespace std;

class testingConto : public ::testing::Test {
public:
    unique_ptr<Conto> c;

    testingConto() {
        c = make_unique<Conto>("testing");
    }
};

TEST_F(testingConto, testDepositoValido) {
    c->depositare(100, "test deposito");
    ASSERT_EQ(100, c->getSaldo());
}

//test modificato per il blocco try catch

TEST_F(testingConto, testDepositoInvalido) {
    ASSERT_THROW(c->depositare(-100, "test deposito"), runtime_error);
}

TEST_F(testingConto, testRitiroValido) {
    c->depositare(100, "test deposito");
    c->ritirare(100, "test ritiro");
    ASSERT_EQ(0, c->getSaldo());
}

//test modificato per il blocco try catch

TEST_F(testingConto, testRitiroInvalido) {
    c->depositare(100, "test deposito");
    ASSERT_THROW(c->ritirare(101, "test ritiro"), runtime_error);
}

TEST_F(testingConto, testTransazioniDepositate) {
    c->depositare(100, "test deposito");
    vector<Transazione> v = c->transazioniDepositate();
    ASSERT_EQ(1, v.size());
}

TEST_F(testingConto, testTransazioniRitirate) {
    c->depositare(100, "test deposito");
    c->ritirare(100, "test ritiro");
    vector<Transazione> v = c->transazioniRitirate();
    ASSERT_EQ(1, v.size());
}


//test aggiunti al conto
TEST_F(testingConto, testCercaPerData) {
    c->aggiungiTransazioneDiVecchiaData(Transazione(10, "20231010", make_pair(13, 50), "test", "ritiro"));
    c->aggiungiTransazioneDiVecchiaData(Transazione(10, "20221010", make_pair(13, 50), "test", "deposito"));
    c->aggiungiTransazioneDiVecchiaData(Transazione(10, "20241010", make_pair(13, 50), "test", "ritiro"));
    vector<Transazione> v = c->cercaPerData("20241010");
    ASSERT_EQ(1, v.size());
}

TEST_F(testingConto, testNumeroTransazioni) {
    c->depositare(100, "test deposito");
    c->ritirare(100, "test ritiro");
    ASSERT_EQ(2, c->getNumeroTransazioni());
}