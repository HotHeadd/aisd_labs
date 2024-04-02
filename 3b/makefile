TARGET = app
LIBNAME = my
ENDFLAGS = -lm -lreadline -g -D $(KEYWORD)
CC = gcc

LIB_LOCATION = ./library
LIB_PREF_SRC = $(LIB_LOCATION)/src/
LIB_PREF_OBJ = $(LIB_LOCATION)/obj/

PROJ_SRC = ./src/
PROJ_OBJ = ./obj/

stack = D # Default Iteratirs
task = M # Static Dynamic
# DS default

CFLAGS = -c
LEFT = ar r
FORMAT = a
ENDCOMP = 

LIBSOURCE = table
LIBNAME = table

CHOICE = M
ifeq ($(CHOICE), M)
	KEYWORD = MAIN_TASK
endif
ifeq ($(CHOICE), D)
	KEYWORD = DOP_TASK
endif

SRC = $(wildcard $(PROJ_SRC)*.c) # все файлы проекта с исходным кодом
OBJ = $(patsubst $(PROJ_SRC)%.c, $(PROJ_OBJ)%.o, $(SRC)) # переделываем их на объектные файлы, меняем директорию

$(TARGET): lib $(OBJ) # И ТУТ МЕНЯЛ
	$(CC) -o $(TARGET) $(PROJ_OBJ)*.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

$(PROJ_OBJ)%.o : $(PROJ_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

lib: clean
	mkdir $(PROJ_OBJ) || true
	mkdir $(LIB_PREF_OBJ) || true
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)basic.c -o $(LIB_PREF_OBJ)basic.o $(ENDFLAGS)
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)$(LIBSOURCE).c -o $(LIB_PREF_OBJ)$(LIBSOURCE).o $(ENDFLAGS)
	$(LEFT) $(LIB_LOCATION)/lib$(LIBNAME).$(FORMAT) $(LIB_PREF_OBJ)*.o

clean:
	@rm -f $(LIB_LOCATION)/libtable.a || true
	@rm -f $(PROJ_OBJ)*.o $(TARGET) || true
	@rm -f vgcore* || true
	@rm -f ./obj/*.o || true
	@rm -f $(LIB_LOCATION)/obj/*.o || true
	@rm -f -d obj ./library/obj
	