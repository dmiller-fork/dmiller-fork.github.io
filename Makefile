CC = gcc
CFLAGS = -Wall -Wextra

LIBSRC = libastro.c libs/libkr.c
CMD_BINS = libastro_fullmoons
TEST_SRC = $(wildcard tests/*_test.c)
TEST_BINS = $(TEST_SRC:.c=)

libastro_fullmoons:
	$(CC) $(CFLAGS) cmds/fullmoon_constellations.c $(LIBSRC) -o astro

run_all: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "Running $$t"; \
		./$$t || exit 1; \
	done

tests/%_test: tests/%_test.c
	$(CC) $(CFLAGS) $< $(LIBSRC) -o $@

clean:
	rm -f $(CMD_BINS) $(TEST_BINS)

EMCC = emcc
EFLAGS = -O2 -sEXPORT_NAME=Astro \
         -sEXPORTED_FUNCTIONS=_fullmoons_for_year \
         -sEXPORTED_RUNTIME_METHODS=ccall,cwrap \
         -sMODULARIZE \
         -sENVIRONMENT=web

SRC = astro.c libastro.c libs/libkr.c
OUT = astro.js

wasm: $(SRC)
	$(EMCC) $(SRC) $(EFLAGS) -o $(OUT)



