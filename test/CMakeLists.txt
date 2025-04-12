include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(test_atm)
target_sources(test_atm
    PRIVATE src/test_atm.cpp
)
target_link_libraries(test_atm
    PRIVATE Catch2::Catch2WithMain
            atm::atm
)

add_test(NAME atm COMMAND test_atm)