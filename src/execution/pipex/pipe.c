/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:26:41 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/07 13:34:23 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	fbuilt_check_command(t_cmd_node *info, t_env *env)
{
	char	*key;

	key = env->first->key;
	
	if (!ft_strcmp(info->cmd_[0], "unset"))
	{
		unset_cmd(env, key);
		return (1);
	}
	else if (!ft_strcmp(info->cmd_[0], "export"))
	{
		export_cmd(env, info->cmd_);
		return (1);
	}
	else if (!ft_strcmp(info->cmd_[0], "echo"))
	{
		ft_echo(info->cmd_);
		return (1);
	}
	return (0);
}

int	fcheck_execv_builtin(t_cmd_node *info, t_env *env)
{
	if (info->cmd_)
	{
		if (!ft_strcmp(info->cmd_[0], "pwd"))
		{
			pwd();
			return (1);
		}
		else if (!ft_strcmp(info->cmd_[0], "exit"))
		{
			ft_exit(info->cmd_);
			return (1);
		}
		else if (!ft_strcmp(info->cmd_[0], "cd"))
		{
			fcd_command_line(info->cmd_, env);
			return (1);
		}
		else if (!ft_strcmp(info->cmd_[0], "env"))
		{
			env_cmd(env);
			return (1);
		}
		else if (fbuilt_check_command(info, env))
			return (1);
	}
	return (0);
}

int	fcommand_built(t_cmd_node *command)
{
	if (command->cmd_)
	{
		if (!ft_strcmp(command->cmd_[0], "cd")
			|| !ft_strcmp(command->cmd_[0], "env")
			|| !ft_strcmp(command->cmd_[0], "export")
			|| !ft_strcmp(command->cmd_[0], "unset")
			|| !ft_strcmp(command->cmd_[0], "pwd")
			|| !ft_strcmp(command->cmd_[0], "echo")
			|| !ft_strcmp(command->cmd_[0], "exit"))
			return (1);
	}
	return (0);
}
