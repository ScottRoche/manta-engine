# Copyright 2022 Scott Roche

CC = g++
CPPFLAGS =

SRC_DIR = src

TARGET=manta

$(TARGET):
	$(CC) $(CPPFLAGS) -o $(TARGET) $(SRC_DIR)/main.cpp
