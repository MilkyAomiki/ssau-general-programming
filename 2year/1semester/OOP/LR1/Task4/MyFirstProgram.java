class MyFirstClass {
	public static void main(String[] s) {
		MySecondClass o = new MySecondClass(5, 6);
		int i, j;
		for (i = 1; i <= 8; i++) {
			for(j = 1; j <= 8; j++) {
				o.setA(i);
				o.setB(j);
				System.out.print(o.multiply());
				System.out.print(" ");
			}
			System.out.println();
		}
	}
}

class MySecondClass {
	private int a;
	private int b;

	public MySecondClass(int a, int b) {
		this.a = a;
		this.b = b;
	}

	public void setA(int val)
	{
		a = val;
	}
	
	public int getA()
	{
		return a;
	}

	public void setB(int val)
	{
		b = val;
	}

	public int getB()
	{
		return b;
	}

	public int multiply()
	{
		return a*b;
	}
}
