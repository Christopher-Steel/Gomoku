PLAYER_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

PLAYER		=	APlayer.cpp	\
			Human.cpp

############################################################

INCPATH		+=	$(addprefix $(PLAYER_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(PLAYER_DIR), $(addprefix $(SRC_FOLDER), $(PLAYER)))
