.SUFFIXES: .tex .dvi .pdf

all: Report2.pdf

clean:
	rm -rf *.aux *.dvi *.log

.tex.dvi:
	platex $<
	platex $<

.dvi.pdf:
	dvipdfmx $<
	rm -rf *.aux *.dvi *.log
	open $@

sample.pdf: sample.tex sample.dvi
