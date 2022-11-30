public class IsEven<Number> implements CustomTest<Number> {
    public boolean test(Number element) {
        int val = element.intValue();
        if (val % 2 == 0) {
            return true;
        }
        return false;
    }
}
