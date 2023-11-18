CC = gcc
SRCDIR = src
BUILD_DIR = build
EXECUTABLE = shinoasm # Specify the name of your executable here

CFLAGS = -Wall -Wextra -Werror -g

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all clean run

all: $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$^
