project1:main.o avl.o entry.o hashtable.o
	g++ -o project1 -std=c++11 main.o avl.o entry.o hashtable.o -g3

avl_test:test_main.o avl.o entry.o
	g++ -o avl_test -std=c++11 test_main.o avl.o entry.o -g3

main.o:main.cpp
	g++ -c -std=c++11 main.cpp -g3

test_main.o:test_main.cpp
	g++ -c -std=c++11 test_main.cpp -g3

avl.o:avl.cpp avl.hpp
	g++ -c -std=c++11 avl.cpp -g3

entry.o:entry.cpp entry.hpp
	g++ -c -std=c++11 entry.cpp -g3

hashtable.o:hashtable.cpp hashtable.hpp
	g++ -c -std=c++11 hashtable.cpp -g3

clean:
	rm project1 main.o avl.o entry.o hashtable.o test_main.o avl_test