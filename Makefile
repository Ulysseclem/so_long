NAME		= so_long
BONUS		= test

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

LIBS	:= ft
LIBS_TARGET :=            \
	lib/libft/libft.a \

INCS        := include    \
	lib/libft/include   \

SRC_DIR     := src
SRCS        := so_long.c \
			get_next_line_utils.c \
			get_next_line.c \
			map_read.c \
			map_error.c \
			ft_printf.c \
			move.c \
			end_game.c \
			map_print.c \
			image_render.c \
			utils.c

SRCS        := $(SRCS:%=$(SRC_DIR)/%)
BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# BONUS --------------------------
SRC_DIR_BONUS	:= bonus
SRCS_BONUS		:= main.c 

SRCS_BONUS	:= $(SRCS_BONUS:%=$(SRC_DIR_BONUS)/%)
BUILD_DIR_B   := .build_b
OBJS_BONUS	:= $(SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(BUILD_DIR_B)/%.o)

# BONUS --------------------------

DEPS        := $(OBJS:.o=.d)
DEPS_B      := $(OBJS_BONUS:.o=.d)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror -g
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))


#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux $(LDLIBS) -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -Imlx_linux -O3 -c -o $@ $<
# $(info CREATED $@)

-include $(DEPS)

#bonus
bonus: $(BONUS)

$(BONUS): $(OBJS_BONUS)
	$(CC) $(LDFLAGS) $(OBJS_BONUS) -Lmlx_linux -lmlx_Linux $(LDLIBS) -Imlx_linux -lXext -lX11 -lm -lz -o $(BONUS)
	$(info CREATED $(BONUS))

$(BUILD_DIR_B)/%.o: $(SRC_DIR_BONUS)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -Imlx_linux -O3 -c -o $@ $<
	$(info CREATED2 $@)
#bonus

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)
	$(RM) $(OBJS_BONUS) $(DEPS_B)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)
	$(RM) $(BONUS)


re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY:		all clean fclean re bonus
