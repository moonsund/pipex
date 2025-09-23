#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		if (s1[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
    char *line = "hello world";
    char *limiter = "world";
    int l_len = 5;

    if (ft_strncmp(line, limiter, l_len) == 0 &&
        (line[l_len + 1] == '\0' || line[l_len + 1] == '\n'))
    // if (ft_strncmp(line, limiter, l_len))
        printf("YES\n");
    else
        printf("NO\n");




    return 0;
}