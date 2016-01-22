#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/17 17:23:01 by rduclos           #+#    #+#              #
#    Updated: 2015/12/09 17:23:51 by tmielcza         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Nibbler
GFXLIBS = gfx-sfml.so
FLAGS = -Wall -Wextra -Werror -std=c++11
FLAGS += -g # Debug

CC = g++

DIROBJ = objs/
DIRSRC = srcs/
HEADERS = -I headers/ -I common/

SRC =	ABonus.cpp AEntity.cpp Food.cpp GameManager.cpp Player.cpp \
		GraphicsManager.cpp MapManager.cpp Point.cpp Segment.cpp Snake.cpp \
		Wall.cpp AGameMode.cpp SoloMode.cpp main.cpp SuperFood.cpp \
		MultiFood.cpp ChasedFood.cpp CutBonus.cpp SlowBonus.cpp DuoMode.cpp \
		MultiMode.cpp Server.cpp S_Clients.cpp Buff_Circle.cpp Client.cpp

OBJ = $(SRC:%.cpp=$(DIROBJ)%.o)

all: init $(NAME)

init:
	@mkdir -p $(DIROBJ)
	@make -C LibSFML/

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $@ $(OBJ) $(HEADERS)
	@echo "\033[2K\t\033[1;36m$(NAME)\t\t\033[0;32m[Ready]\033[0m"

$(DIROBJ)%.o: $(DIRSRC)%.cpp
	@echo "==> Compiling $<"
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS)

clean:
	@rm -rf $(DIROBJ)
	@echo "[$(NAME)]--> Objects removed"
	@make clean -C LibSFML/

fclean: clean
	@rm -f $(NAME)
	@echo "[$(NAME)]--> Program removed"
	@make fclean -C LibSFML/

test:
	@clear
	@make && clear && ./Nibbler -nowall -player 2 -port 1024

re: fclean all
