# include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Usage: ./PmergeMe [args]" << std::endl;
		return 1;
	}
	try
	{
		PmergeMe container(av);

		std::cout << "Befor: ";
		std::cout << container << std::endl;

		std::cout << "After: ";
		container.sort_vector();
		std::cout << container << std::endl;
		container.sort_time("std::vector");

		container.sort_deque();
		container.sort_time("std::deque");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
