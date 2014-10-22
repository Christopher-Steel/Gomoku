NAME		=	gomoku

# Directories

ROOT		=	./

INC_FOLDER	=	inc/
SRC_FOLDER	=	src/
OBJ_FOLDER	=	obj/

INCPATH		=	$(ROOT)$(INC_FOLDER)
LOCAL		=	$(ROOT)$(SRC_FOLDER)

MODDIR		=	./modules/

# Modules

MODULE_DIRS	=	$(MODDIR)Goban		\
			$(MODDIR)Referee	\
			$(MODDIR)Player		\
			$(MODDIR)Graphic

MODULES		=	$(addsuffix /make_module.mk, $(MODULE_DIRS))

# Sources

SRC		=	$(LOCAL)BitMask.cpp	\
			$(LOCAL)main.cpp

include $(MODULES)

OBJ		=	$(SRC:.cpp=.o)

# Debug

DEBUG		?=	false

ifneq		($(DEBUG), false)
CXXFLAGS		+=	-DDEBUG
CXXFLAGS		+=	-g3
else
CXXFLAGS		+=	-O3
endif

# Binary tools

CXX		=	g++
CP		=	cp
RM		=	rm -f
MV		=	mv

PRINTF		?=	/usr/bin/printf

# Flags

CXXFLAGS	+=	-std=gnu++11		\
			$(addprefix -I, $(INCPATH))

# Rules

$(NAME)		:	$(OBJ)
			@ $(PRINTF) "\nCompiled with $(CXX) and following flags:\t\033[34m$(CXXFLAGS)\033[m\n"
			@ $(PRINTF) "Binary name is: \033[36m $@\033[m\n"
			@ $(CXX) -o $@ $(OBJ) $(CXXFLAGS)
			@ $(MV) $(OBJ) $(ROOT)$(OBJ_FOLDER)

all		:	$(NAME)

clean		:
			@ $(PRINTF) "\033[36mRemoved all object files.\033[m\n"
			@ $(RM) $(OBJ_FOLDER)/*.o

fclean		:	clean
			@ $(PRINTF) "\033[36mRemoved binaries.\033[m\n"
			@ $(RM) $(NAME)

re		:	fclean all

%.o		:	%.cpp
			@ $(CXX) $(CXXFLAGS) -o $@ -c $<
			@ $(PRINTF) "\033[32m[OK]\033[m --> $< \n"

.PHONY		:	all clean fclean re

.SUFFIXES	:	%.cpp
