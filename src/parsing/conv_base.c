/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:01:36 by gyvergni          #+#    #+#             */
/*   Updated: 2024/09/05 11:25:55 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putnbr_code(char *code, unsigned int int_nbr, char *base_to, int off)
{
	int						i;
	size_t					len;
	int						pow;
	unsigned int			nb;

	nb = int_nbr;
	i = 0;
	pow = power(int_nbr, ft_strlen(base_to));
	if (pow == 1)
		pow++;
	len = ft_strlen(base_to);
	while (nb != 0)
	{
		code[pow - i - 1 + off] = base_to[nb % len];
		nb = nb / len;
		i++;
	}
}

char	*generate_code(int pow, int signe, char *code)
{
	if (pow == 1)
	{
		code = malloc(sizeof(char) * (pow + signe + 1));
		if (!code)
			return (NULL);
		code[0] = '0';
		code[pow + signe] = '\0';
	}
	else
	{
		code = malloc(sizeof(char) * (pow + signe));
		if (!code)
			return (NULL);
		code[pow + signe - 1] = '\0';
	}
	return (code);
}

char	*converter(unsigned int nbr, char *base_to, int pow, int signe)
{
	char	*code;

	code = NULL;
	code = generate_code(pow, signe, code);
	if (!code)
		return (NULL);
	if (base_check(base_to, ft_strlen(base_to)) == 1)
	{
		if (signe == 2)
		{
			code[0] = '-';
			ft_putnbr_code(code, nbr, base_to, 1);
		}
		else
			ft_putnbr_code(code, nbr, base_to, 0);
	}
	return (code);
}

char	*cas_zero(char *nbr, char *base_from, char *base_to)
{
	char	*code;
	int		i;

	i = 0;
	code = malloc(sizeof(char) * 3);
	if (!code)
		return ((void *)0);
	while (nbr[i] == 32 || nbr[i] == 43 || nbr[i] == 45
		|| (nbr[i] >= 9 && nbr[i] <= 13))
		i++;
	code[0] = '0';
	if (nbr[i] == base_from[0])
	{
		code[1] = base_to[0];
	}
	else
		code[1] = '0';
	code[2] = '\0';
	return (code);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	unsigned int		int_nbr;
	int					pow;
	int					signe;
	int					nb;

	if (base_check(base_from, ft_strlen(base_from)) == 0
		|| base_check(base_to, ft_strlen(base_to)) == 0)
		return (NULL);
	signe = 1;
	nb = ft_atoi_base(nbr, base_from);
	if (nb == 0)
		return (cas_zero(nbr, base_from, base_to));
	if (nb < 0)
	{
		signe++;
		int_nbr = -nb;
	}
	else
		int_nbr = nb;
	pow = power(int_nbr, ft_strlen(base_to));
	return (converter(int_nbr, base_to, pow, signe));
}
