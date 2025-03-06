#ifndef APPLICATION_STATUS_HPP
#define APPLICATION_STATUS_HPP

#include <napi.h>

typedef struct StatusParams{ 
  std::string applicationName; 
  std::string windowTitle;
};

class PlatformNativeApplicationStatus {
  public:
    virtual ~PlatformNativeApplicationStatus() {
      StopListener();
    }
    virtual void ListenForStatus(Napi::Env &env, Napi::ThreadSafeFunction &&callback) {
      _callback = std::move(callback);
    }
    virtual void StopListener() {
      _callback = NULL;
    }
  protected:
    PlatformNativeApplicationStatus() = default;
    Napi::ThreadSafeFunction _callback = NULL;
};

class NativeApplicationStatus: public Napi::Addon<NativeApplicationStatus> {
  public:
    NativeApplicationStatus(Napi::Env env, Napi::Object exports);
  private:
    void ListenForStatus(const Napi::CallbackInfo& info);
    void StopListener(const Napi::CallbackInfo& info);
};

#endif // APPLICATION_STATUS_HPP