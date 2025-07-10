#ifndef PMERGEME_CPP
# define PMERGEME_CPP

# include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const &src)
{
	*this = src;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &src)
{
	if (this != &src)
	{
		_vector = src._vector;
		_deque = src._deque;
		_start = src._start;
		_end = src._end;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

std::vector<int> &PmergeMe::getVector()
{
	return _vector;
}

// template <typename T>
std::ostream &operator<<(std::ostream &o, PmergeMe  &src)
{
	std::vector<int>::const_iterator it;
	for (it = src.getVector().begin(); it != src.getVector().end(); ++it)
		o << *it << " ";
	return o;
}


//---------------------------------------

PmergeMe::PmergeMe(char **av)
{
	std::string str;
	for (int i = 1; av[i]; i++)
	{
		str += av[i];
		if (av[i] != NULL)
			str += " ";
	}
	int val;
	std::istringstream iss(str);
	while (iss >> val)
	{
		if (std::find(_vector.begin(), _vector.end(), val) != _vector.end())
			throw std::runtime_error("Error: duplicate value");
		_vector.push_back(val);
		_deque.push_back(val);
	}
	if (_vector.size() != count_words(str))
		throw std::runtime_error("Error: invalid input");
}

size_t	PmergeMe::count_words(std::string str)
{
	size_t count = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] != ' ' && str[i] != '\0')
		{
			count++;
			while (str[i] != ' ' && str[i] != '\0')
			{
				if (!isdigit(str[i]) && str[i] != '+')
					throw std::runtime_error("Error: invalid input");
				i++;
			}
		}
	}
	return count;
}

void	PmergeMe::sort_vector()
{
	_start = clock();
	Merge_Insertion_sort(_vector);
	_end = clock();
}

void	PmergeMe::sort_deque()
{
	_start = clock();
	Merge_Insertion_sort(_deque);
	_end = clock();
}

float	PmergeMe::time()
{
	return static_cast<float>(_end - _start) / CLOCKS_PER_SEC;
}

void	PmergeMe::sort_time(std::string type)
{
	std::cout << "Time to process a range of " << _vector.size()
			<< " elements with " << type
			<< " : " << std::fixed << std::setprecision(6)
			<< time() << " s" << std::endl;
}

std::vector<size_t> PmergeMe::generate_jacobsthal_order(size_t k) {
    std::vector<size_t> order;
    std::vector<size_t> jacob;

    jacob.push_back(0);
    jacob.push_back(1);
    size_t i = 2;
    while (true) {
        size_t next = jacob[i - 1] + 2 * jacob[i - 2];
        if (next >= k) break;
        jacob.push_back(next);
        ++i;
    }

    // Add valid and unique indices from jacob
    std::vector<bool> seen(k, false);
    for (int i = static_cast<int>(jacob.size()); i >= 0; --i) {
        if (jacob[i] < k && !seen[jacob[i]]) {
            order.push_back(jacob[i]);
            seen[jacob[i]] = true;
        }
    }

    // Add the rest of the indices in reverse order
    for (int i = k - 1; i >= 0; --i) {
        if (!seen[i]) order.push_back(i);
    }
    return order;
}

// void PmergeMe::binaryInsert(std::vector<int>& sorted, int element) {
//     std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), element);
//     sorted.insert(it, element);
// }

// void PmergeMe::binaryInsert(std::deque<int>& sorted, int element) {
//     std::deque<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), element);
//     sorted.insert(it, element);
// }

// void	PmergeMe::Merge_Insertion_sort(std::vector<int> &vec)
// {
// 	// _start = clock();
// 	if (vec.size() < 2)
// 		return ;

// 	std::vector<int> max_set, min_set;
// 	for (size_t i = 0; i < vec.size(); i += 2)
// 	{
// 		if (i + 1 < vec.size())
// 		{
// 			if (vec[i] > vec[i + 1])
// 			{
// 				max_set.push_back(vec[i]);
// 				min_set.push_back(vec[i + 1]);
// 			}
// 			else
// 			{
// 				max_set.push_back(vec[i + 1]);
// 				min_set.push_back(vec[i]);
// 			}
// 		}
// 	}
// 	bool is_odd = vec.size() % 2 == 1;
// 	int leftover = is_odd ? vec.back() : -1;

// 	Merge_Insertion_sort(max_set);

// 	// Step 2: Generate Jacobsthal insertion order
// 	std::vector<size_t> order = generate_jacobsthal_order(min_set.size());

// 	// Step 3: Insert into the sorted list using Jacobsthal order
// 	for (size_t i = 0; i < order.size(); ++i)
// 		binaryInsert(max_set, min_set[order[i]]);
// 	// Step 4: Insert the remaining elements
// 	if (is_odd)
// 		binaryInsert(max_set, leftover);
// 	vec = max_set;
// 	// _end = clock();
// }

// void	PmergeMe::Merge_Insertion_sort(std::deque<int> &vec)
// {
// 	// _start = clock();
// 	if (vec.size() < 2)
// 		return ;

// 	std::deque<int> max_set, min_set;
// 	for (size_t i = 0; i < vec.size(); i += 2)
// 	{
// 		if (i + 1 < vec.size())
// 		{
// 			if (vec[i] > vec[i + 1])
// 			{
// 				max_set.push_back(vec[i]);
// 				min_set.push_back(vec[i + 1]);
// 			}
// 			else
// 			{
// 				max_set.push_back(vec[i + 1]);
// 				min_set.push_back(vec[i]);
// 			}
// 		}
// 	}
// 	bool is_odd = vec.size() % 2 == 1;
// 	int leftover = is_odd ? vec.back() : -1;

// 	Merge_Insertion_sort(max_set);

// 	// Step 2: Generate Jacobsthal insertion order
// 	std::vector<size_t> order = generate_jacobsthal_order(min_set.size());

// 	// Step 3: Insert into the sorted list using Jacobsthal order
// 	for (size_t i = 0; i < order.size(); ++i)
// 		binaryInsert(max_set, min_set[order[i]]);
// 	// Step 4: Insert the remaining elements
// 	if (is_odd)
// 		binaryInsert(max_set, leftover);
// 	vec = max_set;
// 	// _end = clock();
// }
#endif
