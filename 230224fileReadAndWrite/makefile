readConfigInfo:readConfigInfo.o
	gcc 06readConfigInfo.o -o readConfigInfo
readConfigInfo.o:readConfigInfo.c
	gcc -c readConfigInfo.c -o readConfigInfo.o

sortFile:sortFile.o
	gcc sortFile.o -o sortFile
sortFile.o:05sortFile.c
	gcc -c 05sortFile.c -o sortFile.o

calFile:calFile.o
	gcc calFile.o -o calFile
calFile.o:04calFile.c
	gcc -c 04calFile.c -o calFile.o

myClock:myClock.o
	gcc myClock.o -o myClock
myClock.o:02myClock.c
	gcc -c 02myClock.c -o myClock.o


myCp:myCp.o
	gcc myCp.o -o myCp
myCp.o:03myCp.c
	gcc -c 03myCp.c -o myCp.o

myCat:myCat.o
	gcc myCat.o -o myCat
myCat.o:01myCat.c
	gcc -c 01myCat.c -o myCat.o

clear:
	rm -rf *.o
