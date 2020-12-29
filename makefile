project1:main.o avl.o entry.o hashtable.o clique.o utility.o parser.o parserlist.o anticlique.o dict.o logistic_regression.o sparse_matrix.o
	g++ -Wall -o project1 -std=c++11 main.o avl.o entry.o hashtable.o clique.o utility.o parser.o parserlist.o anticlique.o dict.o logistic_regression.o sparse_matrix.o -g3

unit_test: unit_test.o hashtable.o avl.o entry.o clique.o utility.o parserlist.o anticlique.o dict.o parser.o sparse_matrix.o logistic_regression.o
	g++ -Wall -o unit_test -std=c++11 unit_test.o avl.o entry.o hashtable.o clique.o utility.o parserlist.o anticlique.o dict.o parser.o sparse_matrix.o logistic_regression.o -g3 

dict:dict_main.o entry.o parser.o parserlist.o clique.o utility.o dict.o anticlique.o parser.o
	g++ -Wall -o dict -std=c++11 dict_main.o entry.o parser.o parserlist.o clique.o utility.o dict.o anticlique.o parser.o -g3

main.o:main.cpp
	g++ -Wall -c -std=c++11 main.cpp -g3

dict_main.o:dict_main.cpp
	g++ -Wall -c -std=c++11 dict_main.cpp -g3

avl.o:avl.cpp avl.hpp
	g++ -Wall -c -std=c++11 avl.cpp -g3

entry.o:entry.cpp entry.hpp
	g++ -Wall -c -std=c++11 entry.cpp -g3

hashtable.o:hashtable.cpp hashtable.hpp
	g++ -Wall -c -std=c++11 hashtable.cpp -g3

clique.o:clique.cpp clique.hpp
	g++ -Wall -c -std=c++11 clique.cpp -g3

anticlique.o:anticlique.cpp anticlique.hpp
	g++ -Wall -c -std=c++11 anticlique.cpp -g3

utility.o:utility.cpp utility.hpp
	g++ -Wall -c -std=c++11 utility.cpp -g3

unit_test.o:unit_test.cpp
	g++ -Wall -c -std=c++11 unit_test.cpp -g3

parser.o:parser.cpp parser.hpp
	g++ -Wall -c -std=c++11 parser.cpp -g3

parserlist.o:parserlist.cpp parserlist.hpp
	g++ -Wall -c -std=c++11 parserlist.cpp -g3

dict.o:dict.cpp dict.hpp
	g++ -Wall -c -std=c++11 dict.cpp -g3

logistic_regression.o:logistic_regression.cpp logistic_regression.hpp
	g++ -Wall -c -std=c++11 logistic_regression.cpp -g3

sparse_matrix.o:sparse_matrix.cpp sparse_matrix.hpp
	g++ -Wall -c -std=c++11 sparse_matrix.cpp -g3

clean:
	rm project1 main.o avl.o entry.o hashtable.o test_main.o clique.o utility.o unit_test.o unit_test parserlist.o parser.o output.csv anticlique.o anticlique dict dict_main.o dict.o logistic_regression.o sparse_matrix.o
