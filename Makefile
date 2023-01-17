FT_NAME		=	ft_containers
STD_NAME	=	std_containers

CC			=	c++
INC			=	-Iincludes -Isrcs
SRCS		=	srcs/
SRC_NAME	=	main.cpp map_tests.cpp

FT_FLAGS	=	-Wall -Wextra -Werror -std=c++98
STD_FLAGS 	=	-D__STD -Wall -Wextra -Werror -std=c++98

FT_OBJ_PATH		=	obj_ft/
STD_OBJ_PATH	=	obj_std/

FT_OBJ_NAME		=	$(SRC_NAME:.cpp=.o)
STD_OBJ_NAME	=	$(SRC_NAME:.cpp=.o)

FT_OBJ	=	$(addprefix $(FT_OBJ_PATH), $(FT_OBJ_NAME))
STD_OBJ	=	$(addprefix $(STD_OBJ_PATH), $(STD_OBJ_NAME))


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
	$(CC) $(FT_FLAGS) $(INC) $(FT_OBJ) -o $(FT_NAME)
	@echo "$(GREEN)Done ! ✅ $(EOC)"

$(STD_NAME):	$(STD_OBJ)
	$(CC) $(STD_FLAGS) $(INC) $(STD_OBJ) -o $(STD_NAME)
	@echo "$(GREEN)Done ! ✅ $(EOC)"
	@echo "$(CYAN)Containers executables are ready ✅ $(EOC)"

$(FT_OBJ_PATH)%.o: $(SRCS)%.cpp
	@echo "$(RED)=====>Compiling FT_NAMESPACE Containers<===== $(WHITE)"
	mkdir -p $(@D)
	$(CC) $(FT_FLAGS) $(INC) -MMD -c $< -o $@

-include $(FT_OBJ:%.o=%.d)

$(STD_OBJ_PATH)%.o: $(SRCS)%.cpp
	@echo "$(RED)=====>Compiling STD_NAMESPACE Containers<===== $(WHITE)"
	mkdir -p $(@D)
	$(CC) $(STD_FLAGS) $(INC) -MMD -c $< -o $@

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