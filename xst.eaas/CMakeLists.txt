add_contract(xst.eaas xst.eaas ${CMAKE_CURRENT_SOURCE_DIR}/src/xst.eaas.cpp)

target_include_directories(xst.eaas
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.token/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)

set_target_properties(xst.eaas
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
