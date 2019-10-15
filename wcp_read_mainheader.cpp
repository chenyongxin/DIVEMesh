/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2019 Hans Bihs

This file is part of REEF3D.

REEF3D is free software; you can redistribute it and/or modify it
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

#include"wcp.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void wcp::read_mainheader(lexer *p, dive *a)
{
    ifstream mainhead;
	mainhead.open(name, ios::binary);
    
    // count numiter
    mainhead.read((char*)&iin, sizeof (int));
    mainhead.read((char*)&iin, sizeof (int));
    mainhead.read((char*)&iin, sizeof (int));
    mainhead.read((char*)&iin, sizeof (int));
    
    numiter=0;
    while(!mainhead.eof())
	{
    mainhead.read((char*)&iin, sizeof (int));
 
    mainhead.read((char*)&ddn, sizeof (double));    
    ++numiter;
    }
    
    mainhead.close();
    
    p->Darray(simtime,numiter);
    
    
    // read mainhead
    mainhead.open(name, ios::binary);
    
    mainhead.read((char*)&iin, sizeof (int));
	numprocs=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGx=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGy=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGz=iin;
    
    count=0;
    while(!mainhead.eof())
	{
    mainhead.read((char*)&iin, sizeof (int));
 
    mainhead.read((char*)&ddn, sizeof (double)); 
    simtime[count] = ddn;
    ++count;
    }
    
    mainhead.close();
}
