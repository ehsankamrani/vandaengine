# The following variables need to be defined before including this file:
#   compiler       The name of the compiler to use
#   compilerFlags  Any additional flags to pass to the compiler
#   linker         The name of the linker to use
#   linkerFlags    Any additional flags to pass to the linker
#   sourcePath     The path containing the source files
#   sources        The source file names (a.cpp b.cpp c.cpp etc)
#   outPath        The path to write the output files to
#   tmpPath        The path to use for temporary files
#   libName        The name of the lib to output (e.g. 'pcre' will be output as libpcre.a)

sources := $(addprefix $(sourcePath), $(sources))
objPath := $(tmpPath)$(libName)/
objs := $(addsuffix .o, $(addprefix $(objPath), $(basename $(notdir $(sources)))))
lib := $(outPath)lib$(libName).a
sourceExtension := $(suffix $(firstword $(notdir $(sources))))

vpath %$(sourceExtension) $(sourcePath)

all: makeDirs $(objs) $(lib)

makeDirs:
	@mkdir -p $(outPath)
	@mkdir -p $(objPath)

$(objPath)%.o : %$(sourceExtension)
	$(compiler) $(compilerFlags) -o $@ $<

# ar rcs lib.a obj1 obj2 ...
$(lib) : $(objs)
	$(linker) $(linkerFlags) $(lib) $(objs)

clean:
	@rm -rf $(objPath)
	@rm -f $(lib)