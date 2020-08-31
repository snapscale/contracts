add_contract(xst.charge xst.charge ${CMAKE_CURRENT_SOURCE_DIR}/src/xst.charge.cpp)

target_include_directories(xst.charge
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.token/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)

set_target_properties(xst.charge
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

