QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    qcustomplot.cc \
    s21_calc_credit.cc \
    s21_calc_deposit.cc \
    s21_calc_model.cc \
    s21_calc_controller.cc \
    s21_calc_viewer.cc

HEADERS += \
    qcustomplot.h \
    s21_calc_credit.h \
    s21_calc_deposit.h \
    s21_calc_model.h \
    s21_calc_controller.h \
    s21_calc_viewer.h

FORMS += \
    s21_calc_credit.ui \
    s21_calc_deposit.ui \
    s21_calc_viewer.ui

# Для Windows
#win32: RC_ICONS += s21_calc.ico

# Для MacOS
macx: ICON = s21_calc.icns

# Для Linux
unix: RC_ICONS += s21_calc.png

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
