#include "microshell.h"

int		ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

char	ft_strcpy(char *dst, char *src)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

char	ft_strdup(char const *str)
{

	int		count;
	char	*ret_s;

	count = ft_strlen(str);
	count++;
	ret_s = malloc(sizeof(char) * count);
	if (ret_s == NULL)
		return (NULL);
	ft_strcpy(ret_s, str);
	return (ret_s);
}
