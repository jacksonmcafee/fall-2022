
public class ECTester {

	public static void main(String[] args) {
		Integer[] intArray = {2, 8, 6, 7, 4, 10, 3, 1, 9, 5};
		Double[] dblArray = {11.9, 12.2, 5.4, 0.2, 3.3, 3.9, 4.2, 1.1, 123456.0, 10.0001};
		String[] strArray = {"Why", "is", "A", "raven", "liKe", "a", "wriTing", "desk?"};
		
		ArrayTester<Integer> intTest = new ArrayTester<Integer>(intArray, new IsEven<Integer>());
		ArrayTester<Double> dblTest = new ArrayTester<Double>(dblArray, new IsEven<Double>());
		ArrayTester<String> strTest = new ArrayTester<String>(strArray, new AllLower());
		ArrayTester<Integer> intCompare = new ArrayTester<Integer>(intArray, new GreaterThan<Integer>(4));
		ArrayTester<Double> dblCompare = new ArrayTester<Double>(dblArray, new GreaterThan<Double>(4.5));
		ArrayTester<String> strCompare = new ArrayTester<String>(strArray, new GreaterThan<String>("last"));
		
		System.out.println("There are " + intTest.countIfValid() + " valid integers");
		System.out.println("They are: ");
		intTest.printIfValid();
		
		System.out.println();
		
		System.out.println("There are " + dblTest.countIfValid() + " valid doubles");
		System.out.println("They are: ");
		dblTest.printIfValid();
		
		System.out.println();
		
		System.out.println("There are " + strTest.countIfValid() + " valid strings");
		System.out.println("They are: ");
		strTest.printIfValid();
		
		System.out.println();
		
		System.out.println("There are " + intCompare.countIfValid() + " integers greater than 4");
		System.out.println("They are: ");
		intCompare.printIfValid();
		
		System.out.println();
		
		System.out.println("There are " + dblCompare.countIfValid() + " doubles greater than 4.5");
		System.out.println("They are: ");
		dblCompare.printIfValid();
		
		System.out.println();
		
		System.out.println("There are " + strCompare.countIfValid() + " strings greater than \"last\"");
		System.out.println("They are: ");
		strCompare.printIfValid();
		
		System.out.println();
		
		
	}
}