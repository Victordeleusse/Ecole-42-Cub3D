NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -MMD

# MINILIB_PATH_LINUX = -L minilibx-linux -lmlx -lm -lXext -lX11
# LIBFT_PATH = -LLibft -lft 
LFLAGS = -LLibft_vde-leus -lft -L minilibx-linux -lmlx -lm -lXext -lX11

define SRCS :=
	main.c
	parsing/ParseData.c
	parsing/ParseTextures.c
	parsing/ParseColors.c
	parsing/ParseMap.c
	GetMapData.c
	Minimap.c
	Action.c
	MyMiniLibx.c
	Raycasting.c
	parsing/Parsing.c
	Free.c
	Textures.c
endef

SRCS_PATH = Srcs
OBJS_PATH = Objs

INCLUDES = -I Includes -I Libft_vde-leus -I minilibx-linux

OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
DEPS = $(OBJS:.o=.d)


all: ${NAME} ./cub3D

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

.PHONY: clean fclean re 

-include $(DEPS)
