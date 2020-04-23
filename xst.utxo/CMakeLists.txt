add_contract(xst.utxo xst.utxo ${CMAKE_CURRENT_SOURCE_DIR}/src/xst.utxo.cpp)

target_include_directories(xst.utxo
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(xst.utxo
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/xst.utxo.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/xst.utxo.contracts.md @ONLY )

# target_compile_options( xst.utxo PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
