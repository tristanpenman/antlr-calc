calculator: calculator.cpp generated
	g++ -o calculator -lantlr4-runtime -std=c++11 -I /usr/local/include/antlr4-runtime calculator.cpp generated/*.cpp

calculator-static: calculator.cpp generated
	g++ -o calculator /usr/local/lib/libantlr4-runtime.a -std=c++11 -I /usr/local/include/antlr4-runtime calculator.cpp generated/*.cpp

generated: Expression.g4
	rm -rf generated
	antlr -Dlanguage=Cpp -o generated Expression.g4
