/**
 * RCOS-EasyContact
 * EasyContact/Backend/include/EasyContact
 * HTTPRouter.hpp
 * Copyright [2021] <RCOS-EasyContact>
 */
#ifndef BACKEND_INCLUDE_EASYCONTACT_HTTPROUTER_HPP_
#define BACKEND_INCLUDE_EASYCONTACT_HTTPROUTER_HPP_
// Libhv Library (C Library)
#include <hv/HttpService.h>
// C++ Standard Library
#include <string>
// Standard Template Library
#include <unordered_map>
#include <utility>
#include <vector>
// EasyContact Header Files
#include <EasyContact/DispatchQueue.hpp>
#include <EasyContact/SingleUser.hpp>
#include <EasyContact/SysLogs.hpp>
#include <EasyContact/UserToken.hpp>
// Global Representation
extern std::unordered_map<std::string, SingleUser> g_ActiveUsers;
extern DispatchQueue g_DispatchQueue;
class HTTPRouter {
 public:
  static int pre(HttpRequest *req, HttpResponse *resp) {
    resp->headers["Access-Control-Allow-Origin"] = "*";
    if (req->method == HTTP_OPTIONS) {
      resp->headers["Access-Control-Allow-Origin"] =
          req->GetHeader("Origin", "*");
      resp->headers["Access-Control-Allow-Methods"] =
          req->GetHeader("Access-Control-Request-Method",
                         "OPTIONS, HEAD, GET, POST, PUT, DELETE, PATCH");
      resp->headers["Access-Control-Allow-Headers"] =
          req->GetHeader("Access-Control-Request-Headers", "Content-Type");
      return HTTP_STATUS_NO_CONTENT;
    }
    resp->content_type = APPLICATION_JSON;
    // std::cout << req->Dump(1, 1).c_str() << std::endl<<std::flush;
    req->ParseBody();
    return 0;
  }
  static int post(HttpRequest *req, HttpResponse *resp) { return 0; }
  static void register_router(HttpService *router) {
    router->preprocessor = pre;
    router->postprocessor = post;
    // Attempt Sign In To RPI's Email Server
    router->POST("/Login", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("POST->", "/Login");
      try {
        const std::string &RCSID = req->json["RCSID"];
        const std::string &Password = req->json["Password"];
        if (BMC::AuthenticateLogin(RCSID, Password) == true) {
          const std::string Token = AUT::GenerateToken();
          g_ActiveUsers.insert(std::pair<std::string, SingleUser>(
              Token, SingleUser(RCSID, Password)));
          resp->json["Token"] = Token;
          return 200;  // OK
        } else {
          return 511;  // Network Authentication Required
        }
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Retrieve All Contact Names
    router->GET("/Contacts/AllNames", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("GET->", "/Contacts/AllNames");
      try {
        const std::string &Token = req->json["Token"];
        const std::unordered_map<std::string, SingleUser>::const_iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        const std::vector<std::string> &AllNames = User->second.getAllNames();
        for (const std::string &i : AllNames) {
          resp->json.push_back(i);
        }
        return 200;  // OK
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Retrieve All Tags
    router->GET("/Contacts/AllTags", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("GET->", "/Contacts/AllTags");
      try {
        const std::string &Token = req->json["Token"];
        const std::unordered_map<std::string, SingleUser>::const_iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        const std::vector<std::string> &TagContains = User->second.getAllTags();
        for (const std::string &i : TagContains) {
          resp->json.push_back(i);
        }
        return 200;  // OK
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Retrieve All Contacts Within One Tag
    router->GET("/Contacts/TagContains", [](HttpRequest *req,
                                            HttpResponse *resp) {
      SYSLOG::PrintRequest("GET->", "/Contacts/TagContains");
      try {
        const std::string &Token = req->json["Token"];
        const std::string &Name = req->json["Name"];
        const std::unordered_map<std::string, SingleUser>::const_iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        const std::vector<std::string> &AllTags =
            User->second.getTagContains(Name);
        for (const std::string &i : AllTags) {
          resp->json.push_back(i);
        }
        return 200;  // OK
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Retrieve Email Address For One Contact
    router->GET("/Contacts/Email", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("GET->", "/Contacts/Email");
      try {
        const std::string &Token = req->json["Token"];
        const std::string &Name = req->json["Name"];
        const std::unordered_map<std::string, SingleUser>::const_iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        const std::string &EmailAddress = User->second.getEmailAddress(Name);
        resp->json.push_back(EmailAddress);
        return 200;  // OK
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Create New Contact
    router->POST("/Contacts/New", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("POST->", "/Contacts/New");
      try {
        const std::string &Token = req->json["Token"];
        const std::string &Name = req->json["Name"];
        const std::string &Email = req->json["Email"];
        const std::unordered_map<std::string, SingleUser>::iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        if (User->second.newContact(Name, Email) == true) {
          return 200;  // OK
        } else {
          return 409;  // Conflict
        }
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Create New Tag
    router->POST("/Contacts/Tag", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("POST->", "/Contacts/Tag");
      try {
        const std::string &Token = req->json["Token"];
        const std::string &TagName = req->json["TagName"];
        const std::unordered_map<std::string, SingleUser>::iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        if (User->second.newTag(TagName) == true) {
          return 200;  // OK
        } else {
          return 409;  // Conflict
        }
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Assign Tag to One Existing Contact
    router->PUT("/Contacts/Assign", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("PUT->", "/Contacts/Assign");
      try {
        const std::string &Token = req->json["Token"];
        const std::string &TagName = req->json["TagName"];
        const std::string &Name = req->json["Name"];
        const std::unordered_map<std::string, SingleUser>::iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        if (User->second.assignTagTo(TagName, Name) == true) {
          return 200;  // OK
        } else {
          return 409;  // Conflict
        }
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Download Lastest X Emails
    router->PUT("/Email/Fetch/:Num", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("PUT->", "/Email/Fetch/:Num");
      try {
        const std::string &Token = req->json["Token"];
        const size_t Num = std::move(stol(req->GetParam("Num")));
        const std::unordered_map<std::string, SingleUser>::const_iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        const SingleUser &S = User->second;
        g_DispatchQueue.Dispatch([S, Num]() { S.Fetch(Num); });
        return 202;  // Accepted
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Send Email
    router->POST("/Email/SendToName", [](HttpRequest *req, HttpResponse *resp) {
      SYSLOG::PrintRequest("POST->", "/Email/SendToName");
      try {
        const std::string &Token = req->json["Token"];
        const std::string &Reciever = req->json["Reciever"];
        const std::string &Subject = req->json["Subject"];
        const std::string &Message = req->json["Message"];
        const std::unordered_map<std::string, SingleUser>::const_iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        const std::string &RecieverEmail =
            User->second.getEmailAddress(Reciever);
        if (RecieverEmail.empty()) {
          return 412;  // Precondition Failed
        }
        User->second.SendMessage(Reciever, RecieverEmail, Subject, Message);
        return 200;  // Accept
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Send Email
    router->POST("/Email/SendToAddress", [](HttpRequest *req,
                                            HttpResponse *resp) {
      SYSLOG::PrintRequest("POST->", "/Email/SendToAddress");
      try {
        const std::string &Token = req->json["Token"];
        const std::string &Reciever = req->json["Reciever"];
        const std::string &Email = req->json["Email"];
        const std::string &Subject = req->json["Subject"];
        const std::string &Message = req->json["Message"];
        const std::unordered_map<std::string, SingleUser>::const_iterator User =
            g_ActiveUsers.find(Token);
        // Verify User Is Current Active
        if (User == g_ActiveUsers.end()) {
          return 401;  // Unauthorized
        }
        User->second.SendMessage(Reciever, Email, Subject, Message);
        return 200;  // Accept
      } catch (const std::exception &Err) {
        SYSLOG::PrintException(Err);
      }
      return 500;  // Internal Server Error
    });
    // Remove Tag For One Existing Contact
    router->Delete(
        "/Contacts/Unassign", [](HttpRequest *req, HttpResponse *resp) {
          SYSLOG::PrintRequest("Delete->", "/Contacts/Unassign");
          try {
            const std::string &Token = req->json["Token"];
            const std::string &TagName = req->json["TagName"];
            const std::string &Name = req->json["Name"];
            const std::unordered_map<std::string, SingleUser>::iterator User =
                g_ActiveUsers.find(Token);
            // Verify User Is Current Active
            if (User == g_ActiveUsers.end()) {
              return 401;  // Unauthorized
            }
            if (User->second.removeTagFor(TagName, Name) == true) {
              return 200;  // OK
            } else {
              return 409;  // Conflict
            }
          } catch (const std::exception &Err) {
            SYSLOG::PrintException(Err);
          }
          return 500;  // Internal Server Error
        });
    // Remove Existing Contact
    router->Delete(
        "/Contacts/Remove", [](HttpRequest *req, HttpResponse *resp) {
          SYSLOG::PrintRequest("Delete->", "/Contacts/Remove");
          try {
            const std::string &Token = req->json["Token"];
            const std::string &Name = req->json["Name"];
            const std::unordered_map<std::string, SingleUser>::iterator User =
                g_ActiveUsers.find(Token);
            // Verify User Is Current Active
            if (User == g_ActiveUsers.end()) {
              return 401;  // Unauthorized
            }
            if (User->second.removeContact(Name) == true) {
              return 200;  // OK
            } else {
              return 409;  // Conflict
            }
          } catch (const std::exception &Err) {
            SYSLOG::PrintException(Err);
          }
          return 500;  // Internal Server Error
        });
    // Remove Existing Tag
    router->Delete(
        "/Contacts/RemoveTag", [](HttpRequest *req, HttpResponse *resp) {
          SYSLOG::PrintRequest("Delete->", "/Contacts/RemoveTag");
          try {
            const std::string &Token = req->json["Token"];
            const std::string &TagName = req->json["TagName"];
            const std::unordered_map<std::string, SingleUser>::iterator User =
                g_ActiveUsers.find(Token);
            // Verify User Is Current Active
            if (User == g_ActiveUsers.end()) {
              return 401;  // Unauthorized
            }
            if (User->second.removeTag(TagName) == true) {
              return 200;  // OK
            } else {
              return 409;  // Conflict
            }
          } catch (const std::exception &Err) {
            SYSLOG::PrintException(Err);
          }
          return 500;  // Internal Server Error
        });
  }
};
#endif  // BACKEND_INCLUDE_EASYCONTACT_HTTPROUTER_HPP_
