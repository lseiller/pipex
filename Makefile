# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 15:10:57 by lseiller          #+#    #+#              #
#    Updated: 2022/05/22 15:04:37 by lseiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS #
_END		=	\e[0m
_BOLD		=	\e[1m
_GREY		=	\e[30m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_BLUE		=	\e[34m

## VARIABLES ##

# FLAGS #
MAKEFLAGS 	+=	--silent

## DIRECTORIES ##
SRCS		=	./srcs
DIR			=	./

# CMDS #
RM			=	rm -rf
CP			=	cp -f

# COMPILED_SOURCES #
BONUS		=	bonus
PIPEX		=	pipex
LIBFT		=	libft

# **************************************************************************** #

all:			$(PIPEX)

$(LIBFT):
				echo -n	"\033[2K\r$(_BLUE)$(_BOLD)$(LIBFT) $(_END)\n"
				$(MAKE) -C $(SRCS)/$(LIBFT)

$(PIPEX):		$(LIBFT)
				echo -n	"\033[2K\r$(_BLUE)$(_BOLD)$(PIPEX) $(_END)\n"
				$(MAKE) -C $(SRCS)/$(PIPEX)
				$(CP) $(SRCS)/$(PIPEX)/$(PIPEX) $(DIR)

bonus:			$(LIBFT)
				echo -n	"\033[2K\r$(_BLUE)$(_BOLD)$(BONUS) $(_END)\n"
				$(MAKE) -C $(SRCS)/$(PIPEX) $(BONUS)
				$(CP) $(SRCS)/$(PIPEX)/$(PIPEX)

clean:
				echo -n	"\033[2K\r$(_BLUE)$(_BOLD)$(LIBFT) $(_END)\n"
				make clean -C $(SRCS)/$(LIBFT)
				echo -n	"\033[2K\r$(_BLUE)$(_BOLD)$(PIPEX) $(_END)\n"
				make clean -C $(SRCS)/$(PIPEX)

fclean:
				echo -n	"\033[2K\r$(_BLUE)$(_BOLD)$(LIBFT) $(_END)\n"
				make fclean -C $(SRCS)/$(LIBFT)
				echo -n	"\033[2K\r$(_BLUE)$(_BOLD)$(PIPEX) $(_END)\n"
				make fclean -C $(SRCS)/$(PIPEX)
				$(RM) $(PIPEX)

re:				fclean all

.PHONY:			all clean fclean re pipex bonus libft
