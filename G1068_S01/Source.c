int c = 8;
void switchInts(int x, int y)
{
	int z = x;
	x = y;
	y = z;
}
void main()
{
	int a = 4;
	int b;
	b = 9;
	switchInts(a, b);
//	b += c;
}