#include "get_next_line.h"

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

	// first read from file
	i = read(fd, buff, BUFFER_SIZE);
	while (i > 0)
	{
		// end the line read with \0 char		
		buff[i] = 0;
		// first copy if nothing stored in *s
		if (!*s)
			*s = ft_substr(buff, 0, i);
		// if *s is not empty, join with what is read in buff
		else
		{
			tmp = *s;
			*s = ft_strjoin(tmp, buff);
			free(tmp);
		}
		// once copy done, search for \n in *s
		// if found, exit loop
		if (ft_strchr(buff, '\n'))
			break ;
		// if not found, read again from file
		i = read(fd, buff, BUFFER_SIZE);
	}
	// once line with \n is read, buff not needed and freed
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

	// first case: file is empty, so *s is NULL
	if (!*s)
	{
		*line = ft_substr("", 0, 0);
		return (0);
	}
	// second case: only one line in file, no \n found
	else if (!ft_strchr(*s, '\n'))
	{
		*line = ft_substr(*s, 0, ft_strlen(*s));
		free(*s);
		*s = NULL;
		return (0);
	}
	// third case: found a line
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
	static char	*s;
	char		*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !buff || read(fd, buff, 0) < 0)
	{
		free(buff);
		return (-1);
	}
	read_line(fd, buff, &s);
	return (make_line(line, &s));
}
