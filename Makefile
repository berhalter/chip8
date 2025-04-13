CC := gcc
CFLAGS := -O0 -std=c99 -ggdb -D_DEFAULT_SOURCE -Wall -Wextra -Werror
LDFLAGS :=
SRCS := $(wildcard src/*.c)
SRC_OBJS := $(SRCS:.c=.o)
TEST_SRCS := $(wildcard tests/*.c) #only used for $(TESTS)
#TEST_OBJS := $(TEST_SRCS:.c=.o) #not used
TESTS := $(basename $(notdir $(TEST_SRCS)))


all: chip8

chip8: $(SRC_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Make throws an error when running this if any tests fail, but it does work.
# Need confirm this, but my current theory is that Criterion returns a non-zero
# value if tests fail, so it probably doesn't matter much.
tests: $(patsubst %, tests/test_%, $(TESTS))
	$(foreach test, $^, ./$(test))

tests/test_%: tests/%.o $(filter-out src/main.o, $(SRC_OBJS)) # Criterion will NOT work if a main function is included
	$(CC) $^ -o $@ -lcriterion

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f chip8 *~ *.o src/*~ src/*.o tests/*~ tests/*.o tests/test_*

.PHONY: all clean tests
