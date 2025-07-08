# Source files
SRC =  ft_strlen.c \
	ft_strrchr.c \
	ft_toupper.c \
	ft_bzero.c \
	ft_isascii.c \
	ft_memcpy.c \
	ft_putnbr_fd.c \
	ft_striteri.c \
	ft_strmapi.c \
	ft_strtrim.c \
	ft_atoi.c \
	is_same.c \
	ft_itoa.c \
	ft_isalpha.c \
	ft_putendl_fd.c \
	ft_strdup.c \
	ft_isdigit.c \
	ft_memset.c \
	ft_split.c \
	ft_strjoin.c \
	ft_strncmp.c  \
	ft_substr.c \
	ft_isalnum.c  \
	ft_isprint.c  \
	ft_putchar_fd.c  \
	ft_strchr.c \
	ft_strlcpy.c \
	ft_strnstr.c \
	ft_tolower.c \
	ft_calloc.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memmove.c \
	ft_putstr_fd.c \
	ft_strlcat.c

B_SRC =  ft_lstadd_back_bonus.c \
	 ft_lstadd_front_bonus.c \
	 ft_lstclear_bonus.c \
	 ft_lstdelone_bonus.c \
	 ft_lstiter_bonus.c \
	 ft_lstlast_bonus.c \
	 ft_lstnew_bonus.c \
	 ft_lstsize_bonus.c \
	 ft_lstmap_bonus.c

SRC_O = $(SRC:.c=.o)
B_SRC_O = $(B_SRC:.c=.o)
CC = cc
C_FLAGS = -Wall -Wextra -Werror
NAME = libft.a

all: $(NAME)

$(NAME): $(SRC_O)
	@ar -rc $(NAME) $(SRC_O)

%.o: %.c libft.h
	@$(CC) $(C_FLAGS) -c $< -o $@

bonus: $(B_SRC_O)
	@ar -rc $(NAME) $(B_SRC_O)

$(B_SRC_O): %.o: %.c libft.h
	$(CC) $(C_FLAGS) -c $< -o $@
clean:
	@rm -f $(SRC_O) $(B_SRC_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
