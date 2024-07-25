/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:01:36 by gyvergni          #+#    #+#             */
/*   Updated: 2024/07/25 11:13:20 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi_base(char *str, char *base);

int		base_check(char *str, int len);

int		str_len(char *str);

int		power(unsigned int nbr, int len);

int	power(unsigned int nbr, int len)
{
	unsigned int					i;
	long long int					pow;

	pow = len;
	i = 0;
	while (pow <= nbr)
	{
		pow = pow * len;
		i++;
	}
	return (i + 1);
}

void	ft_putnbr_code(char *code, unsigned int int_nbr, char *base_to, int off)
{
	int						i;
	int						len;
	int						i_nb;
	int						pow;
	unsigned int			nb;

	nb = int_nbr;
	i_nb = 0;
	i = 0;
	pow = power(int_nbr, str_len(base_to));
	len = str_len(base_to);
	while (nb != 0)
	{
		code[pow - i - 1 + off] = base_to[nb % len];
		nb = nb / len;
		i++;
	}
}

char	*converter(unsigned int nbr, char *base_to, char *code, int signe)
{
	if (base_check(base_to, str_len(base_to)) == 1)
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
	code = malloc(sizeof(char) * 2);
	if (!code)
		return ((void *)0);
	while (nbr[i] == 32 || nbr[i] == 43 || nbr[i] == 45 
		|| (nbr[i] >= 9 && nbr[i] <= 13))
		i++;
	if (nbr[i] == base_from[0])
	{
		code[0] = base_to[0];
	}
	else
		code[0] = '0';
	code[1] = '\0';
	return (code);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	unsigned int		int_nbr;
	char				*code;
	int					pow;
	int					signe;
	int					nb;

	if (base_check(base_from, str_len(base_from)) == 0 
		|| base_check(base_to, str_len(base_to)) == 0)
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
	pow = power(int_nbr, str_len(base_to));
	code = malloc(sizeof(char) * (pow + signe));
	code[pow + signe - 1] = '\0';
	return (converter(int_nbr, base_to, code, signe));
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	base_check(char *str, int len)
{
	int		i;
	int		j;

	i = 0;
	if (len <= 1)
		return (0);
	while (str[i])
	{
		if (str[i] == 43 || str[i] == 45
			|| (str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			return (0);
		j = i + 1;
		while (str[j])
		{
			if (str[j] == str[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	decodage(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (9);
}

int	is_base(char p, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == p)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	unsigned int	len;
	unsigned int	i;
	int				num;
	int				signe;

	len = str_len(base);
	signe = 1;
	i = 0;
	num = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) 
			|| str[i] == 32))
		i++;
	while (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			signe = signe * (-1);
		i++;
	}
	while (str[i] != '\0' && is_base(str[i], base) == 1)
		num = num * len + decodage(str[i++], base);
	return (num * signe);
}

