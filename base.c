#include "arx.h"

static int	ft_atoi_base(t_st *infix, char *value, int base, int calc)
{
	char			*bvals;
	int				i;
	int				j;
	long long int	res;
	
	bvals = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@_";
	res = 0;
	if (value)
	{
		i = -1;
		while (value[++i])
		{
			j = -1;
			while (++j < base)
			{
				if (bvals[j] == value[i])
				{
					res	= base * res + j;
					break;
				}
			}
			if (j == base)
				return (0);
		}
	}
	if (calc)
		ft_modify_link(infix, ft_itoa(res), "integer");
	return (1);
}

static int	ft_hash_exp(t_st *infix, t_st *begin, int calc)
{
	char	**split;
	int		base;

	split = ft_strsplit(infix->op, '#');
	base = ft_atoi(split[0]);
	if ((base < 2 || base > 64) && !calc)
	{	
		ft_print_error(INVBA, infix, begin);
		//free(split);
		return (0);
	}
	if ((ft_strchr(infix->op, '#') != ft_strrchr(infix->op, '#')) && !calc)
	{
		ft_print_error(INVNU, infix, begin);
		//free(split);
		return (0);
	}
	if (!ft_atoi_base(infix, split[1], base, calc) && !calc)
	{
		ft_print_error(VTGFB, infix, begin);
		//free(split)
		return (0);
	}
	//free(split)
	return (1);
}

static int	ft_hexoct_exp(t_st *infix, t_st *begin, int calc)
{
	char	*tmp;
	int		base;
	int		i;

	if (ft_toupper(infix->op[1]) == 'X')
	{
		base = 16;
		tmp = ft_strdup(&infix->op[2]);
		i = -1;
		while (tmp[++i])
			tmp[i] = ft_tolower(tmp[i]);
	}
	else
	{
		base = 8;
		tmp = ft_strdup(&infix->op[1]);
	}
	if (!ft_atoi_base(infix, tmp, base, calc) && !calc)
	{
		ft_print_error(INVOP, infix, begin);
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int	ft_base(t_st *infix, t_st *begin, int calc)
{
	if (ft_strequ(infix->type, "hash"))
	{
		if (infix->op[0] == '#' && !calc)
		{	
			ft_print_error(OPEXP, infix, begin);
			return (0);
		}	
		if (!ft_hash_exp(infix, begin, calc))
			return (0);
	}
	else if (ft_strequ(infix->type, "hexoct"))
	{
		if (!ft_hexoct_exp(infix, begin, calc))
			return (0);
	}
	return (1);
}

void	ft_base_calc(t_st *infix)
{
	while (infix)
	{
		if (ft_strequ(infix->type, "hash") || ft_strequ(infix->type, "hexoct"))
			ft_base(infix, NULL, 1);
		infix = infix->next;
	}
}
