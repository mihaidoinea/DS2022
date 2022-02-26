int c = 7;
void switchInts(int x, int y)
{
	int z = x;
	x = y;
	y = z;
}
void main()
{
	int a = 5;
	int b;
	b = 8;
	//b += c;
	switchInts(a, b);
}