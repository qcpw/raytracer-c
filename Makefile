### Raytrace makefile - modified from:
# CSE170 glutapp makefile v2.1 - M. Kallmann 2009

SOURCES = image.cpp view.cpp testview.cpp vec.cpp object.cpp sphere.cpp raytrace.cpp plane.cpp triangle.cpp model.cpp #triModel.cpp #new_ray.cpp
DEPENDS = $(SOURCES:.cpp=.d)
OBJECTS = $(SOURCES:.cpp=.o)
OS = $(shell uname) # For Mac OS detection (by Rolando Yanez)
PROGRAM = testView

#######################################################################

OPTFLAGS = -g
CC       = g++
CFLAGS   = -Wall -Wno-format $(OPTFLAGS)

ifeq ($(OS),Darwin)
	LDFLAGS = -framework GLUT -framework OpenGL
else
	LDFLAGS = -lGLU -lglut
endif

#######################################################################

all: $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJECTS) $(DEPENDS)
	$(RM) $(PROGRAM)
	$(RM) *~

check-syntax:
	$(CC) -o /dev/null -S ${CHK_SOURCES}
#######################################################################

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< > $@

#######################################################################

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

#######################################################################




