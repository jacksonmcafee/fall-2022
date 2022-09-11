/*
IntegerSet.java for COP3252 Fall2022 Asgn2
Jackson McAfee, 3 Sept. 2022
*/

// Class IntegerSet
public class IntegerSet {
	private boolean[] intArr;	
	private int arraySize = 101;

	public IntegerSet() {
		// assign memory to intArr
		intArr = new boolean[arraySize];

		// initialize array to empty, all false
		for (int i = 0; i < arraySize; i++) {
			intArr[i] = false;
		}
	}

	public IntegerSet union(IntegerSet iSet) {
		IntegerSet temp = new IntegerSet();
		for (int i = 0; i < arraySize; i++) {
			// if either arrays[i] are true, there is a union at i
			if (this.intArr[i] == true || iSet.intArr[i] == true) {
				temp.intArr[i] = true;
			}
		}
		return temp;
	}

	public IntegerSet intersection(IntegerSet iSet) {
		IntegerSet temp = new IntegerSet();
		for (int i = 0; i < arraySize; i++) {
			// if both arrays[i] are true, there is a intersection at i
			if (this.intArr[i] == true && iSet.intArr[i] == true) {
				temp.intArr[i] = true;
			}
		}
		return temp;
	}

	public IntegerSet insertElement(int data) {
		// set array[data] = true, regardless of original
		this.intArr[data] = true;
		return this; 
	}

	public IntegerSet deleteElement(int data) {
		// set array[data] = false, regardless of original
		this.intArr[data] = false;
		return this;
	}

	public boolean isEqualTo(IntegerSet iSet) {
		int count = 0;
		for (int i = 0; i < arraySize; i++) {
			if (this.intArr[i] == iSet.intArr[i]) {
				count++;
			}
		}

		// if count is 101, then every element is identical, return true
		if (count == 101) {
			return true;
		}
		// else return false
		else {
			return false;
		}
	}

	public String toString() {
		// create blank string obj to return
		String returnString = "";
		for (int i = 0; i < arraySize; i++) {
			// if array[i] is true, that i is a member of the set
			if (this.intArr[i] == true) {
				returnString += i;
				returnString += " ";
			}
		}

		// if string is blank, append dash to indicate as such
		if (returnString.length() == 0) {
			returnString += "—";
		}

		return returnString;
	}
}