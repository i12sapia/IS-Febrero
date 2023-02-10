/*
 * Usuario.cpp
 *
 *  Created on: 4 dic 2022
 *      Author: youne
 */

#include "Usuario.h"
#include "../datos/UsuarioDatos.h"

UsuarioDatos usuarioDatos;


TipoUsuario Usuario::iniciarSesion(std::string dni, std::string clave){
	TipoUsuario tipoUsuario = TipoUsuario::INCORRECTO;
	Usuario usuario;
	if(!usuarioDatos.existeUsuario(dni)) {
		return tipoUsuario;
	}else{
		usuario = usuarioDatos.buscar(dni);
		if (usuario.getClaveAcceso() == clave){
			return usuario.getTipoUsuario();
		}else{
			return tipoUsuario;
		}
	}

	return tipoUsuario;
}

bool Usuario::crearUsuario (Usuario usuario){
	if(!usuarioDatos.existeUsuario(usuario.getDni())){
		if (usuarioDatos.insertar(usuario)) return true;
		return false;
	}
	return false;
}

bool Usuario::modificarUsuario(Usuario usuario) {
	if (usuarioDatos.existeUsuario(usuario.getDni())) {
		if (usuarioDatos.modificar(usuario)) return true;
		else return false;
	}else return false;
}

bool Usuario::modificarClaveAcceso(std::string dniUsuario, std::string nuevaClave) {
	Usuario usuario;
	if (usuarioDatos.existeUsuario(dniUsuario)) {
		usuario = usuarioDatos.buscar(dniUsuario);
		usuario.setClaveAcceso(nuevaClave);
		if (modificarUsuario(usuario)) return true;
		return false;
	}else return false;

}








