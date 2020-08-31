add_contract(xst.actlog xst.actlog ${CMAKE_CURRENT_SOURCE_DIR}/src/xst.actlog.cpp)

target_include_directories(xst.actlog
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.token/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)

set_target_properties(xst.actlog
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

