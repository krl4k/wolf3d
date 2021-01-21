NAME = cub3D
CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBFT_DIR   = ./libft/
PARSER_DIR   = ./parser/
ENGINE_DIR   = ./engine/
MLX_HELPER_DIR = ./mlx_helper/
LIBMLX = ./libmlx.dylib
HEADERS = ./includes/

SRC_MAIN = main.c
SRC_PARSER = $(addprefix $(PARSER_DIR), argv_check.c error_handler.c pars_color.c read_file.c\
	pars_file.c start_pars_map.c pars_resolution.c start_pars_map2.c\
	pars_textures.c parser.c)
SRC_ENGINE = $(addprefix $(ENGINE_DIR), flood_fill.c screen_save.c init_all.c sortsprites.c\
		paint_sprites.c start.c pars_map2.c start_utils.c read_text.c)
SRC_MLX_HELPER = $(addprefix $(MLX_HELPER_DIR), hook_helper.c my_mlx_init.c my_mlx_pixel_put.c)

OBJ_PARSER = $(SRC_PARSER:.c=.o)
OBJ_ENGINE = $(SRC_ENGINE:.c=.o)
OBJ_MLX_HELPER = $(SRC_MLX_HELPER:.c=.o)
OBJ_MAIN = $(SRC_MAIN:.c=.o)

#SRCS = $(addprefix $(PARSER_DIR), $(SRC_PARSER))\
#	$(addprefix $(ENGINE_DIR), $(SRC_ENGINE))\
#	$(addprefix $(MLX_HELPER_DIR), $(SRC_MLX_HELPER))\
#	$(SRC_MAIN))

SRCS = $(SRC_MAIN) $(SRC_PARSER) $(SRC_ENGINE) $(SRC_MLX_HELPER)


OBJS = $(OBJ_MAIN) $(OBJ_PARSER) $(OBJ_MLX_HELPER) $(OBJ_ENGINE)


all:$(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc -I$(HEADERS) $(OBJS) $(FLAGS) $(LIBFT_DIR)/libft.a libmlx.dylib -o $(NAME)

$(OBJ_PARSER): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

$(OBJ_ENGINE): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(HEADERS) -I $(LIBFT_DIR) -c $< -o $@

$(OBJ_MLX_HELPER): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_MAIN): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR) -c $< -o $@


%.o:%.c%$(HEADERS)
	$(CC) $(FLAGS) -o I$(HEADER)  $@ -c $<

clean:
	@rm -rf *.o
	@rm -f $(PARSER_DIR)/*.o
	@rm -f $(ENGINE_DIR)/*.o
	@rm -f $(MLX_HELPER_DIR)/*.o
	@make -C $(LIBFT_DIR) clean
	@echo Objects files deleted!


fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

start:
	./cub3d map.cub

norme:
	norminette ./engine/*.c ./includes/libft.h includes/cub3d.h includes/parser.h \
	./mlx_helper/*.c parser/*.c libft/*.c libft/*.h

forbidden:
	cat ./engine/*.c ./includes/libft.h includes/cub3d.h includes/parser.h \
        	./mlx_helper/*.c parser/*.c libft/*.c libft/*.h | grep "printf"

re: fclean all

.PHONY: all objs clean fclean re