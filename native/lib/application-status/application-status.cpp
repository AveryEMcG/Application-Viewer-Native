
#include "application-status.hpp"
#include <string>

#if defined(_WIN32)
  #include "application-status.windows.hpp"
#elif __APPLE__
    #include <TargetConditionals.h>
    #ifdef TARGET_OS_MAC
      #include "application-status.mac.hpp"
    #endif
#endif


NativeApplicationStatus::NativeApplicationStatus(Napi::Env env, Napi::Object exports) {
  /* Advertise to node the functions this module supports */
  DefineAddon(
    exports,
    {
      InstanceMethod("ListenForStatus", &NativeApplicationStatus::ListenForStatus, napi_enumerable),
      InstanceMethod("StopListener", &NativeApplicationStatus::StopListener, napi_enumerable),
    }
  );
}


// Create a new native module NativeApplicationStatus. Use the existing native module called
// NativeApplicationScanner as boilerplate for working with the node module API, compiling, error
// handling, etc. NativeApplictionStatus will fulfill the following requirements:
// ● NativeApplicationStatus shall expose a function called ListenForStatus that takes two
// inputs and has no outputs.
// ○ The first input shall have type { applicationName: string, windowTitle: string }
// ○ The second input shall be a callback of type ({ status: 'open' | 'hidden' | 'closed',
// dimensions?: { x, y, width, height } }) => void
// ○ If there is an error parsing the inputs to ListenForStatus, it should throw a JS
// error

void NativeApplicationStatus::ListenForStatus(const Napi::CallbackInfo& info) {
  /*
   * Parse the inputs; we don't really ensure concrete types, just the type shape
   *  throw if anything looks wrong
   */
  auto env = info.Env();
  auto length = info.Length();
  if (length != 1 || !info[0].IsFunction())
  {
    Napi::TypeError::New(env, "Expected 1 argument of callbackFn").ThrowAsJavaScriptException();
    return;
  }
  auto callback_fn = info[0].As<Napi::Function>();
  if (!callback_fn)
  {
    Napi::TypeError::New(env, "Failed to retrieve pointer of callbackFn")
        .ThrowAsJavaScriptException();
    return;
  }
  auto threadsafe_callback_fn = Napi::ThreadSafeFunction::New(
      env, callback_fn, "ContextWatcherCallback", 0, 1);
  if (!threadsafe_callback_fn)
  {
    Napi::TypeError::New(env, "Failed to cast callbackFn to threadsafe")
        .ThrowAsJavaScriptException();
    return;
  }

  /*
   * Invoke platform specific application status; throw if one is not available
   */

#if defined(_WIN32)
  WindowsApplicationStatus::instance().ListenForStatus(env, std::move(threadsafe_callback_fn));
#elif defined(TARGET_OS_MAC)
#else
  Napi::TypeError::New(env, "No PlatformNativeApplicationStatus available for this platform")
      .ThrowAsJavaScriptException();
#endif

  Napi::Function consoleLog = env.Global().Get("console").As<Napi::Object>().Get("log").As<Napi::Function>();
  consoleLog.Call({Napi::String::New(env, "Successfully started NativeApplicationStatus")});
}

void NativeApplicationStatus::StopListener(const Napi::CallbackInfo& info) {

  auto env = info.Env();

/*
 * Invoke platform specific application status; don't throw even if ones not available as the function
 *  would be idempotent
 */

#if defined(_WIN32)
#elif defined(TARGET_OS_MAC)
#endif

  Napi::Function consoleLog = env.Global().Get("console").As<Napi::Object>().Get("log").As<Napi::Function>();
  consoleLog.Call({Napi::String::New(env, "Successfully stopped NativeApplicationStatus")});
}

NODE_API_ADDON(NativeApplicationStatus)
