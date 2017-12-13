include make.objects

# general compiler settings
CPPFLAGS=-Iexternal/glfw-3.2.1/include
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++11 -DGLM_FORCE_RADIANS
#LDFLAGS=-L/usr/lib/nvidia-304/ -Lexternal/glfw-3.2.1/build/nix/src -Lexternal/SOIL/lib -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -ldl -pthread -lSOIL

debug: CXXFLAGS+=-O0 -ggdb
debug: all

# compile for release, optimisations, no debug etc
release: CPPFLAGS+=-DNDEBUG
release: CXXFLAGS+=-O3
release: all

all: $(ENGINE) $(OBJECT) $(GUI) $(UTIL) $(VISAGE)
	ar rcs libengine.a $(ENGINE) $(OBJECT) $(GUI) $(UTIL) $(VISAGE)
#	$(CXX) $(CXXFLAGS) $(ENGINE) $(OBJECT) $(GUI) $(UTIL) $(VISAGE) -o $(EXEC) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

docs:
	doxygen doxygen.config

clean:
	$(warning Cleaning...)
	@$(RM) $(ENGINE) $(OBJECT) $(GUI) $(UTIL) $(VISAGE) libengine.a

.PHONY: debug release all docs clean

