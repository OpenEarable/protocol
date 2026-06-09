include("${CMAKE_CURRENT_LIST_DIR}/../protocol_sources.cmake")

zephyr_library_named(open_earable_protocols)
zephyr_library_sources(${OPEN_EARABLE_PROTOCOLS_SOURCES})
zephyr_include_directories("${CMAKE_CURRENT_LIST_DIR}/..")
