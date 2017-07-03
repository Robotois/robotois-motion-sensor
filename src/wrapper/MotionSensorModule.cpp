#include <node.h>
#include "MotionSensorWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  MotionSensorWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  MotionSensorWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(MotionSensorModule, InitAll)
