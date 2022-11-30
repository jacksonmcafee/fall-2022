 public class AllLower implements CustomTest<String> {
    public boolean test(String element) {
        // cast element to char[] to make it iterable
        // ch_ar = char array hahahahahahaha...
        char[] ch_ar = element.toCharArray();
        // iterate through char array and check for non-lowercase values
        for (char x : ch_ar) {
            // check that x isn't numeric
            if (Character.isAlphabetic(x)) {
                if (Character.isUpperCase(x)) {
                    // if uppercase, return false
                    return false;
                }
            }
        }
        return true;
    }
}