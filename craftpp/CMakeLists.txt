#
# Copyright (c) 2024 Dmitry Poroh
# All rights reserved.
# Distributed under the terms of the MIT License. See the LICENSE file.
#

set(SUBLIBS
  result
  error
  types
  maybe
  string
  binary
  variant
)

add_library(craftpp)

foreach (sublib IN LISTS SUBLIBS)
    add_subdirectory(${sublib})
endforeach()




