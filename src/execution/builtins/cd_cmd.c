/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:24:04 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/05 10:53:46 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	fcd_command_line(char **paths, t_env *env)
{
	t_env	*curr;
	char 	buf[256];
	int		ret;

	curr = env;
	ret = 0;
	fcode.exit_status = 1;
	if ((!ft_strcmp(paths[0], "cd") && paths[1] == NULL))
		chdir(getenv("HOME"));
	if ((*paths != NULL && (!ft_strcmp(paths[1], "~"))))
		chdir(getenv("HOME"));
	else
		ret = chdir((const char *) paths[1]);
	getcwd(buf, 256);
	printf("%s\n", buf);
}
