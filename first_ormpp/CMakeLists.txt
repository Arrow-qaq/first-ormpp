#设定工程名称
Project(first_ormpp)

#设置CMake最低版本要求
cmake_minimum_required(VERSION 3.6.0)

INCLUDE(CheckCXXCompilerFlag)
IF(MSVC)
  ADD_DEFINITIONS(/bigobj)
  ADD_DEFINITIONS(/DNOMINMAX /DWIN32_LEAN_AND_MEAN=1 /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS)

  ADD_COMPILE_OPTIONS(/W3 /wd4005 /wd4068 /wd4244 /wd4267 /wd4800)
  IF (MSVC_VERSION GREATER_EQUAL 1900)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    IF (_cpp_latest_flag_supported)
      ADD_COMPILE_OPTIONS("/std:c++latest")
    ENDIF()
  ENDIF()    
ENDIF()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#设置窗口程序对应的入口函数是Winmain，控制台程序对应的入口函数是main
#SET(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
#增加宏定义
add_definitions(-DWIN32)
add_definitions(-DORMPP_ENABLE_MYSQL)
add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
#工程类型
if(DEBUG)
    SET(CMAKE_BUILD_TYPE    "Debug")
    SET(NAME_SUFFIX         "_d")
    SET(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
elseif(RELEASE)
    SET(CMAKE_BUILD_TYPE    "Release")
    SET(NAME_SUFFIX         "")
    SET(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
endif()
#定义变量
set(LIB_DIR             ${PROJECT_SOURCE_DIR}/lib)
set(LINK_LIB_PATH       ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})

if(WIN32)
    set(PLATFORM        WIN32)
    set(LIB_SUFFIX      .lib)
    set(APP_NAME        ${PROJECT_NAME}.exe)
    set(SGX_LINK_PATH   )  
elseif(ARM)
    set(PLATFORM        arm)
    set(LIB_SUFFIX      .so)
    set(APP_NAME        ${PROJECT_NAME})
endif()
#各种目录变量
set(SRC_DIR                    	${PROJECT_SOURCE_DIR}/src)
set(EXTERNAL_SRC_DIR           	${PROJECT_SOURCE_DIR}/externalsrc)
set(BUILD_DIR                  	${PROJECT_SOURCE_DIR}/build/src)
set(BUILD_DIR_EXTERNALS         ${PROJECT_SOURCE_DIR}/build/externalsrc)
set(OUTPUT_PATH                	${PROJECT_SOURCE_DIR}/lib)
set(OUTPUT_DLL_PATH            	${OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/Service)

#添加子目录，进一步Make
add_subdirectory(src)

#多核编译
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/MP /ZI /MT")
else(ARM)
endif()
