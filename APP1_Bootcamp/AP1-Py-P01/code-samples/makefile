CC := gcc
CFLAGS := -I./inc -std=c99 -Wall -Werror -pedantic -g

GENERATOR_OBJS :=	out/connectivity_checker.o \
					out/dungeon_generation.o \
					out/dungeon_output.o \
					out/dungeon_to_map_translation.o \
					out/entity_generation.o \
					out/main_generator.o


WALKER_OBJS :=	out/dungeon_generation.o\
				out/dungeon_to_map_translation.o\
				out/entity_generation.o \
				out/main_walker.o \
				out/movement.o \
				out/screen.o

walker: $(WALKER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lncursesw -lm

generator: $(GENERATOR_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lncursesw -lm

debug_walker: $(WALKER_OBJS)
	$(CC) $(CFLAGS) -g $^ -o $@ -lncursesw -lm

debug_generator: $(GENERATOR_OBJS)
	$(CC) $(CFLAGS) -g $^ -o $@ -lncursesw -lm

out/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) out/*.o walker generator debug_walker debug_generator

.PHONY: clean