FT_NAME		=	ft_containers
STD_NAME	=	std_containers

FT_FLAGS	=	-Wall -Wextra -Werror -std=c++98
STD_FLAGS	=	-D__STD -Wall -Wextra -Werror -std=c++98 #<--Here __STD is included to change the namespace from ft:: to std:: (i.e std::vector, ft::vector)

FT_OBJ_PATH		=	obj_ft/
STD_OBJ_PATH	=	obj_std/

CC			=	c++
SRC_PATH	=	srcs/
INCLUDES	=	-Iincludes -Isrcs
SRC_NAME	=	main.cpp							\
				map_tests.cpp						\
				set_tests.cpp						\
				stack_tests.cpp						\
				vector_tests.cpp


OBJ_NAME	=	$(SRC_NAME:.cpp=.o)
FT_OBJ		=	$(addprefix $(FT_OBJ_PATH), $(OBJ_NAME))
STD_OBJ		=	$(addprefix $(STD_OBJ_PATH), $(OBJ_NAME))

#----------COLORS---------#
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m
EOC			=	\033[0;0m



all: $(FT_NAME) $(STD_NAME)

$(FT_NAME): $(FT_OBJ)
	@echo "$(RED)=====>Compiling FT_NAMESPACE Containers<===== $(WHITE)"
	$(CC) $(FT_FLAGS) $(INCLUDES) $(FT_OBJ) -o $(FT_NAME)
	@echo "$(GREEN)Done ! ✅ $(EOC)"

$(FT_OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	mkdir -p $(@D)
	$(CC) $(FT_FLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(FT_OBJ:%.o=%.d)

$(STD_NAME): $(STD_OBJ)
	@echo "$(RED)=====>Compiling STD_NAMESPACE Containers<===== $(WHITE)"
	$(CC) $(STD_FLAGS) $(INCLUDES) $(STD_OBJ) -o $(STD_NAME)
	@echo "$(GREEN)Done ! ✅ $(EOC)"
	@echo "$(CYAN)Containers executables are ready ✅ $(EOC)"

$(STD_OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	mkdir -p $(@D)
	$(CC) $(STD_FLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(STD_OBJ:%.o=%.d)


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