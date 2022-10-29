# Copyright 2022 Scott Roche

CC := g++
CPPFLAGS :=

TARGET := manta

SOURCE := src/main.cpp
CORE_SOURCE := src/core/log.cpp

SOURCE += $(CORE_SOURCE)

BUILD_PARAMS =

ifeq ($(MANTA_DEBUG), 1)
	BUILD_PARAMS += -DMANTA_DEBUG
endif

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CPPFLAGS) $(BUILD_PARAMS) -o $@ $^

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(BUILD_PARAMS) -c $< -o $@

clean:
	rm -f manta