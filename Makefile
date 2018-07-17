OBJ = main.o HSDArc.o charDataExtract.o

FEHUnitDataExtractor: $(OBJ)
	g++ -o FEHUnitDataExtractor $(OBJ) -static

-include dependencies

.PHONY: depend
depend:
	g++ -MM *.cpp > dependencies

