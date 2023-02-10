#ifndef NEGOCIO_RECURSO_RECURSO_H_
#define NEGOCIO_RECURSO_RECURSO_H_
#include <iostream>
#include <cstdlib>

class Recurso{

private:
	std::string nombre_;

public:
	Recurso(std::string nombre){
		nombre_ = nombre;
	}

	virtual ~Recurso();

	const std::string& getNombre() const {
		return nombre_;
	}

	void setNombre(const std::string &nombre) {
		nombre_ = nombre;
	}
};


#endif /* NEGOCIO_RECURSO_RECURSO_H_ */
