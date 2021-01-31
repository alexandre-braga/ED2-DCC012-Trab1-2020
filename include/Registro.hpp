#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>
#include <ostream>
#include <istream>
#include <vector>
#include <random>

class Registro
{
	private:
		std::string _date;
		std::string _state;
		std::string _city;
		std::string _code;
		int _cases;
		int _deaths;
		
	public:
		const std::string& date() const;
		const std::string& state() const;
		const std::string& city() const;
		const std::string& code() const;
		int cases() const;
		int deaths() const;

		int setDate(const std::string& date);
  		int setState(const std::string& state);
  		int setCity(const std::string& city);
  		int setCode(const std::string& code);
  		int setCases(int cases);
  		int setDeaths(int deaths);
	
  		std::ostream& print(std::ostream& os) const;
  		std::istream& read(std::istream& is);

		static int comparaLocalData(const Registro& r1, const Registro& r2);
		static int comparaCasos(const Registro& r1, const Registro& r2);

		static std::vector<Registro> nAleatorios(std::vector<Registro>& vet, size_t n);
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