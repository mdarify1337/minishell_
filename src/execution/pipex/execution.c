/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:03 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/07 12:50:30 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int     finitial_variables_commands(t_cmd_node  **command, t_mounaji    *value,\
            t_env    *env)
{
    value->start = 0;
    value->end = 0;
    value->proc = 0;
    value->count = fcalcule_size(*(command)) - 1;
    if (!value->count && fcheck_execv_builtin(*command, env))
        return (0);
    value->fd = malloc(value->count * sizeof(int    *));
    value->pid = malloc((value->count + 1) * sizeof(int ));
    value->i = 0;
    *command = (*command)->next;
    return (1);
}

void    fchild_pipe_execution(t_cmd_node   **command, t_mounaji   *val, t_env *env)
{
    if ((*command)->cmd_ && (*command)->cmd_[0])
    {
        val->pid[val->proc++] = fork();
        if (val->pid[val->proc - 1] == 0)
            fchild_command_execution(*(command), env, val);
    }
    if ((*command)->io_in != 0)
        close((*command)->io_in);
    if ((*command)->io_out != 0)
        close((*command)->io_out);
    val->i++;
    *command = (*command)->next;
}

void    fpclose(t_mounaji   *minishell)
{
    while (minishell->start < minishell->end)
    {
        close(minishell->fd[minishell->start][0]);
        close(minishell->fd[minishell->start][1]);
        minishell->start++;
    }
}

void    fwait_command(t_mounaji     *minishell)
{
    int l;

    l = 0;
    while (l < minishell->count + 1)
    {
        waitpid(minishell->pid[l], &minishell->status, 0);
        l++;
    }
    if (minishell->status == 2)
        fcode.exit_status = 130;
    else if (minishell->status == 3)
        fcode.exit_status = 131;
    else if (WIFEXITED(minishell->status))
        fcode.exit_status = WEXITSTATUS(minishell->status);
    free(minishell->pid);
}

void	flinked_execution_pipex(t_cmd_node *shell, t_env *env)
{
	t_mounaji   *value;

    value = malloc(sizeof (t_mounaji ));
    finitial_variables_commands(&shell, value, env);
    while (shell)
    {
        if (value->i && value->count)
        {
            pipe(value->fd[value->i]);
                value->end++;
            if (value->i && !(value->i % 2))
            {
                close(value->fd[value->start][0]);
                close(value->fd[value->start][1]);
                value->start++;
            }
        }
        fchild_pipe_execution(&shell, value, env);
    }
    fpclose(value);
    fwait_command(value);
    free(value->fd);
}
