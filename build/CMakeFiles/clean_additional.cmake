# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  [[CMakeFiles\Qt-Scenario-Manager_autogen.dir\AutogenUsed.txt]]
  [[CMakeFiles\Qt-Scenario-Manager_autogen.dir\ParseCache.txt]]
  "Qt-Scenario-Manager_autogen"
  )
endif()
