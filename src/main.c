/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:22:34 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/04 20:11:41 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, const char **argv)
{
	t_info general;
	e_prog_state prog_state;

	prog_state = STATE_OK;
	parsing(argc, prog_state);
	inicializer(&general, argc, argv, prog_state);
	// create a function to run all
	pthread_mutex_lock(&(general.die));
	pthread_mutex_unlock(&(general.die));
	//sleep_time(5);
	clean_free(&general);
	return(0);
}