all: references p1.pdf 

references: references.bib
	bibtex p1
	pdflatex p1.tex

p1.pdf: p1.tex p1.aux references.bib
	pdflatex p1.tex
