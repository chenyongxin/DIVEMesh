/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2019 Hans Bihs

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

#include"solid.h"
#include"dive.h"
#include"lexer.h"


void solid::ray_cast_y(lexer* p, dive* a, int ts, int te)
{
	double ys,ye,zs,ze;
	double Px,Py,Pz;
	double Qx,Qy,Qz;
	double Rx,Ry,Rz;
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Cx,Cy,Cz;
	double PQx,PQy,PQz;
	double PAx,PAy,PAz;
	double PBx,PBy,PBz;
	double PCx,PCy,PCz;
	double Mx,My,Mz;
	int is,ie,js,je,ks,ke;
	int ir,insidecheck;
	double u,v,w;
	double denom;
	double psi = 1.0e-8*p->DXM;

    
	for(n=ts; n<te; ++n)
	{
	Ax = p->tri_x[n][0];
	Ay = p->tri_y[n][0];
	Az = p->tri_z[n][0];
		
	Bx = p->tri_x[n][1];
	By = p->tri_y[n][1];
	Bz = p->tri_z[n][1];
		
	Cx = p->tri_x[n][2];
	Cy = p->tri_y[n][2];
	Cz = p->tri_z[n][2];
	
	xs = MIN3(Ax,Bx,Cx);
	xe = MAX3(Ax,Bx,Cx);
	
	zs = MIN3(Az,Bz,Cz);
	ze = MAX3(Az,Bz,Cz);
	
	is = p->posf_i(xs);
	ie = p->posf_i(xe);
	
	ks = p->posf_k(zs);
    ke = p->posf_k(ze);
    
    xs = MIN3(Ax,Bx,Cx) - epsi*p->DXP[is +marge-1];
	xe = MAX3(Ax,Bx,Cx) + epsi*p->DXP[ie +marge+1];
	
	zs = MIN3(Az,Bz,Cz) - epsi*p->DZP[ks +marge-1];
	ze = MAX3(Az,Bz,Cz) + epsi*p->DZP[ke +marge+1];
	
	is = p->posf_i(xs);
	ie = p->posf_i(xe);
	
	ks = p->posf_k(zs);
    ke = p->posf_k(ze);
	
	is = MAX(is,0);
	ie = MIN(ie,p->knox);
	
	ks = MAX(ks,0);
	ke = MIN(ke,p->knoz);

	
	
		for(i=is;i<ie;i++)
		for(k=ks;k<ke;k++)
		{
			
		
		Px = p->XN[IP1]+psi + p->xmin;
		Py = p->ymin-10.0*p->DXM ;
		Pz = p->ZN[KP1]+psi + p->zmin;
		
		Qx = p->XN[IP1]+psi + p->xmin;
		Qy = p->ymax+10.0*p->DXM ;
		Qz = p->ZN[KP1]+psi + p->zmin;
		
		
		PQx = Qx-Px;
		PQy = Qy-Py;
		PQz = Qz-Pz;
		
		PAx = Ax-Px;
		PAy = Ay-Py;
		PAz = Az-Pz;
		
		PBx = Bx-Px;
		PBy = By-Py;
		PBz = Bz-Pz;
		
		PCx = Cx-Px;
		PCy = Cy-Py;
		PCz = Cz-Pz;
		
		// uvw
		Mx = PQy*Pz - PQz*Py;
		My = PQz*Px - PQx*Pz;
		Mz = PQx*Py - PQy*Px;

		
		u = PQx*(Cy*Bz - Cz*By) + PQy*(Cz*Bx - Cx*Bz) + PQz*(Cx*By - Cy*Bx)
		  + Mx*(Cx-Bx) + My*(Cy-By) + Mz*(Cz-Bz);
		  
		v = PQx*(Ay*Cz - Az*Cy) + PQy*(Az*Cx - Ax*Cz) + PQz*(Ax*Cy - Ay*Cx)
		  + Mx*(Ax-Cx) + My*(Ay-Cy) + Mz*(Az-Cz);
		  
		w = PQx*(By*Az - Bz*Ay) + PQy*(Bz*Ax - Bx*Az) + PQz*(Bx*Ay - By*Ax)
		  + Mx*(Bx-Ax) + My*(By-Ay) + Mz*(Bz-Az);
		
		
		int check=1;
		if(u==0.0 && v==0.0 && w==0.0)
		check = 0;
		
			if(((u>=0.0 && v>=0.0 && w>=0.0) || (u<0.0 && v<0.0 && w<0.0)) && check==1)
			{
			denom = 1.0/(u+v+w);
			u *= denom;
			v *= denom;
			w *= denom;
			
			Ry = u*Ay + v*By + w*Cy;
			
            j = p->posf_j(Ry);
            
            int distcheck=1;
            
            
            //cout<<"IJ: "<<i<<" "<<j<<" "<<k<<" |   : "<<endl;
            
            if(Ry<p->YN[JP1])
            if(j>=0 && j<=p->knoy)
            if(a->solid(i,j,k)<0 && a->solid(i,j-1,k)<0)
            distcheck=0;
            
            if(Ry>=p->YN[JP1])
            if(j>=0 && j<=p->knoy)
            if(a->solid(i,j,k)<0 && a->solid(i,j+1,k)<0)
            distcheck=0;
            
            
            
            if(distcheck==1)
			for(j=0;j<p->knoy;++j)
			a->solid_dist(i,j,k)=MIN(fabs(Ry-p->YN[JP1]-p->ymin),a->solid_dist(i,j,k));
			}
		}
	}
	
}