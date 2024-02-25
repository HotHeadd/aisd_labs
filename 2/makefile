TARGET = app
LIBNAME = my
ENDFLAGS = -lm -lreadline
CC = gcc

LIB_LOCATION = ./library
LIB_PREF_SRC = $(LIB_LOCATION)/src/
LIB_PREF_OBJ = $(LIB_LOCATION)/obj/

PROJ_SRC = ./src/
PROJ_OBJ = ./obj/

stack = V # Vect List
lib = S # Static Dynamic
# LD default

ifeq ($(stack), V)
	LIBSOURCE = stack_vector
	LIBNAME = vector
else
	LIBSOURCE = stack_LList
	LIBNAME = list
endif
ifeq ($(lib), S)
	CFLAGS = -c
	LMAKE = ar r
	FORMAT = a
	ENDCOMP = 
else
	CFLAGS = -c -fPIC
	LEFT = $(CC) -shared -o
	FORMAT = so
	ENDCOMP = -Wl,-rpath,$(LIB_LOCATION)
endif

SRC = $(wildcard $(PROJ_SRC)*.c) # все файлы проекта с исходным кодом
OBJ = $(patsubst $(PROJ_SRC)%.c, $(PROJ_OBJ)%.o, $(SRC)) # переделываем их на объектные файлы, меняем директорию

$(TARGET): lib $(OBJ) # И ТУТ МЕНЯЛ
	$(CC) -o $(TARGET) $(PROJ_OBJ)*.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP)

# СПРОСИ ПОЧЕМУ БИБЛИОТЕКА КАЖДЫЙ РАЗ ЗАНОВО СОБИРАЕТСЯ, ДАЖЕ ЕСЛИ СДЕЛАТЬ ПРАВИЛЬНО
# $(LIB_LOCATION)/lib$(LIBNAME).$(FORMAT) : lib

$(PROJ_OBJ)%.o : $(PROJ_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

lib: # ГИТ НЕ СИНХРОНИЗИРУЕТ ПУСТЫЕ ДИРЕКТОРИИ, ПОЭТОМУ ДОБАВИЛ ГЕНЕРАЦИЮ OBJ-ДИРЕКТОРИЙ
	mkdir $(PROJ_OBJ) || true
	mkdir $(LIB_PREF_OBJ) || true
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)basic.c -o $(LIB_PREF_OBJ)basic.o
	$(CC) $(CFLAGS) $(LIB_PREF_SRC)$(LIBSOURCE).c -o $(LIB_PREF_OBJ)$(LIBSOURCE).o
	$(LEFT) $(LIB_LOCATION)/lib$(LIBNAME).$(FORMAT) $(LIB_PREF_OBJ)*.o

clean: # КАК НЕ ВЫВОДИТЬ ОШИБКИ RM-a???
	@rm $(LIB_LOCATION)/libvector.a || true
	@rm $(LIB_LOCATION)/libvector.so || true
	@rm $(LIB_LOCATION)/liblist.so || true
	@rm $(LIB_LOCATION)/liblist.a || true
	@rm $(PROJ_OBJ)*.o $(TARGET) || true
	@rm vgcore* || true
	@rm ./obj/*.o || true
	@rm $(LIB_LOCATION)/obj/*.o || true
	@rmdir obj ./library/obj
	