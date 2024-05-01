/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:16:30 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 18:44:20 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_name_heredoc(int file_heredoc)
{
	char	filename[30];
	char	*number_str;

	ft_bzero(filename, 30);
	number_str = ft_itoa(file_heredoc);
	ft_strlcat(filename, "/tmp/file_heredoc_", 30);
	ft_strlcat(filename, number_str, 30);
	free(number_str);
	return (ft_strdup(filename));
}

char	*ft_move_space(char *command)
{
	while (*command)
	{
		if (*command == ' ' || *command == '\t')
			command++;
		else
			return (command);
	}
	return (command);
}

void	read_heredoc(int *exit_status, t_envp *envp_vars, char *del, char *file)
{
	int		fd;
	char	*line_read;
	int		s;
	t_envp	*t;

	s = *exit_status;
	t = envp_vars;
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line_read = readline("> ");
	while (line_read && (ft_strcmp(line_read, del)))
	{
		get_last_exit_status(&line_read, *exit_status);
		variables(&line_read, envp_vars);
		write(fd, line_read, ft_strlen(line_read));
		write(fd, "\n", 1);
		free(line_read);
		line_read = readline("> ");
	}
	if (!line_read)
		print_error_msg("warning: heredoc delimited by EOF. Wanted", del);
	free(line_read);
	close(fd);
	free(del);
	rl_clear_history();
	exit(0);
}

void	heredoc(char *command)
{
	static int	i;
	char		*file;
	char		*del;
	int			fd;

	i = 0;
	del = ft_file_name(ft_move_space(command));
	file = file_name_heredoc(i);
	i++;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_perror_msg("open", file);
		free(file);
	}
	free(del);
	free(file);
	redirect_fd(fd, 0);
}

int	redirect_input(char *command, t_envp **envp_vars)
{
	char	*file;
	int		fd;
	t_envp	*t;

	t = *envp_vars;
	command = ft_move_space(command);
	file = ft_file_name(command);
	fd = open(file, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("open", file);
		free(file);
		return (0);
	}
	else
	{
		dup2(fd, 0);
		close(fd);
	}
	free(file);
	return (1);
}
