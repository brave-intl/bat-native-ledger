/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_LEDGER_MOCK_LEDGER_CLIENT_
#define BAT_LEDGER_MOCK_LEDGER_CLIENT_

#include "bat/ledger/ledger_client.h"
#include "bat/ledger/ledger.h"

namespace ledger {
class Ledger;
class LedgerCallbackHandler;
}

namespace bat_ledger {

class MockLedgerClient : public ledger::LedgerClient {
 public:
  MockLedgerClient();
  ~MockLedgerClient() override;

  std::unique_ptr<ledger::Ledger> ledger_;

 protected:
  // ledger::LedgerClient
  std::string GenerateGUID() const override;
  void OnWalletInitialized(
      ledger::Result result) override;
  void FetchWalletProperties() override;
  void OnWalletProperties(
      ledger::Result result,
      std::unique_ptr<ledger::WalletInfo>) override;
  void OnReconcileComplete(
      ledger::Result result,
      const std::string& viewing_id,
      ledger::PUBLISHER_CATEGORY category,
      const std::string& probi) override;

  void LoadLedgerState(
      ledger::LedgerCallbackHandler* handler) override;
  void SaveLedgerState(
      const std::string& ledger_state,
      ledger::LedgerCallbackHandler* handler) override;

  void LoadPublisherState(
      ledger::LedgerCallbackHandler* handler) override;
  void SavePublisherState(
      const std::string& publisher_state,
      ledger::LedgerCallbackHandler* handler) override;

  void SavePublishersList(
      const std::string& publisher_state,
      ledger::LedgerCallbackHandler* handler) override;
  void LoadPublisherList(
      ledger::LedgerCallbackHandler* handler) override;

  void LoadNicewareList(
      ledger::GetNicewareListCallback callback) override;

  void SavePublisherInfo(
      std::unique_ptr<ledger::PublisherInfo> publisher_info,
      ledger::PublisherInfoCallback callback) override;
  void LoadPublisherInfo(
      ledger::PublisherInfoFilter filter,
      ledger::PublisherInfoCallback callback) override;
  void LoadMediaPublisherInfo(
      const std::string& media_key,
      ledger::PublisherInfoCallback callback) override;
  void SaveMediaPublisherInfo(
      const std::string& media_key,
      const std::string& publisher_id) override;
  void LoadPublisherInfoList(
      uint32_t start,
      uint32_t limit,
      ledger::PublisherInfoFilter filter,
      ledger::PublisherInfoListCallback callback) override;
  void LoadCurrentPublisherInfoList(
      uint32_t start, uint32_t limit,
      ledger::PublisherInfoFilter filter,
      ledger::PublisherInfoListCallback callback) override;

  void FetchGrant(
      const std::string& lang,
      const std::string& paymentId) override;
  void OnGrant(
      ledger::Result result,
      const ledger::Grant& grant) override;
  void GetGrantCaptcha() override;
  void OnGrantCaptcha(
      const std::string& image,
      const std::string& hint) override;
  void OnRecoverWallet(
      ledger::Result result,
      double balance,
      const std::vector<ledger::Grant>& grants) override;
  void OnGrantFinish(
      ledger::Result result,
      const ledger::Grant& grant) override;
  void OnPublisherActivity(
      ledger::Result result,
      std::unique_ptr<ledger::PublisherInfo>,
      uint64_t windowId) override;
  void OnExcludedSitesChanged() override;
  void FetchFavIcon(
      const std::string& url,
      const std::string& favicon_key,
      ledger::FetchIconCallback callback) override;
  void SaveContributionInfo(
      const std::string& probi,
      const int month,
      const int year,
      const uint32_t date,
      const std::string& publisher_key,
      const ledger::PUBLISHER_CATEGORY category) override;
  void GetRecurringDonations(
      ledger::PublisherInfoListCallback callback) override;
  void OnRemoveRecurring(
      const std::string& publisher_key,
      ledger::RecurringRemoveCallback callback) override;

  void SetTimer(
      uint64_t time_offset,
      uint32_t & timer_id) override;

  std::string URIEncode(
      const std::string& value) override;

  std::unique_ptr<ledger::LedgerURLLoader> LoadURL(
      const std::string& url,
      const std::vector<std::string>& headers,
      const std::string& content,
      const std::string& contentType,
      const ledger::URL_METHOD& method,
      ledger::LedgerCallbackHandler* handler) override;
  // RunIOTask is a temporary workarounds for some IO tasks
  void RunIOTask(
      std::unique_ptr<ledger::LedgerTaskRunner> task) override;
  void SetContributionAutoInclude(
      std::string publisher_key,
      bool excluded,
      uint64_t windowId) override;

  // Logs debug information
  std::unique_ptr<ledger::LogStream> Log(
      const char* file,
      int line,
      const ledger::LogLevel log_level) const override;
};

}  // namespace bat_ledger

#endif  // BAT_LEDGER_MOCK_LEDGER_CLIENT_
