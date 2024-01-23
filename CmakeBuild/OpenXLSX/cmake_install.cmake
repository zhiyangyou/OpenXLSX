# Install script for directory: I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/OpenXLSX")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/OpenXLSX/OpenXLSX-Exports.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/IZipArchive.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLCell.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLCellIterator.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLCellRange.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLCellReference.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLCellValue.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLColor.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLColumn.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLCommandQuery.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLConstants.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLContentTypes.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLDateTime.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLDocument.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLException.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLFormula.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLIterator.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLProperties.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLRelationships.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLRow.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLRowData.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLSharedStrings.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLSheet.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLWorkbook.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLXmlData.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLXmlFile.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLXmlParser.hpp"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/headers/XLZipArchive.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX" TYPE FILE FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/OpenXLSX.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "lib" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/output/Debug/OpenXLSXd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/output/Release/OpenXLSX.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/output/MinSizeRel/OpenXLSX.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/output/RelWithDebInfo/OpenXLSX.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "bin" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/output/Debug/OpenXLSXd.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/output/Release/OpenXLSX.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/output/MinSizeRel/OpenXLSX.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/output/RelWithDebInfo/OpenXLSX.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/OpenXLSX/OpenXLSXConfig.cmake"
    "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/OpenXLSX/OpenXLSX/OpenXLSXConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake"
         "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "I:/__workSpace/_Github/OpenXLSX-Sharp/OpenXLSX/CmakeBuild/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets-release.cmake")
  endif()
endif()

