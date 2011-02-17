CFLAGS += -O2 -Wall
LDFLAGS += -s

tactile: tactile.o

install: tactile
	install tactile $(DESTDIR)/usr/bin
	install -m755 demo.py $(DESTDIR)/usr/bin/tactile-demo.py
	install -m644 tactile.sudoers $(DESTDIR)/etc/sudoers.d

clean:
	rm -f tactile tactile.o
