import java.util.Comparator;

public class GreaterThan<T extends Comparable<? super T>> implements CustomTest<T> {
    private T data;

    GreaterThan(T data) {
        this.data = data;
    }

    public boolean test(T data) {
        if (this.data.compareTo(data) == )
    }

}