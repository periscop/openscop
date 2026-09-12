option(ENABLE_ASAN "Build with AddressSanitizer" OFF)
if(ENABLE_ASAN)
  include(CheckCSourceCompiles)
  include(CMakePushCheckState)
  cmake_push_check_state(RESET)
  set(CMAKE_REQUIRED_FLAGS "-fsanitize=address -fno-omit-frame-pointer -fno-sanitize-recover=address")
  check_c_source_compiles("#include <stdlib.h>\nint main(void) { char *p = malloc(1); p[0] = 0; free(p); return 0; }" ASAN_SUPPORTED)
  cmake_pop_check_state()
  if(NOT ASAN_SUPPORTED)
    message(FATAL_ERROR "AddressSanitizer requires a compiler and runtime supporting -fsanitize=address")
  endif()
  add_compile_options(-O1 -g -fsanitize=address -fno-omit-frame-pointer -fno-sanitize-recover=address)
  # CMake 3.12 predates add_link_options.
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -fsanitize=address")
  string(APPEND CMAKE_SHARED_LINKER_FLAGS " -fsanitize=address")
endif()

# Reconfiguration changes compile commands, so CMake rebuilds affected objects.
set(ASAN_BUILD_CONFIG)
set(ASAN_TEST_CONFIG)
if(CMAKE_CONFIGURATION_TYPES)
  set(ASAN_BUILD_CONFIG --config "$<CONFIG>")
  set(ASAN_TEST_CONFIG -C "$<CONFIG>")
endif()
add_custom_target(asan
  COMMAND "${CMAKE_COMMAND}" "${CMAKE_SOURCE_DIR}" -DENABLE_ASAN=ON
  COMMAND "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" ${ASAN_BUILD_CONFIG}
  COMMAND "${CMAKE_CTEST_COMMAND}" --output-on-failure ${ASAN_TEST_CONFIG}
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  VERBATIM
  USES_TERMINAL
  COMMENT "Enable AddressSanitizer, rebuild, and run tests")
