# Version: 1.001
# setup.py
# simple build system generator for paradox libraries
import json
import os
import platform
import subprocess

class Library:
    def __init__(self):
        self.name = ""
        self.path = ""
        self.paradox_library = False

class BuildInfo:
    def __init__(self):
        self.name = ""
        self.prefix = ""
        self.type = ""
        self.library_type = "SHARED"

        self.c_compiler_definitions = []
        self.cpp_compiler_definitions = []
        self.swift_compiler_definitions = []

        self.c_sources = []
        self.cpp_sources = []
        self.swift_sources = []

        self.c_includes = []
        self.cpp_includes = []
        self.swift_includes = []

        self.c_libraries = []
        self.cpp_libraries = []
        self.swift_libraries = []

        self.c_linker_options = []
        self.cpp_linker_options = []
        self.swift_linker_options = []

library_dict = {}
build_infos = []

def allowed(obj):
    if "os" in obj and len(obj["os"]) > 0:
        found = False
        for os_name in obj["os"]:
            if "windows" == os_name and "Windows" == platform.system():
                found = True
                break
            if "linux" == os_name and "Linux" != platform.system():
                found = True
                break
            if "osx" == os_name and "Darwin" != platform.system():
                found = True
                break
        if False == found:
            return False
    return True

def load_project(project_json_path, main_project = False):
    if not os.path.exists(project_json_path):
        return
    build_json = json.loads(open(project_json_path, "r").read())
    project_name = build_json["name"]
    project_prefix = project_name.upper().replace("-", "_")
    for build_type in build_json:
        if build_type != "external-libraries" and build_type != "paradox-libraries":
            continue

        lib_objs = build_json[build_type]
        for lib_obj in lib_objs:
            if allowed(lib_obj) == False:
                continue
            
            lib_name = lib_obj["name"]
            if lib_name in library_dict:
                continue

            lib_config = None
            if "config" in lib_obj: lib_config = lib_obj["config"]

            git_path = f"https://github.com/ParadoxGene/{lib_name}.git" if build_type == "paradox-libraries" else ""
            git_branch = "main"

            for config in lib_config:
                if "git" == config:
                    git_path = lib_config["git"]
                if "version" == config:
                    git_branch = lib_config["version"]
            
            if os.path.exists(f"modules/{lib_name}"):
                subprocess.call(f"cd modules/{lib_name} & git fetch origin & git pull origin {git_branch} & git checkout {git_branch}", shell = True)
            else:
                subprocess.call(f"git clone -b {git_branch} {git_path} modules/{lib_name} & git checkout {git_branch}", shell = True)
            
            library = Library()
            library.name = lib_name
            library.path = f"modules/{lib_name}"
            library.paradox_library = True if build_type == "paradox-libraries" else False
            library_dict[lib_name] = library
            if library.paradox_library:
                load_project(f"modules/{lib_name}/build.json")

    for build_type in build_json:
        if(build_type != "build"):
            continue
        
        for build in build_json["build"]:
            build_info = BuildInfo()
            build_info.name = build["name"]
            build_info.prefix = build_info.name.upper().replace("-", "_")
            build_info.type = build["type"]
            if "compiler-definitions" in build:
                for definition in build["compiler-definitions"]:
                    if not allowed(definition): continue
                    
                    build_info.c_compiler_definitions.append(definition["define"])
                    build_info.cpp_compiler_definitions.append(definition["define"])
                    build_info.swift_compiler_definitions.append(definition["define"])
            if "library-type" in build:
                build_info.library_type = build["library-type"].upper()
            for source in build["sources"]:
                source_dir = source["repo"]
                if project_name == source_dir and main_project:
                    build_info.c_sources.append(f"api/c/{source["library"]}/src/{source["directory"]}")
                    build_info.cpp_sources.append(f"api/cpp/{source["library"]}/src/{source["directory"]}")
                    build_info.swift_sources.append(f"api/swift/{source["library"]}/src/{source["directory"]}")
                elif source_dir in library_dict:
                    library = library_dict[source_dir]
                    if library.paradox_library:
                        build_info.c_sources.append(f"{library.path}/api/c/{source["library"]}/src/{source["directory"]}")
                        build_info.cpp_sources.append(f"{library.path}/api/cpp/{source["library"]}/src/{source["directory"]}")
                        build_info.swift_sources.append(f"{library.path}/api/swift/{source["library"]}/src/{source["directory"]}")
                    else:
                        build_info.c_sources.append(f"{library.path}/{source["directory"]}")
                        build_info.cpp_sources.append(f"{library.path}/{source["directory"]}")
                        build_info.swift_sources.append(f"{library.path}/{source["directory"]}")
            
            if "includes" in build:
                for include in build["includes"]:
                    include_dir = include["repo"]
                    if project_name == include_dir and main_project:
                        build_info.c_includes.append(f"api/c/{include["library"]}/include")
                        build_info.cpp_includes.append(f"api/cpp/{include["library"]}/include")
                        build_info.swift_includes.append(f"api/swift/{include["library"]}/include")
                    elif include_dir in library_dict:
                        library = library_dict[include_dir]
                        if library.paradox_library:
                            build_info.c_includes.append(f"{library.path}/api/c/{include["library"]}/include")
                            build_info.cpp_includes.append(f"{library.path}/api/cpp/{include["library"]}/include")
                            build_info.swift_includes.append(f"{library.path}/api/swift/{include["library"]}/include")
                        else:
                            build_info.c_includes.append(f"{library.path}/{include["directory"]}")
                            build_info.cpp_includes.append(f"{library.path}/{include["directory"]}")
                            build_info.swift_includes.append(f"{library.path}/{include["directory"]}")

            if "libraries" in build:
                for lib in build["libraries"]:
                    lib_name = lib["name"]
                    build_info.c_libraries.append(lib_name)
                    if lib_name in library_dict and library_dict[lib_name].paradox_library:
                        build_info.cpp_libraries.append(lib_name + "-framework")
                    else:
                        build_info.cpp_libraries.append(lib_name)
                    build_info.swift_libraries.append(lib_name)

            build_infos.append(build_info)

def generate_makefile():
    makefile_txt = f"""
word-hyphen=$(word $2,$(subst -, ,$1))
build-compiler-part=$(strip $(call word-hyphen,$@,1))
build-config-part=$(strip $(call word-hyphen,$@,2))
build-lang-part=$(strip $(call word-hyphen,$@,3))
get-cmake-generator=$(strip \
	$(if $(filter $(call build-compiler-part),msvc),"Visual Studio 17 2022")\
	$(if $(filter $(call build-compiler-part),xcode),"Xcode")\
	$(if $(filter $(call build-compiler-part),gcc),"Unix Makefiles")\
	$(if $(filter $(call build-compiler-part),clang),"Unix Makefiles"))
get-cmake-c-compiler=$(strip \
	$(if $(filter $(call build-compiler-part),msvc),cl)\
	$(if $(filter $(call build-compiler-part),gcc),gcc)\
	$(if $(filter $(call build-compiler-part),clang),clang))
get-cmake-cxx-compiler=$(strip \
	$(if $(filter $(call build-compiler-part),msvc),cl)\
	$(if $(filter $(call build-compiler-part),gcc),g++)\
	$(if $(filter $(call build-compiler-part),clang),clang++))
get-cmake-config-type=\
	$(if $(filter $(call build-config-part),debug),Debug)\
	$(if $(filter $(call build-config-part),release),Release)
""" +\
("""
all: msvc-release-c msvc-release-cpp;
""" if "Windows" == platform.system() else "") +\
("""
all: gcc-release-c gcc-release-cpp;
""" if "Linux" == platform.system() else "") +\
("""
all: xcode-release-swift;
""" if "Darwin" == platform.system() else "") +\
"""
define build_project
@ cmake\
	--log-level=STATUS\
	-G $(call get-cmake-generator)\
	-B "./build/$(call build-compiler-part)-$(call build-lang-part)/cmake"\
	-S "./"\
	-D CMAKE_CXX_COMPILER=$(call get-cmake-cxx-compiler)\
	-D CMAKE_C_COMPILER=$(call get-cmake-c-compiler)\
	-D CMAKE_BUILD_TYPE=$(call build-config-part)\
	-D PARADOX_COMPILER=$(call build-compiler-part)\
	-D PARADOX_LANGUAGE=$(call build-lang-part)\
	-D PARADOX_BUILD_C_LIBS=${1}\
	-D PARADOX_BUILD_CXX_LIBS=${2}\
	-D PARADOX_BUILD_Swift_LIBS=${3}\
	-D PARADOX_BUILD_TESTS=${4}\
	-D PARADOX_BUILD_DOCS=${5}
@ cmake\
	--build "./build/$(call build-compiler-part)-$(call build-lang-part)/cmake" --config $(call get-cmake-config-type)
endef

define build_project_c_libs
	$(call build_project,ON,OFF,OFF,OFF,OFF)
endef

define build_project_cpp_libs
	$(call build_project,OFF,ON,OFF,OFF,OFF)
endef

define build_project_swift_libs
	$(call build_project,OFF,OFF,ON,OFF,OFF)
endef

define build_project_tests
	$(call build_project,OFF,OFF,OFF,ON,OFF)
endef

define build_project_docs
	$(call build_project,OFF,OFF,OFF,OFF,ON)
endef

%-c: %-c-lib %-c-tests %-c-docs;
%-cpp: %-cpp-lib %-cpp-tests %-cpp-docs;
%-swift: %-swift-lib %-swift-tests %-swift-docs;

%-c-lib:
	@ echo ---building c libraries---
	$(call build_project_c_libs)
	@ echo ---c libraries are ready---

%-cpp-lib:
	@ echo ---building c++ libraries---
	$(call build_project_cpp_libs)
	@ echo ---c++ libraries are ready---
	$(call newline)

%-swift-lib:
	@ echo ---building swift libraries---
	$(call build_project_swift_libs)
	@ echo ---swift libraries are ready---

%-tests: %-lib
	@ echo ---building tests---
	$(call build_project_tests)
	@ echo ---tests are ready---

%-docs:
	@ echo ---building documentation---
	$(call build_project_docs)
	@ echo ---documentation is ready---
"""
    with open('makefile', 'w') as makefile: makefile.write(makefile_txt)

def generate_cmakefile():
    cmakefile_txt = f"""
cmake_minimum_required(VERSION 3.14)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

set(PROJECT_DIR "${{CMAKE_CURRENT_SOURCE_DIR}}/.")

if("${{PARADOX_COMPILER}}" STREQUAL "msvc")
    set(MSVC ON)
elseif("${{PARADOX_COMPILER}}" STREQUAL "gcc")
    set(GCC ON)
elseif("${{PARADOX_COMPILER}}" STREQUAL "clang")
    set(Clang ON)
elseif("${{PARADOX_COMPILER}}" STREQUAL "xcode")
    set(XCode ON)
else()
    message(FATAL_ERROR "Please set PARADOX_COMPILER to either msvc, gcc, clang, or xcode")
endif()

if("${{PARADOX_LANGUAGE}}" STREQUAL "cpp")
        set(PARADOX_BUILD_LANG CXX)
        set(PARADOX_BUILD_LANG_EXT "cpp")
elseif("${{PARADOX_LANGUAGE}}" STREQUAL "c")
    set(PARADOX_BUILD_LANG C)
    set(PARADOX_BUILD_LANG_EXT "c")
elseif("${{PARADOX_LANGUAGE}}" STREQUAL "swift")
    set(PARADOX_BUILD_LANG Swift)
    set(PARADOX_BUILD_LANG_EXT "swift")
else()
    message(FATAL_ERROR "Please set PARADOX_LANGUAGE to either cpp, c, or swift")
endif()

if((${{CMAKE_BUILD_TYPE}} STREQUAL "Release") OR (${{CMAKE_BUILD_TYPE}} STREQUAL "release"))
    set(PARADOX_RELEASE ON)
elseif((${{CMAKE_BUILD_TYPE}} STREQUAL "Debug") OR (${{CMAKE_BUILD_TYPE}} STREQUAL "debug"))
    set(PARADOX_DEBUG ON)
    set(PARADOX_MSVC_DEBUG_FLAGS /W4 /WX)
    set(PARADOX_CLANG_DEBUG_FLAGS -Og -Wpedantic -Wall -Wextra -Werror)
    set(PARADOX_GCC_DEBUG_FLAGS -Og -Wpedantic -Wall -Wextra -Werror)
else()
    message(FATAL_ERROR "Please set CMAKE_BUILD_TYPE to either Release or Debug" )
endif()

if(WIN32)
    if(MSVC)
        list(APPEND PARADOX_C_DEBUG_FLAGS ${{PARADOX_MSVC_DEBUG_FLAGS}})
        list(APPEND PARADOX_CXX_DEBUG_FLAGS ${{PARADOX_MSVC_DEBUG_FLAGS}})
    elseif(Clang)
        list(APPEND PARADOX_C_DEBUG_FLAGS ${{PARADOX_CLANG_DEBUG_FLAGS}})
        list(APPEND PARADOX_CXX_DEBUG_FLAGS ${{PARADOX_CLANG_DEBUG_FLAGS}})
    elseif(GCC)
        list(APPEND PARADOX_C_DEBUG_FLAGS ${{PARADOX_GCC_DEBUG_FLAGS}})
        list(APPEND PARADOX_CXX_DEBUG_FLAGS ${{PARADOX_GCC_DEBUG_FLAGS}})
    endif()
    list(APPEND PARADOX_C_COMPILE_DEFINITIONS -D_CRT_SECURE_NO_DEPRECATE)
    list(APPEND PARADOX_CXX_COMPILE_DEFINITIONS -D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_DEFINITIONS}})
elseif(LINUX)
    if(Clang)
        set(PARADOX_CXX_DEBUG_FLAGS ${{PARADOX_CLANG_DEBUG_FLAGS}})
    elseif(GCC)
        set(PARADOX_CXX_DEBUG_FLAGS ${{PARADOX_GCC_DEBUG_FLAGS}})
    endif()
elseif(APPLE)
    if(XCode)
        set(PARADOX_SWIFT_DEBUG_FLAGS ${{PARADOX_XCODE_DEBUG_FLAGS}})
    elseif(Clang)
        set(PARADOX_CXX_DEBUG_FLAGS ${{PARADOX_CLANG_DEBUG_FLAGS}})
    elseif(GCC)
        set(PARADOX_CXX_DEBUG_FLAGS ${{PARADOX_GCC_DEBUG_FLAGS}})
    endif()
endif()

if(PARADOX_RELEASE)
    set(PARADOX_CXX_COMPILE_FLAGS ${{PARADOX_CXX_COMPILE_FLAGS}} ${{PARADOX_CXX_RELEASE_FLAGS}})
elseif(PARADOX_DEBUG)
    set(PARADOX_CXX_COMPILE_FLAGS ${{PARADOX_CXX_COMPILE_FLAGS}} ${{PARADOX_CXX_DEBUG_FLAGS}})
endif()

if(MSVC)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${{CMAKE_BUILD_TYPE}} "${{CMAKE_BINARY_DIR}}/../../paradox-static")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${{CMAKE_BINARY_DIR}}/../../paradox-static")
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${{CMAKE_BUILD_TYPE}} "${{CMAKE_BINARY_DIR}}/../../paradox-shared/${{CMAKE_BUILD_TYPE}}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${{CMAKE_BINARY_DIR}}/../../paradox-shared/${{CMAKE_BUILD_TYPE}}")
endif()

if(MSVC)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${{CMAKE_BUILD_TYPE}} "${{CMAKE_BINARY_DIR}}/../../paradox-static")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${{CMAKE_BINARY_DIR}}/../../paradox-static")
else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${{CMAKE_BUILD_TYPE}} "${{CMAKE_BINARY_DIR}}/../../paradox-static/${{CMAKE_BUILD_TYPE}}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${{CMAKE_BINARY_DIR}}/../../paradox-static/${{CMAKE_BUILD_TYPE}}")
endif()

if(MSVC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${{CMAKE_BUILD_TYPE}} "${{CMAKE_BINARY_DIR}}/../../paradox-shared")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${{CMAKE_BINARY_DIR}}/../../paradox-shared")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${{CMAKE_BUILD_TYPE}} "${{CMAKE_BINARY_DIR}}/../../paradox-shared/${{CMAKE_BUILD_TYPE}}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${{CMAKE_BINARY_DIR}}/../../paradox-shared/${{CMAKE_BUILD_TYPE}}")
endif()

# Sets up the general library options
# PARADOX_BUILD_LANG for single language build
option(PARADOX_BUILD_C_LIBS "Builds static|shared C libraries" ON)
option(PARADOX_BUILD_CXX_LIBS "Builds static|shared C++ libraries" ON)
option(PARADOX_BUILD_Swift_LIBS "Builds Swift libraries" ON)
option(PARADOX_BUILD_SHARED_LIBS "Builds shared libraries" ON)
if(PARADOX_BUILD_CXX_LIBS OR PARADOX_BUILD_C_LIBS OR PARADOX_BUILD_Swift_LIBS)
    set(PARADOX_BUILD_LIB ON)
endif()

option(PARADOX_BUILD_TESTS "Builds the test cases" OFF)
option(PARADOX_BUILD_DOCS "Builds the documentation" OFF)

if("${{PARADOX_BUILD_LANG}}" STREQUAL "C")
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS ON)
elseif("${{PARADOX_BUILD_LANG}}" STREQUAL "CXX")
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS ON)
elseif("${{PARADOX_BUILD_LANG}}" STREQUAL "Swift")
endif()

project(paradox-project ${{PARADOX_BUILD_LANG}})
"""
    for build_info in build_infos:
        if "paradox-library" == build_info.type or "library" == build_info.type:
            cmakefile_txt += f"""
if(PARADOX_BUILD_LIB)
    if(PARADOX_BUILD_C_LIBS)
        file(GLOB_RECURSE {build_info.prefix}_C_SRC {"/**.c ".join(build_info.c_sources) + "/**.c"})
        add_library({build_info.name}-c {build_info.library_type} ${{{build_info.prefix}_C_SRC}})
        set_target_properties({build_info.name}-c PROPERTIES OUTPUT_NAME "{build_info.name}")
        target_compile_options({build_info.name}-c PRIVATE ${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_FLAGS}})
        target_compile_definitions({build_info.name}-c PRIVATE ${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_DEFINITIONS}} {build_info.prefix}_BUILD_DLL {" ".join(build_info.c_compiler_definitions)})
        target_include_directories({build_info.name}-c PRIVATE {" ".join(build_info.c_includes)})

        target_link_directories({build_info.name}-c PRIVATE ${{CMAKE_LIBRARY_OUTPUT_DIRECTORY}} ${{CMAKE_ARCHIVE_OUTPUT_DIRECTORY}})
        target_link_libraries({build_info.name}-c PRIVATE {" ".join(build_info.c_libraries)})
        target_link_options({build_info.name}-c PRIVATE {" ".join(build_info.c_linker_options)})
    endif()
endif()
"""
            cmakefile_txt += f"""
if(PARADOX_BUILD_LIB)
    if(PARADOX_BUILD_CXX_LIBS)
        file(GLOB_RECURSE {build_info.prefix}_CXX_SRC {"/**.cpp ".join(build_info.cpp_sources) + "/**.cpp"})
        add_library({build_info.name}-cxx {build_info.library_type} ${{{build_info.prefix}_CXX_SRC}})
        set_target_properties({build_info.name}-cxx PROPERTIES OUTPUT_NAME "{build_info.name + ("-framework" if "paradox-library" == build_info.type else "")}")
        target_compile_options({build_info.name}-cxx PRIVATE ${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_FLAGS}})
        target_compile_definitions({build_info.name}-cxx PRIVATE ${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_DEFINITIONS}} {build_info.prefix}_BUILD_DLL {" ".join(build_info.cpp_compiler_definitions)})
        target_include_directories({build_info.name}-cxx PRIVATE {" ".join(build_info.cpp_includes)})

        target_link_directories({build_info.name}-cxx PRIVATE ${{CMAKE_LIBRARY_OUTPUT_DIRECTORY}} ${{CMAKE_ARCHIVE_OUTPUT_DIRECTORY}})
        target_link_libraries({build_info.name}-cxx PRIVATE {" ".join(build_info.cpp_libraries)})
        target_link_options({build_info.name}-cxx PRIVATE {" ".join(build_info.cpp_linker_options)})
    endif()
endif()
"""
        elif "paradox-application"  == build_info.type or "application" == build_info.type:
            cmakefile_txt += f"""
if(PARADOX_BUILD_LIB)
    if(PARADOX_BUILD_C_LIBS)
        file(GLOB_RECURSE {build_info.prefix}_C_SRC {"/**.c ".join(build_info.c_sources) + "/**.c"})
        add_executable({build_info.name}-c ${{{build_info.prefix}_C_SRC}})
        set_target_properties({build_info.name}-c PROPERTIES OUTPUT_NAME "{build_info.name}")
        target_compile_options({build_info.name}-c PRIVATE ${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_FLAGS}})
        target_compile_definitions({build_info.name}-c PRIVATE ${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_DEFINITIONS}} {build_info.prefix}_BUILD_DLL {" ".join(build_info.c_compiler_definitions)})
        target_include_directories({build_info.name}-c PRIVATE {" ".join(build_info.c_includes)})

        target_link_directories({build_info.name}-c PRIVATE ${{CMAKE_LIBRARY_OUTPUT_DIRECTORY}} ${{CMAKE_ARCHIVE_OUTPUT_DIRECTORY}})
        target_link_libraries({build_info.name}-c PRIVATE {" ".join(build_info.c_libraries)})
        target_link_options({build_info.name}-c PRIVATE {" ".join(build_info.c_linker_options)})
    endif()
endif()
"""
            cmakefile_txt += f"""
if(PARADOX_BUILD_LIB)
    if(PARADOX_BUILD_CXX_LIBS)
        file(GLOB_RECURSE {build_info.prefix}_CXX_SRC {"/**.cpp ".join(build_info.cpp_sources) + "/**.cpp"})
        add_executable({build_info.name}-cxx ${{{build_info.prefix}_CXX_SRC}})
        set_target_properties({build_info.name}-cxx PROPERTIES OUTPUT_NAME "{build_info.name}")
        target_compile_options({build_info.name}-cxx PRIVATE ${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_FLAGS}})
        target_compile_definitions({build_info.name}-cxx PRIVATE ${{PARADOX_${{PARADOX_BUILD_LANG}}_COMPILE_DEFINITIONS}} {build_info.prefix}_BUILD_DLL {" ".join(build_info.cpp_compiler_definitions)})
        target_include_directories({build_info.name}-cxx PRIVATE {" ".join(build_info.cpp_includes)})

        target_link_directories({build_info.name}-cxx PRIVATE ${{CMAKE_LIBRARY_OUTPUT_DIRECTORY}} ${{CMAKE_ARCHIVE_OUTPUT_DIRECTORY}})
        target_link_libraries({build_info.name}-cxx PRIVATE {" ".join(build_info.cpp_libraries)})
        target_link_options({build_info.name}-cxx PRIVATE {" ".join(build_info.cpp_linker_options)})
    endif()
endif()
"""
    with open('CMakeLists.txt', 'w') as cmakefile: cmakefile.write(cmakefile_txt)

load_project("build.json", True)
generate_makefile()
generate_cmakefile()