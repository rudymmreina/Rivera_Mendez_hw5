#include <stdio.h>
#include <stdlib.h>
float xprim(float y,float z);
float yprim(float x,float y,float z);
float zprim(float x,float y,float z);
float *RK2(float told,float xold,float yold,float zold,float h);

int main()
{
  char filename[100]="xyz.dat";
  int i;
  float *x;
  float *y;
  float *z;
  float *t;
  float *espacio;
  float tmin=0;
  float tmax=3;
  float h=0.01;
  FILE *in;
  int N=(tmax-tmin)/h;
  espacio=malloc(sizeof(float)*4);
  x=malloc(sizeof(float)*N);
  y=malloc(sizeof(float)*N);
  z=malloc(sizeof(float)*N);
  t=malloc(sizeof(float)*N);
  t[0]=tmin;
  x[0]=-5;
  y[0]=2;
  z[0]=7;
  in = fopen(filename,"w");
  if(!in)
    {
      printf("problems opening the file %s\n", filename);
      exit(1);
    }

  for(i=1;i<N;i++)
    {
      espacio=RK2(t[i-1],x[i-1],y[i-1],z[i-1],h);
      t[i]=espacio[0];
      x[i]=espacio[1];
      y[i]=espacio[2];
      z[i]=espacio[3];
      fprintf(in,"%f \t %f \t %f \t %f \t \n",t[i],x[i],y[i],z[i]);
    }
   
}

float xprim(float x,float y)
{
  float xd;
  float sigma=10.0;
  xd=sigma*(y-x);
  return xd;
}

float yprim(float x,float y,float z)
{
  float yd;
  float rho=28.0;
  yd=x*(rho-z)-y;
  return yd;
}

float zprim(float x,float y, float z)
{
  float zd;
  float beta=8/3;
  zd=x*y-beta*z;
  return zd;
}

float *RK2(float told,float xold,float yold,float zold,float h)
{
  float xp1;
  float yp1;
  float zp1;
  float tmi;
  float xmi;
  float ymi;
  float zmi;
  float xp2;
  float yp2;
  float zp2;
  float *pos;
  float tnew;
  float xnew;
  float ynew;
  float znew;
  pos=malloc(sizeof(float)*3);
  xp1=xprim(xold,yold);
  yp1=yprim(xold,yold,zold);
  zp1=zprim(xold,yold,zold);

  tmi=told+h/2;
  xmi=xold+(h/2)*xp1;
  ymi=yold+(h/2)*yp1;
  zmi=zold+(h/2)*zp1;
  
  xp2=xprim(xmi,ymi);
  yp2=yprim(xmi,ymi,zmi);
  zp2=zprim(xmi,ymi,zmi);
  
  tnew=told+h;
  xnew=xold+h*xp2;
  ynew=yold+h*yp2;
  znew=zold+h*zp2;

  pos[0]=tnew;
  pos[1]=xnew;
  pos[2]=ynew;
  pos[3]=znew;
  
  return pos;

  
}
