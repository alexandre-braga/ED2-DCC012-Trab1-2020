#include "../include/Registro.hpp"

#include <iostream>
#include <cstring>

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

unsigned int Registro::cases() const
{
	return this->_cases;
}

unsigned int Registro::deaths() const
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

int Registro::setCases(unsigned int cases)
{
	// validate cases
	this->_cases = cases;
	return 0;
}

int Registro::setDeaths(unsigned int deaths)
{
	// validate deaths
	this->_deaths = deaths;
	return 0;
}

std::ostream& Registro::print(std::ostream& os) const
{
	os << "Date: " << this->date() << '\n';
	os << "State: " << this->state() << '\n';
	os << "City: " << this->city() << '\n';
	os << "Code: " << this->code() << '\n';
	os << "Cases: " << this->cases() << '\n';
	os << "Deaths: " << this->deaths() << '\n';
	return os;
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
