include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(atm_tests)
target_sources(atm_tests
    PRIVATE tests.cpp
)
target_link_libraries(atm_tests
    PRIVATE Catch2::Catch2WithMain
            atm::atm
)

add_test(NAME atm_tests COMMAND atm_tests)