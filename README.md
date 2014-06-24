# Node-Qt

Node-Qt provides native bindings to the [Qt library](http://developer.qt.nokia.com/doc/qt-5.3/) as a [Node.js addon](http://nodejs.org/docs/latest/api/addons.html). The focus is on GUI bindings; there is no need to duplicate the functionality of the Node API and its modules.

We try to follow [Qt's API](http://developer.qt.nokia.com/doc/qt-5.3/) as closely as possible, but sometimes quirks are inevitable (for example, virtual methods that handle events are translated into callback setters). See the header files in `src/` for a list of available bindings, and comments in `.cc` files for possible API differences.

Supported platforms: **Mac OS X** | **Windows** | **Linux**


#### Hello world

Ever wanted to create native apps directly from Node?

![Screenshot](https://github.com/dubcanada/node-qt/raw/master/examples/helloworld.png)

```javascript
var qt = require('..'),
    app = new qt.QApplication;

// Prevent objects from being GC'd
global.app = app;

var hello = new qt.QPushButton('Hello World');
hello.setGeometry(200,200,200,200);
hello.show();

// Start application
app.exec();
```

# Getting started

From your project directory, run (see below for requirements):

```
$ npm install node-qt
```

Alternatively, to use the latest development version from Github:

```
$ npm install git://github.com/dubcanada/node-qt.git
```

This will download and build Node-Qt in `node_modules/`. Then create a new file, say `helloworld.js`, copy the example above and run Node as usual:

```
$ node helloworld
```

See the [examples/](https://github.com/dubcanada/node-qt/tree/master/examples) directory for other simple use cases.

# Status

Modules | Completed | Total
--- | --- | ---
QtCore | 1  | 213
QtGUI | 0 | 207
QtMultimedia | 0 | 82
QtWidgets | 2 | 202

# Build requirements

Node-Qt was designed to build seamlessly with minimal dependencies on most platforms. The necessary platform-dependent Qt binaries are bundled with the module (due to heterogeneous dependencies, Linux is an exception).

For all platforms: Node >= **0.10.29**

+ **Mac:** Python, Make, and GCC.
+ **Windows:** Python and MSVC++ (either [free](http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express) or commercial).
+ **Linux:** Python, Make, GCC, pkg-config, and Qt 5.3+.


# Contributing


## Building and testing

To download and build the development version:

```
$ git clone git://github.com/dubcanada/node-qt.git
$ cd node-qt
$ npm install
```

#### Binding to new classes

1. Create your files (e.g. `qclass.h`, `qclass.cc`) from the provided templates `src/template.h`, `src/template.cc`
2. `qclass.*`: search and replace all occurrences of `__Template__`, `__TEMPLATE__`, and `__template__` with the corresponding class name
3. `node-qt.gyp`: Add qclass.cc to sources list
4. `qt.cc`: Include `qclass.h`
5. `qt.cc`: Add `QClass::Initialize()` to `Initialize()`

#### Binding to new methods

1. `qclass.h`: Declare static method as per `Example()` method in `template.h`
2. `qclass.cc`: Implement method as per `Example()` in `template.cc`
3. `qclass.cc`: Expose method to JavaScript via `tpl->PrototypeTemplate()` call in `Initialize()`. Again see template.cc.