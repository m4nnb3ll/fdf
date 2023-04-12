NAME		:= fdf
CFLAGS		:= -Wextra -Wall -Werror -Ofast
LIBMLX		:= ~/MLX42
BUILD_DIR	:= build_mac
GLFW_DIR	:= $(LIBMLX)/$(BUILD_DIR)/_deps/glfw-build/src
HEADERS		:= -I ./include -I $(LIBMLX)/include
LIBS		:= $(LIBMLX)/$(BUILD_DIR)/libmlx42.a $(GLFW_DIR)/libglfw3.a -ldl -lm libft.a
FRAMEWORKS	:= -framework Cocoa -framework OpenGL -framework IOKit

SRCS		:= 	main.c\
				fdf_utils/color/color.c\
				fdf_utils/color/gradient.c\
				fdf_utils/drawing/ft_project_point.c\
				fdf_utils/drawing/ft_plot_line.c\
				fdf_utils/drawing/ft_scale_n_offset.c\
				fdf_utils/drawing/transform_n_draw.c\
				fdf_utils/errors/error.c\
				fdf_utils/map/free_map.c\
				fdf_utils/map/get_map.c\
				fdf_utils/map/map_borders.c\
				fdf_utils/miscellaneous/misc0.c\

OBJS		:= ${SRCS:.c=.o}

#COLORS
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

all: $(NAME)

main.o: main.c include/*.h
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

libft.a:
	@make bonus -C libft/
	@cp libft/libft.a .
	@make fclean -C libft/
	@echo "$(GREEN)libft ✓$(NC)"

$(NAME): $(OBJS) libft.a
	@$(CC) $(OBJS) $(FRAMEWORKS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)Done ✓$(NC)"

clean:
	@rm -f $(OBJS) libft.a

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
