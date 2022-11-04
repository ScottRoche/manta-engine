# Copyright 2022 Scott Roche

CC := g++
CPPFLAGS := -lX11 -lGL

INCLUDE := -Ivendor/glad/include

TARGET := manta

SOURCE := src/main.cpp
CORE_SOURCE := src/core/application.cpp \
	src/core/window.cpp \
	src/core/linux/x11-window.cpp \
	src/core/log.cpp

RENDERER_SOURCE := src/renderer/renderer.cpp \
	src/renderer/opengl/buffers.cpp \
	src/renderer/opengl/shader.cpp

SOURCE += $(CORE_SOURCE) $(RENDERER_SOURCE) vendor/glad/src/glad.c

BUILD_PARAMS =

ifeq ($(MANTA_DEBUG), 1)
	BUILD_PARAMS += -DMANTA_DEBUG
endif

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CPPFLAGS) $(INCLUDE) $(BUILD_PARAMS) -o $@ $^

%.o: %.c
	gcc $(CPPFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDE) $(BUILD_PARAMS) -c $< -o $@

clean:
	rm -f manta