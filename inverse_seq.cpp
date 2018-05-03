#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
///////////////////Matrices Initialization start//////////////////////
void initialize(float **&upper, float **&lower,float **&identity, float**& inverse,int n)
{
	int i,j;
	upper= new float *[n];
	lower= new float *[n];
	identity= new float *[n];
	inverse= new float *[n];
	for (i=0;i<n;i++)
	{
		upper[i]= new float [n];
	    lower[i]= new float [n];
		identity[i]= new float [n];
		inverse[i]= new float [n];
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		
			if (i==j)
			{
				
				upper[i][j]=(((float)i+1)*((float)i+1))/(float)2;;
				lower[i][j]=1;
				identity[i][j]=1;
				inverse[i][j]=0;
			}
			else
			{
				
				upper[i][j]=(((float)i+1)+((float)j+1))/(float)2;
				lower[i][j]=0;
				identity[i][j]=0;
				inverse[i][j]=0;
				
			}

		
}
///////////////////Matrices Initialization end//////////////////////

///////////////////////inverse computing start//////////////////////
void inversecomputing(float **&upper,float **&lower,float **&inverse,float **identity,int n)
{ 
	float temp,*c,*z,*x;
	////////computing upper&lower start//////////
	
		for (int j=0; j<n-1;j++)

			for (int i=j+1;i<n;i++)
			{
				temp=upper[i][j]/upper[j][j];
				lower[i][j]=temp;
				for (int k=j;k<n; k++ )
					upper[i][k]=upper[i][k]-(upper[j][k]*temp) ;
			}
	///////computing upper&lower end////////////
			c= new float [n];
			z= new float [n];
			x= new float [n];
	////copmuting [L][Z]=[c]&[u][x]=[z] start////
       for (int j=0; j<n;j++)
       {
		   for (int i =0; i<n; i++)
			{
				   c[i] = identity[i][j];
                   z[i] = 0;
				   x[i]=0;
		    }
////////// computing [L][z]=[c] start//////////

			for (int i = 0 ; i < n ; i++) 
                  {
                    if (i == 0)
                      z[i] = c[i]/lower[i][i];
                    else
                   {
                     for (int k = 0 ; k < i ; k++)
                     z[i] = z[i] + lower[i][k] * z[k];
                     z[i] = (c[i] - z[i]) / lower[i][i];
                   }
                  }
///////// computing [L][z]=[c] end////////////
///////// computing [u][x]=[z] start/////////
              
              for (int i = n-1 ; i >=0 ; i--)
               {
                 if (i == n-1) 
                   x[i] = z[i]/ upper[i][i];
                 else
                 {
              for (int k = n-1 ; k > i; k--)
               x[i] = x[i] + upper[i][k] * x[k];
               x[i] = (z[i] - x[i]) / upper[i][i];
               }
               }

              
///////// computing [u][x]=[z] end//////////

       for (int i=0;i<n;i++)
		   inverse[i][j]=x[i];
	   }

			////coputing [L][Z]=[c]&[u][x]=[z] end////

delete c;
delete x;
delete z;
}
/////////////////////inverse computing end//////////////////////////

////////////////////delete matrices start//////////////////////////
void deletematrices(float** upper, float **lower, float **inverse, float **identity,int n)
{
delete[] upper;

delete[] lower;

delete[] inverse;

delete[] identity;

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
	float **upper, **lower, **inverse, **identity, runtime;
	int n = atoi(argv[1]); 
	cout<< setiosflags(ios::fixed)<< setprecision(1);
	initialize(upper, lower, identity,inverse ,n);
	runtime = clock()/(float)CLOCKS_PER_SEC;
	inversecomputing(upper,lower,inverse,identity,n);
	if (n<=9)
	print(upper, lower, inverse, n);
	runtime = clock()/(float)CLOCKS_PER_SEC - runtime;
	cout<< "Inverse generation runs in "<< runtime << " seconds\n";
	deletematrices (upper, lower,inverse, identity,n);
	return 0;
}

