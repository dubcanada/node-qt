#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "qapplication.h"
#include "../qt_v8.h"

using namespace v8;

Persistent<Function> QApplicationWrap::constructor;

int QApplicationWrap::argc_ = 0;
char** QApplicationWrap::argv_ = NULL;

// Supported implementations:
//   QApplication ( ??? )
QApplicationWrap::QApplicationWrap() {
  q_ = new QApplication(argc_, argv_);
}

QApplicationWrap::~QApplicationWrap() {
  delete q_;
}

void QApplicationWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QApplication"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Methods
  tpl->PrototypeTemplate()->Set(String::NewSymbol("exec"),
      FunctionTemplate::New(exec)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setStyleSheet"),
      FunctionTemplate::New(setStyleSheet)->GetFunction());


  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QApplication"), constructor);
}

Handle<Value> QApplicationWrap::New(const Arguments& args) {
  HandleScope scope;

  QApplicationWrap* w = new QApplicationWrap();
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QApplicationWrap::exec(const Arguments& args) {
  HandleScope scope;

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());
  QApplication* q = w->GetWrapped();

  q->exec();

  return scope.Close(Undefined());
}

Handle<Value> QApplicationWrap::setStyleSheet(const Arguments& args) {
  HandleScope scope;

  if (!args[0]->IsString())
    return ThrowException(Exception::TypeError(
        String::New("QApplication:setStylesheet: bad argument")));

  qApp->setStyleSheet(qt_v8::ToQString(args[0]->ToString()));

  return scope.Close(Undefined());
}
