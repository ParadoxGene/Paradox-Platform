include config/make/operating-system.mk
include config/make/build-commands.mk

PROJECT_NAME := paradox-platform

ifeq ($(OS_NAME),Windows)
all: msvc-release-c msvc-release-cpp;
else ifeq ($(OS_NAME),Linux)
all: gcc-release-c gcc-release-cpp;
else ifeq ($(OS_NAME),Macintosh)
all: xcode-release-swift;
endif

define build_project
	cmake\
	-G $(call get-cmake-generator)\
	-B "./build/$(call build-compiler-part)-$(call build-lang-part)/${1}/cmake"\
	-S "./"\
	-D CMAKE_CXX_COMPILER=$(call get-cmake-cxx-compiler)\
	-D CMAKE_C_COMPILER=$(call get-cmake-c-compiler)\
	-D CMAKE_BUILD_TYPE=$(call build-config-part)\
	-D PARADOX_COMPILER=$(call build-compiler-part)\
	-D PARADOX_LANGUAGE=$(call build-lang-part)\
	-D PARADOX_PLATFORM_BUILD_LIBS=${2}\
	-D PARADOX_PLATFORM_BUILD_TESTS=${3}\
	-D PARADOX_PLATFORM_BUILD_DOCS=${4}
@ cmake\
	--build "./build/$(call build-compiler-part)-$(call build-lang-part)/${1}/cmake" --config $(call get-cmake-config-type)
endef

define build_project_libs
	$(call build_project,${1},ON,OFF,OFF)
endef

define build_project_tests
	$(call build_project,${1},OFF,ON,OFF)
endef

define build_project_docs
	$(call build_project,${1},OFF,OFF,ON)
endef

%-c: %-c-lib %-c-tests %-c-docs;
%-cpp: %-cpp-lib %-cpp-tests %-cpp-docs;
%-swift: %-swift-lib %-swift-tests %-swift-docs;

%-lib:
	@ echo Building Libs...
	$(call build_project_libs,paradox-platform)
	@ echo Done Building Libs

%-tests: %-lib
	@ echo Building Tests...
	$(call build_project_tests,paradox-platform)
	@ echo Done Building Tests

%-docs:
	@ echo Building Docs...
	$(call build_project_docs,paradox-platform)
	@ echo Done Building Docs