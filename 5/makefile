TARGET = app
LIBNAME = my
ENDFLAGS = -lm -lreadline -g -lcgraph -lgvc# -D $(KEYWORD)
CC = gcc

.PHONY: lib final clean rmlib rmproj

LIB_LOCATION = ./library
LIB_PREF_SRC = $(LIB_LOCATION)/src/
LIB_PREF_OBJ = $(LIB_LOCATION)/obj/
LINBAME = tree

PROJ_SRC = ./src/
PROJ_OBJ = ./obj/


CFLAGS = -c
LEFT = ar r
FORMAT = .a
ENDCOMP = 

# CHOICE = M
# KEYWORD =
# ifeq ($(CHOICE), M)
# 	KEYWORD = MAIN_TASK
# endif
# ifeq ($(CHOICE), D)
# 	KEYWORD = DOP_TASK
# endif

# SRC = $(wildcard $(PROJ_SRC)*.c)
# OBJ = $(patsubst $(PROJ_SRC)%.c, $(PROJ_OBJ)%.o, $(SRC))

LIB_SRC = $(wildcard $(LIB_PREF_SRC)*.c)
LIB_OBJ = $(patsubst $(LIB_PREF_SRC)%.c, $(LIB_PREF_OBJ)%.o, $(LIB_SRC))

# .PHONY : test

# test: lib
# 	gcc -c test.c -o test.o -g
# 	gcc -o ttt test.o -L./library -lmy -g -lm

final : clean $(TARGET) # remove clean to turn off auto remake

app : $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(PROJ_OBJ) $(PROJ_OBJ)app.o
	$(CC) -o app $(PROJ_OBJ)app.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

datagen : $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(PROJ_OBJ) $(PROJ_OBJ)datagen.o
	$(CC) -o data $(PROJ_OBJ)datagen.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

$(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) : $(LIB_PREF_OBJ) $(LIB_OBJ)
	$(LEFT) $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(LIB_PREF_OBJ)*.o

$(PROJ_OBJ)%.o : $(PROJ_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

$(LIB_PREF_OBJ)%.o : $(LIB_PREF_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

$(LIB_PREF_OBJ):
	mkdir -p $(LIB_PREF_OBJ)
$(PROJ_OBJ):
	mkdir -p $(PROJ_OBJ)

lib : rmlib $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT)

clean : rmlib rmproj

rmproj:
	@rm -f $(PROJ_OBJ)*.o app
	@rm -f vgcore*
	@rm -f -d $(PROJ_OBJ)
	
rmlib:
	@rm -f $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT)
	@rm -f $(LIB_LOCATION)/obj/*.o
	@rm -f -d $(LIB_PREF_OBJ)