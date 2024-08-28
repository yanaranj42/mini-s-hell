/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:41:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/28 18:42:49 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*builtin. Todos estos son esquemas, ya que hay que meter los FD para las
redirecciones y mas cosas
*/
/*tiene que salir por e STDOUT*/
int	ft_env(t_env *env)
{
	printf(YELLOW"OUR ENVIRONMENT\n\n"END);
	while (env && env->next != NULL)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd(GREEN"="END, 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);
	return (0);
}

//IMPRIME EL PRIMER NOMBRE DEL ENVIROMENT EN AMARILLO, NO ENTIENDO PORQUE, 
//Y FALTA EL NAME DE LA ULTIMA VARIABLE DE ENTORNO, SOLO DA EL VALOR

//AL CREAR LA COPIA DEL ENV LLAMO A  ESTA FUNCION PARA QUE AUTOMATICAMENTE 
//SE IMPRIMA LA COPIA Y COMPROVAR QUE SE HACE TODO BIEN, PERO SOLO IMPRIME 
//LO DE OUR ENVIROMENT Y EL MAIL DIRECTAMENTE




int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		printf(BLUE"PWD: %s\n"END, cwd);
		return (SUCCESS);
	}
	return (FAIL);
}
/*busca */

