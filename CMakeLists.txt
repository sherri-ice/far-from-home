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
        GameObject/portal_object.cpp
        GameObject/rigid_body.cpp
        GameObject/view_circle.cpp
        images.qrc
        main.cpp
        Model/constants.h
        Model/generator.cpp
        Model/group.cpp
        Model/model.cpp
        Model/point.cpp
        Model/size.cpp
        Model/timer.cpp
        resourses.qrc
        View/animation.cpp
        View/global_progress_bar.cpp
        Model/music_player.cpp
        View/menu.cpp
        View/menu.ui
        View/progress_bar.cpp
        View/resizer.cpp
        View/view.cpp
        View/warning.cpp
        View/result_window.cpp
        View/result_window.ui
        View/background.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})


find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
