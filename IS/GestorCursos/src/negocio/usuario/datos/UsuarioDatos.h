/*
 * UsuarioDatos.h
 *
 *  Created on: 8 dic 2022
 *      Author: youne
 */

#ifndef NEGOCIO_USUARIO_DATOS_USUARIODATOS_H_
#define NEGOCIO_USUARIO_DATOS_USUARIODATOS_H_
#include "../objeto/Usuario.h"
#include <list>
#include <cstdlib>

#include <iostream>

class UsuarioDatos {
public:
	UsuarioDatos();
	bool existeUsuario(std::string dniUsuario);
	bool insertar(Usuario usuario);
	Usuario buscar(std::string dniUsuario);
	bool modificar(Usuario usuario);
	virtual ~UsuarioDatos();
};

#endif /* NEGOCIO_USUARIO_DATOS_USUARIODATOS_H_ */
