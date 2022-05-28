/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:22 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/28 17:33:47 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_paths(char *env_var, char *cmd)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(env_var, ':');
	if(!path[i])
	{
		printf("UO");
		
	}
	while (path[i])
	{
		path[i] = ft_strjoin2(path[i], "/");
		path[i] = ft_strjoin2(path[i], cmd);
		if (access(path[i], F_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

int envlist_sz(t_envlist **envlist)
{
	int count;
	t_envlist *env;

	count = 0;
	env = (*envlist);
	while(env)
	{
		count++;
		env = env->next;
	}
	return(count);
}

char **envlist_to_envarr(t_envlist **envlist)
{
	char **arr;
	int i;
	t_envlist *env;
	
	i = 0;
	env = (*envlist);
	arr = malloc(envlist_sz(envlist) * sizeof(char *));
	while(env)
	{
		arr[i] = join_3_strings(env->key, "=", env->value);
		i++;
		env = env->next;
	}
	arr[i] = 0;
	return(arr);
}

void	execute_cmd(t_parse *cmd_list,t_envlist **envlist)
{
	char	*path;
	char **envp;

	envp = envlist_to_envarr(envlist);
	if (cmd_list->cmd)
	{
		path = ft_paths(env_value(envlist, "PATH"), cmd_list->cmd);
		if (execve(path, cmd_list->args, envp) == -1)
			exit(127);
	}
	exit(99);
}
