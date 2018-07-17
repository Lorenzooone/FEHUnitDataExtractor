OBJ = main.o HSDArc.o charDataExtract.o

FEHUnitDataExtractor: $(OBJ)
	g++ -o FEHUnitDataExtractor $(OBJ)

-include dependencies

.PHONY: depend
depend:
	g++ -MM *.cpp > dependencies

