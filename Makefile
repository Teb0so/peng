# -------- Config --------
CC      := gcc
TARGET  := peng
SRC     := main.c game.c
OBJ     := $(SRC:.c=.o)

# Raylib paths
RAYLIB_DIR := raylib
RAYLIB_INC := $(RAYLIB_DIR)/src
RAYLIB_LIB := $(RAYLIB_INC)/libraylib.a

# Compiler / linker flags
CFLAGS  := -Wall -Wextra -O2 -I$(RAYLIB_INC)
LDFLAGS :=
LDLIBS  := -lm -lpthread -ldl -lrt -lX11

# -------- Rules --------
all: $(TARGET)

$(TARGET): $(OBJ) $(RAYLIB_LIB)
	$(CC) $(OBJ) $(RAYLIB_LIB) -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

