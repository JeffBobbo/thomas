include make.objects

# general compiler settings
CPPFLAGS=-DGLM_FORCE_RADIANS -Iinclude/engine -Iexternal
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++11

debug: CXXFLAGS+=-O0 -ggdb
debug: all

# compile for release, optimisations, no debug etc
release: CPPFLAGS+=-DNDEBUG
release: CXXFLAGS+=-O3
release: all

all: $(ENGINE) $(OBJECT) $(GUI) $(UTIL) $(VISAGE) $(EXTERNAL)
	ar rcs libengine.a $(ENGINE) $(OBJECT) $(GUI) $(UTIL) $(VISAGE) $(EXTERNAL)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

docs:
	doxygen doxygen.config

clean:
	$(warning Cleaning...)
	@$(RM) $(ENGINE) $(OBJECT) $(GUI) $(UTIL) $(VISAGE) libengine.a

.PHONY: debug release all docs clean

