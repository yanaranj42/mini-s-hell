//En varias funciones veo que son de tipo int pero en relidad al llamarlas el resultado 
//no se le asigna a nada
//Revisar si hay que cambiarlas a tipo void o si el valor de retorno es necesario para 
//checkear que todo es correcto y en caso contrario hacer free y break del while

//He quitado mi funcion env y he dejado la tuya para unificar, ya que la necesitas para los builtins

//La llamada para crear el env la he sacado de initalitations y la he puesto en el main,
//ya que originalmente ponias que se hiciera la copia if env existe, pero en realidad 
//habria que llamar a la funcion siempre, y si no existe env que retorne null y acabar 
//el programa, para que no de segfault

//Mirar los archivos de builtins.c y minishell.h