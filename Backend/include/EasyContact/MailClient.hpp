/**
 * RCOS-EasyContact
 * EasyContact/Backend/include/EasyContact
 * MailClient.hpp
 * Copyright [2021] <RCOS-EasyContact>
 */
#ifndef BACKEND_INCLUDE_EASYCONTACT_MAILCLIENT_HPP_
#define BACKEND_INCLUDE_EASYCONTACT_MAILCLIENT_HPP_
// Resolve Conflict with LibBoost
#ifdef defer
#undef defer
#endif
// C++ Standard Library
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
// Standard Template Library
#include <list>
#include <utility>
// MailIO Header Files
#include <mailio/imap.hpp>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
// EasyContact Header Files
#include <EasyContact/SysLogs.hpp>
namespace BMC {
bool AuthenticateLogin(const std::string& RCSID, const std::string& Password);
class MailClient {
 private:
  const std::string RCSID;
  const std::string Password;
  const std::string EmailAddress;
  mutable std::string Nickname;

 protected:
  [[nodiscard]] size_t InboxEmails() const;
  [[nodiscard]] bool RecvEmail(const size_t& ID, mailio::message* M) const;
  [[nodiscard]] bool RemoveEmail(const size_t& ID);

 public:
  explicit MailClient(const std::string& _RCSID, const std::string& _Password);
  void ChangeNickname(const std::string& _Nickname) noexcept;
  bool Fetch(const size_t& NumEmails) const;
  bool SendMessage(const std::string& Recipient_Name,
                   const std::string& Recipient_Email,
                   const std::string& Subject,
                   const std::string& MessageBody) const;
};
}  // namespace BMC
#endif  // BACKEND_INCLUDE_EASYCONTACT_MAILCLIENT_HPP_
