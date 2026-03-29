# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/28 12:25:05 by lud-adam          #+#    #+#              #
#    Updated: 2026/03/28 16:41:47 by mvachon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus fclean re clean clean-bin clean-obj

CC     = cc
CFLAGS = -Wextra -Wall -Werror -MMD -MP
NO_DIR = --no-print-directory
MAKE  := $(MAKE) -j $(NO_DIR)
NAME       = alum1
NAME_BONUS = alum1_bonus

#############################################################################################
#                                         DIRECTORIES                                       #
#############################################################################################

P_SRC     = src/
P_INC     = inc/
P_OBJ     = .obj/
P_OBJ_BON = .obj_bonus/

#############################################################################################
#                                           FILES                                           #
#############################################################################################

SRC = \
	main.c \
	game.c \
	board.c \
	utils.c \

SRC_BONUS = \
	main_bonus.c \
	board.c \
	utils.c \
	window.c \
	input.c \

#############################################################################################
#                                        MANIPULATION                                       #
#############################################################################################

SRCS     = $(addprefix $(P_SRC), $(SRC))
OBJS     = $(subst $(P_SRC), $(P_OBJ), $(SRCS:.c=.o))
DEPS     = $(OBJS:%.o=%.d)

SRCS_BON = $(addprefix $(P_SRC), $(SRC_BONUS))
OBJS_BON = $(subst $(P_SRC), $(P_OBJ_BON), $(SRCS_BON:.c=.o))
DEPS_BON = $(OBJS_BON:%.o=%.d)

P_RAYLIB    = libs/raylib
RAYLIB_SRC  = $(P_RAYLIB)/src
RAYLIB_LIB  = $(RAYLIB_SRC)/libraylib.a
LDFLAGS_BON = -L$(RAYLIB_SRC) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

#############################################################################################
#                                          RULES                                            #
#############################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ && \
	echo "$(Green)Creating executable $@$(Color_Off)" || \
	echo "$(Red)Error creating $@$(Color_Off)"

$(P_OBJ)%.o: $(P_SRC)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(P_INC) -c $< -o $@ && \
	echo "$(Cyan)Compiling $<$(Color_Off)" || \
	echo "$(Red)Error compiling $<$(Color_Off)"

bonus: $(RAYLIB_LIB) $(OBJS_BON)
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BON) $(LDFLAGS_BON) && \
	echo "$(Green)Creating executable $(NAME_BONUS)$(Color_Off)" || \
	echo "$(Red)Error creating $(NAME_BONUS)$(Color_Off)"

$(P_OBJ_BON)%.o: $(P_SRC)%.c | $(P_RAYLIB)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(P_INC) -I$(RAYLIB_SRC) -c $< -o $@ && \
	echo "$(Cyan)Compiling $< (bonus)$(Color_Off)" || \
	echo "$(Red)Error compiling $<$(Color_Off)"

$(P_RAYLIB):
	@echo "$(Yellow)Cloning raylib...$(Color_Off)"
	@mkdir -p libs
	@git clone --depth 1 https://github.com/raysan5/raylib.git $(P_RAYLIB)
	@echo "$(Green)Raylib cloned!$(Color_Off)"

$(RAYLIB_LIB): $(P_RAYLIB)
	@echo "$(Yellow)Building raylib...$(Color_Off)"
	@$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP --silent
	@echo "$(Green)Raylib built!$(Color_Off)"

#############################################################################################
#                                      Other RULES                                          #
#############################################################################################

clean:
	rm -rfd $(P_OBJ) $(P_OBJ_BON)

clean-bin:
	rm -f $(NAME) $(NAME_BONUS)

clean-obj:
	@$(MAKE) clean

fclean:
	@$(MAKE) clean
	@$(MAKE) clean-bin
	@rm -rf $(P_RAYLIB) libs
	@echo "$(Red)Removed raylib$(Color_Off)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

clear: clean
fclear: fclean
flcean: fclean
flcear: fclean

#############################################################################################
#                                           DEBUG                                           #
#############################################################################################

debug:
	@$(MAKE) $(NAME) CFLAGS="-Wall -Wextra -g3 -D DEBUG=1"

#############################################################################################
#                                         COSMETIC                                          #
#############################################################################################

Color_Off=\033[0m

Black=\033[0;30m
Red=\033[0;31m
Green=\033[0;32m
Yellow=\033[0;33m
Blue=\033[0;34m
Purple=\033[0;35m
Cyan=\033[0;36m
White=\033[0;37m

-include $(DEPS)
-include $(DEPS_BON)
