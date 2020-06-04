CC=g++
CFLAGS=-Wall

all: bin/obj bin/sim

bin/sim: bin/obj/main.o bin/obj/transfer.o bin/obj/sender.o bin/obj/receiver.o
	$(CC) -o $@ $^ $(CFLAGS) -lrt -pthread -lconfig++

bin/obj:
	echo here
	mkdir -p $@

run_du: 
	cd bin; ./sim receiver


run_ru: 
	cd bin; ./sim sender

clean:
	rm -rf bin/obj
	rm sim

# Main
bin/obj/main.o: module/main/src/main.cpp module/packet/transfer.hpp module/packet/sender.hpp module/packet/receiver.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

# Packet
bin/obj/transfer.o: module/packet/src/transfer.cpp module/packet/transfer.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

bin/obj/sender.o: module/packet/src/sender.cpp module/packet/sender.hpp module/packet/transfer.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

bin/obj/receiver.o: module/packet/src/receiver.cpp module/packet/receiver.hpp module/packet/transfer.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule