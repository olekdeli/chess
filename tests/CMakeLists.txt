file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(tests 
    ${TEST_SOURCES} 
    ${_SOURCES} 
)

target_precompile_headers(tests PRIVATE
    <iostream>
    <cassert>
    <vector>
    <cstdint>
)

target_include_directories(tests PRIVATE ../include)
add_test(NAME CoreTests COMMAND tests)
