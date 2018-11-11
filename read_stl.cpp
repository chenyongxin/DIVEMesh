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

#include"lexer.h"

void lexer::read_stl()
{
	string word;
	int count, vert_count;
	
	// read and count number of triangles
	
	ifstream stl("solid.stl", ios_base::in);
	
	count=trinum;
	while(!stl.eof())
	{
	
		stl>>word;
		
		if(word=="facet")
		++count;
	}
    
    //cout<<"READ STL :"<<count<<endl;
	
	stl.close();
	stl.clear();
	
	trinum+=count;
	
	cout<<"STL : "<<trinum<<endl;
	
	// create arrays
	Darray(tri_x,trinum,3);
	Darray(tri_y,trinum,3);
	Darray(tri_z,trinum,3);
	
	Darray(trivec_x,trinum);
	Darray(trivec_y,trinum);
	Darray(trivec_z,trinum);
	
	
	// reopen and read triangles
	

	stl.open("solid.stl", ios_base::in);
	
	int chk=0;
	while(!stl.eof())
	{
		stl>>word;
		
		if(word=="ascii")
		chk=1;

	}
	
	if(chk==0)
	{
	cout<<"Please convert STL file to ASCII format!"<<endl<<endl;
	cout<<"See User's Guide for more information!"<<endl<<endl<<endl;
	//exit(0);
	}
	
	stl.close();
	stl.open("solid.stl", ios_base::in);
	
	count=-1;
	while(!stl.eof())
	{
	
		stl>>word;
		
		if(word=="facet")
		{
		++count;
		vert_count=0;
		}
		
		if(word=="normal")
		stl>>trivec_x[count]>>trivec_y[count]>>trivec_z[count];
		
		if(word=="vertex")
		{
		stl>>tri_x[count][vert_count]>>tri_y[count][vert_count]>>tri_z[count][vert_count];
		++vert_count;
		}
	}
	
	stl.close();
	
	tricount=count+1;
    
    //cout<<"Tricoun_read: "<<tricount<<endl;
	
	// scale STL model
	for(n=0; n<trinum; ++n)
	for(q=0; q<3; ++q)
	{
	tri_x[n][q]*=S4;
	tri_y[n][q]*=S4;
	tri_z[n][q]*=S4;
	}
	
	// change orgin
	if(S7==1)
	for(n=0; n<trinum; ++n)
	for(q=0; q<3; ++q)
	{
	tri_x[n][q]+=S7_dx;
	tri_y[n][q]+=S7_dy;
	tri_z[n][q]+=S7_dz;
	}
	
	
	// rotate STL model
	S8 = S8*PI/180.0;
	
	double xval,yval;
	for(n=0; n<trinum; ++n)
	for(q=0; q<3; ++q)
	{
	xval = tri_x[n][q]*cos(S8) - tri_y[n][q]*sin(S8);
	yval = tri_x[n][q]*sin(S8) + tri_y[n][q]*cos(S8);
	
	tri_x[n][q] = xval;
	tri_y[n][q] = yval;
	}
	

	
	// find min/max coordinates
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Cx,Cy,Cz;
	xs_stl = 1.0e9;
	ys_stl = 1.0e9;
	zs_stl = 1.0e9;
	
	xe_stl = -1.0e9;
	ye_stl = -1.0e9;
	ze_stl = -1.0e9;
	
	for(n=0; n<trinum; ++n)
	{
	Ax = tri_x[n][0];
	Ay = tri_y[n][0];
	Az = tri_z[n][0];
		
	Bx = tri_x[n][1];
	By = tri_y[n][1];
	Bz = tri_z[n][1];
		
	Cx = tri_x[n][2];
	Cy = tri_y[n][2];
	Cz = tri_z[n][2];
	
	xs_stl = MIN(xs_stl,MIN3(Ax,Bx,Cx));
	xe_stl = MAX(xe_stl,MAX3(Ax,Bx,Cx));
	
	ys_stl = MIN(ys_stl,MIN3(Ay,By,Cy));
	ye_stl = MAX(ye_stl,MAX3(Ay,By,Cy));
	
	zs_stl = MIN(zs_stl,MIN3(Az,Bz,Cz));
	ze_stl = MAX(ze_stl,MAX3(Az,Bz,Cz));
	
	}
	
	xs_stl -= S3_xs;
	xe_stl += S3_xe;
	
	ys_stl -= S3_ys;
	ye_stl += S3_ye;
	
	zs_stl -= S3_zs;
	ze_stl += S3_ze;
	
}




void lexer::pre_read_stl()
{
	string word;
	int count, vert_count;
    double val;
    
    double **tx,**ty,**tz;
	
	// read and count number of triangles
	
	ifstream stl("solid.stl", ios_base::in);
	
	count=trinum;
	while(!stl.eof())
	{
	
		stl>>word;
		
		if(word=="facet")
		++count;
	}
	
	stl.close();
	stl.clear();
	
	trinum=count;
	
	cout<<"STL : "<<trinum<<endl;
	
	// create arrays
	Darray(tx,trinum,3);
	Darray(ty,trinum,3);
	Darray(tz,trinum,3);

	
	// reopen and read triangles
	

	stl.open("solid.stl", ios_base::in);
	
	int chk=0;
	while(!stl.eof())
	{
		stl>>word;
		
		if(word=="ascii")
		chk=1;

	}
	
	if(chk==0)
	{
	cout<<"Please convert STL file to ASCII format!"<<endl<<endl;
	cout<<"See User's Guide for more information!"<<endl<<endl<<endl;
	//exit(0);
	}
	
	stl.close();
	stl.open("solid.stl", ios_base::in);
	
	count=-1;
	while(!stl.eof())
	{
	
		stl>>word;
		
		if(word=="facet")
		{
		++count;
		vert_count=0;
		}
		
		if(word=="normal")
		stl>>val>>val>>val;
		
		if(word=="vertex")
		{
		stl>>tx[count][vert_count]>>ty[count][vert_count]>>tz[count][vert_count];
		++vert_count;
		}
	}
	
	stl.close();
	
	tricount=count+1;
	
	// scale STL model
	for(n=0; n<trinum; ++n)
	for(q=0; q<3; ++q)
	{
	tx[n][q]*=S4;
	ty[n][q]*=S4;
	tz[n][q]*=S4;
	}
	
	// change orgin
	if(S7==1)
	for(n=0; n<trinum; ++n)
	for(q=0; q<3; ++q)
	{
	tx[n][q]+=S7_dx;
	ty[n][q]+=S7_dy;
	tz[n][q]+=S7_dz;
	}
	
	
	// rotate STL model
	S8 = S8*PI/180.0;
	
	double xval,yval;
	for(n=0; n<trinum; ++n)
	for(q=0; q<3; ++q)
	{
	xval = tx[n][q]*cos(S8) - ty[n][q]*sin(S8);
	yval = tx[n][q]*sin(S8) + ty[n][q]*cos(S8);
	
	tx[n][q] = xval;
	ty[n][q] = yval;
	}
	

	
	// find min/max coordinates
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Cx,Cy,Cz;
	xs_stl = 1.0e9;
	ys_stl = 1.0e9;
	zs_stl = 1.0e9;
	
	xe_stl = -1.0e9;
	ye_stl = -1.0e9;
	ze_stl = -1.0e9;
	
	for(n=0; n<trinum; ++n)
	{
	Ax = tx[n][0];
	Ay = ty[n][0];
	Az = tz[n][0];
		
	Bx = tx[n][1];
	By = ty[n][1];
	Bz = tz[n][1];
		
	Cx = tx[n][2];
	Cy = ty[n][2];
	Cz = tz[n][2];
	
	xs_stl = MIN(xs_stl,MIN3(Ax,Bx,Cx));
	xe_stl = MAX(xe_stl,MAX3(Ax,Bx,Cx));
	
	ys_stl = MIN(ys_stl,MIN3(Ay,By,Cy));
	ye_stl = MAX(ye_stl,MAX3(Ay,By,Cy));
	
	zs_stl = MIN(zs_stl,MIN3(Az,Bz,Cz));
	ze_stl = MAX(ze_stl,MAX3(Az,Bz,Cz));
	
	}
	
	xs_stl -= S3_xs;
	xe_stl += S3_xe;
	
	ys_stl -= S3_ys;
	ye_stl += S3_ye;
	
	zs_stl -= S3_zs;
	ze_stl += S3_ze;
    
    
    
    del_Darray(tx,trinum,3);
	del_Darray(ty,trinum,3);
	del_Darray(tz,trinum,3);
	
}
