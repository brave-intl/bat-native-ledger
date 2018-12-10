// /* This Source Code Form is subject to the terms of the Mozilla Public
//  * License, v. 2.0. If a copy of the MPL was not distributed with this
//  * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "ledger_client_mock.h"

namespace ledger {

MockLogStreamImpl::MockLogStreamImpl(
    const char* file,
    int line,
    const LogLevel log_level) {
  std::string level;

  switch (log_level) {
    case LogLevel::LOG_ERROR: {
      level = "ERROR";
      break;
    }
    case LogLevel::LOG_WARNING: {
      level = "WARNING";
      break;
    }
    case LogLevel::LOG_INFO: {
      level = "INFO";
      break;
    }
    case LogLevel::LOG_DEBUG: {
      level = "DEBUG";
      break;
    }
    case LogLevel::LOG_REQUEST: {
      level = "REQUEST";
      break;
    }
    case LogLevel::LOG_RESPONSE: {
      level = "RESPONSE";
      break;
    }
  }

  log_message_ = level + ": in " + file + " on line "
    + std::to_string(line) + ": ";
}

std::ostream& MockLogStreamImpl::stream() {
  std::cout << std::endl << log_message_;
  return std::cout;
}

MockLedgerClient::MockLedgerClient() {};

MockLedgerClient::~MockLedgerClient() {};

std::unique_ptr<LogStream> MockLedgerClient::Log(
    const char* file,
    int line,
    const LogLevel log_level) const {
  return std::make_unique<MockLogStreamImpl>(file, line, log_level);
}

}  // namespace ledger
