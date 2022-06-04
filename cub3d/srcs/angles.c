/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:20:48 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/13 17:45:36 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	rad(float degrees)
{
	return (degrees * (M_PI / 180.0));
}

float	deg(float radians)
{
	return (radians * (180.0 / M_PI));
}

float	normalize_ang(float ang)
{
	if (ang < rad(0))
		ang += rad(360);
	else if (ang > rad(360))
		ang -= rad(360);
	return (ang);
}
