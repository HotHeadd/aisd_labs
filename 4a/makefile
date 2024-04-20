TARGET = app
LIBNAME = my
ENDFLAGS = -lm -lreadline -g -lcgraph -lgvc # -D $(KEYWORD)
CC = gcc

.PHONY: lib final clean rmlib rmproj libdir projdir dirs

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

final : clean $(TARGET) # remove clean to turn off auto remake

app : projdir $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(PROJ_OBJ)app.o 
	$(CC) -o app $(PROJ_OBJ)app.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

timer : projdir $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(PROJ_OBJ)timer.o
	$(CC) -o timer $(PROJ_OBJ)timer.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

count : projdir $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(PROJ_OBJ)count.o
	$(CC) -o count $(PROJ_OBJ)count.o -L$(LIB_LOCATION) -l$(LIBNAME) $(ENDCOMP) $(ENDFLAGS)

$(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) : libdir $(LIB_OBJ)
	$(LEFT) $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT) $(LIB_PREF_OBJ)*.o

$(PROJ_OBJ)%.o : $(PROJ_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

$(LIB_PREF_OBJ)%.o : $(LIB_PREF_SRC)%.c
	$(CC) -c $< -o $@ $(ENDFLAGS)

libdir:
	mkdir -p $(LIB_PREF_OBJ)
projdir:
	mkdir -p $(PROJ_OBJ)

lib : rmlib $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT)

clean : rmlib rmproj

rmproj:
	@rm -f $(PROJ_OBJ)*.o app timer
	@rm -f vgcore*
	@rm -f -d obj
	
rmlib:
	@rm -f $(LIB_LOCATION)/lib$(LIBNAME)$(FORMAT)
	@rm -f $(LIB_LOCATION)/obj/*.o
	@rm -f -d $(LIB_PREF_OBJ)