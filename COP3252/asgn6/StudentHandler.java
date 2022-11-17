import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Collections;
import java.util.Comparator;
import java.io.*;

public class StudentHandler {
    // data 
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
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        // initialize StudentHandler sh
        StudentHandler sh = new StudentHandler();

        // create scanner to pass to various functions
        Scanner s = new Scanner(System.in);

        // indefinite loop until 6 is input
        while(true) {
            System.out.printf("%s %s %s %s %s %s", opt[0], opt[1], opt[2], opt[3], opt[4], opt[5]);
            try {
                int input = s.nextInt();
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
            catch (InputMismatchException e) {
                System.out.println("Invalid choice, try again!");
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
            System.out.println("Object serialized successfully.");
        }
        // catch IOException, exit to menu
        catch (IOException e) {
            System.out.printf("Issue saving file. Returning to main menu\n.");
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
            instream.close();
            System.out.println("Object deserialized successfully.");

        }
        // catch IOException, exit to menu
        catch (IOException e) {
            System.out.printf("Issue reading file. Returning to main menu.\n");
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
                }
            }
            if (flag == true) { continue; }

            // set student name
            newStudent.setname(fn, ln);

            // request student homework grades
            boolean innerFlag = true;
            int flip = 0;
            double grade = 0;
            while(innerFlag) {
                switch (flip) {
                    case 0:
                        System.out.println("Please input student homework grades one at a time (negative value to finish): ");
                        try {
                            grade = s.nextDouble();
                            if (isValidGrade(grade)) {
                                newStudent.addHW(grade);
                                flip++;
                            }
                            else {

                            }
                        }
                        catch (InputMismatchException e) {
                            System.out.println("Invalid input, please try inputting the student again.");
                        }
                        innerFlag = false;
                        break;

                    case 1:
                        System.out.println("Please add another homework grade (negative value to finish): ");
                        try {
                            grade = s.nextDouble();
                            if (isValidGrade(grade)) {
                                newStudent.addHW(grade);
                            }
                            else if (grade < 0) {
                                break;
                            }
                        }
                        catch (InputMismatchException e) {
                            System.out.println("Invalid input, please try inputting the student again.");
                        }
                        innerFlag = false;
                        break;
                }
            }
        if (innerFlag == false) { continue; }

        // reset flag
        innerFlag = true;
        
        // get test grades 
        while(innerFlag) {
                switch (flip) {
                    case 0:
                        System.out.println("Please input student homework grades one at a time (negative value to finish): ");
                        try {
                            grade = s.nextDouble();
                            if (isValidGrade(grade)) {
                                newStudent.addTest(grade);
                                flip++;
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
                                newStudent.addTest(grade);
                            }
                        }
                        catch (InputMismatchException e) {
                            System.out.println("Invalid input, please try inputting the student again.");
                        }
                }
            }

        }
    }

    private void printAllStudents() {
        // sort ArrayList students 
        Collections.sort(students, new StudentComparator());
        
        // print out each student
        for (Student s : students) {
            printStudent(s);
        }
        System.out.printf("Printed %d student records.", )
    }

    private void printStudent(Student s) {
        System.out.printf("First Name: %s%n", s.getFirst());
        System.out.printf("Last Name: %s%n", s.getLast());
        System.out.printf("Final Grade: %f%n%n", s.getGrade());
    }

    private void clearAllStudents() {
        students.clear();
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