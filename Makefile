NAME=minirt
CSRCS= main.c get_next_line.c allocation.c tools.c parse_element.c parse.c split.c  vector.c trans_matrix.c new_world.c calcul_matrix.c Garbage_Collector.c
CFLAGS= -Wall -Wextra -Werror
CC= gcc

OBJS=$(CSRCS:.c=.o)

all: $(NAME) clean

$(NAME):$(OBJS)
	@$(CC) -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $^

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)


re : fclean all clean