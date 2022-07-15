set(SOURCES
    ExampleTest.cpp    
)

#Import googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(workshop_tests ${SOURCES})
target_link_libraries(workshop_tests PUBLIC
    gtest_main 
    workshop
)

include(GoogleTest)
gtest_discover_tests(workshop_tests)
