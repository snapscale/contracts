add_contract(xst.stable xst.stable ${CMAKE_CURRENT_SOURCE_DIR}/src/xst.stable.cpp)

target_include_directories(xst.stable
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)

set_target_properties(xst.stable
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

