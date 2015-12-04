#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/17 17:23:01 by rduclos           #+#    #+#              #
#    Updated: 2015/12/04 16:32:56 by rduclos          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Nibbler
GFXLIBS = gfx-sfml.so
FLAGS = -Wall -Wextra -Werror -std=c++11
FLAGS += -g # Debug

CC = g++

DIROBJ = objs/
DIRSRC = srcs/
HEADERS = headers/

SRC =	ABonus.cpp AEntity.cpp Food.cpp GameManager.cpp Player.cpp \
		GraphicsManager.cpp MapManager.cpp Point.cpp Segment.cpp Snake.cpp \
		Wall.cpp AGameMode.cpp UsualMode.cpp main.cpp

OBJ = $(SRC:%.cpp=$(DIROBJ)%.o)

all: init $(NAME)

init:
	@mkdir -p $(DIROBJ)
	@make -C LibSFML/

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $@ $(OBJ) -I $(HEADERS)
	@echo "\033[2K\t\033[1;36m$(NAME)\t\t\033[0;32m[Ready]\033[0m"

$(DIROBJ)%.o: $(DIRSRC)%.cpp
	@echo "==> Compiling $<"
	@$(CC) $(FLAGS) -o $@ -c $< -I $(HEADERS)

clean:
	@rm -rf $(DIROBJ)
	@echo "[$(NAME)]--> Objects removed"
	@make clean -C LibSFML/

fclean: clean
	@rm -f $(NAME)
	@echo "[$(NAME)]--> Program removed"
	@make fclean -C LibSFML/

re: fclean all
