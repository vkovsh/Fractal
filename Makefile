NAME = fractal

CC = gcc
CC_FLAGS = -O3 #-Wall -Werror -Wextra

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LIB_LNK = -lpthread -lGL -lX11 -lm -lXext -lGLEW -lglut -lGLU #-lglfw

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_NAME =	main.c			\
			checker.c		\
			close_app.c		\
			init.c			\
			draw.c			\
			reshape.c		\
			motion.c		\
			mouse.c

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) -o $(NAME) $(OBJ) $(LIB_LNK)
		@echo "Compiling" [ $(NAME) ]

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH)
		@$(CC) $(CC_FLAGS) $(INC) -o $@ -c $<
		@echo "Linking" [ $< ]

clean:
		@rm -rf $(OBJ_PATH)
		@echo "Cleaning obj Fractol..."

fclean: clean
		@rm -f $(NAME)
		@echo "Remove..." [ $(NAME) ]

re: fclean all