calculator: calculator.cpp generated *.h
	g++ -o calculator -lantlr4-runtime -std=c++11 -I /usr/local/include/antlr4-runtime calculator.cpp generated/*.cpp

calculator-static: calculator.cpp generated *.h
	g++ -o calculator-static /usr/local/lib/libantlr4-runtime.a -std=c++11 -I /usr/local/include/antlr4-runtime calculator.cpp generated/*.cpp

ast: ast.cpp generated
	g++ -o ast -lantlr4-runtime -std=c++11 -I /usr/local/include/antlr4-runtime ast.cpp generated/*.cpp

generated: Expression.g4
	rm -rf generated
	antlr -Dlanguage=Cpp -visitor -o generated Expression.g4
