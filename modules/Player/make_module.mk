PLAYER_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

PLAYER		=	

############################################################

INCPATH		+=	$(addprefix $(PLAYER_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(PLAYER_DIR), $(addprefix $(SRC_FOLDER), $(PLAYER)))
