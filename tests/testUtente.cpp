//
// Created by tommy on 12/09/2023.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Utente.h"

using testing::Eq;
using namespace std;

class testingUtente : public ::testing::Test {
public:
    unique_ptr<Utente> ut;
    DataDiNascita data;

    testingUtente() {
        ut = nullptr;
    }

    void SetUp() override {
        data.giorno = 10;
        data.mese = "Dicembre";
        data.anno = 1000;
        ut = make_unique<Utente>("Nome", " Cognome", data);
    }


};

TEST_F(testingUtente, testCreazioneConto) {
    ut->creaConto("test");
    ASSERT_EQ(1, ut->getNumeroConti());
}

TEST_F(testingUtente, testDepositoValido) {
    ut->creaConto("test");
    ut->deposita(0, 100, "test deposito");
    ASSERT_EQ(100, ut->getConto(0)->getSaldo());
}

TEST_F(testingUtente, testDepositoInvalido) {
    ut->creaConto("test");
    ut->deposita(0, -100, "test deposito");
    ASSERT_EQ(0, ut->getConto(0)->getSaldo());
}

TEST_F(testingUtente, testRitiroValido) {
    ut->creaConto("test");
    ut->deposita(0, 100, "test deposito");
    ut->ritira(0, 100, "test ritiro");
    ASSERT_EQ(0, ut->getConto(0)->getSaldo());
}

TEST_F(testingUtente, testRitiroInvalido) {
    ut->creaConto("test");
    ut->deposita(0, 100, "test deposito");
    ut->ritira(0, 101, "test ritiro");
    ASSERT_EQ(100, ut->getConto(0)->getSaldo());
}

TEST_F(testingUtente, testTrasferimentoValido) {
    ut->creaConto("test 1");
    ut->creaConto("test 2");
    ut->deposita(0, 100, "test deposito");
    ut->trasferisci(0, 1, 100, "trasferimento");
    ASSERT_EQ(0, ut->getConto(0)->getSaldo());
    ASSERT_EQ(100, ut->getConto(1)->getSaldo());
}

TEST_F(testingUtente, testTrasferimentoInvalido) {
    ut->creaConto("test 1");
    ut->creaConto("test 2");
    ut->deposita(0, 100, "test deposito");
    ut->trasferisci(0, 1, 101, "trasferimento");
    ASSERT_EQ(100, ut->getConto(0)->getSaldo());
    ASSERT_EQ(0, ut->getConto(1)->getSaldo());
}


