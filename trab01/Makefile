# Makefile

BINDIR := bin
LIBDIR := lib

CCFLAGS := -pedantic

CC := g++ -g -std=c++11

# src/ (declarcaoes de funcoes, de calsses + codigo)
# main/ (programas principais)
# bin/ (temporarios, .o, .exe)
# lib/ (bibliotecas) biblioteca FC

# making library
# - static: .a
# - shareable: .so

VPATH = main:src

ROOTLIB := $(shell root-config --libs)
ROOTINC := $(shell root-config --incdir)

SRC := $(wildcard src/*.C)
OBJ := $(patsubst %.C, $(BINDIR)/%.o, $(notdir $(SRC)))
INC := $(wildcard src/*.h)

lib: $(LIBDIR)/libFC.a

trab01: $(BINDIR)/main_trab01.exe

$(LIBDIR)/libFC.a: $(OBJ) 
	@echo make lib...
	ar ruv $@ $^
	ranlib $@

$(BINDIR)/main_trab01.exe: $(BINDIR)/main_trab01.o $(LIBDIR)/libFC.a 
	@echo compiling and linking... 
	$(CC) -I src $< -o $@ -L lib -l FC $(ROOTLIB)

$(BINDIR)/%.o: %.C | $(INC)
	@echo compiling... $<
	$(CC) -I src -I $(ROOTINC) -c $< -o $@


######### clean

tilde := $(wildcard */*~) $(wildcard *~)
exe := $(wildcard */*.exe) $(wildcard *.exe)
obj := $(wildcard */*.o) $(wildcard *.o) $(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)

clean:
	@echo cleaning dir...
	rm -f $(exe) $(obj) $(tilde)
