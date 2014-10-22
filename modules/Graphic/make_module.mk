GRAPHIC_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

GRAPHIC		=	$(SRC_FOLDER)GobanPrinter.cpp

############################################################

INCPATH		+=	$(addprefix $(GRAPHIC_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(GRAPHIC_DIR), $(GRAPHIC))
