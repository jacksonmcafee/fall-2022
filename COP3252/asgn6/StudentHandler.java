/*
Jackson McAfee, 2022-11-17
StudentHandler.java for COP3252 Asgn6
*/

// import statements
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Collections;
import java.util.Comparator;
import java.io.*;

public class StudentHandler {
    ArrayList<Student> students;

    // array of string to make printing clearer
    static String[] opt = {"1: Print out all loaded students\n",
                    "2: Add student\n", 
                    "3: Clear students\n",
                    "4: Save students to file\n",
                    "5: Load students from file\n",
                    "6: Quit\n"
                };

    // main function
    public static void main(String[] args) throws IOException, ClassNotFoundException, NumberFormatException {
        // initialize StudentHandler sh
        StudentHandler sh = new StudentHandler();

        // create scanner to pass to various functions
        Scanner s = new Scanner(System.in);

        // declare input for sh
        int input = 0;

        // indefinite loop until 6 is input
        while(true) {
            System.out.printf("%s%s%s%s%s%s", opt[0], opt[1], opt[2], opt[3], opt[4], opt[5]);
            System.out.print("Please input the number of your choice: ");
            try {
                String s_input = s.nextLine();
                input = Integer.parseInt(s_input);
                
                // format and flush
                System.out.println();

                if (input > 6 || input < 1) {
                    // if input is out of range, skip
                    System.out.println("Invalid choice, try again!");
                    continue;
                }

                switch (input) {
                    case 1:
                        sh.printAllStudents();
                        break;
                    case 2:
                        sh.addStudent(s);
                        break;
                    case 3:
                        sh.clearAllStudents();
                        break;
                    case 4:
                        sh.saveStudents(s);
                        break;
                    case 5:
                        sh.loadStudents(s);
                        break;
                    case 6:
                        System.out.println("Goodbye!");
                        System.exit(0);

                }
            }
            catch (NumberFormatException e) {
                System.out.println("Error thrown.");
                System.out.println("Invalid choice, try again!");
                input = 0;
            }
        }
    }

    // constructor
    StudentHandler() {
        // initialize students
        students = new ArrayList<Student>();
    }

    // save students object to file filename
    private void saveStudents(Scanner s) throws IOException {
        // request filename
        System.out.println("Input your filename: ");
        String filename = s.nextLine();

        // serialize and save to file filename
        try {
            // create ObjectOutputStream based on filename
            ObjectOutputStream outstream = new ObjectOutputStream(new FileOutputStream(filename));

            // write to file, close stream and return to menu
            outstream.writeObject(students);
            outstream.close();
            System.out.printf("Object serialized successfully.%n%n");
        }
        // catch IOException, exit to menu
        catch (IOException e) {
            System.out.printf("Issue saving file. Returning to main menu%n%n.");
        }
    }

    private void loadStudents(Scanner s) throws IOException, ClassNotFoundException {
        // clear ArrayList students
        clearAllStudents();

        // request filename
        System.out.println("Input your filename: ");
        String filename = s.nextLine();

        // deserialize and load into ArrayList students
        try {
            // create ObjectInputStream based on filename
            ObjectInputStream instream = new ObjectInputStream(new FileInputStream(filename));

            // load from file, close stream and return to menu
            students = (ArrayList<Student>) instream.readObject();

            // recalculate grades for each student to populate grade
            for (Student st : students) {
                st.calcGrade();
                st.incrementStudentCount();
            }

            instream.close();
            System.out.printf("Object deserialized successfully.%n%n");

        }
        // catch IOException, exit to menu
        catch (IOException e) {
            System.out.printf("Issue reading file. Returning to main menu.%n%n");
        }
        // catch ClassNotFoundException, exit to menu
        catch (ClassNotFoundException e) {
            System.out.printf("File does not contain the correct data. Returning to main menu.\n");
        }
    }

    // this method is unfortunately a bit robust...
    private void addStudent(Scanner s) throws InputMismatchException {
        // create new student object, thought this declaration was kinda funny
        Student newStudent = new Student();
        boolean flag = true;

        // loop to get student data
        while(flag) {
            // swap flag, if all goes well, exit at the end of one iteration
            flag = false;

            // request first name
            System.out.print("Please input a first name: ");
            String fn = s.next();
            char[] fna = fn.toCharArray();

            // verify that fn doesn't contain numbers
            for (char x : fna) {
                if (Character.isDigit(x)) {
                    flag = true;
                    System.out.println("Invalid input, please try inputting the student again.");
                } 
            }
            if (flag == true) { continue; }

            // request last name
            System.out.print("Please input a last name: ");
            String ln = s.next();
            char[] lna = ln.toCharArray();
            
            // verify that ln doesn't contain numbers
            for (char x : lna) {
                if (Character.isDigit(x)) {
                    flag = true;
                    System.out.println("Invalid input, please try inputting the student again.");
                }
            }
            if (flag == true) { continue; }
        
            // reset flag
            flag = false;

            // set student name
            newStudent.setname(fn, ln);

            // request student homework grades
            boolean innerFlag = true;
            int flip = 0;
            double grade = 0;
            while(innerFlag) {
                if (flag == true) {
                    System.out.println("Invalid input, please try inputting the student again.");
                    break;
                }
                switch (flip) {
                    case 0:
                        System.out.println("Please input student homework grades one at a time (negative value to finish): ");
                        try {
                            grade = s.nextDouble();
                            if (isValidGrade(grade)) {
                                newStudent.addHW(grade);
                                flip++;
                            }
                            else if (grade < 0) {
                                innerFlag = false;
                                break;
                            }
                            else {
                                flag = true;
                            }
                        }
                        catch (InputMismatchException e) {
                            System.out.println("Invalid input, please try inputting the student again.");
                        }
                        break;

                    case 1:
                        System.out.println("Please add another homework grade (negative value to finish): ");
                        try {
                            grade = s.nextDouble();
                            if (isValidGrade(grade)) {
                                newStudent.addHW(grade);
                            }
                            else if (grade < 0) {
                                innerFlag = false;
                                break;
                            }
                            else {
                                flag = true;
                            }
                        }
                        catch (InputMismatchException e) {
                            System.out.println("Invalid input, please try inputting the student again.");
                            flag = true;
                        }
                }
            }
        if (flag == true) { continue; }

        // reset flag
        innerFlag = true;
        
        // get test grades 
        while(innerFlag) {
                if (flag == true) {
                    System.out.println("Invalid input, please try inputting the student again.");
                    break;
                }
                switch (flip) {
                    case 0:
                        System.out.println("Please input student test grades one at a time (negative value to finish): ");
                        try {
                            grade = s.nextDouble();
                            if (isValidGrade(grade)) {
                                newStudent.addTest(grade);
                                flip++;
                            }
                            else if (grade < 0) {
                                innerFlag = false;
                                break;
                            }
                            else {
                                flag = true;
                            }
                        }
                        catch (InputMismatchException e) {
                            System.out.println("Invalid input, please try inputting the student again.");
                        }
                        break;

                    case 1:
                        System.out.println("Please add another test grade (negative value to finish): ");
                        try {
                            grade = s.nextDouble();
                            if (isValidGrade(grade)) {
                                newStudent.addTest(grade);
                            }
                            else if (grade < 0) {
                                innerFlag = false;
                                break;
                            }
                            else {
                                flag = true;
                            }
                        }
                        catch (InputMismatchException e) {
                            System.out.println("Invalid input, please try inputting the student again.");
                            flag = true;
                        }
                }
            }
            if (flag == true) { continue; }

            // if everything succeeds, add student to ArrayList students
            students.add(newStudent);
            
            // flush scanner
            s.nextLine();
            System.out.println();
        }
    }

    private void printAllStudents() {
        // sort ArrayList students 
        Collections.sort(students, new StudentComparator());
        
        // print out each student
        for (Student s : students) {
            printStudent(s);
        }
        // create temp student object to increment student count
        Student s = new Student();
        s.decrementStudentCount();
        System.out.printf("Printed %d student records.%n%n", s.getNumStudents());
    }

    // helper function to make the above function more concise
    private void printStudent(Student s) {
        System.out.printf("%nFirst Name: %s%n", s.getFirst());
        System.out.printf("Last Name: %s%n", s.getLast());
        System.out.printf("Final Grade: %f%n%n", s.getGrade());
    }

    // clears students with Collections.clear()
    private void clearAllStudents() {
        // clear ArrayList students
        students.clear();

        // create temp student object to reset student count
        Student s = new Student();
        s.resetStudentCount();

        System.out.println("Clearing all students was successful.");
    }

    private boolean isValidGrade(double d) {
        // verify if grade is valid or not
        if (d < 0 || d > 100) {
            return false;
        }
        return true;
    }
}

class StudentComparator implements Comparator<Student> {
    public int compare(Student s1, Student s2) {
        int lastCompare = s1.getLast().compareTo(s2.getLast());
        if (lastCompare == 0) {
            lastCompare = s1.getFirst().compareTo(s2.getFirst());
        }
        return lastCompare;
    }
}