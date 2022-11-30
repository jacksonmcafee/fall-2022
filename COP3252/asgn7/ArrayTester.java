public class ArrayTester<T> {
    T[] array;
    CustomTest<T> tester; 

    // constructor 
    ArrayTester(T[] elements, CustomTest<T> test) {
        // assign array
        array = elements;

        // sort array into natural ordering
        
        // assign tester
        tester = test;
    }

    void printIfValid() {
        for (T x : array) {
            if (tester.test(x)) {
                System.out.print(x + " ");
            }
        }
    }

    int countIfValid() {
        int count = 0;
        for (T x : array) { 
            if (tester.test(x)) {
                System.out.print(x + " ");
                count++;
            }
        }
    return count;
    }
}