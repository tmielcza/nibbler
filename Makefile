#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/17 17:23:01 by rduclos           #+#    #+#              #
#    Updated: 2015/11/17 17:26:36 by rduclos          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Nibbler
FLAGS = -Wall -Wextra -Werror -std=c++11

CC = g++

DIROBJ = objs/
DIRSRC = srcs/
HEADERS = headers/

SRC =	ABonus.cpp AEntity.cpp AGameMode.cpp Food.cpp GameManager.cpp \
		GraphicsManager.cpp MapManager.cpp Point.cpp Segment.cpp Snake.cpp \
		Wall.cpp

OBJ = $(SRC:%.cpp=$(DIROBJ)%.o)

all: init $(NAME)

init:
	@mkdir -p $(DIROBJ)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $@ $(OBJ) -I $(HEADERS)
	@echo "\033[2K\t\033[1;36m$(NAME)\t\t\033[0;32m[Ready]\033[0m"

$(DIROBJ)%.o: $(DIRSRC)%.cpp
	@echo "==> Compiling $<"
	@$(CC) $(FLAGS) -o $@ -c $< -I $(HEADERS)

clean:
	@rm -rf $(DIROBJ)
	@echo "[$(NAME)]--> Objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "[$(NAME)]--> Program removed"

re: fclean all
