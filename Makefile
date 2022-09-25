NAME	= ft_ls

CFLAGS	= -Wall -Werror -Wextra -std=c99
SRC		= main.c

LIBFT_D	= ./libft/
LIBFT_I	= $(addprefix $(LIBFT_D), "include")
LIBFT	= $(addprefix $(LIBFT_D), libft.a)

LINK	= -L $(LIBFT_D) -lft

INC_DIR	= ./include/
SRC_DIR	= ./src/
OBJ_DIR	= ./obj/

OBJ		= $(SRC:.c=.o)
OBJS	= $(foreach element, $(OBJ), $(OBJ_DIR)$(element))
SRCS	= $(foreach element, $(SRC), $(SRC_DIR)$(element))

all: obj $(LIBFT) $(NAME)

obj:
	$(info [+] Creating $(OBJ_DIR) folder)
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(info [+] Compiling libft library)
	@make -C $(LIBFT_D)

$(OBJS): %.o: $(SRCS)
	$(info [+] Compiling src files in .o files)
	@gcc $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_I) -c $^
	@mv $(OBJ) $(OBJ_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(info [+] Linking library and compiling executable)
	@gcc $(LINK) $(OBJS) -o $@

clean:
	$(info [+] Removing objects file)
	@/bin/rm -f $(OBJS)

	$(info [+] Cleaning lifbt)
	@make clean -C $(LIBFT_D)

fclean: clean
	$(info [+] Removin $(NAME))
	@/bin/rm -f $(NAME)

	$(info [+] Fclean libft)
	@make fclean -C $(LIBFT_D)

re: fclean all

.PHONY: all, clean, fclean, re, obj