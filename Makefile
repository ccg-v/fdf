# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 21:20:12 by ccarrace          #+#    #+#              #
#    Updated: 2023/07/31 17:35:12 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables -------------------------------------------------------------- #

CC				=		gcc
HEADER_NAME		=		fdf.h
LIBMLX_NAME		=		libmlx.a
LIBFT_NAME		=		libft.a
NAME			=		fdf

# --- Compiler flags --------------------------------------------------------- #

CFLAGS			=		-MMD -Wall -Wextra -Werror -g
LIBMLX_FLAGS	=		-lmlx -framework OpenGL -framework AppKit

# --- Directories ------------------------------------------------------------ #

HEADER_DIR		=		inc/
LIBMLX_DIR		=		minilibx_macos/
LIBFT_DIR		=		libft/

# --- Includes --------------------------------------------------------------- #

INCLUDES		=		-I $(HEADER_DIR) -I $(LIBFT_DIR) -I $(LIBMLX_DIR)
LIB_INCLUDE		=		-L $(LIBFT_DIR) -lft -L $(LIBMLX_DIR)

# --- Paths ------------------------------------------------------------------ #

LIBFT_PATH		= 		$(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
LIBMLX_PATH		= 		$(addprefix $(LIBMLX_DIR), $(LIBMLX_NAME))

# --- Files ------------------------------------------------------------------ #

SRC_FILES		=		main.c \
						checking.c \
						reading.c \
						centering.c \
						drawing.c \
						key_handling.c \
						transforming.c \
						menu_displaying.c \
						ft_utils.c \

# --- Macros ----------------------------------------------------------------- #

OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)

# --- Compilation rules ------------------------------------------------------ #

all:
		$(MAKE) -C $(LIBFT_DIR)
		$(MAKE) -C $(LIBMLX_DIR)
		$(MAKE) $(NAME)

$(NAME): $(OBJ_FILES) $(LIBMLX_PATH)
	$(CC) $(CFLAGS)  $(INCLUDES) $(OBJ_FILES) -o $@ $(LIB_INCLUDE) $(LIBMLX_FLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEP_FILES)

# --- Cleaning rules --------------------------------------------------------- #

clean:	
			rm -f $(OBJ_FILES) $(DEP_FILES)
			$(MAKE) -C $(LIBFT_DIR) clean
			$(MAKE) -C $(LIBMLX_DIR) clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(MAKE) -C $(LIBMLX_DIR) clean

re:			fclean all

.PHONY:		all clean fclean re
