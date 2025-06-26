#ifndef RPN_HPP
#define RPN_HPP

# include <iostream>
# include <stack>
# include <algorithm>
# include <sstream>

void	check_operation(std::stack<int> &stack, std::string &token);
void	push_to_stack(std::stack<int> &stack, std::string &token);
int		evaluateRPN(std::stack<int> &stack, std::istringstream &iss, std::string &token);

#endif
