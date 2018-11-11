/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

This file is part of DIVEMesh.

DIVEMesh is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------
--------------------------------------------------------------------*/

#include"field2d.h"
#include"lexer.h"

field2d::field2d(lexer *p)
{
	p->Darray(feld,p->knox+2*xma,p->knoy+2*yma);

	dx=-x1+xma;
	dy=-y1+yma;
}



double& field2d::operator()(int ii, int jj)
{
	return feld[ii+dx][jj+dy];
}


