#ifndef PMERGEME_CPP
# define PMERGEME_CPP

# include "PmergeMe.hpp"

template <typename T>
PmergeMe<T>::PmergeMe()
{
}

template <typename T>
PmergeMe<T>::PmergeMe(PmergeMe const &src)
{
	*this = src;
}

template <typename T>
PmergeMe<T> &PmergeMe<T>::operator=(PmergeMe const &src)
{
	if (this != &src)
		this->_container = src._container;
	return *this;
}

template <typename T>
PmergeMe<T>::~PmergeMe()
{
}

template <typename T>
std::ostream &operator<<(std::ostream &o, PmergeMe<T>  &src)
{
	typename T::const_iterator it;
	for (it = src.begin(); it != src.end(); ++it)
		o << *it << " ";
	return o;
}


//---------------------------------------

template <typename T>
PmergeMe<T>::PmergeMe(char **av)
{
	std::string str;
	for (int i = 1; av[i]; i++)
	{
		str += av[i];
		if (av[i] != NULL)
			str += " ";
	}
	valuetype val;
	std::istringstream iss(str);
	while (iss >> val)
	{
		if (std::find(_container.begin(), _container.end(), val) != _container.end())
			throw std::runtime_error("Error: duplicate value");
		_container.push_back(val);
	}
	if (_container.size() != count_words(str))
		throw std::runtime_error("Error: invalid input");
}

template <typename T>
size_t	PmergeMe<T>::count_words(std::string str)
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

template <typename T>
void	PmergeMe<T>::sort()
{
	// sort(_container);

	Merge_Insertion_sort(_container);
}

template <typename T>
std::string	PmergeMe<T>::container_type()
{
	if (typeid(T) == typeid(std::vector<valuetype>))
		return "std::vector";
	else if (typeid(T) == typeid(std::deque<valuetype>))
		return "std::deque";
	else
		throw std::runtime_error("Error: invalid container type");
}

template <typename T>
float	PmergeMe<T>::time()
{
	return static_cast<float>(_end - _start) / CLOCKS_PER_SEC;
}

template <typename T>
void	PmergeMe<T>::sort_time()
{
	float	elapsedTime = time();
	std::cout << "Time to process a range of " << _container.size()
			<< " elements with " << container_type()
			<< " : " << std::fixed << std::setprecision(6)
			<< elapsedTime << " s" << std::endl;
}

template <typename T>
typename T::iterator	PmergeMe<T>::begin()
{
	return _container.begin();
}

template <typename T>
typename T::iterator	PmergeMe<T>::end()
{
	return _container.end();
}

template <typename T>
void PmergeMe<T>::binaryInsert(T &sorted, int element)
{
	iterator it = std::lower_bound(sorted.begin(), sorted.end(), element);
	sorted.insert(it, element);
}

template <typename T>
void	PmergeMe<T>::Merge_Insertion_sort(T &vec)
{
	_start = clock();
	if (vec.size() < 2)
		return;

	std::vector<std::pair<int, int> > pairs;

	for (size_t i = 0; i < vec.size(); i += 2)
	{
		if (i + 1 < vec.size())
		{
			if (vec[i] > vec[i + 1])
				pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
			else
				pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
		}
		else
			pairs.push_back(std::make_pair(vec[i], -1));
	}

	T larger_set;
	for (size_t i = 0; i < pairs.size(); ++i)
		if (pairs[i].second != -1)
			larger_set.push_back(pairs[i].second);

	Merge_Insertion_sort(larger_set);

	T sorted = larger_set;
	for (size_t i = 0; i < pairs.size(); ++i)
		if (pairs[i].first != -1)
			binaryInsert(sorted, pairs[i].first);

	vec = sorted;
	_end = clock();
}

#endif


// template <typename T>
// void	PmergeMe<T>::sort(T &vec)
// {
// 	static int order = 1;
// 	if(order == 1)
// 		_start = clock();
// 	int unit_size = vec.size() / order;
// 	if (unit_size < 2) return;

// 	bool is_odd = unit_size % 2 == 1;
// 	iterator start = vec.begin();
// 	iterator end = vec.begin() + ((order * unit_size) - (is_odd * order));

// 	for (iterator it = start; it < end; it += (order * 2)) {
// 		if (*(it + (order - 1)) > *(it + ((order * 2) - 1))) {
// 			for (int i = 0; i < order; i++) {
// 				std::swap(*(it + i), *(it + i + order));
// 			}
// 		}
// 	}

// 	order *= 2;
// 	sort(vec);
// 	order /= 2;

// 	T main;
// 	T pend;
// 	valuetype odd = 0;
// 	T left;

// 	main.push_back(*(start + order - 1));
// 	main.push_back(*(start + order * 2 - 1));

// 	for (iterator it = start + order * 2; it < end; it += order) {
// 		pend.push_back(*(it + order - 1));
// 		it += order;
// 		main.push_back(*(it + order - 1));
// 	}

// 	if (is_odd) odd = *(end + order - 1);

// 	left.insert(left.end(), end + (order * is_odd), vec.end());

// 	if (is_odd || !pend.empty())
// 		insert(main, pend, odd, left, vec, is_odd, order);
// 	if(order == 1)
// 		_end = clock();
// }


// template <typename T>
// int PmergeMe<T>::Jacobsthal(int k){
//     return round((pow(2, k + 1) + pow(-1, k)) / 3);
// }


// template <typename T>
// void PmergeMe<T>::insert(T &main, T &pend, valuetype odd, T &left, T &vec, bool is_odd, int order) {
// 	iterator end;
// 	if (pend.size() == 1) {
// 		end = std::upper_bound(main.begin(), main.end(), *pend.begin());
// 		main.insert(end, *pend.begin());
// 	} else if (pend.size() > 1) {
// 		size_t jc = 3;
// 		size_t count = 0;
// 		size_t idx;
// 		size_t decrease;
// 		while (!pend.empty()) {
// 			idx = Jacobsthal(jc) - Jacobsthal(jc - 1);
// 			if (idx > pend.size())
// 				idx = pend.size();
// 			decrease = 0;
// 			while (idx) {
// 				end = main.begin();
// 				if (Jacobsthal(jc + count) - decrease <= main.size())
// 					end = main.begin() + Jacobsthal(jc + count) - decrease;
// 				else
// 					end = main.end();
// 				end = std::upper_bound(main.begin(), end, *(pend.begin() + idx - 1));
// 				main.insert(end, *(pend.begin() + idx - 1));
// 				pend.erase(pend.begin() + idx - 1);
// 				idx--;
// 				decrease++;
// 				count++;
// 			}
// 			jc++;
// 		}
// 	}
// 	T yaslam;
// 	if (is_odd) {
// 		end = std::upper_bound(main.begin(), main.end(), odd);
// 		main.insert(end, odd);
// 	}
// 	for (iterator i = main.begin(); i != main.end(); i++) {
// 		iterator it = std::find(vec.begin(), vec.end(), *i);
// 		yaslam.insert(yaslam.end(), it - (order - 1), it + 1);
// 	}
// 	yaslam.insert(yaslam.end(), left.begin(), left.end());
// 	vec = yaslam;
// }
