class Array {
	private int[] intArr;
	private int size;

	Array() {
		intArr = new int[100];
		
		for (int i = 0; i < 100; i++) {
			intArr[i] = 0;
		}
		
		size = 0;
	}

	private void fillArr(int temp) {
		intArr[size] = temp;
		size++;
	}

	private double meanIntArr() {
		int sum = sumIntArr();
		return sum / size;
	}

	private int sumIntArr() {
		int sum = 0;
		for (int i = 0; i < intArr.length; i++) {
			sum += intArr[i];
		}
		return sum;
	}

	private int prodIntArr() {
		int prod = 1;
		for (int i = 0; i < size; i++) {
			prod *= intArr[i];
		}
		return prod;
	}

	public static void main(String[] args) {
		Array myArr = new Array();
		myArr.fillArr(5);
		myArr.fillArr(10); 
		System.out.println(myArr.prodIntArr());
	}
}