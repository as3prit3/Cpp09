# ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <algorithm>
# include <vector>
# include <deque>
# include <sstream>
# include <typeinfo>
#include <ctime>
#include <iomanip>
# include <cmath>

template <typename T>
class PmergeMe
{
	private:
		T _container;
		time_t _start;
		time_t _end;
		void	Merge_Insertion_sort(T &vec);
		void 	binaryInsert(T &sorted, int element);
		size_t	count_words(std::string str);
	public:
		PmergeMe();
		PmergeMe(char **av);
		PmergeMe(PmergeMe const &src);
		PmergeMe &operator=(PmergeMe const &src);
		~PmergeMe();

		typedef typename T::iterator	iterator;
		typedef typename T::value_type	valuetype;
		iterator	begin();
		iterator	end();
		void		sort();
		void		sort_time();
		std::string	container_type();
		float		time();
};

template <typename T>
std::ostream &operator<<(std::ostream &o, PmergeMe<T> &src);

# include "PmergeMe.cpp"

#endif

		// void	sort(T &container);
		// void	insert(T &main, T &pend, valuetype odd, T &left, T &vec, bool is_odd, int order);
		// int Jacobsthal(int k);
