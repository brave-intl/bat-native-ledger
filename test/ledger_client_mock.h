/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include <iostream>

#include "testing/gmock/include/gmock/gmock.h"

#include "bat/ledger/ledger_client.h"
#include "bat/ledger/ledger.h"

namespace ledger {

class MockLogStreamImpl : public LogStream {
 public:
  MockLogStreamImpl(const char* file, int line, const LogLevel log_level);
  std::ostream& stream() override;

 private:
  std::string log_message_;

  // Not copyable, not assignable
  MockLogStreamImpl(const MockLogStreamImpl&) = delete;
  MockLogStreamImpl& operator=(const MockLogStreamImpl&) = delete;
};

class MockLedgerClient : public LedgerClient {
 public:
  MockLedgerClient();
  ~MockLedgerClient() override;

  MOCK_CONST_METHOD0(GenerateGUID, std::string());

  MOCK_METHOD1(OnWalletInitialized, void(
      Result result));

  MOCK_METHOD0(FetchWalletProperties, void());

  MOCK_METHOD2(OnWalletProperties, void(
      Result result,
      std::unique_ptr<WalletInfo>));

  MOCK_METHOD4(OnReconcileComplete, void(
      Result result,
      const std::string& viewing_id,
      PUBLISHER_CATEGORY category,
      const std::string& probi));

  MOCK_METHOD1(LoadLedgerState, void(
      LedgerCallbackHandler* handler));

  MOCK_METHOD2(SaveLedgerState, void(
      const std::string& ledger_state,
      LedgerCallbackHandler* handler));

  MOCK_METHOD1(LoadPublisherState, void(
      LedgerCallbackHandler* handler));

  MOCK_METHOD2(SavePublisherState, void(
      const std::string& publisher_state,
      LedgerCallbackHandler* handler));

  MOCK_METHOD2(SavePublishersList, void(
      const std::string& publisher_state,
      LedgerCallbackHandler* handler));

  MOCK_METHOD1(LoadPublisherList, void(
      LedgerCallbackHandler* handler));

  MOCK_METHOD1(LoadNicewareList, void(
      GetNicewareListCallback callback));

  MOCK_METHOD2(SavePublisherInfo, void(
      std::unique_ptr<PublisherInfo> publisher_info,
      PublisherInfoCallback callback));

  MOCK_METHOD2(LoadPublisherInfo, void(
      PublisherInfoFilter filter,
      PublisherInfoCallback callback));

  MOCK_METHOD2(LoadMediaPublisherInfo, void(
      const std::string& media_key,
      PublisherInfoCallback callback));

  MOCK_METHOD2(SaveMediaPublisherInfo, void(
      const std::string& media_key,
      const std::string& publisher_id));

  MOCK_METHOD4(LoadPublisherInfoList, void(
      uint32_t start,
      uint32_t limit,
      PublisherInfoFilter filter,
      PublisherInfoListCallback callback));

  MOCK_METHOD4(LoadCurrentPublisherInfoList, void(
      uint32_t start,
      uint32_t limit,
      PublisherInfoFilter filter,
      PublisherInfoListCallback callback));

  MOCK_METHOD2(FetchGrant, void(
      const std::string& lang,
      const std::string& paymentId));

  MOCK_METHOD2(OnGrant, void(
      Result result,
      const Grant& grant));

  MOCK_METHOD0(GetGrantCaptcha, void());

  MOCK_METHOD2(OnGrantCaptcha, void(
      const std::string& image,
      const std::string& hint));

  MOCK_METHOD3(OnRecoverWallet, void(
      Result result,
      double balance,
      const std::vector<Grant>& grants));

  MOCK_METHOD2(OnGrantFinish, void(
      Result result,
      const Grant& grant));

  MOCK_METHOD3(OnPublisherActivity, void(
      Result result,
      std::unique_ptr<PublisherInfo>,
      uint64_t windowId));

  MOCK_METHOD0(OnExcludedSitesChanged, void());

  MOCK_METHOD3(FetchFavIcon, void(
      const std::string& url,
      const std::string& favicon_key,
      FetchIconCallback callback));

  MOCK_METHOD6(SaveContributionInfo, void(
      const std::string& probi,
      const int month,
      const int year,
      const uint32_t date,
      const std::string& publisher_key,
      const PUBLISHER_CATEGORY category));

  MOCK_METHOD1(GetRecurringDonations, void(
      PublisherInfoListCallback callback));

  MOCK_METHOD2(OnRemoveRecurring, void(
      const std::string& publisher_key,
      RecurringRemoveCallback callback));

  MOCK_METHOD2(SetTimer, void(
      uint64_t time_offset,
      uint32_t & timer_id));

  MOCK_METHOD1(URIEncode, std::string(
      const std::string& value));

  MOCK_METHOD6(LoadURL, std::unique_ptr<LedgerURLLoader>(
      const std::string& url,
      const std::vector<std::string>& headers,
      const std::string& content,
      const std::string& contentType,
      const URL_METHOD& method,
      LedgerCallbackHandler* handler));

  MOCK_METHOD1(RunIOTask, void(
      std::unique_ptr<LedgerTaskRunner> task));

  MOCK_METHOD3(SetContributionAutoInclude, void(
      std::string publisher_key,
      bool excluded,
      uint64_t windowId));

  std::unique_ptr<LogStream> Log(
      const char* file,
      int line,
      const LogLevel log_level) const;
};

}  // namespace ledger
