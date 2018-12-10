/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "ledger_client_mock.h"
#include "brave/vendor/bat-native-ledger/src/ledger_impl.h"

// npm run test -- brave_unit_tests --filter=LedgerTest.*

namespace bat_ledger {

class LedgerTest : public ::testing::Test {
 protected:
  ledger::MockLedgerClient *mock_ledger_client;
  LedgerImpl* ledger;

  LedgerTest() :
      mock_ledger_client(new ledger::MockLedgerClient()),
      ledger(new LedgerImpl(mock_ledger_client)) {
    // You can do set-up work for each test here
  }

  ~LedgerTest() override {
    // You can do clean-up work that doesn't throw exceptions here
    delete ledger;
    delete mock_ledger_client;
  }

  // If the constructor and destructor are not enough for setting up and
  // cleaning up each test, you can use the following methods

  void SetUp() override {
    // Code here will be called immediately after the constructor (right before
    // each test)
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right before the
    // destructor)
  }

  // Objects declared here can be used by all tests in the test case
};

TEST_F(LedgerTest, ValidTest) {
  EXPECT_TRUE(true);
}

}  // namespace bat_ledger
