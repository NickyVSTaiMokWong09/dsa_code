#声明一个变量
objects = main.o

#第一个目标文件
edit : $(objects)
	clang++ -o edit $(objects)

main.o : vector.h main.cpp


.PHONY : clean
clean :
	-rm edit $(objects)
