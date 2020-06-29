
trunk_path = $(shell pwd | sed "s/\/src.*//")
include $(trunk_path)/make.rules
TARGET_DIR_NAME=src

CUR_PATH = $(trunk_path)/$(TARGET_DIR_NAME)
CPPS := $(wildcard $(CUR_PATH)/*.cc)
OBJS := $(patsubst $(CUR_PATH)/%.cc, ./%.o, $(CPPS))

TARGETS = libflynet.so
#TARGETS = flynet

INC = -I ../inc

all:$(TARGETS)

$(TARGETS) : $(OBJS)
	$(CXX) $(OBJS) $(CFLAGS) $(INC) -shared -o $(TARGETS) 
#	$(CXX) $(OBJS) $(CFLAGS) $(INC) -o $(TARGETS) 

%.o : $(CUR_PATH)/%.cc
	$(CXX) $(CFLAGS) $(INC) -c $< -o $@


clean:
	@rm -f *.d *.o $(TARGETS)
