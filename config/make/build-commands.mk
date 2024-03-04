include config/make/operating-system.mk

word-hyphen = $(word $2,$(subst -, ,$1))
build-compiler-part = $(strip $(call word-hyphen,$@,1))
build-config-part = $(strip $(call word-hyphen,$@,2))
build-lang-part = $(strip $(call word-hyphen,$@,3))
get-cmake-generator = $(strip \
	$(if $(filter $(call build-compiler-part),msvc),"Visual Studio 17 2022")\
	$(if $(filter $(call build-compiler-part),xcode),"Xcode")\
	$(if $(filter $(call build-compiler-part),gcc),"Unix Makefiles")\
	$(if $(filter $(call build-compiler-part),clang),"Unix Makefiles"))
get-cmake-c-compiler = $(strip \
	$(if $(filter $(call build-compiler-part),msvc),cl)\
	$(if $(filter $(call build-compiler-part),gcc),gcc)\
	$(if $(filter $(call build-compiler-part),clang),clang))
get-cmake-cxx-compiler= $(strip \
	$(if $(filter $(call build-compiler-part),msvc),cl)\
	$(if $(filter $(call build-compiler-part),gcc),g++)\
	$(if $(filter $(call build-compiler-part),clang),clang++))
get-cmake-config-type =\
	$(if $(filter $(call build-config-part),debug),Debug)\
	$(if $(filter $(call build-config-part),release),Release)
