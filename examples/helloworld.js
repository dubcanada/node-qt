var qt = require('..'),
    app = new qt.QApplication;

// Prevent objects from being GC'd
global.app = app;

var hello = new qt.QPushButton('Hello World');
hello.setGeometry(200,200,200,200);
hello.show();

// Start application
app.exec();