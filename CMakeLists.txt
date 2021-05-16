cmake_minimum_required(VERSION 3.14)
project(far_from_home)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if (MINGW)
    set(THREADS_OPTION "-mthreads")
else (MINGW)
    set(THREADS_OPTION "-pthread")
endif (MINGW)

if (MINGW)
    set(THREADS_OPTION "-no-pie -mthreads")
else (MINGW)
    set(THREADS_OPTION "-pthread")
endif (MINGW)


set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Multimedia MultimediaWidgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-no-pie -Wall -Wextra -Wno-sign-compare -Wno-attributes")
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-fno-omit-frame-pointer ${THREADS_OPTION}")


set(SOURCES
        Controller/controller.cpp
        GameObject/cat.cpp
        GameObject/dog.cpp
        GameObject/food.cpp
        GameObject/game_object.cpp
        GameObject/moving_object.cpp
        GameObject/player.cpp
        GameObject/rigid_body.cpp
        main.cpp
        Model/model.cpp
        Model/size.cpp
        Model/point.cpp
        Model/constants.h
        View/view.cpp
        View/resizer.cpp
        GameObject/view_circle.cpp
        View/animation.cpp
        Model/generator.cpp
        Model/timer.cpp
        resourses.qrc
        images.qrc
        Model/group.cpp
        View/button.cpp
        View/button_handler.cpp
        View/button_handler.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})


find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
