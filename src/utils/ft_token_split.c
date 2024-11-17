/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:10 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 03:39:15 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	token_num_words(const char *s, char del, t_general *data)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	init_quote_values(data);
	while (s[i])
	{
		if ((s[i] == '"' && data->qdata.miniquotes == 0) || (s[i] == '\''
				&& data->qdata.quotes == 0))
			account_quotes(s[i], data);
		if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0
			&& s[i] != del && (s[i + 1] == del || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

int	build_matrix_word(t_split *info, int *i, int word, t_general *data)
{
	if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
	{
		find_end_of_the_word(i, info->s, info->del, data);
		info->res[word] = ft_substr(info->s, info->start, *i - info->start);
	}
	else if (data->qdata.quotes == 1)
	{
		find_end_of_the_quotes_word(i, info->s, info->del, data);
		info->res[word] = ft_substr(info->s, info->start, *i - info->start);
	}
	else if (data->qdata.miniquotes == 1)
	{
		find_end_of_the_miniquotes_word(i, info->s, info->del, data);
		info->res[word] = ft_substr(info->s, info->start, *i - info->start);
	}
	if (!info->res[word])
	{
		free_token_matrix(info->res, word);
		return (0);
	}
	return (1);
}

int	matrix_process(t_split *info, int *i, int word, t_general *data)
{
	if ((info->s[*i] == '"' && data->qdata.miniquotes == 0)
		|| (info->s[*i] == '\'' && data->qdata.quotes == 0))
		account_quotes(info->s[*i], data);
	if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		skip_delimiter(i, info->s, info->del, data);
	info->start = *i;
	if (build_matrix_word(info, i, word, data) == 0)
		return (0);
	return (1);
}

char	**matrix_token_words(char **res, const char *s, char del,
		t_general *data)
{
	int		word;
	int		j;
	int		i;
	t_split	info;

	info.s = s;
	info.del = del;
	info.res = res;
	j = 0;
	i = 0;
	word = 0;
	info.stopper = token_num_words(s, del, data);
	while (j < info.stopper)
	{
		if (matrix_process(&info, &i, word, data) == 0)
			return (NULL);
		word++;
		j++;
	}
	info.res[word] = NULL;
	return (info.res);
}

char	**ft_token_split(char const *s, char del, t_general *data)
{
	int		words;
	char	**res;

	words = token_num_words(s, del, data);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res = matrix_token_words(res, s, del, data);
	return (res);
}
