include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "v1.14.0"
    SOURCE_DIR ${PROJECT_DIR}/modules/googletest
)
FetchContent_Populate(googletest)