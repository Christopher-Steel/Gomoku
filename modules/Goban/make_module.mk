GOBAN_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

GOBAN		=	Goban.cpp

############################################################

INCPATH		+=	$(addprefix $(GOBAN_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(GOBAN_DIR), $(addprefix $(SRC_FOLDER), $(GOBAN)))
