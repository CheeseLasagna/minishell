/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:51:16 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/25 13:48:05 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_overflowcase(char *nprt, int ispositive)
{
	int		a;
	char	*max;

	a = 0;
	while (nprt[a] && nprt[a] > 47 && nprt[a] < 58)
		a++;
	if (a > 19)
		return (1);
	else if (a < 19)
		return (0);
	max = "9223372036854775807";
	a = 0;
	while (nprt[a])
	{
		if (a == 19 && !ispositive && a > 8)
			return (1);
		else if (nprt[a] > max[a])
			return (1);
		a++;
	}
	return (0);
}

static int	ft_overflowresult(int ispositive)
{
	if (ispositive == 1)
		return (-1);
	return (0);
}

int			ft_atoi(const char *nptr)
{
	unsigned int	i;
	int				ispositive;
	int				result;

	ispositive = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		ispositive = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	result = 0;
	if (ft_overflowcase((char*)nptr + i, ispositive))
		return (ft_overflowresult(ispositive));
	while (nptr[i] && nptr[i] > 47 && nptr[i] < 58)
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (result * ispositive);
}
