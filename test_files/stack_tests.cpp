/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:03:19 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/19 01:22:15 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

template <typename T, typename Container>
std::ostream	&operator<<(std::ostream &os, NAMESPACE::stack<T, Container> stack)
{
	if (stack.empty() && PRINT)
		return os << "Stack is empty";
	else if (stack.empty())
		return (os);
	os << stack.top();
	stack.pop();
	while (stack.size())
	{
		os << " " << stack.top();
		stack.pop();
	}
	return os;
}

void stack_constructors()
{
	std::cout << C_GREEN << "====STACK CONSTRUCTORS TESTS====" << C_WHITE << std::endl;
	{
		title("Constructor with no argument");
		NAMESPACE::stack<int> q;
		std::cout << "The stack : " << q << std::endl;
	}
	{
		title("Constructor with container_type argument");
		std::deque<int> d;
		for (int i = 0; i < 10; i++)
			d.push_back(i);
		std::cout << "Container :";
		for (int i = 0; i < 10; i++)
			std::cout << " " << d[i];
		std::cout << std::endl;
		NAMESPACE::stack<int, std::deque<int> > q(d);
		std::cout << "The stack : " << q << std::endl;
	}
	std::cout << C_GREEN << "====END OF CONSTRUCTORS TESTS====" << C_WHITE << std::endl << std::endl;
}

void stack_size_push()
{
	std::cout << C_GREEN << "====STACK SIZE_PUSH TESTS====" << C_WHITE << std::endl;
	NAMESPACE::stack<int> q;
	title("Test of empty");
	std::cout << "The stack : " << q << std::endl;
	title("Test of size and push");
	std::cout << "Size : " << q.size() << std::endl;
	for (int i = 0; i < 3; i++)
	{
		q.push(i);
		std::cout << "The stack : " << q << std::endl;
		std::cout << "Size : " << q.size() << std::endl;
	}
	std::cout << C_GREEN << "====END OF SIZE_PUSH TESTS====" << C_WHITE << std::endl << std::endl;
}

void stack_accessors()
{
	std::cout << C_GREEN << "====STACK ACCESSORS TESTS====" << C_WHITE << std::endl;
	NAMESPACE::stack<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	NAMESPACE::stack<int> const q1 = q;

	std::cout << "The stack before the tests : " << q << std::endl;
	std::cout << "top element : " << q.top() << std::endl;
	q.top() = 44;
	std::cout << "top element : " << q.top() << std::endl;
	std::cout << "top element but stack is const : " << q1.top() << std::endl;
	std::cout << "The stack after the tests : " << q << std::endl;
	std::cout << C_GREEN << "====END OF ACCESSORS TESTS====" << C_WHITE << std::endl << std::endl;
}

void	stack_tests()
{
	stack_constructors();
	stack_size_push();
	stack_accessors();
}