# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Sign_up_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Sign_up_autogen.dir\\ParseCache.txt"
  "Sign_up_autogen"
  )
endif()
