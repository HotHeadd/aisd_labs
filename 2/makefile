TARGET = app
LIBNAME = my
ENDFLAGS = -lm -lreadline -g
CC = gcc

LIB_LOCATION = ./library
LIB_PREF_SRC = $(LIB_LOCATION)/src/
LIB_PREF_OBJ = $(LIB_LOCATION)/obj/

PROJ_SRC = ./src/
PROJ_OBJ = ./obj/

stack = V # Vect List
lib = S # Static Dynamic
# VS default

ifeq ($(stack), L)
	LIBSOURCE = stack_LList
	LIBNAME = list
else
	LIBSOURCE = stack_vector
	LIBNAME = vector
endif
ifeq ($(lib), D)
	CFLAGS = -c -fPIC
	LEFT = $(CC) -shared -o
	FORMAT = so
	ENDCOMP = -Wl,-rpath,$(LIB_LOCATION)
else
	CFLAGS = -c
	LEFT = ar r
	FORMAT = a
	ENDCOMP = 
endif

SRC = $(wildcard $(PROJ_SRC)*.c) # все файлы проекта с исходным кодом
OBJ = $(patsubst $(PROJ_SRC)%.c, $(PROJ_OBJ)%.o, $(SRC)) # переделываем их на объектные файлы, меняем директорию

$(TARGET): lib $(OBJ) # И ТУТ МЕНЯЛ
	$(CC) -o $(TARGET) $(PROJ_OBJ)*.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

# СПРОСИ ПОЧЕМУ БИБЛИОТЕКА КАЖДЫЙ РАЗ ЗАНОВО СОБИРАЕТСЯ, ДАЖЕ ЕСЛИ СДЕЛАТЬ ПРАВИЛЬНО
# $(LIB_LOCATION)/lib$(LIBNAME).$(FORMAT) : lib

$(PROJ_OBJ)%.o : $(PROJ_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

lib:
	mkdir $(PROJ_OBJ) || true
	mkdir $(LIB_PREF_OBJ) || true
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)basic.c -o $(LIB_PREF_OBJ)basic.o $(ENDFLAGS)
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)$(LIBSOURCE).c -o $(LIB_PREF_OBJ)$(LIBSOURCE).o $(ENDFLAGS)
	$(LEFT) $(LIB_LOCATION)/lib$(LIBNAME).$(FORMAT) $(LIB_PREF_OBJ)*.o

clean:
	@rm -f $(LIB_LOCATION)/libvector.a || true
	@rm -f $(LIB_LOCATION)/libvector.so || true
	@rm -f $(LIB_LOCATION)/liblist.so || true
	@rm -f $(LIB_LOCATION)/liblist.a || true
	@rm -f $(PROJ_OBJ)*.o $(TARGET) || true
	@rm -f vgcore* || true
	@rm -f ./obj/*.o || true
	@rm -f $(LIB_LOCATION)/obj/*.o || true
	@rm -f -d obj ./library/obj
	