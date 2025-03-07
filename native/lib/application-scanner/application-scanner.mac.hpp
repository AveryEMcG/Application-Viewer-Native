#ifndef MAC_APPLICATION_SCANNER_HPP
#define MAC_APPLICATION_SCANNER_HPP

#include "application-scanner.hpp"

class MacApplicationScanner: PlatformNativeApplicationScanner {
  MacApplicationScanner() {}
  void ListenForApplications(Napi::Env &env, Napi::ThreadSafeFunction &&callback) final;
  void StopListener() final;
};


#endif // MAC_APPLICATION_SCANNER_HPP