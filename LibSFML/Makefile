#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/11 13:30:53 by tmielcza          #+#    #+#              #
#    Updated: 2015/12/04 16:35:42 by rduclos          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SFMLDIR=SFML2.2

include_dir=/usr/X11R6/include $(SFMLDIR)/SFML-2.2-osx-clang-universal/include
library_dir=/usr/X11R6/lib
cairo=cairo
x11=X11
sfml=SFML sfml-graphics sfml-window sfml-system OpenGL
src_dir=
obj_dir=

SFMLFRAMDIR=$(SFMLDIR)/SFML-2.2-osx-clang-universal/Frameworks
PWD=$(shell pwd)
CXX=clang++
FRAMSFML=-F $(SFMLFRAMDIR) $(addprefix -framework , $(sfml))
LIBRARY= $(LIBCAIRO) $(LIBX11)
INCLUDE=$(addprefix -I, $(include_dir))
LIB=$(addprefix -L, $(library_dir)) $(LIBRARY)

NAME=gfx-sfml.so
TEST=test
CPPFLAGS = -Wall -Wextra -Werror -std=c++11 $(INCLUDE)
CPPFLAGS += -g # Debug
VPATH=$(include_dir) $(library_dir) $(src_dir)
vpath %.dylib $(library_dir)

SRC=Displayer.cpp ADisplayable.cpp

OBJ=$(SRC:%.cpp=%.o)

.SECONDARY: $(OBJ)

.PHONY: all clean fclean re

all: $(SFMLDIR) $(NAME) $(TEST)

$(SFMLDIR):
	curl -OL http://www.sfml-dev.org/files/SFML-2.2-osx-clang-universal.tar.gz
	mkdir $(SFMLDIR)
	tar zxvfC SFML-2.2-osx-clang-universal.tar.gz $(SFMLDIR)
	rm SFML-2.2-osx-clang-universal.tar.gz
	cd $(SFMLFRAMDIR) && ln -s ../extlibs/freetype.framework

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJ) $(LIB) $(FRAMSFML) -rpath $(PWD)/$(SFMLFRAMDIR) -dynamiclib

$(TEST): $(OBJ)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJ) main.cpp $(LIB) $(FRAMSFML) -rpath $(PWD)/$(SFMLFRAMDIR)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
