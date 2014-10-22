GOBAN_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

GOBAN		=	$(SRC_FOLDER)Goban.cpp

############################################################

INCPATH		+=	$(addprefix $(GOBAN_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(GOBAN_DIR), $(GOBAN))
