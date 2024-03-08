include config/make/operating-system.mk

ifeq ($(OS_NAME),Windows)
define newline
@ echo.
endef
else ifeq ($(OS_NAME),Linux)
define newline
@ echo 
endef
else ifeq ($(OS_NAME),Macintosh)
define newline
@ echo 
endef
endif