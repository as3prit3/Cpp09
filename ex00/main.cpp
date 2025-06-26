# include "BitcoinExchange.hpp"

void get_data_file(std::map<std::string, double> &btcprices)
{
	std::ifstream dbfile("data.csv");
	std::string line;
	std::getline(dbfile, line);

	while (std::getline(dbfile, line))
	{
		std::string	date;
		double		price;
		std::istringstream iss(line);

		std::getline(iss, date, ',');
		iss >> price;
		btcprices[date] = price;
	}
	dbfile.close();
}

int main (int ac, char **av)
{
	std::map<std::string, double> btcprices;

	if (ac != 2)
		return (std::cout << "Usage: ./btc <input_file>" << std::endl, 1);

	get_data_file(btcprices);
	get_input_file(btcprices, av[1]);
}
