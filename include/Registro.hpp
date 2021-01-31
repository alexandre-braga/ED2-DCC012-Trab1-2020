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
  		int setCases(unsigned int cases);
  		int setDeaths(unsigned int deaths);
	
  		std::ostream& print(std::ostream& os) const;
  		std::istream& read(std::istream& is);
		//static std::vector<Registro> nAleatorios(std::vector<Registro>& vet, size_t n);

		static int comparaLocalData(const Registro& r1, const Registro& r2) 
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
		};

		static int comparaCasos(const Registro& r1, const Registro& r2) 
		{
			if (r1.cases() < r2.cases())
				return -1;
			if (r2.cases() < r1.cases())
				return 1;
			return 0;
		};

		static std::vector<Registro> nAleatorios(std::vector<Registro>& vet, size_t n)
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
			for(size_t i = 0; i < n; ++i)
				aleatorios.push_back(vet[distr(gen)]);

			return aleatorios;
		};
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