cmake_minimum_required(VERSION 3.2)

PROJECT(dmxlsx)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

SET(DMXLSX_VERSION_MAJOR "1")
SET(DMXLSX_VERSION_MINOR "0")
SET(DMXLSX_VERSION_PATCH "1")
SET(DMXLSX_VERSION "${DMXLSX_VERSION_MAJOR}.${DMXLSX_VERSION_MINOR}.${DMXLSX_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMXLSX_VERSION}")

OPTION(USE_DMXLSX "use dmxlsx" OFF)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

LibImport("dmxlsx" "src/dmxlsx")
LibImport("dmxlsximpl" "src/dmxlsximpl")
ModuleInclude("zippy" "src/zippy")
ExeImport("test" "dmxlsx;dmxlsximpl")

include(GenerateExportHeader)
generate_export_header(dmxlsx)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/dmxlsx_export.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)

#ADD_CUSTOM_COMMAND(
#TARGET dmxlsxtest
#PRE_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy_if_different
#${CMAKE_CURRENT_SOURCE_DIR}/config/test.csv
#$<TARGET_FILE_DIR:dmxlsxtest>
#)

#INSTALL(DIRECTORY include/ DESTINATION include)
#INSTALL(TARGETS dmxlsx
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib)

#SET(DMXLSX_LIBS "dmxlsx")
#MARK_AS_ADVANCED(${DMXLSX_LIBS})