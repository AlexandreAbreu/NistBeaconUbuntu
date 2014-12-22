include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
    BEACON_SOURCES
    modules/Beacon/plugin.cc
    modules/Beacon/plugin.h
    modules/Beacon/request.cc
    modules/Beacon/request.h
    modules/Beacon/request-result.cc
    modules/Beacon/request-result.h
)

add_library(Beacon MODULE
    ${BEACON_SOURCES}
)

set_target_properties(Beacon PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY Beacon)

qt5_use_modules(Beacon Gui Qml Quick Xml)

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(Beacon-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/Beacon/qmldir ${CMAKE_CURRENT_BINARY_DIR}/Beacon
    DEPENDS ${QMLFILES}
)

# Install plugin file
install(TARGETS Beacon DESTINATION ${QT_IMPORTS_DIR}/Beacon/)
install(FILES   modules/Beacon/qmldir DESTINATION ${QT_IMPORTS_DIR}/Beacon/)

