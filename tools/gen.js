var fs = require('fs');

var argv = require('yargs')
    .usage('Generate skeleton file for QT Library.\nusage: $0')
    .example('$0 -f', 'Folder for Qt Library (QtCore, QtGui, QtWidget) proper CaSe')
    .example('$0 -n', 'Name of the QT Library in proper CaSe')
    .example('$0 -m', 'List of methods seperated by , (ex. setGeometry,setValue,setStylesheet)')
    .demand(['f','n','m'])
    .argv;

var cc = fs.readFileSync('skeleton/template.cc', 'utf8');
var h = fs.readFileSync('skeleton/template.h', 'utf8');

// Replace cc
cc = cc.replace(/__template__/g, argv.n.toLowerCase());
cc = cc.replace(/__Template__/g, argv.n);

// Replace h
h = h.replace(/__Template__/g, argv.n);
h = h.replace(/__TEMPLATE__/g, argv.n.toUpperCase());

var method_cc = '  tpl->PrototypeTemplate()->Set(String::NewSymbol("__Name__"),\n\
      FunctionTemplate::New(__Name__)->GetFunction());';

var method_h = '  static v8::Handle<v8::Value> __Name__(const v8::Arguments& args);';

var func_cc = ' Handle<Value> __F_Template__Wrap::__Template__(const Arguments& args) {\n\
  HandleScope scope;\n\
\n\
  __F_Template__Wrap* w = ObjectWrap::Unwrap<__F_Template__Wrap>(args.This());\n\
  __F_Template__* q = w->GetWrapped();\n\
\n\
\n\
\n\
  return scope.Close(Undefined());\n\
}\n';

// Add methods
var methods = argv.m.split(',');
var cc_methods = '';
var h_methods = '';
var cc_funcs = '';

methods.forEach(function(method) {
    cc_methods += method_cc
        .replace(/__Name__/g, method) + '\n';

    cc_funcs += func_cc
        .replace(/__F_Template__/g, argv.n)
        .replace(/__Template__/g, method) + '\n';

    h_methods += method_h
        .replace('__Name__', method) + '\n';
});

cc = cc.replace('__METHODS__', cc_methods);
cc = cc.replace('__METHOD_FUNCS__', cc_funcs);
h = h.replace('__METHODS__', h_methods);

// Write CC
fs.writeFile('../src/' + argv.f + '/' + argv.n.toLowerCase() + '.cc', cc);

// Write h
fs.writeFile('../src/' + argv.f + '/' + argv.n.toLowerCase() + '.h', h);