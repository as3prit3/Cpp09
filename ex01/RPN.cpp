# include "RPN.hpp"

void	check_operation(std::stack<int> &stack, std::string &token)
{
	int	operand1, operand2;

	if (stack.size() < 2)
		throw std::exception();
	operand2 = stack.top();
	stack.pop();
	operand1 = stack.top();
	stack.pop();
	if (token == "+")
		stack.push(operand1 + operand2);
	else if (token == "-")
		stack.push(operand1 - operand2);
	else if (token == "*")
		stack.push(operand1 * operand2);
	else
	{
		if (operand2 == 0)
			throw std::exception();
		stack.push(operand1 / operand2);
	}
}

void	push_to_stack(std::stack<int> &stack, std::string &token)
{
	for (size_t i = 0; i < token.length(); ++i)
		if (!isdigit(token[i]))
			throw std::exception();
	double nb = std::atof(token.c_str());
	if (nb < 0 || nb > 9)
		throw std::exception();
	stack.push(static_cast<int>(nb));
}

int	evaluateRPN(std::stack<int> &stack, std::istringstream &iss, std::string &token)
{
	while (iss >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
			check_operation(stack, token);
		else
			push_to_stack(stack, token);
	}
	if (stack.size() != 1)
		throw std::exception();
	return (stack.top());
}
