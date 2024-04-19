TARGET = app
LIBNAME = my
ENDFLAGS = -lm -lreadline -g # -D $(KEYWORD)
CC = gcc

.PHONY = lib

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

CHOICE = M
KEYWORD =
# ifeq ($(CHOICE), M)
# 	KEYWORD = MAIN_TASK
# endif
# ifeq ($(CHOICE), D)
# 	KEYWORD = DOP_TASK
# endif

SRC = $(wildcard $(PROJ_SRC)*.c)
OBJ = $(patsubst $(PROJ_SRC)%.c, $(PROJ_OBJ)%.o, $(SRC))

$(TARGET): $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(OBJ) 
	$(CC) -o $(TARGET) $(PROJ_OBJ)*.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

$(PROJ_OBJ)%.o : $(PROJ_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

$(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT): clean # remove clean to turn off auto remake everyting
	mkdir $(PROJ_OBJ) || true
	mkdir $(LIB_PREF_OBJ) || true
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)basic.c -o $(LIB_PREF_OBJ)basic.o $(ENDFLAGS)
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)$(LINBAME).c -o $(LIB_PREF_OBJ)$(LINBAME).o $(ENDFLAGS)
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)$(LINBAME)_gr.c -o $(LIB_PREF_OBJ)$(LINBAME)_gr.o $(ENDFLAGS)
	$(LEFT) $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(LIB_PREF_OBJ)*.o


lib: rmlib $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT)

clean: rmlib
	@rm -f $(PROJ_OBJ)*.o $(TARGET) || true
	@rm -f vgcore* || true
	@rm -f -d obj ./library/obj
	
rmlib:
	@rm -f $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) || true
	@rm -f $(LIB_LOCATION)/obj/*.o || true