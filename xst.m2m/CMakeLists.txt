add_contract(xst.m2m xst.m2m ${CMAKE_CURRENT_SOURCE_DIR}/src/xst.m2m.cpp)

target_include_directories(xst.m2m
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(xst.m2m
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/xst.m2m.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/xst.m2m.contracts.md @ONLY )

# target_compile_options( xst.m2m PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
