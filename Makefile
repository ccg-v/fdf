# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 21:20:12 by ccarrace          #+#    #+#              #
#    Updated: 2023/06/23 00:25:26 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables -------------------------------------------------------------- #

CC				=		gcc
HEADER_NAME		=		fdf.h
LIB_NAME		=		libmlx.a
NAME			=		fdf

# --- Compiler flags --------------------------------------------------------- #

CFLAGS			=		-MMD -Wall -Wextra -Werror
LIB_FLAGS		=		-lmlx -framework OpenGL -framework AppKit

# --- Directories ------------------------------------------------------------ #

HEADER_DIR		=		inc/
LIB_DIR			=		minilibx_macos/

# --- Includes --------------------------------------------------------------- #

HEADER_INCLUDE	=		-I $(HEADER_DIR)
LIB_INCLUDE		=		-L $(LIB_DIR)

# --- Paths ------------------------------------------------------------------ #

LIB_PATH		= 		$(addprefix $(LIB_DIR), $(LIB_NAME))

# --- Files ------------------------------------------------------------------ #

SRC_FILES		=		main.c

# --- Macros ----------------------------------------------------------------- #

OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)

# --- Compilation rules ------------------------------------------------------ #

all:
		$(MAKE) $(NAME)

$(NAME): $(OBJ_FILES) $(LIB_PATH)
	$(CC) $(CFLAGS) $(HEADER_INCLUDE) $(OBJ_FILES) $(LIB_INCLUDE) $(LIB_FLAGS) -o $@

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(HEADER_INCLUDE) $(LIB_INCLUDE) $(LIB_FLAGS) -c $< -o $@

-include $(DEP_FILES)

#gcc -Wall -Wextra -Werror -I minilibx/ main.c -L minilibx -lmlx -framework OpenGL -framework AppKit

# --- Cleaning rules --------------------------------------------------------- #

clean:	
			rm -f $(OBJ_FILES) $(DEP_FILES)
			$(MAKE) -C $(LIB_DIR) clean

fclean:		clean
			rf -f $(NAME)
			$(MAKE) -C $(LIB_DIR) clean

re:			fclean all

.PHONY:		all clean fclean re