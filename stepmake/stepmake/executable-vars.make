MODULE_LIBES =$(addprefix $(outdir)/../, $(addsuffix /$(outbase)/library.a, $(MODULE_LIBS)))
LOADLIBES = $(MODULE_LIBES) $(CONFIG_LIBS)

EXECUTABLE = $(outdir)/$(NAME)
EXECUTABLES = $(notdir $(EXECUTABLE))


