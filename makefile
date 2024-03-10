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
	-D PARADOX_BUILD_C_LIBS=${2}\
	-D PARADOX_BUILD_CXX_LIBS=${3}\
	-D PARADOX_BUILD_Swift_LIBS=${4}\
	-D PARADOX_BUILD_TESTS=${5}\
	-D PARADOX_BUILD_DOCS=${6}
@ cmake\
	--build "./build/$(call build-compiler-part)-$(call build-lang-part)/${1}/cmake" --config $(call get-cmake-config-type)
endef

define build_project_c_libs
	$(call build_project,${1},ON,OFF,OFF,OFF,OFF)
endef

define build_project_cpp_libs
	$(call build_project,${1},OFF,ON,OFF,OFF,OFF)
endef

define build_project_swift_libs
	$(call build_project,${1},OFF,OFF,ON,OFF,OFF)
endef

define build_project_tests
	$(call build_project,${1},OFF,OFF,OFF,ON,OFF)
endef

define build_project_docs
	$(call build_project,${1},OFF,OFF,OFF,OFF,ON)
endef

%-c: %-c-lib %-c-tests %-c-docs;
%-cpp: %-cpp-lib %-cpp-tests %-cpp-docs;
%-swift: %-swift-lib %-swift-tests %-swift-docs;

%-c-lib:
	@ echo ---$(PROJECT_NAME): building c libraries---
	$(call build_project_c_libs,$(PROJECT_NAME))
	@ echo ---$(PROJECT_NAME): c libraries are ready---
	$(call newline)
	$(call newline)

%-cpp-lib:
	@ echo ---$(PROJECT_NAME): building c++ libraries---
	$(call build_project_cpp_libs,$(PROJECT_NAME))
	@ echo ---$(PROJECT_NAME): c++ libraries are ready---
	$(call newline)
	$(call newline)

%-swift-lib:
	@ echo ---$(PROJECT_NAME): building swift libraries---
	$(call build_project_swift_libs,$(PROJECT_NAME))
	@ echo ---$(PROJECT_NAME): swift libraries are ready---
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