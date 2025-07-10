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

class PmergeMe
{
	private:
		std::vector<int> _vector;
		std::deque<int> _deque;
		time_t _start;
		time_t _end;
		template <typename T>
		void 	binaryInsert(T &sorted, int element);
		// void 	binaryInsert(std::deque<int> &sorted, int element);
		template <typename T>
		void	Merge_Insertion_sort(T &vec);
		// void	Merge_Insertion_sort(std::deque<int> &vec);
		size_t	count_words(std::string str);
		std::vector<size_t> generate_jacobsthal_order(size_t k);
	public:
		PmergeMe();
		PmergeMe(char **av);
		PmergeMe(PmergeMe const &src);
		PmergeMe &operator=(PmergeMe const &src);
		~PmergeMe();

		std::vector<int> &getVector();
		void		sort_vector();
		void		sort_deque();
		void		sort_time(std::string type);
		float		time();
};

std::ostream &operator<<(std::ostream &o, PmergeMe &src);

template <typename T>
void PmergeMe::binaryInsert(T &sorted, int element)
{
	typename T::iterator it = std::lower_bound(sorted.begin(), sorted.end(), element);
	sorted.insert(it, element);
}


template <typename T>
void	PmergeMe::Merge_Insertion_sort(T &vec)
{
	_start = clock();
	if (vec.size() < 2)
		return _end = clock(), void();

	T max_set;
	T min_set;
	for (size_t i = 0; i < vec.size(); i += 2)
	{
		if (i + 1 < vec.size())
		{
			if (vec[i] > vec[i + 1])
			{
				max_set.push_back(vec[i]);
				min_set.push_back(vec[i + 1]);
			}
			else
			{
				max_set.push_back(vec[i + 1]);
				min_set.push_back(vec[i]);
			}
		}
	}
	bool is_odd = vec.size() % 2 == 1;
	int leftover = is_odd ? vec.back() : -1;

	Merge_Insertion_sort(max_set);

	// Step 2: Generate Jacobsthal insertion order
	std::vector<size_t> order = generate_jacobsthal_order(min_set.size());

	// Step 3: Insert into the sorted list using Jacobsthal order
	for (size_t i = 0; i < order.size(); ++i)
		binaryInsert(max_set, min_set[order[i]]);
	// Step 4: Insert the remaining elements
	if (is_odd)
		binaryInsert(max_set, leftover);
	vec = max_set;
	_end = clock();
}

#endif

		// void	sort(T &container);
		// void	insert(T &main, T &pend, valuetype odd, T &left, T &vec, bool is_odd, int order);
		// int Jacobsthal(int k);
