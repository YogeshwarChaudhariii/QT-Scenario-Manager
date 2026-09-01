# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  [[CMakeFiles\QTScenarioManager_autogen.dir\AutogenUsed.txt]]
  [[CMakeFiles\QTScenarioManager_autogen.dir\ParseCache.txt]]
  "QTScenarioManager_autogen"
  )
endif()
