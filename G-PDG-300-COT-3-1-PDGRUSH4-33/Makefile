##
## EPITECH PROJECT, 2026
## MyGKrellm
## File description:
## Makefile
##

NAME	=	MyGKrellm

CXX	=	g++
CXXFLAGS =	-Wall -Wextra -std=c++17 -I. -IInterfaces

SRC	=	core/Core.cpp \
		Display/ADisplay.cpp \
		Display/SfmlDisplay.cpp \
		Display/backsfmldisplay.cpp \
		Display/drawCPU.cpp \
		Display/drawRam.cpp \
		Display/nCursesDisplay.hpp \
		Display/utilis_Function_draw.cpp \
		Display/drawBacterry.cpp \
		Display/drawNetwork.cpp \
		Display/initsfmldisplay.cpp \
		Display/updateSfmlDisplay.cpp \
		Module/AModule.cpp \
		Module/src/HostnameModule.cpp \
		Module/src/UserModule.cpp \
		Module/src/OsModule.cpp \
		Module/src/KernelModule.cpp \
		Module/src/DateTimeModule.cpp \
		Module/src/CpuModule.cpp \
		Module/src/RamModule.cpp \
		Module/src/NetworkModule.cpp \
		Module/src/BatteryModule.cpp

OBJ	=	$(SRC:.cpp=.o)

LDFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
