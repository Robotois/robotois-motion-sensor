#ifndef MOTIONSENSORWRAPPER_H
#define MOTIONSENSORWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../MotionSensor.h"

class MotionSensorWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit MotionSensorWrapper(uint8_t _header);
  ~MotionSensorWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getValue(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  MotionSensor *motion;
};

#endif
