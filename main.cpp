#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

void initial(int a[], int n);
void ordonCresc(int a[], int n);
void ordonDescresc(int a[], int n);
void invers(int a[], int n);
void inter(int a[], int b[], int rez[], int na, int nb);
void divizibil(int a[], int n, int &, int &, int &);
int prezent(int x, int v[], int n);
void scriu(int a[], int n);

int main()
{
    int a[100], b[100] , c[100];
    int n =7;
    // I start the random number generator
    // Create the n random values.
    initial(a, n);
    initial(b, n);
    //Sort ascending the string "a" with a Bubble Sort
    ordonCresc(a, n);
    //Display the string a
    cout << "String 'a' sorted ascending (Bubble Sort):" << endl;
    for (int i = 0; i < n-1; i++)
        cout << a[i] << ", ";
    cout << a[n-1];

    //Sort descending the string "b" with an Insertion Sort
    ordonDescresc(b, n);
    //Display the string b
    cout << endl;
    cout << "String 'b' sorted descending (Insertion Sort):" << endl;
    for (int i = 0; i < n-1; i++)
        cout << b[i] << ", ";
    cout << b[n-1];

    //Invert the series b
    invers(b, n);
    //Merge the ordered series a and b to obtain a new series c ascending
    //order
    inter(a, b, c, n, n);
    //Display the string c
    cout << endl;
    cout << "Merged ascending strings a and b:" << endl;
    for (int i = 0; i < 2*n - 1; i++)
        cout << c[i] << ", ";
    cout << c[2*n - 1] << endl;

    int div3, div5, div3_5;

    //Display how many values in the series c meet the conditions: they are
    //divisible by 3 (nrdiv3); are divisible by 5 (nrdin5); are divisible
    //by both 3 and 5(nrdiv3si5).
    divizibil(c, 2*n, div3, div5, div3_5);

    cout << "Divisible by 3: " << div3 << " numbers, " << endl;
    cout << "Divisible by 5: " << div5 << " numbers, " << endl;
    cout << "Divisible by 3 and 5: " << div3_5 << " numbers." << endl;

    //Check if a certain value 6334 is present in the series c
    cout << "Check if a certain value 6334 is present in the series c:";
    cout << endl;
    if (prezent(6334, c, 2*n))
        cout << "Present!" << endl;
    else
        cout << "Absent!" << endl;

    //Write the values in series c to a file fdate.txt on disk
    scriu(c, 2*n);

    return 0;
}

void initial(int a[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        a[i] = rand();
}

//Bubble Sort ascending order
void ordonCresc(int a[], int n)
{
   int i, aux, fanion, k;
   k = 0;

   do
   {
      fanion = 0;//Initialize outside the cycle

      for(i = 0; i < n - 1 - k; i++)
      {
         if(a[i] > a[i + 1])
         {
            aux = a[i];
            a[i] = a[i + 1];
            a[i + 1] = aux;
            fanion = 1;//A reversal has been made
         }
      }
      k++;
   }
   while (fanion);//The string is ordered
}

//Insertion Sort descending order
void ordonDescresc(int a[], int n)
{
    int i, j, aux;

    for(i = 1; i < n; i++)  //  i is the mark
    {
        for(j = i; j > 0; j--)
        {
            if(a[j - 1] < a[j])
            {
                aux = a[j - 1];
                a[j - 1] = a[j];
                a[j] = aux;
            }
        }
    }
}

//Invert the series
void invers(int a[], int n)
{
    int i, j, aux;

    for (i = 0, j = n - 1; i < j; i++, j--)
    {
        aux = a[i];
        a[i] = a[j];
        a[j] = aux;
    }
}

//Merge the ordered series a and b to obtain a new series rez ascending
//order
void inter(int a[], int b[], int rez[], int na, int nb)
{
	int i=0, j=0;

	do
	{
		if(i < na && j < nb)
			if(a[i] <= b[j])
			{
				rez[i+j] = a[i];
				i++;
			}
			else
			{
				rez[i+j] = b[j];
				j++;
			}
		else
			if(i < na)
			{
				rez[i+j] = a[i];
				i++;
			}
			else
			{
				rez[i+j] = b[j];
				j++;
			}
	}
	while(i + j < na + nb);
}

//How many values in the series c meet the conditions: they are divisible
//by 3 (nrdiv3); are divisible by 5 (nrdin5); are divisible by both 3 and 5
//(nrdiv3si5).
void divizibil(int a[], int n, int &nrdiv3, int &nrdiv5, int &nrdiv3si5)
{
    int i;
    nrdiv3 = nrdiv5 = nrdiv3si5 = 0;

    for (i = 0; i < n; i++)
    {
        if (a[i] % 3 == 0)
            nrdiv3++;

        if (a[i] % 5 == 0)
            nrdiv5++;

        if (a[i] % 3 + a[i] % 5 == 0)
            nrdiv3si5++;
    }
}

//Check if a certain value x is present in the series v
int prezent(int x, int v[], int n)
{
   int mini, maxi, mijloc;
   mini = 0;
   maxi = n - 1;

   while (mini <= maxi)
   {
      mijloc = (mini + maxi) / 2;

      if (x < v[mijloc])
         maxi = mijloc - 1;
      else if (x > v[mijloc])
         mini = mijloc + 1;
      else
         return mijloc;    //  Gasit!
   }
   return -1;              //  Absent!
}

//Write the values in series c to a file fdate.txt on disk
void scriu(int a[], int n)
{
    fstream fd;

    fd.open("fdate.txt", ios::out);

    for (int i = 0; i < n-1; i++)
        fd << a[i] << ", ";
    fd << a[n-1];

    fd.close();
}
