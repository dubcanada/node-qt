#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "qsound.h"
#include "../qt_v8.h"

using namespace v8;

Persistent<Function> QSoundWrap::constructor;

// Supported implementations:
//   QSound ( ??? )
QSoundWrap::QSoundWrap(const Arguments& args) : q_(NULL) {
  q_ = new QSound(qt_v8::ToQString(args[0]->ToString()));
}

QSoundWrap::~QSoundWrap() {
  delete q_;
}

void QSoundWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QSound"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Methods
  tpl->PrototypeTemplate()->Set(String::NewSymbol("play"),
      FunctionTemplate::New(play)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setLoops"),
      FunctionTemplate::New(setLoops)->GetFunction());


  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QSound"), constructor);
}

Handle<Value> QSoundWrap::New(const Arguments& args) {
  HandleScope scope;

  QSoundWrap* w = new QSoundWrap(args);
  w->Wrap(args.This());

  return args.This();
}

 Handle<Value> QSoundWrap::play(const Arguments& args) {
  HandleScope scope;

  QSoundWrap* w = ObjectWrap::Unwrap<QSoundWrap>(args.This());
  QSound* q = w->GetWrapped();

  q->play();

  return scope.Close(Undefined());
}

 Handle<Value> QSoundWrap::setLoops(const Arguments& args) {
  HandleScope scope;

  QSoundWrap* w = ObjectWrap::Unwrap<QSoundWrap>(args.This());
  QSound* q = w->GetWrapped();

  if (!args[0]->IsNumber())
    return ThrowException(Exception::TypeError(
        String::New("QSound:setLoops: bad argument")));

  q->setLoops(args[0]->IntegerValue());

  return scope.Close(Undefined());
}