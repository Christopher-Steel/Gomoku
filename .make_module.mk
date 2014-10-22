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

XXX_DIR	:=	$(dir $(lastword $(MAKEFILE_LIST)))

############################################################

XXX		=	

############################################################

INCPATH		+=	$(addprefix $(XXX_DIR), $(INC_FOLDER))
SRC		+=	$(addprefix $(XXX_DIR), $(addprefix $(SRC_FOLDER), $(XXX)))
