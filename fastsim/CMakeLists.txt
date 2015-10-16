include_directories(
	${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/datamodel
#        ${CMAKE_CURRENT_SOURCE_DIR}/utilities
)

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

foreach( _conf ${CMAKE_CONFIGURATION_TYPES} )
  string(TOUPPER ${_conf} _conf )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_conf} ${CMAKE_CURRENT_BINARY_DIR} )
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${_conf} ${CMAKE_CURRENT_BINARY_DIR} )
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${_conf} ${CMAKE_CURRENT_BINARY_DIR} )
endforeach()


file(GLOB pcms ${CMAKE_CURRENT_BINARY_DIR}/*.pcm ${CMAKE_CURRENT_BINARY_DIR}/*.rootmap)
file(GLOB sources datamodel/*.cc)
file(GLOB headers datamodel/*.h)
file(GLOB sources_utils utilities/*.cc)
file(GLOB headers_utils utilities/*.h)

add_library(FastSimDataModel SHARED ${sources} ${sources_utils} ${headers} ${headers_utils})
target_link_libraries(FastSimDataModel podio )
install(TARGETS FastSimDataModel DESTINATION fastsim)

REFLEX_GENERATE_DICTIONARY(FastSimDataModel ${headers} SELECTION datamodel/selection.xml)
add_library(FastSimDataModelDict SHARED FastSimDataModel.cxx)
target_link_libraries(FastSimDataModelDict FastSimDataModel podio )
install(TARGETS FastSimDataModelDict DESTINATION fastsim)
install(FILES ${pcms} DESTINATION fastsim)

file(GLOB executables RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach( sourcefile ${executables} )
  string( REPLACE ".cpp" "" name ${sourcefile} )
  add_executable( ${name} ${sourcefile} )
  target_link_libraries( ${name} FastSimDataModelDict ${GTEST_LIBRARIES})
  install(TARGETS ${name} DESTINATION fastsim)
endforeach( sourcefile ${executables} )


#--- Adding tests --------------------------------------------------------------
add_test(NAME writeSim COMMAND writeSim)
set_property(TEST writeSim PROPERTY ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/fastsim:$ENV{LD_LIBRARY_PATH})

add_test(NAME readSim COMMAND readSim DEPENDS writeSim)
set_property(TEST readSim PROPERTY ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/fastsim:$ENV{LD_LIBRARY_PATH})
