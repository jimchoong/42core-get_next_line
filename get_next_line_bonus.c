#include "get_next_line_bonus.h"

/*
* read_line: 
* DESCRIPTION: Reads line from file, and fill into *s
* PARAMS: int file descriptor fd, char *buffer, our static var char *s
* RETURNS: None
* Cases:
* if empty file: read() returns 0, s remains NULL, buff is empty and freed
* if file <= BUFFER_SIZE: read() returns <= BUFFER_SIZE, copy buff to *s
* if file > BUFFER_SIZE: keep reading and copy to *s until strchr finds \n or EOF
*/
void	read_line(int fd, char *buff, char **s)
{
	ssize_t	i;
	char	*tmp;

	i = read(fd, buff, BUFFER_SIZE);
	while (i > 0)
	{
		buff[i] = 0;
		if (!*s)
			*s = ft_substr(buff, 0, i);
		else
		{
			tmp = *s;
			*s = ft_strjoin(tmp, buff);
			free(tmp);
		}
		if (ft_strchr(buff, '\n'))
			break ;
		i = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
}

/*
* make_line
* DESCRIPTION: process line in *s and copy to **line var
* PARAMS: char **line, static var char **s
* RETURN: 0 if EOF, 1 if \n found
* CASES:
* if empty file: return empty str; *s remains NULL
* if EOF: no \n found; copy *s to *line, free and init *s
* if EOL: found \n, copy before \n to *line, *s updated to line after \n
*/
int	make_line(char **line, char **s)
{
	size_t	eol_idx;
	char	*tmp;

	if (!*s)
	{
		*line = ft_substr("", 0, 0);
		return (0);
	}
	else if (!ft_strchr(*s, '\n'))
	{
		*line = ft_substr(*s, 0, ft_strlen(*s));
		free(*s);
		*s = NULL;
		return (0);
	}
	else
	{
		eol_idx = ft_strchr(*s, '\n') - *s;
		*line = ft_substr(*s, 0, eol_idx);
		tmp = *s;
		*s = ft_substr(tmp, eol_idx + 1, ft_strlen(tmp) - eol_idx + 1);
		free(tmp);
		return (1);
	}
}

/*
* get_next_line:
* DESCRIPTION: returns a line read from file descriptor, without the \n char
* PARAMS: int fd to read, char **line to store value of what has been read
* RETURN: 1 if read success, 0 if EOF, -1 if error
*/
int	get_next_line(int fd, char **line)
{
	static char	*s[FD_SIZE];
	char		*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !buff || read(fd, buff, 0) < 0)
	{
		free(buff);
		return (-1);
	}
	read_line(fd, buff, &s[fd]);
	return (make_line(line, &s[fd]));
}
