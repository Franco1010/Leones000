//
//  main.cpp
//  SIEVE OF ATKINS
//
//  Created by Crystal Rodriguez  on 02/04/17.
//  Copyright © 2017 Crystal Rodriguez . All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define MAX 100000

vector <int> primos;
void SieveOfAtkin( int limit)
{
    int n,y,x,r,i,a;
    bool sieve[limit];
    for (int i=0; i<limit; i++)
        sieve[i] = false;
    
    sieve[2]=true;
    sieve[3]=true;
    for ( x = 1; x*x < limit; x++)
    {
        for ( y = 1; y*y < limit; y++)
        {
            n = (4*x*x)+(y*y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
                sieve[n] ^= true;
            
            n = (3*x*x)+(y*y);
            if (n <= limit && n % 12 == 7)
                sieve[n] ^= true;
            
            n = (3*x*x)-(y*y);
            if (x > y && n <= limit && n % 12 == 11)
                sieve[n] ^= true;
        }
    }
    
    for (r = 5; r*r < limit; r++)
    {
        if (sieve[r])
        {
            for (i= r*r; i < limit; i += r*r)
                sieve[i] = false;
        }
    }
    
    for (a = 2; a < limit; a++)
        if (sieve[a])
            primos.push_back(a);
    
}
