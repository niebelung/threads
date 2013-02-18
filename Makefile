# .RECIPEPREFIX = >
threads : threads.o lib_threads.o
	gcc -o $@ -lpthread threads.o lib_threads.o
threads.o : threads.c lib_threads.c lib_threads.h
	gcc -c  $<
lib_threads.o : lib_threads.c lib_threads.h
	gcc -c  $<
clean :
	rm -fr threads threads.o lib_threads.o