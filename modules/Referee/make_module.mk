REFEREE_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

REFEREE		=	$(SRC_FOLDER).cpp		\

############################################################

#INCPATH		+=	$(addprefix $(REFEREE_DIR), $(INC_FOLDER))
#SRC		+=	$(addprefix $(REFEREE_DIR), $(REFEREE))
