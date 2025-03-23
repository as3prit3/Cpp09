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
		PmergeMe<std::vector<int> > v(av);
		PmergeMe<std::deque<int> > d(av);

		std::cout << "Befor: ";
		std::cout << d << std::endl;

		std::cout << "After: ";
		v.sort();
		d.sort();
		std::cout << d << std::endl;

		v.sort_time();
		d.sort_time();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
