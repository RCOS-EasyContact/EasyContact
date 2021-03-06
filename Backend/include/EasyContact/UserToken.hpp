/**
 * RCOS-EasyContact
 * EasyContact/Backend/include/EasyContact
 * UserToken.hpp
 * Copyright [2021] <RCOS-EasyContact>
 */
#ifndef BACKEND_INCLUDE_EASYCONTACT_USERTOKEN_HPP_
#define BACKEND_INCLUDE_EASYCONTACT_USERTOKEN_HPP_
// C Standard Library
#include <unistd.h>
// C++ Standard Library
#include <ctime>
#include <string>
namespace AUT {
[[nodiscard]] inline static std::string GenerateToken() noexcept {
  static const size_t Length = 1024;
  static const char AlphaNum[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
  std::string Result;
  Result.reserve(Length);
  for (size_t i = 0; i < Length; ++i) {
    Result += AlphaNum[rand() % (sizeof(AlphaNum) - 1)];
  }
  return Result;
}
}  // namespace AUT
#endif  // BACKEND_INCLUDE_EASYCONTACT_USERTOKEN_HPP_
