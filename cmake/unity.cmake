include(FetchContent)
FetchContent_Declare(Unity
    GIT_REPOSITORY "https://github.com/ThrowTheSwitch/Unity.git"
    GIT_TAG "v2.5.2" 
    SOURCE_DIR ${PROJECT_DIR}/modules/Unity   
)
FetchContent_Populate(Unity)