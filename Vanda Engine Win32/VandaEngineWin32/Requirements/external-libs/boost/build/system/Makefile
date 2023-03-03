# To build for Mac, just run 'make'. To build for PS3, run 'make platform=ps3'

platform := mac

ifneq ($(platform), ps3)
# Mac
compiler := g++
linker := ar
compilerFlags += -arch ppc -arch i386
outPath := mac/
else
# PS3
compiler := ppu-lv2-g++
linker := ppu-lv2-ar
compilerFlags += -DBOOST_NO_STD_LOCALE
outPath := ps3/
endif

sources := error_code.cpp
compilerFlags += -Wall -c -O2 -I../../../
linkerFlags += rcs
libName := boost_system
sourcePath := ../src/
tmpPath := $(outPath)tmp/

sources := $(addprefix $(sourcePath), $(sources))
objPath := $(tmpPath)$(libName)/
objs := $(addsuffix .o, $(addprefix $(objPath), $(basename $(notdir $(sources)))))
lib := $(outPath)lib$(libName).a

vpath %.cpp $(sourcePath)

all: makeDirs $(objs) $(lib)

makeDirs:
	@mkdir -p $(outPath)
	@mkdir -p $(objPath)

$(objPath)%.o : %.cpp
	$(compiler) $(compilerFlags) -o $@ $<

# ar rcs lib.a obj1 obj2 ...
$(lib) : $(objs)
	$(linker) $(linkerFlags) $(lib) $(objs)

clean:
	@rm -rf $(objPath)
	@rm -f $(lib)