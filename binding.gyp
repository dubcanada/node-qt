{
  'targets': [
    {
      'target_name': 'qt',
      'sources': [
        'src/qt.cc',

        'src/QtWidget/qapplication.cc',
        'src/QtWidget/qlabel.cc',
        'src/QtWidget/qpushbutton.cc',

        'src/QtMultimedia/qsound.cc',
      ],
      'conditions': [
        ['OS=="mac"', {
          'include_dirs': [
            'deps/qt-5.3.0/darwin/x64/include',
            'deps/qt-5.3.0/darwin/x64/include/QtCore',
            'deps/qt-5.3.0/darwin/x64/include/QtGui',
            'deps/qt-5.3.0/darwin/x64/include/QtMultimedia',
            'deps/qt-5.3.0/darwin/x64/include/QtTest'
          ],
          'libraries': [
            # TODO: fix node-gyp behavior that requires ../
            '../deps/qt-5.3.0/darwin/x64/lib/QtCore.framework/QtCore',
            '../deps/qt-5.3.0/darwin/x64/lib/QtGui.framework/QtGui',
            '../deps/qt-5.3.0/darwin/x64/lib/QtGui.framework/QtMultimedia',
            '../deps/qt-5.3.0/darwin/x64/lib/QtTest.framework/QtTest'
          ],
        }],
        ['OS=="linux"', {
          'cflags': [
            '<!@(pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets Qt5Multimedia)'
          ],
          'ldflags': [
            '<!@(pkg-config --libs-only-L --libs-only-other Qt5Core Qt5Gui Qt5Widgets Qt5Multimedia)'
          ],
          'libraries': [
            '<!@(pkg-config --libs-only-l Qt5Core Qt5Gui Qt5Widgets Qt5Multimedia)'
          ]
        }],
        ['OS=="win"', {
          'include_dirs': [
              'deps/qt-5.3.0/win32/ia32/include',
              'deps/qt-5.3.0/win32/ia32/include/QtCore',
              'deps/qt-5.3.0/win32/ia32/include/QtGui',
              'deps/qt-5.3.0/win32/ia32/include/QtMultimedia',
              'deps/qt-5.3.0/win32/ia32/include/QtWidgets',
          ],
          'libraries': [
              # TODO: fix node-gyp behavior that requires ../
              '../deps/qt-5.3.0/win32/ia32/lib/Qt5Core.lib',
              '../deps/qt-5.3.0/win32/ia32/lib/Qt5Gui.lib',
              '../deps/qt-5.3.0/win32/ia32/lib/Qt5Multimedia.lib',
              '../deps/qt-5.3.0/win32/ia32/lib/Qt5Widgets.lib'
          ],
        }]
      ]
    },
    {
      'target_name': 'copy_binary',
      'type': 'none',
      'dependencies': ['qt'],
      'conditions': [
        ['OS=="win"', {
          'copies':
          [
            {
              'destination': 'build/Release/',
              'files': [
                'deps/qt-5.3.0/win32/ia32/Qt5Widgets.dll',
                'deps/qt-5.3.0/win32/ia32/Qt5Core.dll',
                'deps/qt-5.3.0/win32/ia32/Qt5Gui.dll',
                'deps/qt-5.3.0/win32/ia32/Qt5Multimedia.dll',
                'deps/qt-5.3.0/win32/ia32/Qt5Network.dll',
                'deps/qt-5.3.0/win32/ia32/libGLESv2.dll',
                'deps/qt-5.3.0/win32/ia32/icudt52.dll',
                'deps/qt-5.3.0/win32/ia32/icuin52.dll',
                'deps/qt-5.3.0/win32/ia32/icuuc52.dll',
              ]
            }
          ]
        }]
      ]
    }
  ]
}
