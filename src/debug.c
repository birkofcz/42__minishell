/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:15:59 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/05 17:09:19 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int i = 0;
    while (data->args[i])
	{
        int j = 0;
        while (data->args[i][j])
		{
            printf("args[%d][%d]: %s\n", i, j, data->args[i][j]);
            j++;
        }
        i++;
    }

	i = 0;
	while (commands[i])
	{
        printf("commands pred checkem[%d] :%s\n",i, commands[i]);
		i++;
    }