cmake_minimum_required(VERSION 3.2)

PROJECT(dmmsgparser)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

SET(DMMSG_VERSION_MAJOR "1")
SET(DMMSG_VERSION_MINOR "0")
SET(DMMSG_VERSION_PATCH "1")
SET(DMMSG_VERSION "${DMMSG_VERSION_MAJOR}.${DMMSG_VERSION_MINOR}.${DMMSG_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMMSG_VERSION}")

OPTION(USE_DMMSG "use dmmsg" OFF)

ModuleImport("dmlog" "thirdparty/dmlog")
ModuleImport("dmsys" "thirdparty/dmsys")
DllImportDepends("dmmsgparser" "src/dmmsgparser_module" "dmsys")
ExeImport("test" "dmmsgparser;dmsys;libprotobuf;libprotoc")

#ADD_CUSTOM_COMMAND(
#TARGET dmmsgtest
#PRE_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy_if_different
#${CMAKE_CURRENT_SOURCE_DIR}/config/test.csv
#$<TARGET_FILE_DIR:dmmsgtest>
#)

#INSTALL(DIRECTORY include/ DESTINATION include)
#INSTALL(TARGETS dmmsg
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib)

#SET(DMMSG_LIBS "dmmsg")
#MARK_AS_ADVANCED(${DMMSG_LIBS})