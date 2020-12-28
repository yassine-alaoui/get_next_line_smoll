#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str)
{
	int i;
	for(i = 0; str[i]; i++);
	return (i);
}

char *ft_strchr(char *str, char c)
{
	for(int i = 0; str[i]; i++)
		if (str[i] == c)
			return (str + i);
	return(0);
}

char *ft_substr(char *str, int start, int len)
{
	char *ret;
	int cc = 0;
	ret = malloc(sizeof(char) * len - start + 1);
	for(int i = 0; i < len - start; i++)
		ret[cc] = str[i + start], cc++;
	ret[cc] = '\0';
	return (ret);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *ret;
	int cc = 0;
	ret = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2));
	for(int i = 0; s1[i]; i++)
		ret[cc] = s1[i], cc++;
	for(int i = 0; s2[i]; i++)
		ret[cc] = s2[i], cc++;
	ret[cc] = '\0';
	free(s1);
	free(s2);
	return (ret);
}

int	get_next_line(char **line)
{
	int ret = 1;
	static char *last = NULL;
	char *buf;
	char *tmp;
	if (!last)
		last = ft_substr(*line, 0, 0);
	while (!(ft_strchr(last, '\n')) && ret > 0)
	{
		buf = malloc(sizeof(char) * 1001);
		if ((ret = read(0, buf, 1001)) < 0)
			return (-1);
		buf[ret] = '\0';
		last = ft_strjoin(last, buf);
	}
	if (ft_strchr(last, '\n'))
	{
		tmp = last;
		*line = ft_substr(last, 0, ft_strchr(last, '\n') - last);
		last = ft_substr(last, ft_strchr(last, '\n') - last + 1, ft_strlen(last));
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_substr(last, 0, ft_strlen(last));
		free(last);
		return (0);
	}
}

int main()
{
	char *line;

	get_next_line(&line);
	printf("%s\n", line);
}