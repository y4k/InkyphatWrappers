Q ?=@ # Helper to make commands silent

# Compiler
CC := g++ -std=c++11 
DEBUG := -O2 -DDEBUG

MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
OUTNAME := $(notdir $(patsubst %/,%,$(dir $(MKFILE_PATH))))

EXEDIR := bin
SRCDIR := src
BUILDDIR := build
TESTSRCDIR := test
HEADERS := include/*hpp
TARGET := lib/lib$(OUTNAME).so

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -Wall -g -DASIO_STANDALONE
INC := -I include
LIB := -lpthread -lwiringPi
SHARED_COMPILE := -fPIC $(CFLAGS)
SHARED_LIB := -shared $(LIB)

TESTSOURCES := $(shell find $(TESTSRCDIR) -type f -name *.$(SRCEXT))
TEST_OUT := $(patsubst $(TESTSRCDIR)/%,$(EXEDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.out))

$(TARGET) : $(OBJECTS)
	$Q echo "Building and linking $(OUTNAME)..."
	$Q echo $(OBJECTS)
	$Q echo "$(CC) $^ -o $(TARGET) $(SHARED_LIB)"; $(CC) $^ -o $(TARGET) $(SHARED_LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$Q echo "Compiling $@..."
	$Q mkdir -p $(BUILDDIR)
	$Q @echo " $(CC) $(SHARED_COMPILE) $(INC) -c -o $@ $<"; $(CC) $(SHARED_COMPILE) $(INC) -c -o $@ $<

.PHONY: clean
clean:
	$Q echo " Cleaning $(OUTNAME)..."
	$Q echo " $(RM) -r $(BUILDDIR) $(TARGET)";$(RM) -r $(BUILDDIR) $(TARGET)
	$Q echo " $(RM) $(EXEDIR)/*";$(RM) $(EXEDIR)/*

.PHONY: tests
tests: $(TEST_OUT)

$(EXEDIR)/%.out: $(TESTSRCDIR)/%.$(SRCEXT) $(TARGET)
	$(CC) $(CFLAGS) $^ $(INC) $(LIB) $(TARGET) -o $@