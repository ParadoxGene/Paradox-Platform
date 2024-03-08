include config/make/operating-system.mk
include config/make/build-commands.mk
include config/make/common.mk

PROJECT_NAME:=paradox-platform
PROJECT_PREFIX:=PARADOX_PLATFORM

ifeq ($(OS_NAME),Windows)
all: msvc-release-c msvc-release-cpp;
else ifeq ($(OS_NAME),Linux)
all: gcc-release-c gcc-release-cpp;
else ifeq ($(OS_NAME),Macintosh)
all: xcode-release-swift;
endif

define build_project
@ cmake\
	--log-level=STATUS\
	-G $(call get-cmake-generator)\
	-B "./build/$(call build-compiler-part)-$(call build-lang-part)/${1}/cmake"\
	-S "./"\
	-D CMAKE_CXX_COMPILER=$(call get-cmake-cxx-compiler)\
	-D CMAKE_C_COMPILER=$(call get-cmake-c-compiler)\
	-D CMAKE_BUILD_TYPE=$(call build-config-part)\
	-D PARADOX_COMPILER=$(call build-compiler-part)\
	-D PARADOX_LANGUAGE=$(call build-lang-part)\
	-D $(PROJECT_PREFIX)_BUILD_LIBS=${2}\
	-D $(PROJECT_PREFIX)_BUILD_TESTS=${3}\
	-D $(PROJECT_PREFIX)_BUILD_DOCS=${4}
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
	@ echo ---$(PROJECT_NAME): building libraries---
	$(call build_project_libs,$(PROJECT_NAME))
	@ echo ---$(PROJECT_NAME): libraries are ready---
	$(call newline)
	$(call newline)
%-tests: %-lib
	@ echo ---$(PROJECT_NAME): building tests---
	$(call build_project_tests,$(PROJECT_NAME))
	@ echo ---$(PROJECT_NAME): tests are ready---
	$(call newline)
	$(call newline)
%-docs:
	@ echo ---$(PROJECT_NAME): building documentation---
	$(call build_project_docs,$(PROJECT_NAME))
	@ echo ---$(PROJECT_NAME): documentation is ready---
	$(call newline)
	$(call newline)