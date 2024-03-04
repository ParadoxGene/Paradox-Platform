OS_NAME := # Windows | Linux | Macintosh
OS_ARCH := # AMD64 | IA32 | ARM

ifeq ($(OS),Windows_NT)
	OS_NAME := Windows
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		OS_ARCH := AMD64
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			OS_ARCH := AMD64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			OS_ARCH := IA32
		endif
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OS_NAME := Linux
	endif
	ifeq ($(UNAME_S),Darwin)
		OS_NAME := Macintosh
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OS_ARCH := AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		OS_ARCH := IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OS_ARCH := ARM
	endif
endif