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
yaja 12/09:	export: ya funciona el parseo del argv recibido cuando llamamos al export.
			Ya agrega el nuevo valor a la variable que si existe en la lista.
			En principio no hay error de malloc ni nada.(testear)
			Estoy checkeando que agrege la nueva variable en la lista en caso de que
			esta no exista.
			Hay que limpiar los mensajes y comentarios que tengan los archivos.
yaja 14/09: Ha dejado de funcionar el export. Cuando le pasamos un var que ya existe,
			y no le ponemos un valor, nos la elimina de la lista de export, cuando
			deberia estar pero con valor "".
			Sigue sin funcionar las variables que de valor son NULL, tanto en las
			nuevas como en las ya existentes.

yaja 29/09: una vez llamamos al env despues de hacer un export, la lista nos la
			printa de forma ordenada porque la direccion de momoria a la que
			apuntan es la misma, y se ha modificado el contenido.
			En caso de querer solucionarlo, habria que hacer una copia del
			puntero y modificar esta otra direccion de memoria.
yaja 07/10: hay que revisar que en los mensajes de error, hagan la salida que
			corresponda. Quiza sea por error_brk()
yaja 08/10: no me compila por el father status. Quiero checkear que las senyales
			me esten iniciando bien con el NORM que he definido y luego seguir
			con el resto.
yaja 10/10: actualizacion de la branch con todos los cambios hechos con Marta
	10:28	(del: KO-OK. Unificar la struct cmd en los builtins, etc).
			Tengo una copia de la anterior version de la branch en mi repo personal
			Procedo a agregar el unset, y seguir con las sigs (las iniciales ya
			Funcionan, tendria que mirar las del here_doc)
	12:23	No funcionan los builtins ya que hay que cambiar el orden de funcio-
			namiento en el executor, ya que ha de hacerlo antes de que entre en
			el CHILD
yaja 16/10: el export ya acepta a23=... y a13vb=...
			el cd tiene los errores pero falta la correcta actualizacion del
			oldpwd, que tiene que ver con el update_pwd.
yaja 17/10: el OLDPWD ya funciona bien. Falta eliminar los leaks. Mirar comentario
			L51 env_add_last();
yaja 21/10:	problemas de cd arreglados, ya funciona el OLDPWD.
			CD: ya controla el error si no es o existe el directorio.
			Parece que ya funciona si eliminamos el dir actual. Solo tenemos que
			guardar el dir actual en un PWD temp para que al llamar a la funcion
			me indique algo.
yaja 07/11:	he agregado la flag hidden con exito en el export y unset (igual
			quedamos a espera de que lo testeen). Ya printa las listas del env y
			export ocultando las vars que se han hecho unset.
			19:35 - he agregado el hidden en el expansor y CD.
			Creo que lo podemos pasar a testeo para ver por donde mas nos puede
			fallar. Ocultamos y modificamos el PWD y OLD aunque no veamos el
			resultado.
yaja 12/11:	CD actualizado. Si eliminamos un directorio, ya nos sale en msj de
			error. Y si volvemos al anterior y no existe, ya tenemos error de 
			"retrueving dir".
yaja 17/11:	signals en modo normal funcionan. Falta mirar porque no lo hace en
			el heredoc
