
#include <iostream>
#include <cmath>
#include <iomanip>
#include <omp.h>
#include <time.h>
using namespace std;
///////////////////Matrices Initialization start//////////////////////
void initialize(float **&upper, float **&lower,float **&identity, float**& inverse,float **&z, int n)
{
	int i,j;
        z= new float *[n];
	upper= new float *[n];
	lower= new float *[n];
	identity= new float *[n];
	inverse= new float *[n];
#pragma omp parallel for schedule(static)
	for (i=0;i<n;i++)
	{
		z[i]= new float [n];
                upper[i]= new float [n];
	        lower[i]= new float [n];
		identity[i]= new float [n];
		inverse[i]= new float [n];
	}
#pragma omp parallel for private(j) schedule(static)
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		
			if (i==j)
			{
				
				upper[i][j]=(((float)i+1)*((float)i+1))/(float)2;;
				lower[i][j]=1;
				identity[i][j]=1;
				inverse[i][j]=0;
                                z[i][j]=0;
			}
			else
			{
				
				upper[i][j]=(((float)i+1)+((float)j+1))/(float)2;
				lower[i][j]=0;
				identity[i][j]=0;
				inverse[i][j]=0;
                                z[i][j]=0;
				
			}

		
}
///////////////////Matrices Initialization end//////////////////////

///////////////////////inverse computing start//////////////////////
void inversecomputing(float **&upper,float **&lower,float **&inverse,float **identity,float **z, int n)
{ 
	float temp;
        int k,i;
         
	////////computing upper&lower start//////////
#pragma omp paralle for private(temp,i,k) schedule(static)
		for (int j=0; j<n-1;j++)

			for (i=j+1;i<n;i++)
			{
				temp=upper[i][j]/upper[j][j];
				lower[i][j]=temp;
				for (int k=j;k<n; k++ )
					upper[i][k]=upper[i][k]-(upper[j][k]*temp) ;
			}
	///////computing upper&lower end////////////
			

	////copmuting [L][Z]=[c]&[u][x]=[z] start////

#pragma omp parallel for firstprivate(i,k) schedule(static) ordered
            for (int j=0; j<n;j++)
       {         
                   
		  
////////// computing [L][z]=[c] start//////////

			for (i = 0 ; i < n ; i++) 
                  {
                    if (i == 0)
                      z[i][j] = identity[i][j]/lower[i][i];
                    else
                   {
                     for (k = 0 ; k < i ; k++)
                     z[i][j] = z[i][j] + lower[i][k] * z[k][j];
                     z[i][j] = (identity[i][j] - z[i][j]) / lower[i][i];
                   }
                  }

///////// computing [L][z]=[c] end////////////

///////// computing [u][x]=[z] start/////////
 
              
              for (i = n-1 ; i >=0 ; i--)
               {
                 if (i == n-1) 
                   inverse[i][j] = z[i][j]/ upper[i][i];
                 else
                 {
              for (k = n-1 ; k > i; k--)
               inverse[i][j] = inverse[i][j] + upper[i][k] * inverse[k][j];
               inverse[i][j] = (z[i][j] - inverse[i][j]) / upper[i][i];
               }
               }

              
///////// computing [u][x]=[z] end//////////

     
 }

			////coputing [L][Z]=[c]&[u][x]=[z] end////

}
/////////////////////inverse computing end//////////////////////////

////////////////////delete matrices start//////////////////////////
void deletematrices(float** upper, float **lower, float **inverse, float **identity, float **z, int n)
{
delete[] upper;

delete[] lower;

delete[] inverse;

delete[] identity;

delete[] z;

}

///////////////////delete matrices end////////////////////////////

////////////////////////printing start/////////////////////////////
void print(float**upper, float** lower,float **inverse, int n)
{
	cout<<"upper matrix"<<endl;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			cout<<upper[i][j]<<" ";
		cout<<endl;
	}

	cout<<"lower matrix"<<endl;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			cout<<lower[i][j]<<" ";
		cout<<endl;
	}
	
	cout<<"inverse matrix"<<endl;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			cout<<inverse[i][j]<<" ";
		cout<<endl;
	}
}

/////////////////////////printing end/////////////////////////////

int main(int argc, char *argv[])
{
	float **upper, **lower, **inverse, **identity, **z, runtime;
	int n = atoi(argv[1]), nthreads = atoi(argv[2]);
        omp_set_num_threads(nthreads); 
	cout<< setiosflags(ios::fixed)<< setprecision(1);
	initialize(upper, lower, identity,inverse ,z, n);
	runtime = omp_get_wtime();
	inversecomputing(upper,lower,inverse,identity,z, n);
	if (n<=9)
	print(upper, lower, inverse, n);
	runtime =omp_get_wtime() - runtime;
	cout<< "Inverse generation runs in "<< runtime << " seconds\n";
	deletematrices (upper, lower,inverse, identity, z, n);
	return 0;
}

