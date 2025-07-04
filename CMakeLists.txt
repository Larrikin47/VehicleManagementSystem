cmake_minimum_required(VERSION 3.16)

project(VehicleManagementSystem VERSION 0.1 LANGUAGES CXX)

# Enable automatic UI, MOC, and RCC for Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔍 Find Qt6 or Qt5 with Widgets and SQL modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# 📁 Define all project source/header/ui files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    loginwindow.cpp
    loginwindow.h
    loginwindow.ui
    addvehicledialog.cpp
    addvehicledialog.h
    addvehicledialog.ui
    rentalmanager.cpp
    rentalmanager.h
    customermanager.cpp        #
    customermanager.h
    addcustomerdialog.cpp      #
    addcustomerdialog.h
    addcustomerdialog.ui
    addrentaldialog.cpp       #
    addrentaldialog.h         #
    addrentaldialog.ui        #

)

# 🏗 Build configuration depending on Qt version
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VehicleManagementSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(VehicleManagementSystem SHARED ${PROJECT_SOURCES})
    else()
        add_executable(VehicleManagementSystem ${PROJECT_SOURCES})
    endif()
endif()

# 🔗 Link with required Qt modules
target_link_libraries(VehicleManagementSystem
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Sql
)

# 📦 macOS/iOS application bundle properties
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VehicleManagementSystem)
endif()

set_target_properties(VehicleManagementSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 🧩 Installation configuration
include(GNUInstallDirs)
install(TARGETS VehicleManagementSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 🛠 Finalize if using Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VehicleManagementSystem)
endif()
