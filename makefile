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

%-c: %-c-lib %-c-tests %-c-docs;
%-cpp: %-cpp-lib %-cpp-tests %-cpp-docs;
%-swift: %-swift-lib %-swift-tests %-swift-docs;

%-lib:
	@ cmake\
		-G $(call get-cmake-generator)\
		-B "./build/$(call build-compiler-part)-$(call build-lang-part)/$(PROJECT_NAME)/cmake"\
		-S "./"\
		-D CMAKE_C_COMPILER=$(call get-cmake-c-compiler)\
		-D CMAKE_CXX_COMPILER=$(call get-cmake-cxx-compiler)\
		-D PARADOX_LANGUAGE=$(call build-lang-part)\
		-D PARADOX_COMPILER=$(call build-compiler-part)\
		-D CMAKE_BUILD_TYPE=$(call build-config-part)\
		-D PARADOX_PLATFORM_BUILD_LIBS=ON -DPARADOX_PLATFORM_BUILD_TESTS=OFF

	@ cmake\
		--build "./build/$(call build-compiler-part)-$(call build-lang-part)/$(PROJECT_NAME)/cmake" --config $(call get-cmake-config-type)

%-tests: %-lib
	@ echo Building Test Cases...
	
	@ cmake\
		-G $(call get-cmake-generator)\
		-B "./build/$(call build-compiler-part)-$(call build-lang-part)/unit-tests/cmake"\
		-S "./"\
		-D CMAKE_C_COMPILER=$(call get-cmake-c-compiler)\
		-D CMAKE_CXX_COMPILER=$(call get-cmake-cxx-compiler)\
		-D PARADOX_LANGUAGE=$(call build-lang-part)\
		-D PARADOX_COMPILER=$(call build-compiler-part)\
		-D CMAKE_BUILD_TYPE=$(call build-config-part)\
		-D PARADOX_PLATFORM_BUILD_LIBS=OFF -DPARADOX_PLATFORM_BUILD_TESTS=ON
	
	@ cmake\
		--build "./build/$(call build-compiler-part)-$(call build-lang-part)/unit-tests/cmake" --config $(call get-cmake-config-type)
	
	@ echo Done Building Test Cases

%-docs: %-lib;