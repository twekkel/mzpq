CXX=g++
CPPFLAGS+=-Dunix
#CXXFLAGS+=-O3 -s -march=native -std=c++17 -Wall -Wpedantic
CXXFLAGS+=-O3 -s -march=native
PREFIX=/usr/local
BINDIR=$(PREFIX)/bin

all: mzpq

libzpaq.o: libzpaq.cpp libzpaq.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c libzpaq.cpp

mzpq.o: mzpq.cpp libzpaq.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c mzpq.cpp

mzpq: mzpq.o libzpaq.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ mzpq.o libzpaq.o 

install: mzpq
	install -m 0755 -d $(DESTDIR)$(BINDIR)
	install -m 0755 mzpq $(DESTDIR)$(BINDIR)
	ln -sf $(DESTDIR)$(BINDIR)/mzpq $(DESTDIR)$(BINDIR)/mzpqcat
	ln -sf $(DESTDIR)$(BINDIR)/mzpq $(DESTDIR)$(BINDIR)/unmzpq

clean:
	rm -f mzpq.o libzpaq.o mzpq
