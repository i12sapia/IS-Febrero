/*
 * CursoDatos.h
 *
 *  Created on: 6 dic 2022
 *      Author: youne
 */

#ifndef NEGOCIO_CURSO_DATOS_CURSODATOS_H_
#define NEGOCIO_CURSO_DATOS_CURSODATOS_H_
#include <iostream>
#include <list>
#include <cstdlib>
#include <fstream>
#include "../objeto/Curso.h"

class CursoDatos {
public:
	CursoDatos();
	virtual ~CursoDatos();
	bool existeCurso(int idCurso);
	bool insertar(Curso curso);
	Curso buscar(int idCurso);
	std::list<Curso> lectura();
	bool modificar(Curso curso);
	bool borrar(int idCurso);

};

#endif /* NEGOCIO_CURSO_DATOS_CURSODATOS_H_ */
