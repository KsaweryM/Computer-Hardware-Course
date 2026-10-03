# Builds every presentation in Lecture_*/ into builded_presentation/<lecture>.pdf.
#
#   make                                 build all presentations
#   make 4                               build a single presentation by its number
#   make 3 5 7                           build several presentations
#   make Lecture_4_Memory_and_Cache      ... or by its directory name
#   make rebuild-4                       build one presentation from scratch, even if nothing changed
#   make rebuild                         build all presentations from scratch
#   make list                            show the available lectures
#   make clean-4                         remove the auxiliary files and the PDF of one presentation
#   make clean                           remove auxiliary files and PDFs

LATEXMK   := latexmk
LATEXOPTS := -pdf -interaction=nonstopmode -halt-on-error -file-line-error

BUILD    := build
PDF      := builded_presentation
LECTURES := $(sort $(patsubst %/main.tex,%,$(wildcard Lecture_*/main.tex)))
PDFS     := $(LECTURES:%=$(PDF)/%.pdf)

# Lecture number, e.g. Lecture_4_Memory_and_Cache -> 4
number = $(word 2,$(subst _, ,$(1)))
NUMBERS := $(foreach l,$(LECTURES),$(call number,$(l)))

.PHONY: all clean list rebuild $(LECTURES) $(NUMBERS) $(NUMBERS:%=rebuild-%) $(NUMBERS:%=clean-%)

all: $(PDFS)

$(LECTURES): %: $(PDF)/%.pdf

$(foreach l,$(LECTURES),$(eval $(call number,$(l)): $(PDF)/$(l).pdf))

# clean-4 / rebuild-4: one presentation, by its number
$(foreach l,$(LECTURES),$(eval clean-$(call number,$(l)): ; rm -rf $(BUILD)/$(l) $(PDF)/$(l).pdf))
$(foreach n,$(NUMBERS),$(eval rebuild-$(n): ; $$(MAKE) clean-$(n) && $$(MAKE) $(n)))

rebuild:
	$(MAKE) clean
	$(MAKE) all

list:
	@$(foreach l,$(LECTURES),echo "  make $(call number,$(l))    $(l)";)

# Auxiliary files go to build/<lecture>/; latexmk runs inside the lecture directory.
$(PDF)/%.pdf: %/main.tex
	cd $* && $(LATEXMK) $(LATEXOPTS) -outdir=$(CURDIR)/$(BUILD)/$* main.tex
	@mkdir -p $(PDF)
	cp $(BUILD)/$*/main.pdf $@

clean:
	rm -rf $(BUILD) $(PDF)
