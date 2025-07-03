QT += core gui widgets sql
CONFIG += c++11

TEMPLATE = app
TARGET = VehicleRentalSystem

SOURCES += \
    main.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    addvehicledialog.cpp \
    rentalmanager.cpp

HEADERS += \
    loginwindow.h \
    mainwindow.h \
    addvehicledialog.h \
    rentalmanager.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    addvehicledialog.ui


