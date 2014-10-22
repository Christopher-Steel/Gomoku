GRAPHIC_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

GRAPHIC		=	GobanPrinter.cpp

############################################################

INCPATH		+=	$(addprefix $(GRAPHIC_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(GRAPHIC_DIR), $(addprefix $(SRC_FOLDER), $(GRAPHIC)))
