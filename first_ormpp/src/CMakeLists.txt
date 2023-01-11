
SET(source_files

)
SET(header_files

)
SET(moc_files

)

include("${CMAKE_CURRENT_SOURCE_DIR}/main/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/include/CMakeLists.rules")

include_directories(
    ./
    ${include_dir}
    ${CMAKE_CURRENT_SOURCE_DIR}/iguana
    ${BUILD_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/mysql
   )

link_directories(${OUTPUT_DLL_PATH})
link_directories(${LINK_LIB_PATH})


add_executable(${PROJECT_NAME} ${moc_files} ${source_files} ${uic_files} ${HEADER_MOCS} ${UIC_OUTPUTS} ${RESOURCES_RCC} ${header_files})
target_link_libraries(${PROJECT_NAME} mysqlclient) 

set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH})
