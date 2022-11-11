public class IsEven<T extends Number> implements CustomTest<T> {
    public boolean test(Number element) {
        // cast element to an int
        int val = element.intValue();
        // return true if val mod 2 == 0
        if (val % 2 == 0) {
            return true;
        }
        return false;
    }
}
