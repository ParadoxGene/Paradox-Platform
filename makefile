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

release:
ifeq ($(OS_NAME_S),Win32)
	cmake -G"Visual Studio 17" -B ./build/paradox-platform -S ./ -DCMAKE_BUILD_TYPE=Release
	cmake --build ./build/paradox-platform --config Release
else ifeq ($(OS_NAME_S),Linux)
	cmake -G"Unix Makefiles" -B ./build/paradox-platform -S ./ -DCMAKE_BUILD_TYPE=Release
	cmake --build ./build/paradox-platform --config Release
else ifeq ($(OS_NAME_S),OSX)
	cmake -G"Xcode" -B ./build/paradox-platform -S ./ -DCMAKE_BUILD_TYPE=Release
	cmake --build ./build/paradox-platform --config Release
endif

debug:
ifeq ($(OS_NAME_S),Win32)
	cmake -G"Visual Studio 17" -B ./build/paradox-platform -S ./ -DCMAKE_BUILD_TYPE=Debug
	cmake --build ./build/paradox-platform --config Debug
else ifeq ($(OS_NAME_S),Linux)
	cmake -G"Unix Makefiles" -B ./build/paradox-platform -S ./ -DCMAKE_BUILD_TYPE=Debug
	cmake --build ./build/paradox-platform --config Debug
else ifeq ($(OS_NAME_S),OSX)
	cmake -G"Xcode" -B ./build/paradox-platform -S ./ -DCMAKE_BUILD_TYPE=Debug
	cmake --build ./build/paradox-platform --config Debug
endif

build_tests:
ifeq ($(OS_NAME_S),Win32)
	cmake -G"Visual Studio 17" -B ./build/paradox-platform -S ./ -DCMAKE_BUILD_TYPE=Debug -DPARADOX_PLATFORM_BUILD_TESTS=ON
	cmake --build ./build/paradox-platform --config Debug
else ifeq ($(OS_NAME_S),Linux)
	cmake -G"Unix Makefiles" -B ./build/paradox-platform -S ./ -DCMAKE_BUILD_TYPE=Debug -DPARADOX_PLATFORM_BUILD_TESTS=ON
	cmake --build ./build/paradox-platform --config Debug
else ifeq ($(OS_NAME_S),OSX)
endif