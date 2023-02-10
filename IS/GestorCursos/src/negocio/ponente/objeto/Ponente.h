/*
 * Ponente.h
 *
 *  Created on: 3 dic 2022
 *      Author: youne
 */

#ifndef NEGOCIO_PONENTE_PONENTE_H_
#define NEGOCIO_PONENTE_PONENTE_H_
#include <iostream>
#include <cstdlib>

class Ponente {
private:
	std::string dni_;
	std::string nombre_;
	std::string tipoPonente_;
public:
	Ponente(std::string dni, std::string nombre,std::string tipoPonente){
		dni_ = dni;
		nombre_ = nombre;
		tipoPonente_ = tipoPonente;
	}


	virtual ~Ponente();

	const std::string& getDni() const {
		return dni_;
	}

	void setDni(const std::string &dni) {
		dni_ = dni;
	}

	const std::string& getNombre() const {
		return nombre_;
	}

	void setNombre(const std::string &nombre) {
		nombre_ = nombre;
	}

	std::string getTipoPonente() const {
		return tipoPonente_;
	}

	void setTipoPonente(std::string tipoPonente) {
		tipoPonente_ = tipoPonente;
	}


};

#endif /* NEGOCIO_PONENTE_PONENTE_H_ */
