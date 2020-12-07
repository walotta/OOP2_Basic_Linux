# You may modify Makefile as your like
# but you should keep `make clean` and `make` works correct

PROGRAM = code

CXX = g++
CXXFLAGS = -IStanfordCPPLib -fvisibility-inlines-hidden -g -std=c++11

CPP_FILES = $(wildcard Basic/*.cpp)
H_FILES = $(wildcard Basic/*.h)

LDOPTIONS = -L.
LIB = -lStanfordCPPLib

all: $(PROGRAM) spl.jar

$(PROGRAM): $(CPP_FILES) $(H_FILES) libStanfordCPPLib.a
	$(CXX) -o $(PROGRAM) $(CXXFLAGS) $(LDOPTIONS) $(CPP_FILES) $(LIB)

libStanfordCPPLib.a:
	@rm -f libStanfordCPPLib.a
	(cd StanfordCPPLib; make all)
	ln -s StanfordCPPLib/libStanfordCPPLib.a .

spl.jar:
	ln -s StanfordCPPLib/spl.jar .

tidy:
	(cd StanfordCPPLib; make clean)
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM) spl.jar score
