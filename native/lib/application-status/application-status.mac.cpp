
#include "application-status.mac.hpp"

void MacApplicationStatus::ListenForStatus(Napi::Env &env, Napi::ThreadSafeFunction &&callback) {
  PlatformNativeApplicationStatus::ListenForStatus(env, std::move(callback));
	// TODO: platform specific initialization
}

void MacApplicationStatus::StopListener() {
	// TODO: platform specific teardown
	PlatformNativeApplicationStatus::StopListener();
}