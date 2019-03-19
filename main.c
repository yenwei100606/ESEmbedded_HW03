int addten(int a)
{
	int b=a+10;
	return b;
}

int test5parameter(int a,int b,int c,int d,int e)
{
	return (a*1)+(b*2)+(c*3)+(d*4)+(e*5);
}


void reset_handler(void)
{
	int x=addten(5);
	int y=test5parameter(1,2,3,4,5);
	while (1)
		;
}
