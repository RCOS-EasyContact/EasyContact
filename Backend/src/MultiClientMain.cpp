/**
 * RCOS-EasyContact
 * EasyContact/Backend/src
 * MultiClientMain.cpp
 * Copyright [2021] <RCOS-EasyContact>
 */
#ifndef BACKEND_SRC_MULTICLIENTMAIN_CPP_
#define BACKEND_SRC_MULTICLIENTMAIN_CPP_
// C Standard Library
#include <signal.h>
#include <stdlib.h>
#include <time.h>
// Libhv Library (C Library)
#include <hv/HttpServer.h>
#include <hv/hv.h>
// C++ Standard Library
#include <iostream>
#include <mutex>
#include <thread>
// Standard Template Library
#include <queue>
#include <unordered_map>
#include <utility>
// EasyContact Header Files
#include <EasyContact/DispatchQueue.hpp>
#include <EasyContact/GlobalMutex.hpp>
#include <EasyContact/HTTPRouter.hpp>
#include <EasyContact/SingleUser.hpp>
#include <EasyContact/SysLogs.hpp>
// Project Defines
#define LISTEN_PORT 3126
// Global Representation
std::unordered_map<std::string, SingleUser> g_ActiveUsers;
DispatchQueue g_DispatchQueue(2);
http_server_t g_Http_Server;
HttpService g_Http_Service;
void Reg_HTTPServer() {
  try {
    g_Http_Server.port = LISTEN_PORT;
    g_Http_Service.base_url = "";
    HTTPRouter::register_router(&g_Http_Service);
    g_Http_Server.service = &g_Http_Service;
    http_server_run(&g_Http_Server, 0);
  } catch (std::exception& Err) {
    SYSLOG::PrintException(Err);
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  // Generate Random Seed
  srand(time(0));
  // Start HTTP Server
  Reg_HTTPServer();
  // Wait
  while (true) {
    pause();
  }
}
#endif  // BACKEND_SRC_MULTICLIENTMAIN_CPP_
