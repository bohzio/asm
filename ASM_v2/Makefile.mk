COMPILATORE= gcc-5 -m32
CODICE= controller.c genera_fascia.s contatore.s
OGGETTO= controller.o genera_fascia.o contatore.o
DEBUG= -g
ESEGUIBILE= controller

# In questa parte viene creato il file eseguibile dai file oggetto (con aggiunta di -g per poter utilizzare il debugger)
$(ESEGUIBILE): $(OGGETTO)
	$(COMPILATORE) $(DEBUG) $(OGGETTO) -o $(ESEGUIBILE)
# -c è la flag da aggiungere per ottenere i file oggetto dai "file codice" con gcc, ed è uguale sia per assembly che per c
$(OGGETTO): $(CODICE)
	$(COMPILATORE) -c controller.c -o controller.o
	$(COMPILATORE) -c genera_fascia.s -o genera_fascia.o
	$(COMPILATORE) -c contatore.s -o contatore.o
clean:
	rm -f $(ESEGUIBILE) core

