project1:main.o avl.o entry.o hashtable.o clique.o utility.o parser.o parserlist.o
	g++ -o project1 -std=c++11 main.o avl.o entry.o hashtable.o clique.o utility.o parser.o parserlist.o -g3

avl_test:avl_test.o avl.o entry.o clique.o utility.o
	g++ -o avl_test -std=c++11 avl_test.o avl.o entry.o clique.o utility.o -g3

clique_test:entry.o clique.o clique_test.o utility.o
	g++ -o clique_test -std=c++11 entry.o clique.o clique_test.o utility.o -g3

entry_test: entry_test.o entry.o clique.o utility.o
	g++ -o entry_test -std=c++11 entry_test.o entry.o clique.o utility.o -g3

hashtable_test: hashtable_test.o hashtable.o avl.o entry.o clique.o utility.o
	g++ -o hashtable_test -std=c++11 hashtable_test.o avl.o entry.o hashtable.o clique.o utility.o -g3

main.o:main.cpp
	g++ -c -std=c++11 main.cpp -g3

avl.o:avl.cpp avl.hpp
	g++ -c -std=c++11 avl.cpp -g3

entry.o:entry.cpp entry.hpp
	g++ -c -std=c++11 entry.cpp -g3

hashtable.o:hashtable.cpp hashtable.hpp
	g++ -c -std=c++11 hashtable.cpp -g3

clique.o:clique.cpp clique.hpp
	g++ -c -std=c++11 clique.cpp -g3

utility.o:utility.cpp utility.hpp
	g++ -c -std=c++11 utility.cpp -g3

clique_test.o:clique_test.cpp
	g++ -c -std=c++11 clique_test.cpp -g3

avl_test.o:avl_test.cpp
	g++ -c -std=c++11 avl_test.cpp -g3

entry_test.o:entry_test.cpp
	g++ -c -std=c++11 entry_test.cpp -g3

hashtable_test.o:hashtable_test.cpp
	g++ -c -std=c++11 hashtable_test.cpp -g3

parser.o:parser.cpp parser.hpp
	g++ -c -std=c++11 parser.cpp -g3

parserlist.o:parserlist.cpp parserlist.hpp
	g++ -c -std=c++11 parserlist.cpp -g3

clean:
	rm project1 main.o avl.o entry.o hashtable.o test_main.o clique.o utility.o clique_test.o avl_test.o avl_test clique_test entry_test entry_test.o hashtable_test.o hashtable_test parserlist.o parser.o output.csv