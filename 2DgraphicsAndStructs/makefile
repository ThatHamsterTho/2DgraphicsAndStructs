CC 		= gcc
CFLAGS	= `simple2d --libs` -Wall -Wextra -Wconversion
INCDIR 	= inc
SRCDIR	= src
BLDDIR  = build
INC 	:= $(shell find $(INCDIR) -name '*.h')
INCL	:= $(patsubst %,-I%/, $(INCDIR))
SRC		:= $(shell find $(SRCDIR) -name '*.c')
OBJ		:= $(patsubst %.c, $(BLDDIR)/%.o, $(notdir $(SRC)))
OUT		= main.exe

$(OUT): $(OBJ)
	gcc -o $@ $^ `simple2d --libs`

$(BLDDIR)/%.o: $(SRCDIR)/%.c $(INC)
	$(CC) $(CFLAGS) -c $< $(INCL) -o $@

clean:
	rm -f $(OBJ)