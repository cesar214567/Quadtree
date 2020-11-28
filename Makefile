all:
	g++ -std=c++17 aux.cpp -I /opt/X11/include -L /opt/X11/lib -lX11 -ljpeg -lz -pthread
	./a.out

clean:
	rm a.out compress
