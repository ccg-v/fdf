# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 21:20:12 by ccarrace          #+#    #+#              #
#    Updated: 2023/06/28 21:48:21 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables -------------------------------------------------------------- #

CC				=		gcc
HEADER_NAME		=		fdf.h
LIB_NAME		=		libmlx.a
NAME			=		fdf

# --- Compiler flags --------------------------------------------------------- #

CFLAGS			=		-MMD -Wall -Wextra -Werror -g
LIB_FLAGS		=		-lmlx -framework OpenGL -framework AppKit

# --- Directories ------------------------------------------------------------ #

HEADER_DIR		=		inc/
GNL_DIR			=		get_next_line/
LIB_DIR			=		minilibx_macos/

# --- Includes --------------------------------------------------------------- #

INCLUDES		=		-I $(HEADER_DIR) -I $(GNL_DIR) -I $(LIB_DIR)
LIB_INCLUDE		=		-L $(LIB_DIR)

# --- Paths ------------------------------------------------------------------ #

LIB_PATH		= 		$(addprefix $(LIB_DIR), $(LIB_NAME))

# --- Files ------------------------------------------------------------------ #

SRC_FILES		=		main.c \
						check_input.c \
						read_file.c \
						draw_map.c \
						ft_atoi.c \
						ft_split.c \
						$(GNL_DIR)get_next_line.c \
						$(GNL_DIR)get_next_line_utils.c

# --- Macros ----------------------------------------------------------------- #

OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)

# --- Compilation rules ------------------------------------------------------ #

all:
		$(MAKE) -C $(LIB_DIR)
		$(MAKE) $(NAME)

$(NAME): $(OBJ_FILES) $(LIB_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) -o $@ $(LIB_INCLUDE) $(LIB_FLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEP_FILES)

# gcc -Wall -Wextra -Werror -I minilibx_macos/ read_file.c draw_map.c ft_atoi.c ft_split.c 
# 	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 
# 	-L minilibx_macos -lmlx -framework OpenGL -framework AppKit

# --- Cleaning rules --------------------------------------------------------- #

clean:	
			rm -f $(OBJ_FILES) $(DEP_FILES)
			$(MAKE) -C $(LIB_DIR) clean

fclean:		clean
			rf -f $(NAME)
			$(MAKE) -C $(LIB_DIR) clean

re:			fclean all

.PHONY:		all clean fclean re