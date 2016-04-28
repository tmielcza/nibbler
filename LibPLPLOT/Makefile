#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmielcza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/19 20:57:11 by tmielcza          #+#    #+#              #
#    Updated: 2016/04/28 20:43:21 by tmielcza         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

PLPLOT_INSTALL_DIR=$(PWD)/plplot_install
LIBPLPLOT = $(PLPLOT_INSTALL_DIR)/lib/libplplotcxx.dylib

includedir =	include/ \
				plplot/bindings/c++ \
				plplot/include

libdir =		$(PLPLOT_INSTALL_DIR)/lib

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
BUILDLIBS = $(LIBPLPLOT)

CMAKE_VAR = -DCMAKE_INSTALL_PREFIX=$(PLPLOT_INSTALL_DIR)
CMAKE_VAR += -DDEFAULT_NO_CAIRO_DEVICES=ON
CMAKE_VAR += -DBUILD_DOC=OFF
CMAKE_VAR += -DBUILD_DOX_DOC=OFF
CMAKE_VAR += -DBUILD_TEST=OFF
CMAKE_VAR += -DBUILD_SHARED_LIBS=ON

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

test : $(BUILDLIBS) test.cpp
	@$(CXX) $(CPPFLAGS) -o $@ test.cpp $(INCLUDE) $(LIBS) -rpath $(PLPLOT_INSTALL_DIR)"/lib"

$(SUBMODULES) :
	@git submodule update --init --recursive

$(LIBPLPLOT) : plplot/.git
	@cd plplot && cmake $(CMAKE_VAR) . && make && make install

clean :
	@rm -rf $(OBJ)
	@echo "Clean : Done."

fclean : clean
	@rm -rf $(NAME)
	@echo "Fclean : Done."

re : fclean all
