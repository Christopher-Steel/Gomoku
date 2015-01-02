##
#
# Makefile header for modules.
#
# To use this template you should copy it into
# your module's root directory and replace XXX
# by the module's name in UPPERCASE.
# (replace-string is your friend)
#
# All files listed in XXX are considered to be
# located in modules/XXX/src/ (XXX being in
# CamelCase in this situation)
#
##

GAME_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

GAME		=	ModuleGame.cpp

############################################################

INCPATH		+=	$(addprefix $(GAME_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(GAME_DIR), $(addprefix $(SRC_FOLDER), $(GAME)))
