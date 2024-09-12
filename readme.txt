*******************************************************************************
*						ARCHIVO PARA DEJAR NOTAS PARA LA					  *
*						OTRA PERSONA. O RECORDATORIOS PARA					  *
*						LLEVAR UN MEJOR CONTROL DEL PROYECTO				  *
*******************************************************************************

yaja: he tenido que crear este archivo para poder generar ramas.
		usaremos este repositorio para poder trabajar fuera de 42
		y luego ya lo iremos subiendo al bueno.

yaja 12/08: BUILTINS - he creado ya la copia del env con nodos. Y tambien ya me
			los libera correctamente y no genera leaks (por el momento) =)
			He modificado un poco el .h, simplemente he ordenado las funciones
			segun el archivo en el que se encuentren!
	 13/08: he retirado la libft de los headers de los archivos y esta en el .h
			me falta completar funciones para cambiar el path del env para el
			CD. Usar mejor la estructura en lugar de los punteros para moverse
			entre los nodos
	 29/08: he separado los builtins de pwd y env. Y el exit ya funciona. Solo
			quedaria limpiar los mensajes y mirar si queremos controlar el exit
			de LONG MIN
yaja 12/08: export: ya funciona el parseo del argv recibido cuando llamamos al export.
	Ya agrega el nuevo valor a la variable que si existe en la lista.
	En principio no hay error de malloc ni nada.(testear)
	Estoy checkeando que agrege la nueva variable en la lista en caso de que
	esta no exista.
	Hay que limpiar los mensajes y comentarios que tengan los archivos.
