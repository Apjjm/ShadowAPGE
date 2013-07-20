#Base Config
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#Enable c++11
QMAKE_CXXFLAGS += -std=c++0x

#SFML
#DEFINES += SFML_STATIC
INCLUDEPATH += C:/Users/Andy/Documents/QtPrj/SFML-TDM471x32/include
DEPENDPATH += C:/Users/Andy/Documents/QtPrj/SFML-TDM471x32/include
LIBS += -LC:/Users/Andy/Documents/QtPrj/SFML-TDM471x32/lib
CONFIG(release, debug|release): LIBS += -lsfml-audio-s -lsfml-graphics-s -lsfml-main -lsfml-network-s -lsfml-window-s -lsfml-system-s
CONFIG(debug, debug|release): LIBS += -lsfml-audio-s-d -lsfml-graphics-s-d -lsfml-main-d -lsfml-network-s-d -lsfml-window-s-d -lsfml-system-s-d

#BOOST
INCLUDEPATH += C:/CPP/boost_1_54_0/includes
DEPENDPATH += C:/CPP/boost_1_54_0/includes
LIBS += -LC:/CPP/boost_1_54_0/boost_1_54_0/stage/lib
CONFIG(release, debug|release): LIBS += libboost_filesystem-mgw47-mt-1_54 libboost_system-mgw47-mt-1_54
CONFIG(debug, debug|release): LIBS += libboost_filesystem-mgw47-mt-d-1_54 libboost_system-mgw47-mt-d-1_54

#SOURCES
SOURCES += main.cpp \
    APGE/Core/Logger.cpp \
    APGE/Core/Application.cpp \
    APGE/Core/Resource/ResourceManager.cpp

HEADERS += \
    SFML_INCLUDES.hpp \
    APGE/APGE.hpp \
    APGE/Core/Application.hpp \
    APGE/Core/CoreTypes.hpp \
    APGE/Core/Logger.hpp \
    APGE/Core/Resource/IResourceHandler.hpp \
    APGE/Core/Resource/TResourceHandler.hpp \
    APGE/Core/Resource/ResourceManager.hpp \
    APGE/Core/Resource/IResourceFromMemoryData.hpp \
    APGE/Core/Resource/IResourceFromStreamData.hpp

