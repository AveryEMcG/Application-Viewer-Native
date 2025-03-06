#ifndef MAC_APPLICATION_STATUS_HPP
#define MAC_APPLICATION_STATUS_HPP

#include "application-status.hpp"

class MacApplicationStatus: PlatformNativeApplicationStatus {
  MacApplicationStatus() {}
  void ListenForStatus(Napi::Env &env, Napi::ThreadSafeFunction &&callback) final;
  void StopListener() final;
};


#endif // MAC_APPLICATION_STATUS_HPP