cmake_minimum_required(VERSION 3.20)

project(open_earable_protocols LANGUAGES C)

include("${CMAKE_CURRENT_LIST_DIR}/protocol_sources.cmake")

add_library(open_earable_protocols STATIC ${OPEN_EARABLE_PROTOCOLS_SOURCES})
add_library(OpenEarable::Protocols ALIAS open_earable_protocols)
set_target_properties(open_earable_protocols PROPERTIES EXPORT_NAME Protocols)

target_compile_features(open_earable_protocols PUBLIC c_std_99)
target_include_directories(
  open_earable_protocols
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
    "$<INSTALL_INTERFACE:include/open_earable_protocols>"
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  TARGETS open_earable_protocols
  EXPORT OpenEarableProtocolsTargets
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
install(
  FILES ${OPEN_EARABLE_PROTOCOLS_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/open_earable_protocols"
)
install(
  EXPORT OpenEarableProtocolsTargets
  FILE OpenEarableProtocolsTargets.cmake
  NAMESPACE OpenEarable::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OpenEarableProtocols"
)

configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/cmake/OpenEarableProtocolsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/OpenEarableProtocolsConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OpenEarableProtocols"
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/OpenEarableProtocolsConfigVersion.cmake"
  VERSION 0.1.0
  COMPATIBILITY SameMajorVersion
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/OpenEarableProtocolsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/OpenEarableProtocolsConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OpenEarableProtocols"
)
