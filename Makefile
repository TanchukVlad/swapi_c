TARGET := swapi
INCDIR := ./inc
SRCDIR := ./src
SRCS = $(TARGET).c
SRCS += takejson.c
SRCS += jsoninf.c
LIBS = gtk+-3.0
BUILDDIR := .build

CFLAGS = -O2 -std=gnu18 -Wall -Wextra -Wpedantic
CFLAGS += $(shell pkg-config --cflags $(LIBS))
LDFLAGS = -ljson-c -lcurl $(shell pkg-config --libs $(LIBS))

CC := gcc

.PHONY: all clean tidy

all: $(TARGET)

$(TARGET): $(BUILDDIR)/$(TARGET)
	cp $< $@

$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRCS:.c=.o))
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(addprefix $(SRCDIR)/,%.c) $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(addprefix -I,$(INCDIR)) -c $< -o $@

$(BUILDDIR): 
	mkdir -p $@

clean:
	@echo Cleaning up
	-rm -rf $(BUILDDIR)/*.o

tidy: clean
	-rm -f $(BUILDDIR)/$(TARGET)



