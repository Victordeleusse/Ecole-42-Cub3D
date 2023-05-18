NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -MMD

# MINILIB_PATH_LINUX = -L minilibx-linux -lmlx -lm -lXext -lX11
# LIBFT_PATH = -LLibft -lft 
LFLAGS = -LLibft_vde-leus -lft -L minilibx-linux -lmlx -lm -lXext -lX11

define SRCS :=
	main.c
	parsing/Parsing.c
	parsing/ParseData.c
	parsing/ParseTextures.c
	parsing/ParseColors.c
	parsing/ParseMap.c
	raycasting/Raycasting.c
	raycasting/DdaCalcul.c
	GetMapData.c
	Minimap1.c
	Minimap2.c
	KeyAction.c
	Movements.c
	MyMiniLibx.c
	Textures.c
	Free.c
endef

SRCS_PATH = Srcs
OBJS_PATH = Objs

INCLUDES = -I Includes -I Libft_vde-leus -I minilibx-linux

OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
DEPS = $(OBJS:.o=.d)


all: ${NAME} ./cub3D

bonus: ${NAME} ./cub3D

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
		mkdir -p ${dir $@}
		${CC} ${CFLAGS} -c $< -o $@ $(INCLUDES)

${NAME}: ${OBJS}
		$(MAKE) -C Libft_vde-leus/ all
		$(CC) -o $(NAME) ${OBJS} $(LFLAGS)

valgrind:	${NAME} 

clean:	
		rm -rf $(OBJS_PATH)
		$(MAKE) -C Libft_vde-leus/ clean
		clear

fclean:	clean
		$(MAKE) -C Libft_vde-leus/ fclean
		rm -f ${NAME}
		clear

re:	fclean all

run: ${NAME}
	@	clear
	@	-./${NAME}

.PHONY: all valgrind clean fclean re run bonus

-include $(DEPS)
