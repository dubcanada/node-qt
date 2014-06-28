var qt = require('..'),
    app = new qt.QApplication;

// Prevent objects from being GC'd
global.app = app;

app.setStyleSheet('QPushButton#hello { background-color: qlineargradient(x1: 0, x2: 1,\
                                       stop: 0 #f22,\
                                       stop: 0.16 #f2f,\
                                       stop: 0.33 #22f,\
                                       stop: 0.49 #2ff ,\
                                       stop: 0.65 #2f2,\
                                       stop: 0.81 #ff2,\
                                       stop: 1 #ff2); color:qlineargradient(x1: 0, x2: 1,\
                                       stop: 1 #f22,\
                                       stop: 0.81 #f2f,\
                                       stop: 0.65 #22f,\
                                       stop: 0.49 #2ff ,\
                                       stop: 0.33 #2f2,\
                                       stop: 0.16 #ff2,\
                                       stop: 0 #ff2); font-size: 36px; }');

var sound = new qt.QSound('click.wav');

var hello = new qt.QPushButton('Hello World', function() {
    sound.play();
});
hello.setGeometry(500,200,500,200);
hello.setObjectName('hello');
hello.show();


// Start application
app.exec();