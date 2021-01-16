#ifndef REGISTRO_HPP
#define REGISTRO_HPP 1

#include <string>
#include <ostream>
#include <istream>

class Registro
{
	private:
		std::string _date;
		std::string _state;
		std::string _city;
		std::string _code;
		unsigned int _cases;
		unsigned int _deaths;
		
	public:
		const std::string& date() const;
		const std::string& state() const;
		const std::string& city() const;
		const std::string& code() const;
		unsigned int cases() const;
		unsigned int deaths() const;

		int setDate(const std::string& date);
  	int setState(const std::string& state);
  	int setCity(const std::string& city);
  	int setCode(const std::string& code);
  	int setCases(unsigned int cases);
  	int setDeaths(unsigned int deaths);
	
  	std::ostream& print(std::ostream& os) const;
  	std::istream& read(std::istream& is);
};

inline std::ostream& operator<<(std::ostream& os, const Registro& r)
{
	return r.print(os);
}

inline std::istream& operator>>(std::istream& is, Registro& r)
{
	return r.read(is);
}

#endif /* REGISTRO_HPP */