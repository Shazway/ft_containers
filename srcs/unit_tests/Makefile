NAME = unit_test
HDRS = ..
VECTORS_SRCS = $(addprefix srcs/vector/, \
	constructor.cpp \
	assign.cpp \
	iterator.cpp \
	capacity.cpp \
	element_access.cpp \
	modifier.cpp \
	non_members_and_miscs.cpp \
	benchmark.cpp)

MAP_SRCS = $(addprefix srcs/map/, \
	constructor.cpp \
	assign.cpp \
	iterator.cpp \
	capacity.cpp \
	element_access.cpp \
	modifier.cpp \
	observer.cpp \
	operation.cpp \
	non_members_and_miscs.cpp \
	benchmark.cpp)

SET_SRCS = $(addprefix srcs/set/, \
	constructor.cpp \
	assign.cpp \
	iterator.cpp \
	capacity.cpp \
	modifier.cpp \
	observer.cpp \
	operation.cpp \
	non_members_and_miscs.cpp \
	benchmark.cpp)

STACK_SRCS = $(addprefix srcs/stack/, \
	general.cpp)

SRCS_BASE = $(addprefix srcs/, main.cpp common.cpp)
SRCS += $(SRCS_BASE)

ifneq ("$(wildcard $(HDRS)/vector.hpp)","")
SRCS += $(VECTORS_SRCS)
$(info vector detected)
endif

ifneq ("$(wildcard $(HDRS)/map.hpp)","")
SRCS += $(MAP_SRCS)
$(info map detected)
endif

ifneq ("$(wildcard $(HDRS)/stack.hpp)","")
SRCS += $(STACK_SRCS)
$(info stack detected)
endif

ifneq ("$(wildcard $(HDRS)/set.hpp)","")
SRCS += $(SET_SRCS)
$(info set detected)
endif

ifeq ("$(SRCS)", "$(SRCS_BASE)")
$(error None of the containers headers were turned in, please check the HDRS variable path at the top of the makefile)
endif

$(info )

OBJS = ${SRCS:.cpp=.o}
DEPS = ${SRCS:.cpp=.d}
FLAGS = -MMD -MP -Wall -Wextra -Werror -std=c++98

CC = c++

all: ${NAME} Makefile

${NAME}: ${OBJS} | $(HDRS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o: %.cpp
	${CC} ${FLAGS} -I$(HDRS) -c $< -o ${<:.cpp=.o}

clean:
	${RM} ${OBJS} ${DEPS}

fclean: clean
	${RM} ${NAME}

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
