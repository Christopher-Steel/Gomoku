PLAYER_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

PLAYER		=	$(SRC_FOLDER).cpp		\

############################################################

INCPATH		+=	$(addprefix $(PLAYER_DIR), $(INC_FOLDER))
#SRC		+=	$(addprefix $(PLAYER_DIR), $(PLAYER))
