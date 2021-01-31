#include "../include/Registro.hpp"

#include <iostream>
#include <cstring>
#include <vector>
#include <random>
#include <algorithm>


int Registro::comparaCasos(const Registro& r1, const Registro& r2) 
{
	return r1.cases() - r2.cases();
}

int Registro::comparaLocalData(const Registro& r1, const Registro& r2) 
{
    if (r1.state() < r2.state())
        return -1;
    if (r2.state() < r1.state())
        return 1;
    if (r1.city() < r2.city())
        return -1;
    if (r2.city() < r1.city())
        return 1;
    if (r1.date() < r2.date())
        return -1;
    return 1;
}

std::vector<Registro> Registro::nAleatorios(std::vector<Registro>& vet, size_t n)
{
	size_t limit;
	if(n <= vet.size())
		limit = n;
	else
		limit = vet.size();
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, limit); // define the range

	std::vector<Registro> aleatorios;
	std::sample(vet.begin(), vet.end(), std::back_inserter(aleatorios), n,  std::mt19937{std::random_device{}()});
	return aleatorios;
	/*
	for(size_t i = 0; i < n; ++i)
		aleatorios.push_back(vet[distr(gen)]);
	return aleatorios;
	*/
}

const std::string& Registro::date() const
{
	return this->_date;
}
const std::string& Registro::state() const
{
	return this->_state;
}

const std::string& Registro::city() const
{
	return this->_city;
}

const std::string& Registro::code() const
{
	return this->_code;
}

int Registro::cases() const
{
	return this->_cases;
}

int Registro::deaths() const
{
	return this->_deaths;
}

int Registro::setDate(const std::string& date)
{
	// validate date
	this->_date = date;
	return 0;
}

int Registro::setState(const std::string& state)
{
	// validate state
	this->_state = state;
	return 0;
}

int Registro::setCity(const std::string& city)
{
	// validate city
	this->_city = city;
	return 0;
}

int Registro::setCode(const std::string& code)
{
	// validate code
	this->_code = code;
	return 0;
}

int Registro::setCases(int cases)
{
	// validate cases
	this->_cases = cases;
	return 0;
}

int Registro::setDeaths(int deaths)
{
	// validate deaths
	this->_deaths = deaths;
	return 0;
}

std::ostream& Registro::print(std::ostream& os) const
{
	return os << this->date() << "," << this->state() << ","
		<< this->city() << "," << this->code() << ","
		<< this->cases() << "," << this->deaths();
}

static std::string string_tok(const std::string *s, char delim)
{
	static size_t pos = 0;
	static const std::string *sptr;

	if (s) {
		sptr = s;
		pos = 0;
	}

	if (pos == sptr->length())
		return "";

	std::string tok;

	if (delim == '\0') {
		tok = sptr->substr(pos);
		pos = sptr->length();

		return tok;
	}

	while (sptr->at(pos) == delim)
		++pos;

	size_t end = sptr->find(delim, pos);

	/* Se não encontrou 'delim' */
	if (end == std::string::npos) {
		tok = sptr->substr(pos);
		pos = sptr->length();
	} else {
		tok = sptr->substr(pos, end - pos);
		pos = end + 1;
	}
	return tok;
}

std::istream& Registro::read(std::istream& is)
{
	std::string line;

	if (std::getline(is, line)) {
		// Adicionar alguma forma de tratamento de erros nessa funcao
		this->setDate(string_tok(&line, ','));
		this->setState(string_tok(nullptr, ','));
		this->setCity(string_tok(nullptr, ','));
		this->setCode(string_tok(nullptr, ','));
		this->setCases(std::stoi(string_tok(nullptr, ',').c_str()));
		this->setDeaths(std::stoi(string_tok(nullptr, '\0').c_str()));
	}
	return is;
}
