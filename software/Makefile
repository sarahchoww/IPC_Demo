CC=g++
CFLAGS=-Wall -g -L/cygdrive/c/Users/sachxa/Downloads/libconfig-master/lib/.libs

all: bin/obj bin/sim

bin/sim: bin/obj/main.o bin/obj/transfer.o bin/obj/sender.o bin/obj/receiver.o bin/obj/config.o bin/obj/du.o bin/obj/encode.o bin/obj/ecpri.o
	$(CC) -o $@ $^ $(CFLAGS) -lrt -pthread -lconfig++

bin/obj:
	echo here
	mkdir bin/obj

run_du: 
	@cd bin; ./sim sender


run_ru: 
	@cd bin; ./sim receiver

clean:
	rm -rf bin/obj
	cd bin; rm sim*

# Main
bin/obj/main.o: module/main/src/main.cpp module/config/config.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

# Config
bin/obj/config.o: module/config/src/config.cpp module/config/config.hpp module/config/struct.hpp module/packet/sender.hpp module/packet/receiver.hpp module/eth/ecpri.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

bin/obj/du.o: module/config/src/du.cpp module/config/du.hpp module/config/config.hpp module/config/struct.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

# Encode / Decode
bin/obj/encode.o: module/encDec/src/encode.cpp module/encDec/encode.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

# ecpri
bin/obj/ecpri.o: module/eth/src/ecpri.cpp module/eth/ecpri.hpp module/config/struct.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

# Packet
bin/obj/transfer.o: module/packet/src/transfer.cpp module/packet/transfer.hpp module/config/struct.hpp module/encDec/encode.hpp module/eth/ecpri.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

bin/obj/sender.o: module/packet/src/sender.cpp module/packet/sender.hpp module/packet/transfer.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule

bin/obj/receiver.o: module/packet/src/receiver.cpp module/packet/receiver.hpp module/packet/transfer.hpp
	$(CC) -c -o $@ $< $(CFLAGS) -Imodule