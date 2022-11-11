public class GreaterThan<T extends Comparable<T>> implements CustomTest<T> {
    private T data;

    // constructor
    GreaterThan(T data) {
        this.data = data;
    }

    public boolean test(T data) {
        // return based on compareTo()
        if (this.data.compareTo(data) < 0) {
            return true;
        }
        return false;
    }
}