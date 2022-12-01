import java.util.Comparator;
import java.util.Collections;
import java.util.List;
import java.util.Arrays;

public class ArrayTester<T extends Comparable<? super T>> {
    private T[] array;
    private CustomTest<T> tester; 

    // constructor 
    public ArrayTester(T[] elements, CustomTest<T> test) {
        // sort array using natural ordering
        Arrays.sort(elements, Comparator.naturalOrder());

        // store values in array
        array = elements;
        
        // assign tester
        tester = test;
    }

    public void printIfValid() {
        // for all elements in array, apply test
        for (T x : array) {
            if (tester.test(x)) {
                // if test == true, print
                System.out.print(x + " ");
            }
        }
    }

    public int countIfValid() {
        int count = 0;
        // for all elements in array, apply test
        for (T x : array) { 
            if (tester.test(x)) {
                // if test == true, increment count
                count++;
            }
        }
    return count;
    }
}