CXX = clang++
TARGET = hcn
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

ifdef debug
    CXXFLAGS = -Weverything -Wno-c++98-compat-pedantic -Wno-exit-time-destructors -Wno-padded
else
    CXXFLAGS = -Wall -Wextra -O2
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

$(foreach SRC, $(SRCS), $(eval $(subst \,,$(shell $(CXX) -MM $(SRC)))))

clean:
	@$(RM) $(TARGET) $(OBJS)
