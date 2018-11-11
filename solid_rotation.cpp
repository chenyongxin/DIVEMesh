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

#include"solid.h"
#include"dive.h"
#include"lexer.h"

void solid::rotate_triangle(lexer* p, dive* a, int ts, int te)
{
	for(int qr=ts;qr<te;++qr)
	{
		rotation(p->tri_x[qr][0],p->tri_y[qr][0],p->tri_z[qr][0],phi,theta,psi);
		rotation(p->tri_x[qr][1],p->tri_y[qr][1],p->tri_z[qr][1],phi,theta,psi);
		rotation(p->tri_x[qr][2],p->tri_y[qr][2],p->tri_z[qr][2],phi,theta,psi);
	}
	
}

void solid::rotation(double &xvec,double &yvec,double &zvec,double phi, double theta, double psi)
{
	double a,b,c;

    // psi
	a = (xvec-xrot)*cos(psi) - (yvec-yrot)*sin(psi); 
	
	b = (xvec-xrot)*sin(psi) + (yvec-yrot)*cos(psi);
	
	c = zvec-zrot;
	
	xvec=a;
	yvec=b;
	zvec=c;	

    // theta
	a = (xvec)*cos(theta) + (zvec)*sin(theta); 
	
	b = yvec;
	
	c = -(xvec)*sin(theta) + (zvec)*cos(theta); 
	
	xvec=a;
	yvec=b;
	zvec=c;	
    
    
    // phi
	a = xvec;
	
	b = (yvec)*cos(phi) - (zvec)*sin(phi); 
	
	c = (yvec)*sin(phi) + (zvec)*cos(phi); 
    
    xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;
}

double solid::xtrans(double xvec,double yvec,double zvec,double xrot,double yrot,double zrot,double alpha,double beta,double gamma)
{
	double a,b,c;
    
    
    // gamma
	a = (xvec-xrot)*cos(gamma) - (yvec-yrot)*sin(gamma); 
	
	b = (xvec-xrot)*sin(gamma) + (yvec-yrot)*cos(gamma);
	
	c = zvec-zrot;
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;
    
    // beta
	a = (xvec-xrot)*cos(beta) + (zvec-zrot)*sin(beta); 
	
	b = yvec-yrot;
	
	c = -(xvec-xrot)*sin(beta) + (zvec-zrot)*cos(beta); 
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;	
    
	// alpha
	a = xvec-xrot;
	
	b = (yvec-yrot)*cos(alpha) - (zvec-zrot)*sin(alpha); 
	
	c = (yvec-yrot)*sin(alpha) + (zvec-zrot)*cos(alpha); 
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;	
	
	
    return xvec;
	
}

double solid::ytrans(double xvec,double yvec,double zvec,double xrot,double yrot,double zrot,double alpha,double beta,double gamma)
{
	double a,b,c;

    
    // gamma
	a = (xvec-xrot)*cos(gamma) - (yvec-yrot)*sin(gamma); 
	
	b = (xvec-xrot)*sin(gamma) + (yvec-yrot)*cos(gamma);
	
	c = zvec-zrot;
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;
	
	// beta
	a = (xvec-xrot)*cos(beta) + (zvec-zrot)*sin(beta); 
	
	b = yvec-yrot;
	
	c = -(xvec-xrot)*sin(beta) + (zvec-zrot)*cos(beta); 
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;

    // alpha
	a = xvec-xrot;
	
	b = (yvec-yrot)*cos(alpha) - (zvec-zrot)*sin(alpha); 
	
	c = (yvec-yrot)*sin(alpha) + (zvec-zrot)*cos(alpha); 
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;	
    
    return yvec;
	
}

double solid::ztrans(double xvec,double yvec,double zvec,double xrot,double yrot,double zrot,double alpha,double beta,double gamma)
{
	double a,b,c;

    // gamma
	a = (xvec-xrot)*cos(gamma) - (yvec-yrot)*sin(gamma); 
	
	b = (xvec-xrot)*sin(gamma) + (yvec-yrot)*cos(gamma);
	
	c = zvec-zrot;
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;
    
    // beta
	a = (xvec-xrot)*cos(beta) + (zvec-zrot)*sin(beta); 
	
	b = yvec-yrot;
	
	c = -(xvec-xrot)*sin(beta) + (zvec-zrot)*cos(beta); 
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;	
    
	// alpha
	a = xvec-xrot;
	
	b = (yvec-yrot)*cos(alpha) - (zvec-zrot)*sin(alpha); 
	
	c = (yvec-yrot)*sin(alpha) + (zvec-zrot)*cos(alpha); 
	
	xvec=a+xrot;
	yvec=b+yrot;
	zvec=c+zrot;	
	
    return zvec;
	
}
    
    
void solid::angle_calc(double dX, double dY, double dZ, double &alpha, double &beta, double &gamma)
{
    double ddX,ddY,ddZ;
    double eps = 1.0e-10;
    
    ddX = fabs(dX)>eps?dX:1.0e20;
    ddY = fabs(dY)>eps?dY:1.0e20;
    ddZ = fabs(dZ)>eps?dZ:1.0e20;
    
    // alpha
    if(dY>eps && dZ>eps)
    alpha = atan(fabs(dZ/ddY));
    
    if(dY<-eps && dZ>eps)
    alpha = -atan(fabs(dZ/ddY));
    
    if(dY<-eps && dZ<-eps)
    alpha = atan(fabs(dZ/ddY));
    
    if(dY>eps && dZ<-eps)
    alpha = -atan(fabs(dZ/ddY));
    
   // beta
    if(dX>eps && dZ>eps)
    beta = -atan(fabs(dZ/ddX));
    
    if(dX<-eps && dZ>eps)
    beta = atan(fabs(dZ/ddX));
    
    if(dX<-eps && dZ<-eps)
    beta = -atan(fabs(dZ/ddX));
    
    if(dX>eps && dZ<-eps)
    beta = atan(fabs(dZ/ddX));
        
        if(fabs(dX)<=eps && dZ>eps)
        beta = -0.5*PI;
                
        if(fabs(dX)<=eps && dZ<-eps)
        beta = 0.5*PI;

    // gamma
    if(dX>eps && dY>eps)
    gamma = atan(fabs(dY/ddX));
    
    if(dX<-eps && dY>eps)
    gamma = atan(fabs(dY/ddX))+0.5*PI;
    
    if(dX<-eps && dY<-eps)
    gamma = atan(fabs(dY/ddX))+PI;
    
    if(dX>eps && dY<-eps)
    gamma = -atan(fabs(dY/ddX));
        
    
        if(dX>eps && fabs(dY)<=eps)
        gamma = 0.0;
        
        if(fabs(dX)<=eps && dY>eps)
        gamma = 0.5*PI;
        
        if(dX<-eps && fabs(dY)<=eps)
        gamma = PI;
        
        if(fabs(dX)<=eps && dY<-eps)
        gamma = -0.5*PI;
}
    
    