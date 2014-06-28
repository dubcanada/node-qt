#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "qpushbutton.h"
#include "../qt_v8.h"

using namespace v8;

Persistent<Function> QPushButtonWrap::constructor;

//
// QPushButtonWrap()
//

/**
 * new QPushButton('Button Text', function() {
 *   console.log("I've been clicked!");
 * });
 */
QPushButtonWrap::QPushButtonWrap(const Arguments& args) : q_(NULL) {
  if (args[0]->IsString()) {
    // QPushButton ( QPushButton Text )
    q_ = new QPushButton(qt_v8::ToQString(args[0]->ToString()));
  } else {
    q_ = new QPushButton();
  }

  if (args[1]->IsFunction()) {
    Handle<Function> cb = Persistent<Function>::New(Local<Function>::Cast(args[1]));

    QObject::connect(q_, &QPushButton::clicked, [=]() {
      const unsigned argc = 0;
      Handle<Value> argv[1] = {};
      cb->Call(Context::GetCurrent()->Global(), argc, argv);
   });
  }
}

QPushButtonWrap::~QPushButtonWrap() {
  delete q_;
}

void QPushButtonWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QPushButton"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("show"),
      FunctionTemplate::New(Show)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setGeometry"),
      FunctionTemplate::New(setGeometry)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QPushButton"), constructor);
}

Handle<Value> QPushButtonWrap::New(const Arguments& args) {
  HandleScope scope;

  QPushButtonWrap* w = new QPushButtonWrap(args);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QPushButtonWrap::Show(const Arguments& args) {
  HandleScope scope;

  QPushButtonWrap* w = ObjectWrap::Unwrap<QPushButtonWrap>(args.This());
  QPushButton* q = w->GetWrapped();

  q->show();

  return scope.Close(Undefined());
}

Handle<Value> QPushButtonWrap::setGeometry(const Arguments& args) {
  HandleScope scope;

  QPushButtonWrap* w = ObjectWrap::Unwrap<QPushButtonWrap>(args.This());
  QPushButton* q = w->GetWrapped();

  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() ||
      !args[3]->IsNumber())
    return ThrowException(Exception::TypeError(
        String::New("QPushButtonWrap:setGeometry: bad arguments")));

  q->setGeometry(args[0]->IntegerValue(), args[1]->IntegerValue(),
                args[2]->IntegerValue(), args[3]->IntegerValue());

  return scope.Close(Undefined());
}