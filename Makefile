NAME = main

TARGET = $(NAME).dvi
DVITARGET = $(NAME).dvi
PDFTARGET = $(NAME).pdf
PDFTARGET_W = $(NAME)_weibo.pdf
SRC = $(wildcard *.tex)
PT = xelatex
LT = latex
TOC = $(NAME).toc
AUX = $(NAME).aux
BBL = $(NAME).bbl


$(PDFTARGET) : $(NAME).tex $(SRC) 
	$(PT) $<
$(NAME)_weibo.tex : $(NAME).tex $(SRC)
	sed -e 's/\( \)\\myauthor/\1weibo:@Fanchy\\_Lee/' $(NAME).tex > $(NAME)_weibo.tex
$(PDFTARGET_W) : $(NAME)_weibo.tex  $(SRC)
	$(PT) $< 
clean : 
	rm -f *.log *.out *.pdf *.dvi *.aux $(NAME)_weibo.tex 
%.dvi : %.tex
	$(LT) $<
%.pdf : %.tex
	$(PT) $<
s : $(PDFTARGET)
	if [ -e $(NAME).pdf ] ;then	evince $(NAME).pdf ;	fi
	if [ -e $(NAME).dvi ] ;then 	evince $(NAME).dvi ;	fi
sw: $(PDFTARGET_W)
	if [ -e $(NAME)_weibo.pdf ] ;then     evince $(NAME)_weibo.pdf ;    fi
	if [ -e $(NAME)_weibo.dvi ] ;then     evince $(NAME)_weibo.dvi ;    fi
$(TOC) : $(NAME).tex  $(SRC)
	$(PT) $<
	rm -f $(PDFTARGET)
$(AUX) : $(NAME).tex  $(SRC)
	$(PT) $<
	rm -f $(PDFTARGET)
$(BBL) : $(AUX)
	bibtex $<
ss : 
	if [ -e $(NAME).pdf ] ;then     evince $(NAME).pdf ;    fi
	if [ -e $(NAME).dvi ] ;then     evince $(NAME).dvi ;    fi
