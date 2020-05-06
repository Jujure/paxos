FLAGS=-pdf -shell-escape

.PHONY: all clean

all: view

pdf:
	latexmk ${FLAGS} main.tex

view: pdf
	evince main.pdf

clean:
	rm -rf *.aux *.log *.nav *.toc *.snm *.pdf *.out *.pyg _minted* *.fls *.fdb_latexmk
