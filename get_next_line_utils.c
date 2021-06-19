#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c)
	{
		if (*s == 0)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ptr = s;
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	*s = 0;
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	char	*src;
	size_t	i;

	s1 = malloc(len + 1);
	if (!s1)
		return (NULL);
	src = (char *)s + start;
	i = 0;
	while (*src && i < len)
		s1[i++] = *src++;
	s1[i] = '\0';
	return (s1);
}
