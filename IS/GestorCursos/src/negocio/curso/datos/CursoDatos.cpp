/*
 * CursoDatos.cpp
 *
 *  Created on: 6 dic 2022
 *      Author: youne
 */

#include "CursoDatos.h"
#include "../objeto/Curso.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <list>
#include <cstring>
#include <vector>
#include <cstdio>

static std::string NOMBRE_FICHERO_CURSOS = "Cursos.txt";
static std::string NOMBRE_FICHERO_AUXILIAR = "FicheroAuxiliar.txt";

static std::string IDCURSO = "IDCURSO:";
static std::string NOMBRE = "NOMBRE:";
static std::string DESCRIPCION = "DESCRIPCION:";
static std::string FECHAINICIO = "FECHAINICIO:";
static std::string FECHAFINAL = "FECHAFINAL:";
static std::string ESTADO = "ESTADO:";
static std::string NUMEROALUMNOS = "NUMEROALUMNOS:";
static std::string AFORO = "AFORO:";
static std::string PONENTES = "PONENTES:";
static std::string USUARIOS = "USUARIOS:";
static std::string RECURSOS = "RECURSOS:";

static std::string ACTIVO = "ACTIVO";
static std::string CADUCADO = "CADUCADO";


CursoDatos::CursoDatos() {
	// TODO Auto-generated constructor stub

}

std::list<std::string> split (std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::list<std::string> res;

	while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}

	res.push_back (s.substr (pos_start));
	return res;
}


bool CursoDatos::insertar(Curso curso){
	std::ofstream fichero;
	fichero.open(NOMBRE_FICHERO_CURSOS.c_str(),std::ios::app);
	if (!fichero.is_open()) return false;
	else {
		fichero<<IDCURSO<<curso.getIdCurso()<<"\n";
		fichero<<NOMBRE<<curso.getNombre()<<"\n";
		fichero<<DESCRIPCION<<curso.getDescripcion()<<"\n";
		fichero<<FECHAINICIO<<curso.getFechaInicio()<<"\n";
		fichero<<FECHAFINAL<<curso.getFechaFinal()<<"\n";
		std::string estado;
		if (curso.isEstado()) estado = ACTIVO;
		else estado = CADUCADO;
		fichero<<ESTADO<<estado<<"\n";
		fichero<<NUMEROALUMNOS<<curso.getNumeroAlumnos()<<"\n";
		fichero<<AFORO<<curso.getAforo()<<"\n";

		std::list<std::string> ponentes = curso.getPonentes();
		std::list<std::string> usuarios = curso.getUsuarios();
		std::list<std::string> recursos = curso.getRecursos();

		if (ponentes.empty()){
			fichero<<PONENTES<<"[]\n";
		}else{
			fichero<<PONENTES<<"[";
			for(std::string ponente: ponentes){
				fichero<<ponente<<",";
			}
			fichero<<"]\n";
		}
		if (usuarios.empty()){
			fichero<<USUARIOS<<"[]\n";
		}else{
			fichero<<USUARIOS<<"[";
			for(std::string usuario: usuarios){
				fichero<<usuario<<",";
			}
			fichero<<"]\n";
		}
		if (recursos.empty()){
			fichero<<RECURSOS<<"[]\n";
		}else{
			fichero<<RECURSOS<<"[";
			for(std::string recurso: recursos){
				fichero<<recurso<<",";
			}
			fichero<<"]\n";
		}
	}
	fichero.close();
	return true;
}

bool CursoDatos::existeCurso(int idCurso) {

	std::string lineaFichero;
	std::string cursoBuscar = IDCURSO + std::to_string(idCurso);
	std::fstream fichero;
	if (!fichero.is_open()) {
		fichero.open(NOMBRE_FICHERO_CURSOS,std::ios::in);
		if(!fichero.is_open()) return false;
		else{
			while(getline(fichero,lineaFichero)) {
				if (lineaFichero==cursoBuscar) {
					fichero.close();
					return true;
				}
			}
		}
	}
	return false;
}

Curso CursoDatos::buscar(int idCurso) {
	Curso curso;
	std::string lineaFichero;
	std::ifstream fichero;
	int index1;
	int index2;
	if (existeCurso(idCurso)){
		fichero.open(NOMBRE_FICHERO_CURSOS,std::ios::in);
		while(getline(fichero, lineaFichero)){
			if (lineaFichero==IDCURSO+std::to_string(idCurso)) {
				curso.setIdCurso(idCurso);
				getline(fichero, lineaFichero);
				lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
				curso.setNombre(lineaFichero);
				getline(fichero, lineaFichero);
				lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
				curso.setDescripcion(lineaFichero);
				getline(fichero, lineaFichero);
				lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
				curso.setFechaInicio(lineaFichero);
				getline(fichero, lineaFichero);
				lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
				curso.setFechaFinal(lineaFichero);
				getline(fichero, lineaFichero);
				lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
				if(lineaFichero==ACTIVO)curso.setEstado(true);
				else curso.setEstado(false);
				getline(fichero, lineaFichero);
				lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
				curso.setNumeroAlumnos(std::stoi(lineaFichero));
				getline(fichero, lineaFichero);
				lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
				curso.setAforo(std::stoi(lineaFichero));
				getline(fichero, lineaFichero);
				index1 = lineaFichero.find("[")+1;
				index2 = (lineaFichero.find(",]")) - index1;
				lineaFichero = lineaFichero.substr(index1,index2);
				curso.setPonentes(split(lineaFichero, ","));
				getline(fichero, lineaFichero);
				index1 = lineaFichero.find("[")+1;
				index2 = (lineaFichero.find(",]")) - index1;
				lineaFichero = lineaFichero.substr(index1,index2);
				curso.setUsuarios(split(lineaFichero, ","));
				getline(fichero, lineaFichero);
				index1 = lineaFichero.find("[")+1;
				index2 = (lineaFichero.find(",]")) - index1;
				lineaFichero = lineaFichero.substr(index1,index2);
				curso.setRecursos(split(lineaFichero, ","));
			}
		}
	}
	fichero.close();
	return curso;
}

std::list<Curso> CursoDatos::lectura(){
	std::list<Curso> cursos;
	std::string lineaFichero;
	std::ifstream fichero;
	int index1;
	int index2;
	Curso cursoAux;
	if (!fichero.is_open()) {
		fichero.open(NOMBRE_FICHERO_CURSOS,std::ios::in);
	}
	while(getline(fichero, lineaFichero)){
		lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
		cursoAux.setIdCurso(std::stol(lineaFichero));
		getline(fichero, lineaFichero);
		lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
		cursoAux.setNombre(lineaFichero);
		getline(fichero, lineaFichero);
		lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
		cursoAux.setDescripcion(lineaFichero);
		getline(fichero, lineaFichero);
		lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
		cursoAux.setFechaInicio(lineaFichero);
		getline(fichero, lineaFichero);
		lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
		cursoAux.setFechaFinal(lineaFichero);
		getline(fichero, lineaFichero);
		lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
		if(lineaFichero==ACTIVO)cursoAux.setEstado(true);
		else cursoAux.setEstado(false);
		getline(fichero, lineaFichero);
		lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
		cursoAux.setNumeroAlumnos(std::stoi(lineaFichero));
		getline(fichero, lineaFichero);
		lineaFichero = lineaFichero.substr(lineaFichero.find(":")+1);
		cursoAux.setAforo(std::stoi(lineaFichero));
		getline(fichero, lineaFichero);
		index1 = lineaFichero.find("[")+1;
		index2 = (lineaFichero.find(",]")) - index1;
		lineaFichero = lineaFichero.substr(index1,index2);
		cursoAux.setPonentes(split(lineaFichero, ","));
		getline(fichero, lineaFichero);
		index1 = lineaFichero.find("[")+1;
		index2 = (lineaFichero.find(",]")) - index1;
		lineaFichero = lineaFichero.substr(index1,index2);
		cursoAux.setUsuarios(split(lineaFichero, ","));
		getline(fichero, lineaFichero);
		index1 = lineaFichero.find("[")+1;
		index2 = (lineaFichero.find(",]")) - index1;
		lineaFichero = lineaFichero.substr(index1,index2);
		cursoAux.setRecursos(split(lineaFichero, ","));

		cursos.push_back(cursoAux);
	}
	fichero.close();
	return cursos;
}

bool CursoDatos::modificar(Curso curso){
	std::ifstream ficheroLectura;
	std::ofstream ficheroEscritura;
	std::string lineaFichero;

	if (!existeCurso(curso.getIdCurso())) return false;
	else{
		if (!ficheroLectura.is_open()) {
			ficheroLectura.open(NOMBRE_FICHERO_CURSOS,std::ios::in);
		}
		if (!ficheroEscritura.is_open()) {
			ficheroEscritura.open(NOMBRE_FICHERO_AUXILIAR,std::ios::app);
		}
		while (getline(ficheroLectura,lineaFichero)) {
			if (lineaFichero == IDCURSO+ std::to_string(curso.getIdCurso())) {
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
				getline(ficheroLectura,lineaFichero);
			}else{
				ficheroEscritura<<lineaFichero<<"\n";
			}
		}
	}
	ficheroEscritura.close();
	ficheroLectura.close();
	std::remove("Cursos.txt");
	std::rename("FicheroAuxiliar.txt","Cursos.txt");
	insertar(curso);
	return true;
}

bool CursoDatos::borrar(int idCurso){
	//No se borran cursos
	return true;
}

CursoDatos::~CursoDatos() {
	// TODO Auto-generated destructor stub
}

