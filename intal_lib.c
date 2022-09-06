#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "intal.h"

static char* str_rev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
static void strip(char* str)
{
    int count=0;
    int i=0;
    while(*(str+i) == '0')
    {
        i++;
        count++;
    }
    if(count>0)
    {
        for(int i=0; i<strlen(str)-count; i++)
            str[i]=str[i+count];
        str[strlen(str)-count]='\0';
    }

}
static char* padding(const char* s, int n)
{
    int n1 = strlen(s);
    char* str = malloc(sizeof(char)*(n1+n+1));
    strcpy(str, s);
    if(n==0) 
        return str;
    for(int i = n1; i<(n1+n); i++)
        str[i] = '0';
    str[n1+n] = '\0';
    return str;
}
static void swap_loc(char** str1, char** str2)
{
    char* temp=*str1;
    *str1=*str2;
    *str2=temp;
}

char* intal_add(const char* intal1, const char* intal2)
{
    int num, carry=0;
    char* sum;
    int l, s;
    int i1=strlen(intal1);
    int i2=strlen(intal2);
    int p=0;
    if(i1>=i2)
    {
        l=i1; s=i2;
        sum=malloc(sizeof(char)*(l+2));
        for(int i=s-1; i>=0; i--)
        {
            num=((intal1[i-s+l]-'0')+(intal2[i]-'0')+carry)%10;
            carry=((intal1[i-s+l]-'0')+(intal2[i]-'0')+carry)/10;
            sum[p]=num+'0';
            p++;
        }
        for(int i=l-s-1; i>=0; i--)
        {
            num=((intal1[i]-'0')+carry)%10;
            carry=((intal1[i]-'0')+carry)/10;
            sum[p]=num+'0';
            p++;
        }
        if(carry)
        {
            sum[p++]=carry+'0';
        }
    }
    else
    {
        l=i2; s=i1;
        sum=malloc(sizeof(char)*(l+2));
        for(int i=s-1; i>=0; i--)
        {
            num=((intal1[i]-'0')+(intal2[i-s+l]-'0')+carry)%10;
            carry=((intal1[i]-'0')+(intal2[i-s+l]-'0')+carry)/10;
            sum[p]=num+'0';
            p++;
        }
        for(int i=l-s-1; i>=0; i--)
        {
            num=((intal2[i]-'0')+carry)%10;
            carry=((intal2[i]-'0')+carry)/10;
            sum[p]=num+'0';
            p++;
        }
        if(carry)
        {
            sum[p++]=carry+'0';
        }
        
    }
    sum[p]='\0';
    str_rev(sum);
    return sum;
}

int intal_compare(const char* intal1, const char* intal2)
{
    int i1=strlen(intal1);
    int i2=strlen(intal2);
    if(i1>i2)
        return 1;
    else if(i2>i1)
        return -1;
    else
    {
        int i=0;
        while(i<i1)
        {
            if((intal1[i]-'0')>(intal2[i]-'0'))
                return 1;
            else if((intal1[i]-'0')<(intal2[i]-'0'))
                return -1;
            i++;
        }
        return 0;
    }
}

char* intal_diff(const char* intal1, const char* intal2)
{
    char* result;
    char* large, *small;
    char* n1=malloc(sizeof(char)*(strlen(intal1)+1));
    char* n2=malloc(sizeof(char)*(strlen(intal2)+1));
    strcpy(n1, intal1);
    strcpy(n2, intal2);
    if(intal_compare(intal1, intal2)==0)
    {
        result=malloc(sizeof(char)*2);
        free(n1);
        free(n2);
        *result='0';
        *(result+1)='\0';
        return result;
    }
    else
    {
        int p=0;
        if(intal_compare(intal1, intal2)==1)
        {
            large=n1; 
            small=n2;
        }
        else 
        {
            large=n2; 
            small=n1;
        }   
        int i1=strlen(large);
        int i2=strlen(small);
        int borrow=0;
        result=malloc(sizeof(char)*i1+1);
        for(int i=i2-1; i>=0; i--)
        { 
            int diff=large[i+(i1-i2)]-small[i]-borrow;
            if(diff<0)
            {
                diff=diff+10;
                borrow=1;
            }
            else
                borrow=0;
            result[p++]=diff+'0';
        }
        for(int i=i1-i2-1; i>=0; i--)
        {
            if(large[i]=='0' && borrow)
            {
                result[p++]='9';
                continue;
            }
            int diff=(large[i]-'0')-borrow;
            result[p++]=diff+'0';
            borrow=0;
        }
        result[p]='\0';
    }   
    str_rev(result);
    strip(result);
    free(n1);
    free(n2);
    return result;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
    int len1 = strlen(intal1); 
    int len2 = strlen(intal2);
    char* product=malloc(sizeof(char)*(len1+len2+2));
    for(int i=0; i<len1+len2+1; i++)
        product[i]='0';
    if((intal_compare(intal1, "0")==0) || (intal_compare(intal2, "0")==0))
    {
        *product='0';
        *(product+1)='\0';
        return product;
    }
    else
    {
        int i_n1=0; 
        int i_n2=0;
        for(int i=len1-1; i>=0; i--)
        {
            int carry=0;
            int n1=intal1[i]-'0';
            i_n2=0;
            for(int j=len2-1; j>=0; j--)
            {
                int n2=intal2[j]-'0';
                int sum=n1*n2+(product[i_n1+i_n2]-'0')+carry;
                carry=sum/10;
                product[i_n1+i_n2]=(sum%10)+'0';
                i_n2++;
            }
            if(carry>0)
            {
                product[i_n1+i_n2]=((product[i_n1+i_n2]-'0')+carry)+'0';
            }
            i_n1++;
        }
        
        product[i_n1+i_n2+1]='\0';
    }
    str_rev(product);
    strip(product);
    return product;
}

char* intal_mod(const char* intal1, const char* intal2)
{
    int c = intal_compare(intal1, intal2);
    int n2 = strlen(intal2);
    int n1 = strlen(intal1);

    if(c<0) 
    {
        char* res = malloc(sizeof(char)*(n1+1));
        strcpy(res, intal1);
        return res;
    }
    else if(c==0)
    {
        char* res = malloc(sizeof(char)*2);
        res[0] = '0';
        res[1] = '\0';
        return res;
    } 
    else
    {   
        char* temp;
        char* res = malloc(sizeof(char)*(n1+1));
        char* res_temp;
        strcpy(res, intal1);
        for(int i = n1 - n2; i>=0; i--)
        {
            temp = padding(intal2, i);
            while(intal_compare(res, temp)>0)
            {
                res_temp = intal_diff(res, temp);
                free(res);
                res = res_temp;
            }
            if(intal_compare(res, temp)==0)
            {
                free(res);
                free(temp);
                res = malloc(sizeof(char)*2);
                res[0] = '0';
                res[1] = '\0';
                return res;
            }
            free(temp);
        }
        return res;
    }    
}

char* intal_pow(const char* intal1, unsigned int n)
{
	char* ans=malloc(1000);
	char *temp=malloc(1000);
	strcpy(temp,intal1);
	strcpy(ans,"1");
	while(n>0)
	{	if(n&1)
		{   
            char* temp1;
            temp1=intal_multiply(ans,temp);
            free(ans);
            ans = temp1;
        }
		n=n>>1;
        char* temp1;
		temp1=intal_multiply(temp,temp);
        free(temp);
        temp = temp1;
	}
	free(temp);
	return ans;
}

char* intal_gcd(const char* intal1, const char* intal2)
{
    char* num1=malloc(sizeof(char)*(strlen(intal1)+1));
    strcpy(num1, intal1);
    char* num2=malloc(sizeof(char)*(strlen(intal2)+1));
    strcpy(num2, intal2);
    while(intal_compare(num2, "0")!=0)
    {
        char* temp1=num1;
        num1=intal_mod(temp1, num2);
        free(temp1);
        swap_loc(&num1, &num2);
    }
    free(num2);
    return num1;
}

char* intal_fibonacci(unsigned int n)
{
    char* a=malloc(sizeof(char) * 2);
    a[0]='0'; a[1]='\0';
    char* b=malloc(sizeof(char) * 2);
    b[0]='1'; b[1]='\0';
    char*c;
    if( n == 0) 
    {   
        free(b);
        return a; 
    }
    for (int i = 2; i <= n; i++) 
    { 
        c = intal_add(a, b); 
        free(a);
        a=malloc(sizeof(char) * (strlen(b)+1));
        strcpy(a, b);
        free(b);
        b=malloc(sizeof(char) * (strlen(c)+1));
        strcpy(b, c); 
        free(c);
    } 
    free(a);
    return b;
}

char* intal_factorial(unsigned int n)
{
    if(n==0)
    {
        char* fact=malloc(sizeof(char)*2);
        fact[0]='1';
        fact[1]='\0';
        return fact;
    }
    char* fact=malloc(sizeof(char) * 2);
    strcpy(fact, "1");
    for(int i=2; i<=n; i++)
    {
        char *temp=malloc(sizeof(char) * (strlen(fact)+1));
        strcpy(temp, fact);
        free(fact);
        int dup=i;
        char* num=malloc(sizeof(char)*4);
        int j=0;
        while(dup!=0)
        {
            *(num+j)=(dup%10)+'0';
            dup=dup/10;
            j++;
        }
        *(num+j)='\0';
        str_rev(num);
        fact=intal_multiply(temp, num);
        free(temp);
        free(num);
    }
    return fact;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
    char** c = malloc(sizeof(char*) * (k+1));
    for(int j=0; j<k+1; j++)
    {
        c[j]=malloc(sizeof(char) * 2);
        strcpy(c[j], "0");
    }
    free(c[0]);
    c[0]=malloc(sizeof(char) * 2);
    strcpy(c[0], "1");
    for(int i=1; i<=n; i++)
    {
        int min;
        if(i<k)
            min=i;
        else 
            min=k;
        for(int j=min; j>=1; j--)
        {
            char* temp=c[j];
            c[j]=intal_add(c[j], c[j-1]);
            free(temp);
        }
    }
    char* result=malloc(sizeof(char) * (strlen(c[k])+1));
    strcpy(result, c[k]);
    for(int i=0; i<k+1; i++)
        free(c[i]);
    free(c);
    return result;
}

int intal_max(char **arr, int n)
{
    int off=0;
    char* max= *arr;
    for(int i=0;i<n-1; i++)
    {
        if(intal_compare(max, arr[i+1])==-1)
        {
            max=arr[i+1];
            off=i+1;
        }
    }
    return off;
}

int intal_min(char **arr, int n)
{
    int off=0;
    char* min=*arr;
    for(int i=0; i<n-1; i++)
    {
        if(intal_compare(min, arr[i+1])==1)
        {
            min=arr[i+1];
            off=i+1;
        }
    }
    return off;
}

int intal_search(char **arr, int n, const char* key)
{
    for(int i=0; i<n; i++)
    {
        if(intal_compare(arr[i], key)==0)
            return i;
    }
    return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
    int high=n-1;
    int m = -1;
    int low=0;
    while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (intal_compare(arr[mid], key)==0)
            m = mid;
		if (intal_compare(arr[mid], key)==-1)
			low = mid + 1;
		else
			high = mid - 1;
	}
    return m;
}

static void swap(char** arr, int a, int b)
{
    char* temp=arr[a];
    arr[a]=arr[b];
    arr[b]=temp;
} 
static void heapify(char** arr, int n, int i) 
{ 
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;   
    if (l < n && (intal_compare(arr[l], arr[largest])==1))
        largest = l;  
    if (r < n && (intal_compare(arr[r], arr[largest])==1)) 
        largest = r;  
    if (largest != i) 
    { 
        swap(arr, i, largest);
        heapify(arr, n, largest); 
    } 
} 
void intal_sort(char **arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i);   
    for (int i=n-1; i>0; i--) 
    { 
        swap(arr, i, 0);
        heapify(arr, i, 0); 
    } 
}

char* coin_row_problem(char **arr, int n)
{
    char **c=malloc(sizeof(char*)*(n+1));
    for(int i=0; i<n; i++)
        c[i+1]=arr[i];
    char **f=malloc(sizeof(char*) * (n+1));
    f[0]=malloc(sizeof(char) * 2);
    strcpy(f[0], "0");
    f[1]=malloc(sizeof(char)*(strlen(c[1])+1));
    strcpy(f[1], c[1]);
    for(int i=2; i<=n; i++)
    {
        char* max;
        char* res=intal_add(c[i], f[i-2]);
        if(intal_compare(res, f[i-1])==1)
        {   
            max=res;
        }
        else
        {   
            free(res);
            max=f[i-1];
        }
        f[i]=malloc(sizeof(char) * (strlen(max)+1));
        strcpy(f[i], max);
        if(max!=f[i-1])
            free(max);
    }

    char* result=malloc(sizeof(char) * strlen(f[n])+1);
    strcpy(result, f[n]);
    free(c); 
    for(int i=0; i<n+1; i++)
        free(f[i]);
    free(f);
    return result;
}

