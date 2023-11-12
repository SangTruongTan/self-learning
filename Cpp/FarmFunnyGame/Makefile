#######################################
# Build Path
#######################################
BUILD_DIR = build

#######################################
# Target
#######################################
TARGET = $(BUILD_DIR)/FarmFunnyGame.o

#######################################
# building variables
#######################################
# optimization
OPT = -O2
# Cxx standard version
CXX_GNU = -std=gnu++11

#######################################
# source
#######################################
SRCS += src/Animal.cxx
SRCS += src/Chicken.cxx
SRCS += src/Logger.cxx
SRCS += src/TimeManager.cxx
SRCS += src/MacDonald.cxx
SRCS += src/main.cxx

#######################################
# include
#######################################
INC += -Iinclude/

#######################################
# LIBS
#######################################
LIBS += -ldlt

#######################################
# LDFLAGS
#######################################

#######################################
# CXXFLAGS
#######################################
CXXFLAGS += $(OPT)
CXXFLAGS += $(CXX_GNU)
CXXFLAGS += -Wall
CXXFLAGS += -pthread
CXXFLAGS += $(INC)

#######################################
# OBJECTS
#######################################
# OBJS = $(SRCS:.cxx=.o)
OBJS = $(patsubst %.cxx,$(BUILD_DIR)/%.o,$(SRCS))

#######################################
# build the application
#######################################
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS) $(LDFLAGS)

# Compile source files to object files in the build directory
$(BUILD_DIR)/%.o: %.cxx | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/src

#######################################
# clean up
#######################################
clean:
	rm -rf $(BUILD_DIR)
