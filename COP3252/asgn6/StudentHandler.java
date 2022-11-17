import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.io.*;

public class StudentHandler {
    // data 
    ArrayList<Student> students;

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
            System.out.println("Object serialized successfully.")
        }
        // catch IOException, exit to menu
        catch (IOException e) {
            System.out.printf("Issue saving file. Returning to main menu\n.");
        }
    }

    private void loadStudents(Scanner s) throws IOException, ClassNotFoundException {
        // clear ArrayList students
        students.clear();

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
            System.out.println("Object deserialized successfully.")

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
                            System.out.println("Invalid input, please try inputting the student again.")
                        }



                    case 1:
                        System.out.println("Please add another homework grade (negative value to finish): ");
                        

                }
            }
        }
    }
    private boolean isValidGrade(double d) {
        // verify if grade is valid or not
        if (d < 0 || d > 100) {
            return false;
        }
        return true;
    }
}