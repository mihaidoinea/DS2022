int c = 4;
void switchints (int x, int y)
{
	int z = x;
	x = y;
	y = z;
}
void main()
{
	int a = 2; 
	int b;
	b = 7;
	switchints(a, b);
}