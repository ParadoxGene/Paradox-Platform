ifeq ($(OS),Windows_NT)
	OS_NAME_S := Win32
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		OS_NAME_P := AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            OS_NAME_P := AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			OS_NAME_P := IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        OS_NAME_S := Linux
    endif
    ifeq ($(UNAME_S),Darwin)
        OS_NAME_S := OSX
    endif

    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        OS_NAME_P := AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        OS_NAME_P := IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
		OS_NAME_P := ARM
    endif
endif

all:
ifeq ($(OS_NAME_S),Win32)
	cmake -G"Visual Studio 17" -B ./build/paradox-platform -S ./
	cmake --build ./build/paradox-platform
else ifeq ($(OS_NAME_S),Linux)
else ifeq ($(OS_NAME_S),OSX)
endif

build_tests:
ifeq ($(OS_NAME_S),Win32)
	cmake -G"Visual Studio 17" -B ./build/paradox-platform -S ./ -DPARADOX_PLATFORM_BUILD_TESTS=ON
	cmake --build ./build/paradox-platform
else ifeq ($(OS_NAME_S),Linux)
else ifeq ($(OS_NAME_S),OSX)
endif