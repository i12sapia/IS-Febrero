# include <iostream>
# include <string>
# include <ctime>
# include <cstdlib>
# include <conio.h>
# include <cstdio>
# include <list>
# include "../negocio/curso/objeto/Curso.h"
# include "../negocio/usuario/objeto/Usuario.h"
# include "../negocio/curso/datos/CursoDatos.h"
# include "../negocio/ponente/objeto/Ponente.h"
# include "../negocio/recurso/objeto/Recurso.h"

using namespace std;

void llamada(int op, int us){
	Usuario user;
	Curso cu;
	bool cambioClave, editarCurso, darAlta, darBaja, asigPonente, quitPonente, inscribirAl, borrarIns, estadoCurso, asigRecursos, quitRecurso;
	string dniUser, claveNueva, idPonente, idUsuario, nombreCurso, descripcionCurso, fechaIni, fechaFin;
	int estadistica, numAlumnos, aforoCurso;
	long idCurso;
	string recursos;
	std::list<string> usuariosCurso;
	std::list<string> ponentesCurso;
	std::list<string> recursosCurso;
	switch(op){
	case 1:	//cambiar contraseña
		system("cls");
		cout << "Introduzca su dni: ";
		cin >> dniUser;
		cout << "Introduzca la nueva clave: ";
		cin >> claveNueva;
		cambioClave = user.modificarClaveAcceso(dniUser, claveNueva);
		if (cambioClave) cout << "Se ha cambiado la contraseña con exito." << endl;
		else cout << "No se ha podido modificar la contraseña" << endl;
		system("pause");
		break;

	case 2: {//buscar cursos
		system("cls");
		std::list<Curso> cursosVigentes;
		std::list<Curso> cursosCompletos;
		std::list<Ponente> ponentes;
		int cont = 1, c=1, cont5 = 1;
		bool valido = false;
		if(us == ADMINISTRADOR or us == GESTOR_CURSOS) cout<<"Funcion para mostrar cursos no vigentes no implementada."<<endl;
		cursosVigentes = cu.verCursosVigentes();
		do{
			c = 1;
			cont = 1;
			cont5 = 1;
			system("cls");
			cout<<"Cursos disponibles para la búsqueda(ID): "<< endl;
			for(Curso cur:cursosVigentes){
				idCurso = cur.getIdCurso();
				cout << "Curso " << c << ": " << idCurso << endl;
				c++;
			}
			cout<<"Introduzca la ID del curso que quiere buscar: ";
			cin >> idCurso;
			system("cls");
			for(Curso cur:cursosVigentes){
				if(cur.getIdCurso() == idCurso){
					valido = true;
					nombreCurso = cur.getNombre();
					descripcionCurso = cur.getDescripcion();
					ponentesCurso = cur.getPonentes();
					fechaIni = cur.getFechaInicio();
					fechaFin = cur.getFechaFinal();
					aforoCurso = cur.getAforo();
					cout << "Nombre: " << nombreCurso << endl;
					cout << "ID: " << idCurso << endl;
					cout << "Descripcion: " << descripcionCurso << endl;
					for(string ponentes:ponentesCurso){
						if(cont != 1){
							cout <<"Ponente "<<cont-1<<": "<< ponentes << endl;
						}
						cont++;
					}
					for(string recursos:recursosCurso){
						if(cont5 != 1){
							cout <<"Recurso "<<cont5-1<<": "<< recursos << endl;
						}
						cont5++;
					}
					cout << "Fecha de inicio: " << fechaIni << endl;
					cout << "Fecha de fin: " << fechaFin << endl;
					cout << "Aforo: " << aforoCurso << endl;

				}
			}
			if(valido == false) cout << "No se ha encontrado un curso con esa ID. " << endl;
			system("pause");
		}while(valido == false);

		break;}

	case 3:	{//editar curso
		system("cls");
		Curso cursoEditado;
		std::list<Curso> cursosVigentes;
		cursosVigentes = cu.verCursosVigentes();
		int c = 1;
		cout<<"Cursos disponibles para editar(ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout<<"Introduzca la ID del curso que quiere editar: ";
		cin >> idCurso;
		cin.ignore();
		cout << "Introduzca el nuevo nombre: ";
		getline(cin, nombreCurso);
		cout << "Introduzca la nueva descripcion: ";
		getline(cin, descripcionCurso);
		cout << "Introduzca el nuevo numero de alumnos: ";
		cin >> numAlumnos;
		cin.ignore();
		cout << "Introduzca la nueva fecha de inicio: ";
		getline(cin, fechaIni);
		cout << "Introduzca la nueva fecha de finalizacion: ";
		getline(cin, fechaFin);
		cout << "Introduzca el nuevo aforo: ";
		cin >> aforoCurso;
		cursoEditado.setIdCurso(idCurso);
		cursoEditado.setNombre(nombreCurso);
		cursoEditado.setDescripcion(descripcionCurso);
		cursoEditado.setNumeroAlumnos(numAlumnos);
		cursoEditado.setFechaInicio(fechaIni);
		cursoEditado.setFechaFinal(fechaFin);
		cursoEditado.setAforo(aforoCurso);
		editarCurso = cu.editarCurso(cursoEditado);
		if (editarCurso) cout << "Se ha editado el curso con exito." << endl;
		else cout << "No se ha podido editar el curso." << endl;
		system("pause");
		break;}
	case 4:{	//ver participantes
		system("cls");
		std::list<std::string> listado;
		std::list<Curso> lista;
		std::list<Curso> cursosVigentes;
		cursosVigentes = cu.verCursosVigentes();
		int cont2 = 1, c = 1;
		cout<<"Cursos disponibles para la búsqueda(ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		listado = cu.verListadoAlumnos(idCurso);
		for(std::string alumno:listado){
			cout << "Alumno " << cont2 << ": " << alumno << endl;
			cont2++;
		}
		system("pause");
		break;}

	case 5:{ //generar estadisticas
		system("cls");
		int c = 1;
		std::list<Curso> cursosVigentes;
		cursosVigentes = cu.verCursosVigentes();
		cout<<"Cursos disponibles para la búsqueda(ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		estadistica = cu.generaEstadistica(idCurso);
		cout << "El porcentaje de ocupacion del curso es de " << estadistica << "%" <<endl;
		system("pause");
		break;}

	case 6: {//dar de alta un curso
		Curso nuevoCurso;
		system("cls");
		cout << "Introduzca el nombre del curso: ";
		cin.ignore();
		getline(cin, nombreCurso);
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		cin.ignore();
		cout << "Introduzca la descripcion del curso: ";
		getline(cin, descripcionCurso);
		cout << "Introduzca la fecha de inicio: ";
		getline(cin, fechaIni);
		cout << "Introduzca la fecha de finalizacion: ";
		getline(cin, fechaFin);
		//cin.ignore();
		cout << "Introduzca el aforo maximo del curso: ";
		cin >> aforoCurso;
		estadoCurso = true;
		nuevoCurso.setNumeroAlumnos(0);
		nuevoCurso.setNombre(nombreCurso);
		nuevoCurso.setIdCurso(idCurso);
		nuevoCurso.setDescripcion(descripcionCurso);
		nuevoCurso.setFechaInicio(fechaIni);
		nuevoCurso.setFechaFinal(fechaFin);
		nuevoCurso.setAforo(aforoCurso);
		nuevoCurso.setEstado(estadoCurso);
		darAlta = cu.darDeAlta(nuevoCurso);
		if(darAlta) cout << "Curso creado con exito." << endl;
		else cout << "No se ha podido crear el curso. Ya existe un curso con esa ID" << endl;
		system("pause");
		break;}

	case 7:	{//dar de baja un curso
		system("cls");
		std::list<Curso> cursosVigentes;
		int c = 1;
		cursosVigentes = cu.verCursosVigentes();
		cout<<"Cursos disponibles para la búsqueda(ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		darBaja = cu.darDeBaja(idCurso);
		if (darBaja) cout << "Se ha cambiado el estado del curso con exito." << endl;
		else cout << "No se ha podido cambiar el estado del curso." << endl;
		system("pause");
		break;}

	case 8:	{//asignar ponentes
		system("cls");
		int c = 1;
		std::list<Curso> cursosVigentes;
		cursosVigentes = cu.verCursosVigentes();
		cout<<"Cursos disponibles (ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		cout << "Introduzca la ID del ponente: ";
		cin >> idPonente;
		asigPonente = cu.asignarPonentes(idCurso, idPonente);
		if(asigPonente) cout << "Se ha asignado el ponente con exito." << endl;
		else cout << "No se ha podido asignar el ponente." << endl;
		system("pause");
		break;}

	case 9:	{//quitar ponentes
		system("cls");
		int c = 1;
		std::list<Curso> cursosVigentes;
		cursosVigentes = cu.verCursosVigentes();
		cout<<"Cursos disponibles(ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		cout << "Introduzca la ID del ponente: ";
		cin >> idPonente;
		quitPonente = cu.quitarPonentes(idCurso, idPonente);
		if(quitPonente) cout << "Se ha quitado al ponente con exito." << endl;
		else cout << "No se ha podido quitar el ponente." << endl;
		system("pause");
		break;}

	case 10:{//quitar recursos
		system("cls");
		int c = 1;
		std::list<Curso> cursosVigentes;
		cursosVigentes = cu.verCursosVigentes();
		cout<<"Cursos disponibles(ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		cout << "Introduzca el recurso que desea eliminar: ";
		cin >> recursos;
		quitRecurso = cu.quitarRecursos(idCurso, recursos);
		if(quitRecurso) cout << "Se ha quitado el recurso con exito." << endl;
		else cout << "No se ha podido quitar el recurso." << endl;
		system("pause");
		break;}
	case 11:{//asignar recursos
		system("cls");
		int c = 1;
		std::list<Curso> cursosVigentes;
		cursosVigentes = cu.verCursosVigentes();
		cout<<"Cursos disponibles (ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		cout << "Introduzca el recurso que desea añadir: ";
		cin >> recursos;
		asigRecursos = cu.asignarRecursos(idCurso, recursos);
		if(asigRecursos) {
			cout << "Se ha asignado el recurso con exito." << endl;
		}
		else {
			cout << "No se ha podido asignar el recurso." << endl;
		}

		system("pause");
		break;}

	case 12:{//ver mis cursos
		system("cls");
		std::list<Curso> listaCursos;
		int cont3 = 1;
		cout << "Introduzca la ID del usuario: ";
		cin >> idUsuario;
		listaCursos = cu.verMisCursos(idUsuario);
		cout<<"Lista de cursos del usuario: "<<endl;
		for(Curso list:listaCursos){
			cout<< "Curso " << cont3 << ": " << list.getIdCurso() << endl;
			cont3++;
		}
		system("pause");
		break;}

	case 13:{//inscribirse a un curso
		system("cls");
		int c = 1;
		std::list<Curso> cursosVigentes;
		cursosVigentes = cu.verCursosVigentes();
		cout<<"Cursos disponibles(ID): "<< endl;
		for(Curso cur:cursosVigentes){
			idCurso = cur.getIdCurso();
			cout << "Curso " << c << ": " << idCurso << endl;
			c++;
		}
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		cout << "Introduzca la ID del usuario: ";
		cin >> idUsuario;
		inscribirAl = cu.inscribirAlumno(idCurso, idUsuario);
		if(inscribirAl) cout << "Alumno inscrito con exito." << endl;
		else cout << "No se ha podido inscribir al alumno." << endl;
		system("pause");
		break;}

	case 14:{//abandonar inscripcion
		system("cls");
		cout << "Introduzca la ID del curso: ";
		cin >> idCurso;
		cout << "Introduzca la ID del usuario: ";
		cin >> idUsuario;
		borrarIns = cu.borrarInscripcion(idCurso, idUsuario);
		if(borrarIns) cout << "Alumno borrado con exito." << endl;
		else cout << "No se ha podido borrar al alumno." << endl;
		system("pause");
		break;}

	}
}




void menus(int usuario){
	int opcion = 0;
	int op_def;
	do{
		switch(usuario){
		case ADMINISTRADOR:
			do{
				system("cls");
				cout <<"==============================================="<<endl;
				cout << "0. Cerrar sesion" << endl;
				cout << "1. Cambiar contraseña" << endl;
				cout << "2. Buscar cursos" << endl;
				cout << "3. Editar curso" << endl;
				cout << "4. Ver participantes de un curso" << endl;
				cout << "5. Generar estadísticas de un curso" << endl;
				cout << "6. Dar de alta un curso" << endl;
				cout << "7. Dar de baja un curso" << endl;
				cout << "8. Asignar ponentes a un curso" << endl;
				cout << "9. Quitar ponentes de un curso" << endl;
				cout << "10. Quitar recursos de un curso" << endl;
				cout << "11. Asignar recursos a un curso" << endl;
				cout <<"==============================================="<<endl;
				cin >> opcion;
				if(opcion<0 or opcion>11){
					cout << "La opcion elegida no es valida. Vuelva a elegir...";
					system("pause");
				}
			}while(opcion<0 or opcion>11);
			op_def = opcion;
			llamada(op_def, usuario);
			break;

		case GESTOR_RECURSOS:
			do{
				system("cls");
				cout <<"==============================================="<<endl;
				cout << "0. Cerrar sesion" << endl;
				cout << "1. Cambiar contraseña" << endl;
				cout << "2. Buscar cursos" << endl;
				cout << "3. Quitar recursos de un curso" << endl;
				cout << "4. Asignar recursos a un curso" << endl;
				cout <<"==============================================="<<endl;
				cin >> opcion;
				if(opcion<0 or opcion>4) {
					cout << "La opcion elegida no es valida. Vuelva a elegir...";
					system("pause");
				}
			}while(opcion<0 or opcion>4);
			if(opcion<=2) op_def = opcion;
			else op_def = opcion + 7;
			llamada(op_def, usuario);
			break;

		case GESTOR_CURSOS:
			do{
				system("cls");
				cout <<"==============================================="<<endl;
				cout << "0. Cerrar sesion" << endl;
				cout << "1. Cambiar contraseña" << endl;
				cout << "2. Buscar cursos" << endl;
				cout << "3. Editar curso" << endl;
				cout << "4. Ver participantes de un curso" << endl;
				cout << "5. Generar estadísticas de un curso" << endl;
				cout << "6. Dar de alta un curso" << endl;
				cout << "7. Dar de baja un curso" << endl;
				cout << "8. Asignar ponentes a un curso" << endl;
				cout << "9. Quitar ponentes de un curso" << endl;
				cout <<"==============================================="<<endl;
				cin >> opcion;
				if(opcion<0 or opcion>9){
					cout << "La opcion elegida no es valida. Vuelva a elegir...";
					system("pause");
				}
			}while(opcion<0 or opcion>9);
			op_def = opcion;
			llamada(op_def, usuario);
			break;

		case USUARIO_REGISTRADO:
			do{
				system("cls");
				cout <<"==============================================="<<endl;
				cout << "0. Cerrar sesion" << endl;
				cout << "1. Cambiar contraseña" << endl;
				cout << "2. Buscar cursos" << endl;
				cout << "3. Ver mis cursos" << endl;
				cout << "4. Inscribirse a un curso" << endl;
				cout << "5. Abandonar inscripcion a un curso" <<endl;
				cout <<"==============================================="<<endl;
				cin >> opcion;
				if(opcion<0 or opcion>5){
					cout << "La opcion elegida no es valida. Vuelva a elegir...";
					system("pause");
				}
			}while(opcion<0 or opcion>5);
			if(opcion<=2) op_def = opcion;
			else op_def = opcion + 9;
			llamada(op_def, usuario);
			break;
		}
	}while(opcion != 0);

}






int main () {
	Curso curso;
	Usuario user;
	int op_inicio_sesion, cont3, cont4;
	string dni, clave;
	int tipo_usuario;
	string nombreCurso, descripcionCurso, fechaIni, fechaFin, aforoCurso;
	std::list<string> ponentesCurso;
	std::list<Ponente> ponentes;
	std::list<string> recursosCurso;
	std::list<Recurso> recursos;
	long ID;

	do{
		system("cls");
		cout <<"==============================================="<<endl;
		cout << "1. Ver cursos como usuario invitado" << endl;
		cout << "2. Iniciar sesion" << endl;
		cout << "3. Salir" << endl;
		cout <<"==============================================="<<endl;
		cin >> op_inicio_sesion;
		switch(op_inicio_sesion){
		case 1:{
			std::list<Curso> cursosVigentes2;
			cursosVigentes2 = curso.verCursosVigentes();
			system("cls");
			for(Curso cur:cursosVigentes2){
				cont3 = 1;
				cont4 = 1;
				ID = cur.getIdCurso();
				nombreCurso = cur.getNombre();
				descripcionCurso = cur.getDescripcion();
				ponentesCurso = cur.getPonentes();
				fechaIni = cur.getFechaInicio();
				fechaFin = cur.getFechaFinal();
				aforoCurso = cur.getAforo();
				recursosCurso = cur.getRecursos();
				cout << "Nombre: " << nombreCurso << endl;
				cout << "ID: " << ID << endl;
				cout << "Descripcion: " << descripcionCurso << endl;
				for(string ponentes:ponentesCurso){
					if(cont3 != 1){
						cout <<"Ponente "<<cont3-1<<": "<< ponentes << endl;
					}
					cont3++;
				}
				for(string recursos:recursosCurso){
					if(cont4 != 1){
						cout <<"Recurso "<<cont4-1<<": "<< recursos << endl;
					}
					cont4++;
				}
				cout << "Fecha de inicio: " << fechaIni << endl;
				cout << "Fecha de fin: " << fechaFin << endl;
				cout << "Aforo: " << aforoCurso << endl;
				cout << "===============================" << endl;
			}
			system("pause");
			break;}

		case 2:{
			do{
				system("cls");
				cout << "Introduzca su dni: ";
				cin >> dni;
				cout << "Introduzca su clave: ";
				cin >> clave;
				tipo_usuario = user.iniciarSesion(dni, clave);
				if(tipo_usuario == INCORRECTO) {
					cout << "La contraseña o el dni son incorrectos. Intentelo de nuevo." << endl;
					system("pause");
				}
			}while (tipo_usuario == INCORRECTO);
			menus(tipo_usuario);
			break;}

		case 3:{
			system("cls");
			cout<<"Hasta la proxima"<<endl;
			system("pause");
			break;}

		default:{
			system("cls");
			cout << "Esa no es una opcion valida. Por favor elija de nuevo..."<<endl;
			system("pause");
			break;}

		}

	}while (op_inicio_sesion !=3);

return 0;
}
