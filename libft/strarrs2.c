/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarrs2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:15:28 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/07 03:43:52 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_strarr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	remove_last_str_in_strarr(char ***strarr, int *strnum)
{
	char	**tmp;
	int		i;

	tmp = (*strarr);
	if (tmp[*strnum])
		free(tmp[*strnum]);
	*strnum -= 1;
	*strarr = ft_calloc(sizeof(char *), (*strnum) + 2);
	i = 0;
	while (i <= *strnum)
	{
		(*strarr)[i] = tmp[i];
		i++;
	}
	free(tmp);
}

int		add_strarr_to_strarr(char ***arr1, char ***arr2)
{
	int		arr1_len;
	int		arr2_len;
	char	**tmp;
	int		i;

	if (!(*arr2))
		return (1);
	arr1_len = ft_strarrlen(*arr1);
	arr2_len = ft_strarrlen(*arr2);
	tmp = *arr1;
	if (!(*arr1 = ft_calloc(sizeof(char *), arr1_len + arr2_len + 1)))
		return (0);
	i = -1;
	while (++i < arr1_len)
		(*arr1)[i] = tmp[i];
	while (i < arr1_len + arr2_len)
	{
		if (!((*arr1)[i] = ft_strdup((*arr2)[i - arr1_len])))
			return (0);
		i++;
	}
	if (tmp)
		free(tmp);
	return (1);
}
