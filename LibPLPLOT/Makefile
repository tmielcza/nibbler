#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmielcza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/19 20:57:11 by tmielcza          #+#    #+#              #
#    Updated: 2016/03/21 19:23:09 by tmielcza         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

includedir =	include/ \
				plplot/bindings/c++ \
				plplot/include

libdir =		plplot/bindings/c++

libs =			plplotcxx

frameworks =

SRCDIR = src/
OBJDIR = obj/
DEPDIR = dep/
CXX = clang++
NAME = gfx-plplot.so
INCLUDE = $(addprefix -I,$(includedir))
LIBS = $(addprefix -L,$(libdir)) $(addprefix -l,$(libs))
FRAMEWORKS = $(addprefix -framework ,$(frameworks))
FLAGS = -Wall -Wextra -Werror -std=c++11
FLAGS += -pedantic-errors #-Weverything
#FLAGS += -O3 -march=native
FLAGS += -g # Debug
CXXFLAGS = $(FLAGS) $(INCLUDE)
PWD=$(shell pwd)

SUBMODULES = plplot/.git
LIBPLPLOT = plplot/bindings/c++/libplplotcxx.dylib
BUILDLIBS = $(LIBPLPLOT)

vpath %.cpp $(SRCDIR)

SRC =

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)
DEP = $(SRC:%.cpp=$(DEPDIR)/%.d)

.SECONDARY: $(OBJ)

.PHONY : all clean fclean re

all : $(DEP) $(NAME)

-include $(DEP)

$(OBJDIR)/%.o : %.cpp | $(SUBMODULES) $(OBJDIR)
	@printf "\e[1;32mCompiling $<...\e[0m\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DEPDIR)/%.d : %.cpp | $(BUILDLIBS) $(SUBMODULES) $(DEPDIR)
	@printf "\e[1;34mGenerating $< dependencies...\n\e[0m"
	@$(CXX) $(CXXFLAGS) -MM $< -MT $(OBJDIR)/$*.o -MF $@

$(OBJDIR) :
	@mkdir -p $@

$(DEPDIR) :
	@mkdir -p $@

$(NAME) : $(BUILDLIBS) $(OBJ)
	@$(CXX) $(CPPFLAGS) -o $@ $(OBJ) $(INCLUDE) $(LIBS) -rpath "$HOME/PLPLOT/bindings/c++" -dynamiclib
#Sed la merd
	@echo "$@ : Done!"

test : $(BUILDLIBS)
	@$(CXX) $(CPPFLAGS) -o $@ test.cpp $(INCLUDE) $(LIBS) -rpath $(PWD)"/plplot/bindings/c++"

$(SUBMODULES) :
	@git submodule update --init --recursive

$(LIBPLPLOT) : plplot/.git
	@cd plplot && cmake . && make

clean :
	@rm -rf $(OBJ)
	@echo "Clean : Done."

fclean : clean
	@rm -rf $(NAME)
	@echo "Fclean : Done."

re : fclean all
