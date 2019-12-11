# $Id: CMakeLists.txt 86065 2018-01-08 14:39:15Z black_bycel $
#CMakeList.txt, с его помощью собирается проект Geant4, файл основан на примере B1
#входящим в стандартную поставку Geant4
#Как правило здесь настраивать ничего не надо

#----------------------------------------------------------------------------
# Setup the project
# Запуск проекта
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(example3)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
# Поиск пакетов Geant4, включение всех доступных интерфейсов пользователя 
# (Qt, GAG, tcsh, csh) и драйверов визуализации по умолчанию.
# Можно использовать переменную окружения WITH_GEANT4_UIVIS, установить в OFF (выключено)
# через командную строку или с помощью ccmake/cmake-gui для сборки проекта только с
# пакетном режимом
# 
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
# Подключение директорий и компилирование определений из Geant4
# Подключение директорий этого проекта
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
# Расположение искодного кода и заголовочных файлов этого проекта
# Заголовочные файлы подключаются, значит что они будут показаны в 
# IDE - среде разработки
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
# Добавление исполняемого файла и связывания его с Geant4 библиотеками
#
add_executable(example3 example3.cpp ${sources} ${headers})
target_link_libraries(example3 ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build exsample. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
# Копирование скриптов в директорию сборки - туда, где мы собираем проект.
# Таким образом мы сможем запустить проект в директории сборки - текущей рабочей
# директории, что нужно например, при отладке.
#
set(EXAMPLE3_SCRIPTS
  run0.mac  
  run1.mac
  vis.mac
  )

foreach(_script ${EXAMPLE3_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
# Для внутеренего использования в Geant4, но не имеет влияния если проект
# компилируется для отдельного использования
#
add_custom_target(ex3 DEPENDS example3)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
# Установка исполняемого файла в 'bin' директорию по пути 
# установки CMAKE_INSTALL_PREFIX
#
install(TARGETS example3 DESTINATION bin)

