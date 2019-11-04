# call make all/clean in 'src' subdirectory
TARGETS=all clean

$(TARGETS): src

src:
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all src

