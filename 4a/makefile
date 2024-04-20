TARGET = app
LIBNAME = my
ENDFLAGS = -lm -lreadline -g # -D $(KEYWORD)
CC = gcc

.PHONY: lib final dirs rmlib app

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

LIB_SRC = $(wildcard $(LIB_PREF_SRC)*.c)
LIB_OBJ = $(patsubst $(LIB_PREF_SRC)%.c, $(LIB_PREF_OBJ)%.o, $(LIB_SRC))

final: clean dirs $(TARGET) # remove clean to turn off auto remake everyting

app: $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(OBJ) 
	$(CC) -o app $(PROJ_OBJ)*.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

$(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT): $(LIB_OBJ)
	$(LEFT) $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(LIB_PREF_OBJ)*.o

$(PROJ_OBJ)%.o : $(PROJ_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

$(LIB_PREF_OBJ)%.o : $(LIB_PREF_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

dirs:
	mkdir $(PROJ_OBJ) || true
	mkdir $(LIB_PREF_OBJ) || true

lib: rmlib $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT)

clean: rmlib
	@rm -f $(PROJ_OBJ)*.o $(TARGET) || true
	@rm -f vgcore* || true
	@rm -f -d obj
	
rmlib:
	@rm -f $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) || true
	@rm -f $(LIB_LOCATION)/obj/*.o || true
	@rm -f -d $(LIB_PREF_OBJ)