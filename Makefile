BASEFLAGS = -Wall -Wextra -Werror $(INCS) -MMD -MP

ifneq (,$(filter optimize%,$(MAKECMDGOALS)))
	BUILD = optimized
	NAME = life_optimized
	CFLAGS = $(BASEFLAGS) -O3 -march=native \
	-mtune=native -fomit-frame-pointer -DNDEBUG -flto
else
	BUILD = normal
	NAME = life
	CFLAGS = $(BASEFLAGS)
endif

SRCS =	main.c							\
		play.c							\
		prepare/state_validation.c		\
		prepare/state_memory.c			\
		prepare/state_utils.c			\
		utils/fd_to_start.c				\
		utils/ft_free.c					\
		utils/get_next_line.c			\
		utils/print_state.c

SRCS_DIR = srcs/

OBJS_DIR = .objs/$(BUILD)/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS_DIR = .deps/$(BUILD)/
DEPS = $(addprefix $(DEPS_DIR), $(SRCS:.c=.d))

CC = cc

INCS = -I./incs/

GREEN = \033[0;32m
RED = \033[0;31m
END = \033[0m

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@) $(dir $(DEPS_DIR)$*)
	@$(CC) $(CFLAGS) -c $< -o $@ -MF $(DEPS_DIR)$*.d

all: $(NAME)
optimize: $(NAME)
optimize-clean: clean

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME): Compilation complete!$(END)"

-include $(DEPS)

clean:
	@rm -rf $(OBJS_DIR) $(DEPS_DIR)
	@echo "$(RED)✅ $(NAME): Clean complete.$(END)"

fclean:
	@rm -rf .objs/ .deps/ life life_optimized
	@echo "$(RED)✅ $(NAME): Fclean complete.$(END)"

re: fclean all

.PHONY: clean fclean re all optimize optimize-clean
