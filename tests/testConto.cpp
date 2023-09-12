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

TEST_F(testingConto, testDepositoInvalido) {
    c->depositare(-100, "test deposito");
    ASSERT_EQ(0, c->getSaldo());
}

TEST_F(testingConto, testRitiroValido) {
    c->depositare(100, "test deposito");
    c->ritirare(100, "test ritiro");
    ASSERT_EQ(0, c->getSaldo());
}

TEST_F(testingConto, testRitiroInvalido) {
    c->depositare(100, "test deposito");
    c->ritirare(101, "test ritiro");
    ASSERT_EQ(100, c->getSaldo());
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