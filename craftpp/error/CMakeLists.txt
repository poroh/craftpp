#
# Copyright (c) 2024 Dmitry Poroh
# All rights reserved.
# Distributed under the terms of the MIT License. See the LICENSE file.
#

set(SOURCES
    error.cpp
    code.cpp
)
file(GLOB HEADERS "*.hpp")

list(TRANSFORM SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

target_sources(craftpp PRIVATE ${SOURCES} ${HEADERS})

install(FILES ${HEADERS} DESTINATION include/craftpp/error)
