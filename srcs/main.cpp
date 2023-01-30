/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/30 17:53:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include <map>
#include "map.hpp"
#include <string>
#include <list>


void	title(std::string const title)
{
	std::cout << C_BLUE << title << C_WHITE << std::endl;
}

template<typename T1, typename T2>
std::ostream	&operator<<(std::ostream &os, ft::pair<T1, T2> const& p)
{
	os << "[" << p.first << ", " << p.second << "]";
	return (os);
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}
#include "vector.hpp"


using namespace NAMESPACE;

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

//int		main(void)
//{
	//try
	//{
	//	std::cout << C_RED << "====MAP TESTS====" << C_END << std::endl;
	//	map_tests();
	//	std::cout << C_RED << "====END OF MAP TESTS====" << C_END << std::endl << std::endl;

		//std::cout << C_RED << "====SET TESTS====" << C_END << std::endl;
		//set_tests();
		//std::cout << C_RED << "====END OF SET TESTS====" << C_END << std::endl << std::endl;

		//std::cout << C_RED << "====STACK TESTS====" << C_END << std::endl;
		//stack_tests();
		//std::cout << C_RED << "====END OF STACK TESTS====" << C_END << std::endl << std::endl;

		//std::cout << C_RED << "====NAMESPACE::vector TESTS====" << C_END << std::endl;
		//vector_tests();
		//std::cout << C_RED << "====END OF NAMESPACE::vector TESTS====" << C_END << std::endl;
	//}
	//catch(const std::exception& e)
	//{
	//	std::cerr << e.what() << '\n';
	//}
//}
int main ()
{
	map<char,int> mymap;
	map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	print(mymap);
	it=mymap.find('b');
	std::cout << "found b\n";
	mymap.erase (it);                   // erasing by iterator
	print(mymap);
	std::cout << "erase iterator to b\n";
	mymap.erase ('c');                  // erasing by key
	print(mymap);
	std::cout << "erase by key 'c'\n";
	it=mymap.find ('e');
	std::cout << "erase by range 'e' to end\n";
	mymap.erase ( it, mymap.end() );    // erasing by range
	print(mymap);

	std::cout << " display :\n";
	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';

	return (0);
}