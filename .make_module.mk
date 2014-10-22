XXX_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

XXX		=	$(SRC_FOLDER).cpp		\

############################################################

INCPATH		+=	$(addprefix $(XXX_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(XXX_DIR), $(XXX))
