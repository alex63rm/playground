/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:13:34 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/12 20:28:48 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	x;
int	y;

int fd[2] =

[x, y]

int fd[2][2]

[[x, y], [x, y]]

int fd[2][2][2]

[[[x, y], [x, y]], [[x, y], [x, y]]]

int fd[2][2][2][2]

[[[[x, y], [x, y]], [[x, y], [x, y]]], [[[x, y], [x, y]], [[x, y], [x, y]]]]

//easy process: start writing from right to left

<------------------------
char	array[2][3][4][5]
<------------------------

//start with 5 (5 variables)
[a, b, c, d, e]

// continue with 4 (4 of the previous set)
[[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]]

// continue with 3 (3 of the previous set)
[[[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]], [[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]], [[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]]]

// finish with 2 (2 of the previous set)
[[[[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]], [[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]], [[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]]], [[[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]], [[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]], [[a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e], [a, b, c, d, e]]]]

// we could reorder it for simplicity:
[
	[
		[
			[a, BB, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e]
		],
		[
			[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e]
		],
		[	[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e]
		]
	],
	[
		[
			[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e]
		],
		[
			[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, d, e]
		],
		[	[a, b, c, d, e],
			[a, b, c, d, e],
			[a, b, c, DD, e],
			[a, b, c, d, e]
		]
	]
]

// so, array[0][0][1][1] = B
// array[2][1][3][4] = D