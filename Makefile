IDIR = include
SDIR = source
ODIR = $(SDIR)/objects
CXX = g++
CXXFLAGS = -I$(IDIR) -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

_DEPS = level.hpp character.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(patsubst %.hpp,%.o,$(_DEPS)) main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi
	$(CXX) -g -c -o $@ $< $(CXXFLAGS)

PacMan: $(OBJ)
	$(CXX) -g -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -fr $(ODIR) PacMan.exe