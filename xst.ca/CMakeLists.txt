add_contract(xst.ca xst.ca ${CMAKE_CURRENT_SOURCE_DIR}/src/xst.ca.cpp)

target_include_directories(xst.ca
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(xst.ca
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/xst.ca.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/xst.ca.contracts.md @ONLY )

# target_compile_options( xst.ca PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
