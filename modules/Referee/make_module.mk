REFEREE_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

REFEREE		=	

############################################################

INCPATH		+=	$(addprefix $(REFEREE_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(REFEREE_DIR), $(addprefix $(SRC_FOLDER), $(REFEREE)))
