#ifndef __TEMPLATE__WRAP_H
#define __TEMPLATE__WRAP_H

#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <__Template__>

class __Template__Wrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  __Template__* GetWrapped() const { return q_; };

 private:
  __Template__Wrap(const v8::Arguments& args);
  ~__Template__Wrap();
  static v8::Persistent<v8::Function> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped methods
__METHODS__

  // Wrapped object
  __Template__* q_;
};

#endif
