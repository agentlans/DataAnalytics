CFLAGS = -O2
LDFLAGS = `pkg-config --libs eigen3` `pkg-config --libs gsl` `pkg-config --libs nlopt`
INCLUDE = -Iinclude/ `pkg-config --cflags eigen3` `pkg-config --cflags gsl` `pkg-config --cflags nlopt`

SRCS = $(wildcard src/*.cpp) # source files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(OBJS)
	$(CXX) -shared -o libanalytic.so $(OBJS) $(LDFLAGS)

$(OBJS): %.o: %.cpp
	$(CXX) -fPIC -c $(CFLAGS) $< -o $@ $(INCLUDE)

clean:
	rm -f src/*.o *.so

