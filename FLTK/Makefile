# We don't know what compiler to use to build fltk on this machine - but fltk-config does...
CXX = $(shell fltk-config --cxx)

# Set the flags for compiler: fltk-config knows the basic settings, then we can add our own...
CXXFLAGS = $(shell fltk-config --cxxflags) -Wall -O3 -I/other/include/paths...

# We don't know what libraries to link with: fltk-config does...
LINKFLTK = $(shell fltk-config --ldstaticflags)
LINKFLTK_GL = $(shell fltk-config --use-gl --ldstaticflags)
LINKFLTK_IMG = $(shell fltk-config --use-images --ldstaticflags)

# Possible steps to run after linking...
STRIP      = strip
POSTBUILD  = fltk-config --post # Required on OSX, does nothing on other platforms, so safe to call


# Define what your target application is called
all: output

# Define how to build the various object files...

classes.o: classes.cxx classes.h constants.h array.h # a C++ file
	$(CXX) -c $< $(CXXFLAGS)

main.o: main.cxx classes.cxx classes.h constants.h array.h # a C++ file
	$(CXX) -c $< $(CXXFLAGS)

# Now define how to link the final app - let's assume it needs image and OpenGL support
output: main.o classes.o
	$(CXX) -o $@ main.o classes.o $(LINKFLTK) $(LINKFLTK_IMG) #$(LINKFLTK_GL)
	$(STRIP) $@
	$(POSTBUILD) $@  # only required on OSX, but call it anyway for portability

# Clean files 
clean:
	rm *.o output
