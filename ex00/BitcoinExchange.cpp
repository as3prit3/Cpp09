# include "BitcoinExchange.hpp"

bool	is_valide_price(double price)
{
	if (price > 1000)
		return (std::cout << "Error: too large a number." << std::endl, false);
	else if (price < 0)
		return (std::cout << "Error: not a positive number." << std::endl, false);
	return (true);
}

bool	is_valide_date(std::string date)
{
	int year, month, day;
	char dash;
	std::istringstream iss(date);

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	if (!(iss >> year >> dash >> month >> dash >> day))
		return (false);

	if ((day < 1 || day > 31) || (month < 1 || month > 12))
		return (false);

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);

	if (month == 2)
	{
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > 29 || (day == 29 && !isLeapYear))
			return false;
	}
	return (true);
}

void	find_closest_date(std::map<std::string, double> &btcprices, std::string date, double price)
{
	std::map<std::string, double>::iterator i = btcprices.lower_bound(date);
	if (i == btcprices.begin() && date < i->first)
		std::cout << "Error: bad input => " << date << std::endl;
	else
	{
		if (date != i->first || i == btcprices.end())
			--i;
		std::cout << date << " => " << price << " = " << i->second * price << std::endl;
	}
}

void	get_input_file(std::map<std::string, double> &btcprices, char *filename)
{
	std::ifstream infile(filename);
	std::string line;
	std::getline(infile, line);

	if (!infile || line != "date | value")
		return (std::cout << "Invalid input file" << std::endl, void());
	while (std::getline(infile, line))
	{
		std::string	date;
		double		price;
		char 		pipe;
		std::istringstream iss(line);

		iss >> date >> pipe >> price;
		if (!is_valide_date(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue ;
		}
		if (!is_valide_price(price))
			continue ;
		if (btcprices.find(date) != btcprices.end())
			std::cout << date << " => " << price << " = " << btcprices[date] * price << std::endl;
		else
			find_closest_date(btcprices, date, price);
	}
}
