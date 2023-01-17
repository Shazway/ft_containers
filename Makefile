FT_NAME	=	ft_containers

FT_CC	=	c++
FT_FLAGS = -Wall -Wextra -Werror -std=c++98

FT_SRC_PATH	=	srcs/
FT_OBJ_PATH	=	obj_ft/
FT_INC	=	-Iincludes -Isrcs

FT_SRC_NAME	=	main.cpp map_tests.cpp
FT_OBJ_NAME	=	$(FT_SRC_NAME:.cpp=.o)

FT_OBJ	=	$(addprefix $(FT_OBJ_PATH), $(FT_OBJ_NAME))
FT_SRC	=	$(addprefix $(FT_SRC_PATH), $(FT_SRC_NAME))

STD_NAME	=	std_containers

STD_CC	=	c++
STD_FLAGS = -D__STD -Wall -Wextra -Werror -std=c++98

STD_SRC_PATH	=	srcs/
STD_OBJ_PATH	=	obj_std/
STD_INC	=	-Isrcs -Iincludes

STD_SRC_NAME	=	main.cpp map_tests.cpp
STD_OBJ_NAME	=	$(STD_SRC_NAME:.cpp=.o)

STD_OBJ	=	$(addprefix $(STD_OBJ_PATH), $(STD_OBJ_NAME))
STD_SRC	=	$(addprefix $(STD_SRC_PATH), $(STD_SRC_NAME))

#----------COLORS---------#
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m
EOC			=	\033[0;0m

$(FT_NAME):	$(FT_OBJ)
	$(FT_CC) $(FT_FLAGS) $(FT_INC) $(FT_OBJ) -o $(FT_NAME)
	@echo "$(GREEN)Done ! ✅ $(EOC)"

$(STD_NAME):	$(STD_OBJ)
	$(STD_CC) $(STD_FLAGS) $(STD_INC) $(STD_OBJ) -o $(STD_NAME)
	@echo "$(GREEN)Done ! ✅ $(EOC)"
	@echo "$(CYAN)Containers executables are ready ✅ $(EOC)"

$(FT_OBJ_PATH)%.o: $(FT_SRC_PATH)%.cpp
	@echo "$(RED)=====>Compiling FT_NAMESPACE Containers<===== $(WHITE)"
	mkdir -p $(@D)
	$(FT_CC) $(FT_FLAGS) $(FT_INC) -MMD -c $< -o $@

-include $(FT_OBJ:%.o=%.d)

$(STD_OBJ_PATH)%.o: $(STD_SRC_PATH)%.cpp
	@echo "$(RED)=====>Compiling STD_NAMESPACE Containers<===== $(WHITE)"
	mkdir -p $(@D)
	$(STD_CC) $(STD_FLAGS) $(STD_INC) -MMD -c $< -o $@

-include $(STD_OBJ:%.o=%.d)

all: $(FT_NAME) $(STD_NAME)

clean:
	@echo "$(CYAN)♻  Cleaning obj files ♻ $(WHITE)"
	rm -rf $(FT_OBJ_PATH)
	rm -rf $(STD_OBJ_PATH)
	@echo "$(GREEN)Done !✅ $(EOC)"

fclean: clean
	@echo "$(CYAN)♻  Cleaning executables ♻ $(WHITE)"
	rm -rf $(FT_NAME)
	rm -rf $(STD_NAME)
	@echo "$(GREEN)Done !✅ $(EOC)"

re: fclean all

.PHONY: all clean fclean re