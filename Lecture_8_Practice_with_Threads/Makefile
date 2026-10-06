# Builds every PDF of Lecture 8 next to its .tex file: all tasks in one PDF (Tasks.pdf),
# the solutions (Solutions/TaskK/TaskK_solution.pdf, kept locally) and the Makefile guide.
#   make          build the PDFs whose .tex, code or common.tex changed
#   make rebuild  build all PDFs from scratch
#   make clean    remove the auxiliary LaTeX files (the PDFs stay)
LATEXMK   := latexmk
LATEXOPTS := -pdf -interaction=nonstopmode -halt-on-error -file-line-error

TEX := Tasks.tex $(sort $(wildcard Solutions/Task*/Task*_solution.tex)) Makefile_guide/Makefile_guide.tex
PDF := $(TEX:.tex=.pdf)

.PHONY: all rebuild clean
.SECONDEXPANSION:

all: $(PDF)

# a PDF depends on its .tex, on common.tex and on the code files it shows
%.pdf: %.tex common.tex $$(wildcard $$(dir $$*)*.cpp $$(dir $$*)*.h $$(dir $$*)*.txt $$(dir $$*)examples/*/*)
	cd $(dir $<) && $(LATEXMK) $(LATEXOPTS) -outdir=build/tex $(notdir $<)
	cp $(dir $<)build/tex/$(notdir $@) $@

# Tasks.pdf shows the text and the code of every task
Tasks.pdf: $(wildcard Task*/*.tex Task*/*.cpp Task*/*.h Task*/*.txt)

rebuild:
	$(MAKE) clean
	$(MAKE) -B all

clean:
	rm -rf $(addsuffix build/tex,$(dir $(TEX)))
