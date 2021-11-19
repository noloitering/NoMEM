# -- CONFIGURATION --
# paths
EXE_NAME ?= client
DESTDIR ?= ./
SRC ?= ../main.cpp
OBJS = $(patsubst %.c, %.o, $(SRC))

# compiler
CC = g++
CFLAGS += -Wall -std=c++17
MAKE = make
PLATFORM ?= PLATFORM_DESKTOP
# DEBUG or RELEASE
BUILD_MODE ?= RELEASE

# libraries
ENET_INSTALL_PATH ?= ../../../../../include/enet-1.3.17
ENET_HEADERS ?= -I$(ENET_INSTALL_PATH)/include
# STATIC (.a/.lib) or SHARED (.so/.dll)
ENET_LIBTYPE ?= STATIC

RAYLIB_INSTALL_PATH ?= ../../../../../include/raylib
RAYLIB_SRC ?= $(RAYLIB_INSTALL_PATH)/src
RAYLIB_HEADERS ?= -I$(RAYLIB_SRC) -I$(RAYLIB_SRC)/external -I$(RAYLIB_SRC)/extras
RAYLIB_LIBS ?= -L$(RAYLIB_INSTALL_PATH) -L$(RAYLIB_SRC)
RAYLIB_LIBTYPE ?= STATIC

LIBPATHS = -L$(ENET_INSTALL_PATH) $(RAYLIB_LIBS)
INCLUDES = $(ENET_HEADERS) $(RAYLIB_HEADERS)
LIBFLAGS = -lenet -lraylib
# -- END OF CONFIGURATION --

# -- SCRIPTS --
# Determine PLATFORM_OS in case PLATFORM_DESKTOP selected
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    # No uname.exe on MinGW!, but OS=Windows_NT on Windows!
    # ifeq ($(UNAME),Msys) -> Windows
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS=WINDOWS
    else
        UNAMEOS=$(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS=LINUX
        endif
        ifeq ($(UNAMEOS),FreeBSD)
            PLATFORM_OS=BSD
        endif
        ifeq ($(UNAMEOS),OpenBSD)
            PLATFORM_OS=BSD
        endif
        ifeq ($(UNAMEOS),NetBSD)
            PLATFORM_OS=BSD
        endif
        ifeq ($(UNAMEOS),DragonFly)
            PLATFORM_OS=BSD
        endif
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS=OSX
        endif
    endif
endif
ifeq ($(PLATFORM),PLATFORM_RPI)
    UNAMEOS=$(shell uname)
    ifeq ($(UNAMEOS),Linux)
        PLATFORM_OS=LINUX
    endif
endif

ifeq ($(PLATFORM_OS),WINDOWS)
	LIBFLAGS += -lopengl32 -lgdi32 -static -lpthread -lws2_32 -lwinmm
	RAYLIB_LIBS += $(RAYLIB_SRC)/raylib.rc.data
	MAKE = mingw32-make
endif

ifeq ($(PLATFORM_OS),LINUX)
	LIBFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
	RAYLIB_HEADERS += /usr/local/include
	RAYLIB_LIBS += -L/usr/local/lib
endif
# -- END OF SCRIPTS --


# -- TARGET ENTRY --
# NOTE: We call this Makefile target or Makefile.Android target
all:
	$(MAKE) $(EXE_NAME)
	
#compile client
$(EXE_NAME): $(OBJS)
	$(CC) -o $(DESTDIR)/$(EXE_NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBPATHS) $(LIBFLAGS) -D$(PLATFORM)

# Compile source files
%.o: %.cpp
	$(CC) -c $^

# Clean everything
clean:
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
		del $(DESTDIR)/*.o $(DESTDIR)/*.exe /s
    endif
    ifeq ($(PLATFORM_OS),LINUX)
	find $(DESTDIR) -type f -executable | xargs file -i | grep -E 'x-object|x-archive|x-sharedlib|x-executable|x-pie-executable' | rev | cut -d ':' -f 2- | rev | xargs rm -fv
    endif
    ifeq ($(PLATFORM_OS),OSX)
		find $(DESTDIR) -type f -perm +ugo+x -delete
		rm -f *.o
    endif
endif
ifeq ($(PLATFORM),PLATFORM_RPI)
	find $(DESTDIR) -type f -executable -delete
	rm -fv *.o
endif
ifeq ($(PLATFORM),PLATFORM_WEB)
	del $(DESTDIR)/.o $(DESTDIR)/.html $(DESTDIR)/.js
endif
	@echo Cleaning done