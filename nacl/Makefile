OBJS = nacl.o bitbase.o bitboard.o endgame.o evaluate.o \
	material.o misc.o movegen.o movepick.o pawns.o position.o psqt.o \
	search.o thread.o timeman.o tt.o uci.o ucioption.o

HEADERS = $(wildcard ../src/*.h)

PNACL_TC_PATH = $(NACL_SDK_ROOT)/toolchain/linux_pnacl
PNACL_CXX = $(PNACL_TC_PATH)/bin/pnacl-clang++
PNACL_FINALIZE = $(PNACL_TC_PATH)/bin/pnacl-finalize

CXXFLAGS = -O3 -std=gnu++11 -fno-exceptions -fno-rtti \
	-I$(NACL_SDK_ROOT)/include \
	-mllvm -inline-threshold=500 \
	-DNDEBUG -DIS_64BIT -DUSE_POPCNT -DNO_PREFETCH \
	-DANTI -DATOMIC -DHORDE -DKOTH -DRACE -DTHREECHECK

LDFLAGS = -L$(NACL_SDK_ROOT)/lib/pnacl/Release -O3 -lppapi_cpp -lppapi -lpthread

stockfish.pexe: stockfish.bc
	$(PNACL_FINALIZE) --compress -o $@ $<

%.o: ../src/%.cpp $(HEADERS) Makefile
	$(PNACL_CXX) -c -o $@ $< $(CXXFLAGS)

stockfish.bc: $(OBJS)
	$(PNACL_CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm stockfish.pexe stockfish.bc *.o
