#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "__template__.h"

using namespace v8;

Persistent<Function> __Template__Wrap::constructor;

// Supported implementations:
//   __Template__ ( ??? )
__Template__Wrap::__Template__Wrap(const Arguments& args) : q_(NULL) {
  q_ = new __Template__;
}

__Template__Wrap::~__Template__Wrap() {
  delete q_;
}

void __Template__Wrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("__Template__"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Methods
__METHODS__

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("__Template__"), constructor);
}

Handle<Value> __Template__Wrap::New(const Arguments& args) {
  HandleScope scope;

  __Template__Wrap* w = new __Template__Wrap(args);
  w->Wrap(args.This());

  return args.This();
}

__METHOD_FUNCS__