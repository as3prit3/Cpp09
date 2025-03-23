#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <algorithm>
# include <fstream>
# include <sstream>
# include <iomanip>

bool	is_valide_price(double price);
bool	is_valide_date(std::string date);
void	find_closest_date(std::map<std::string, double> &btcprices, std::string date, double price);
void	get_input_file(std::map<std::string, double> &btcprices, char *filename);
void	get_data_file(std::map<std::string, double> &btcprices);

#endif
