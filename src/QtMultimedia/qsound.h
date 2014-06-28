#ifndef QSOUNDWRAP_H
#define QSOUNDWRAP_H

#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <QSound>

class QSoundWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QSound* GetWrapped() const { return q_; };

 private:
  QSoundWrap(const v8::Arguments& args);
  ~QSoundWrap();
  static v8::Persistent<v8::Function> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped methods
  static v8::Handle<v8::Value> play(const v8::Arguments& args);
  static v8::Handle<v8::Value> setLoops(const v8::Arguments& args);


  // Wrapped object
  QSound* q_;
};

#endif
