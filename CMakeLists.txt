cmake_minimum_required(VERSION 3.16)
project(far_from_home)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler

# You can set CMake prefix path here or pass it to CMake executable.
#set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/gcc_64/lib/cmake")
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\")")
endif ()

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Widgets Multimedia)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Widgets Qt5::Multimedia)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -O3")

set(SOURCES
        Controller/controller.cpp

        GameObject/game_object.cpp
        GameObject/cat.cpp

        main.cpp
        Model/model.cpp
        Model/level.cpp
        Model/game_map.cpp
        Model/size.cpp
        Model/point.cpp

        View/view.cpp GameObject/moving_object.cpp GameObject/moving_object.h Model/constants.h)

#qt5_add_big_resources(RESOURCES database.qrc music.qrc images.qrc)
add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})


find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
#target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

#add_executable(server
#        Server/main.cpp
#        Server/message.cpp
#        Server/server.cpp)
#target_link_libraries(server Qt5::Core Qt5::WebSockets)
