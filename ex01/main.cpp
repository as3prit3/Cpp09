# include "RPN.hpp"

int main(int ac, char **av)
{
	std::stack<int> stack;
	std::istringstream iss(av[1]);
	std::string	token;

	if (ac != 2)
		return (std::cout << "Usage: ./RPN <input>" << std::endl, 1);
	try
	{
		int num = evaluateRPN(stack, iss, token);
		std::cout << num << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Error" << std::endl;
	}
}
