# Common variables
compilerFlags += -c -O2 -I./ -I../ -DHAVE_CONFIG_H
linker := ppu-lv2-ar
linkerFlags += rcs
sourcePath := ../
outPath := ./
tmpPath := ./tmp/

# By default, export all variables to the sub-makes
export

# Build libpcre.a and libpcrecpp.a
all:
	$(MAKE) -fpcre.mk $(MAKECMDGOALS)
	$(MAKE) -fpcrecpp.mk $(MAKECMDGOALS)

clean:
	$(MAKE) -fpcre.mk $(MAKECMDGOALS)
	$(MAKE) -fpcrecpp.mk $(MAKECMDGOALS)
	@rm -rf $(tmpPath)