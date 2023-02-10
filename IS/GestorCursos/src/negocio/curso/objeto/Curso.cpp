/*
 * Curso.cpp
 *
 *  Created on: 3 dic 2022
 *      Author: youne
 */

#include "Curso.h"
#include "../../usuario/objeto/Usuario.h"
#include "../datos/CursoDatos.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstring>
#include <iterator>

CursoDatos cursoDatos;


bool Curso::darDeAlta(Curso curso){
	if(!cursoDatos.existeCurso(curso.getIdCurso())) {
		if (cursoDatos.insertar(curso)) return true;
		return false;
	}else return false;

}


bool Curso::darDeBaja(int idCurso){
	//dar de baja un curso es cambiar el estado
	if(cursoDatos.existeCurso(idCurso)) {
		Curso curso = cursoDatos.buscar(idCurso);
		curso.setEstado(false);
		if (cursoDatos.modificar(curso)) return true;
		return false;
	}
	return false;
}

bool Curso::editarCurso(Curso curso){
	if (cursoDatos.existeCurso(curso.getIdCurso())) {
		if (cursoDatos.modificar(curso)) return true;
		else return false;
	}else return false;
}

bool Curso::inscribirAlumno(int idCurso, std::string idUsuario){
	Curso curso = cursoDatos.buscar(idCurso);
	std::list<std::string> usuarios = curso.getUsuarios();
	usuarios.push_back(idUsuario);
	curso.setUsuarios(usuarios);
	int nAlumnosRefrescado = curso.getNumeroAlumnos() + 1;
	curso.setNumeroAlumnos(nAlumnosRefrescado);

	if (cursoDatos.modificar(curso)) return true;
	else return false;
}

bool Curso::borrarInscripcion(int idCurso, std::string idUsuario) {
	Curso curso = cursoDatos.buscar(idCurso);
	std::list<std::string> usuarios = curso.getUsuarios();
	usuarios.remove(idUsuario);
	std::cout<<"break";
	curso.setUsuarios(usuarios);
	int nAlumnosRefrescado = curso.getNumeroAlumnos() - 1;
	curso.setNumeroAlumnos(nAlumnosRefrescado);

	if (cursoDatos.modificar(curso)) return true;
	else return false;
}

std::list<Curso> Curso::verMisCursos (std::string idUsuario){
	std::list<Curso> listadoCompletoCursos = cursoDatos.lectura();
	std::list<Curso> listadoMisCursos;
	for (Curso curso: listadoCompletoCursos) {
		if (curso.isEstado()){
			std::list<std::string> usuarios = curso.getUsuarios();
			for (std::string usuario:usuarios){
				if (usuario == idUsuario){
					listadoMisCursos.push_back(curso);
				}
			}
		}
	}
	return listadoMisCursos;
}

std::list<Curso> Curso::verCursosVigentes (){
	std::list<Curso> listadoCompletoCursos = cursoDatos.lectura();
	std::list<Curso> listadoCursosVigentes;
	for (Curso curso: listadoCompletoCursos) {
		if (curso.isEstado()) {
			listadoCursosVigentes.push_back(curso);
		}
	}
	return listadoCursosVigentes;
}

bool Curso::asignarPonentes(int idCurso, std::string idPonente){
	Curso curso = cursoDatos.buscar(idCurso);
	std::list<std::string> ponentes = curso.getPonentes();
	ponentes.push_back(idPonente);
	curso.setPonentes(ponentes);

	if (cursoDatos.modificar(curso)) return true;
	else return false;
}

bool Curso::quitarPonentes(int idCurso, std::string idPonente){
	Curso curso = cursoDatos.buscar(idCurso);
	std::list<std::string> ponentes = curso.getPonentes();
	ponentes.remove(idPonente);
	curso.setPonentes(ponentes);

	if (cursoDatos.modificar(curso)) return true;
	else return false;
}

bool Curso::asignarRecursos(int idCurso, std::string recursos){
	Curso curso = cursoDatos.buscar(idCurso);
	std::list<std::string> recurso = curso.getRecursos();
	recurso.push_back(recursos);
	curso.setRecursos(recurso);

	if(cursoDatos.modificar(curso)) return true;
	else return false;
}

bool Curso::quitarRecursos(int idCurso, std::string recursos){
	Curso curso = cursoDatos.buscar(idCurso);
	std::list<std::string> recurso = curso.getRecursos();
	recurso.remove(recursos);
	curso.setRecursos(recurso);

	if (cursoDatos.modificar(curso)) return true;
	else return false;
}

std::list<std::string> Curso::verListadoAlumnos(int idCurso){
	std::list<std::string> listadoAlumnos;
	if (cursoDatos.existeCurso(idCurso)) {
		Curso curso = cursoDatos.buscar(idCurso);
		listadoAlumnos = curso.getUsuarios();
	}

	return listadoAlumnos;
}

int Curso::generaEstadistica(int idCurso) {
	Curso curso;
	int inscritos;
	int estadistica;
	int aforo;
	if(cursoDatos.existeCurso(idCurso)) {
		curso = cursoDatos.buscar(idCurso);
		inscritos = curso.getNumeroAlumnos();
		aforo = curso.getAforo();
		estadistica = inscritos * 100 / aforo;
	}
	return estadistica;
}








