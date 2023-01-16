FT_NAME	=	ft_containers

FT_CC	=	c++
FT_FLAGS = -Wall -Wextra -Werror -std=c++98

FT_SRC_PATH	=	srcs/
FT_OBJ_PATH	=	obj/
FT_INC	=	-Isrcs

FT_SRC_NAME	=	containers_main.cpp
FT_OBJ_NAME	=	$(FT_SRC_NAME:.cpp=.o)

FT_OBJ	=	$(addprefix $(FT_OBJ_PATH), $(FT_OBJ_NAME))
FT_SRC	=	$(addprefix $(FT_SRC_PATH), $(FT_SRC_NAME))

STD_NAME	=	std_containers

STD_CC	=	c++
STD_FLAGS = -D__STD -Wall -Wextra -Werror -std=c++98

STD_SRC_PATH	=	srcs/
STD_OBJ_PATH	=	obj/
STD_INC	=	-Isrcs

STD_SRC_NAME	=	containers_main.cpp
STD_OBJ_NAME	=	$(STD_SRC_NAME:.cpp=.o)

STD_OBJ	=	$(addprefix $(STD_OBJ_PATH), $(STD_OBJ_NAME))
STD_SRC	=	$(addprefix $(STD_SRC_PATH), $(STD_SRC_NAME))


$(FT_NAME):	$(FT_OBJ)
	$(FT_CC) $(FT_FLAGS) $(FT_INC) $(FT_OBJ) -o $(FT_NAME)
	clear

$(STD_NAME):	$(STD_OBJ)
	$(STD_CC) $(STD_FLAGS) $(STD_INC) $(STD_OBJ) -o $(STD_NAME)
	clear

$(FT_OBJ_PATH)%.o: $(FT_SRC_PATH)%.cpp
	mkdir -p $(@D)
	$(FT_CC) $(FT_FLAGS) $(FT_INC) -MMD -c $< -o $@

-include $(FT_OBJ:%.o=%.d)

$(STD_OBJ_PATH)%.o: $(STD_SRC_PATH)%.cpp
	mkdir -p $(@D)
	$(STD_CC) $(STD_FLAGS) $(STD_INC) -MMD -c $< -o $@

-include $(STD_OBJ:%.o=%.d)

all: $(FT_NAME) $(STD_NAME)

clean:
	rm -rf $(FT_OBJ_PATH)
	rm -rf $(STD_OBJ_PATH)

fclean: clean
	rm -rf $(FT_NAME)
	rm -rf $(STD_NAME)

re: fclean all

.PHONY: all clean fclean re