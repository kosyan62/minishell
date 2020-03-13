/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 17:47:19 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 17:47:19 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

extern char **g_env;

void		get_tilda(char **line, size_t i)
{
	char *tmp;
	char *tmp2;
	char *str[3];

	tmp = *line;
	tmp[i] = '\0';
	if (!(str[0] = ft_strdup(tmp)))
		malloc_error();
	str[1] = ft_get_env_value("HOME");
	if (!(str[2] = ft_strdup(&tmp[i + 1])))
		malloc_error();
	free(*line);
	if (!(tmp = ft_strjoin(str[0], str[1])))
		malloc_error();
	free(str[0]);
	free(str[1]);
	if (!(tmp2 = ft_strjoin(tmp, str[2])))
		malloc_error();
	free(tmp);
	free(str[2]);
	*line = tmp2;
}

size_t		get_dollr_var(char *src, char **dst)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!ft_isalpha(src[i]) && src[i] != '_')
	{
		*dst = ft_strnew(1);
		return (2);
	}
	while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
		i++;
	tmp = ft_strnew(i);
	ft_strncpy(tmp, src, i);
	*dst = ft_get_env_value(tmp);
	free(tmp);
	if (*dst == NULL)
		*dst = ft_strnew(1);
	return (i + 1);
}

void		get_dollar(char **line, size_t i)
{
	char	*tmp;
	char	*tmp2;
	char	*str[3];
	size_t	sp;

	tmp = *line;
	tmp[i] = '\0';
	str[0] = ft_strdup(tmp);
	sp = get_dollr_var(&tmp[i + 1], &str[1]);
	str[2] = ft_strdup(&tmp[i + sp]);
	free(*line);
	tmp = ft_strjoin(str[0], str[1]);
	free(str[0]);
	free(str[1]);
	tmp2 = ft_strjoin(tmp, str[2]);
	free(tmp);
	free(str[2]);
	*line = tmp2;
}

char		*get_expansion(char *line)
{
	size_t i;

	if (!g_env)
		return (line);
	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '~')
			get_tilda(&line, i);
		else if (line[i] == '$')
			get_dollar(&line, i);
		i++;
	}
	return (line);
}
