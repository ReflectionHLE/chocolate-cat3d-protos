DEBUG=0
BUILDASCPP=0
BINPREFIX=

ifeq ($(BUILDASCPP), 1)
	CXX=$(BINPREFIX)g++
else
	CXX=$(BINPREFIX)gcc
endif

STRIPBIN=$(BINPREFIX)strip
SDLCONFIG=sdl2-config
SRC=src
RSRC=rsrc
OBJ=obj

OBJECTS=$(OBJ)/id_ca.o \
	$(OBJ)/id_in.o \
	$(OBJ)/id_mm.o \
	$(OBJ)/id_rf_a.o \
	$(OBJ)/id_rf.o \
	$(OBJ)/id_sd.o \
	$(OBJ)/id_us_1.o \
	$(OBJ)/id_us_2.o \
	$(OBJ)/id_us_a.o \
	$(OBJ)/id_vw_a.o \
	$(OBJ)/id_vw_ac.o \
	$(OBJ)/id_vw.o \
	$(OBJ)/be_sdl.o \
	$(OBJ)/be_sdl_audio_timer.o \
	$(OBJ)/be_sdl_graphics.o \
	$(OBJ)/dbopl.o

INTCXXFLAGS=

ifeq ($(DEBUG),1)
	INTCXXFLAGS+= -g -DCHOCOLATE_KEEN_CONFIG_DEBUG
else
	INTCXXFLAGS+= -O2
endif

INTCXXFLAGS+= -I$(SRC) `$(SDLCONFIG) --cflags`
#We need -lm for dbopl
INTLDFLAGS=`$(SDLCONFIG) --libs` -lm

ifeq ($(BUILDASCPP), 0)
	INTCXXFLAGS+= -std=c99
endif

ifeq ($(PLATFORM), WINDOWS)
	EXE_EXT=.exe
endif

EXE_PATH=chocolate-cat3d$(EXE_EXT)

.PHONY: all game clean veryclean

all: game

game: $(EXE_PATH)

$(EXE_PATH): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(INTLDFLAGS) -o $@
ifeq ($(DEBUG),0)
	$(STRIPBIN) $(EXE_PATH)
endif

$(EXE_PATH): $(OBJECTS)

$(OBJ)/dbopl.o: $(SRC)/opl/dbopl.c
	$(CXX) -c $(INTCXXFLAGS) $(CXXFLAGS) $< -o $@
$(OBJ)/%.o: $(SRC)/%.c
	$(CXX) -c $(INTCXXFLAGS) $(CXXFLAGS) $< -o $@
veryclean:
	-rm -f $(OBJ)/* chocolate-cat3d$(EXE_EXT)
clean:
	-rm -f $(EXE_PATH) $(OBJECTS)
