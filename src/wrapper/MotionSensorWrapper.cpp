#include <node.h>
#include "MotionSensorWrapper.h"

using namespace v8;

Persistent<Function> MotionSensorWrapper::constructor;

MotionSensorWrapper::MotionSensorWrapper(uint8_t _header){
  motion = new MotionSensor(_header);
}

MotionSensorWrapper::~MotionSensorWrapper(){
}

void MotionSensorWrapper::release(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  MotionSensorWrapper* temp_obj = ObjectWrap::Unwrap<MotionSensorWrapper>(args.Holder());
  temp_obj->motion->release();
  delete temp_obj->motion;
}


void MotionSensorWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"MotionSensorWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"getValue",getValue);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);

  constructor.Reset(isolate,tpl->GetFunction());
}

void MotionSensorWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _header = 0x01;
  MotionSensorWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    if(_argc == 1){
      _header = (uint8_t) args[0]->NumberValue();
      obj = new MotionSensorWrapper(_header);
      obj->Wrap(args.This());
      args.GetReturnValue().Set(args.This());
    }else{
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments...")));
      return;
    }
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    if(_argc != 1){
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments...")));
      return;
    }
    Local<Value>* argv = new Local<Value>[_argc];
    for(uint8_t i = 0; i < _argc; i++){
      argv[i] = args[i];
    }
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(_argc, argv));
  }
}

void MotionSensorWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  if(_argc != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
    return;
  }
  Handle<Value>* argv = new Handle<Value>[_argc];
  for(uint8_t i = 0; i < _argc; i++){
    argv[i] = args[i];
  }
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance(_argc, argv);

  args.GetReturnValue().Set(instance);
}

void MotionSensorWrapper::getValue(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  MotionSensorWrapper* temp_obj = ObjectWrap::Unwrap<MotionSensorWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->motion->getValue()));
}
