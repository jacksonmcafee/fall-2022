/*
Fraction.java for COP3252 Fall2022 Asgn2
Jackson McAfee, 3 Sept. 2022
*/

// Class Fraction
public class Fraction
{
  private int numerator = 0;		// numerator (and keeps sign)
  private int denominator = 1;		// always stores positive value

  public Fraction()
  {

  }

  public Fraction(int n)
  {
    this(n,1);
  }

  public Fraction(int n, int d)
  {
    if (set(n,d)==false)
	set(0,1);
  }

  public boolean set(int n, int d)
  {
    if (d > 0)
    {
	numerator = n;
	denominator = d;
	return true;
    }
    else
	return false;
  }
  
  public void show()
  {
    System.out.print(numerator + "/" + denominator);
  }

  public String toString()
  {
    return (numerator + "/" + denominator);
  }

  public int getNumerator()
  {
    return numerator;
  }

  public int getDenominator()
  {
    return denominator;
  }

  public double decimal()
  {
    return (double)numerator / denominator;
  }

  public Fraction simplify() {
    // check if denominator is negative
    // any case w/ neg denominator results in both being *= -1
    if (denominator < 0) {
        denominator *= -1;
        numerator *= -1;
    }

    Fraction simplifiedFrac = new Fraction(numerator, denominator);

    if(simplifiedFrac.numerator == 0) {
      simplifiedFrac.numerator = 0;
      simplifiedFrac.denominator = 1;
    }
    else {
      // calls gcd to find value to simplify by
      int gcd = gcd(simplifiedFrac.numerator, simplifiedFrac.denominator);
      simplifiedFrac.numerator /= gcd;
      simplifiedFrac.denominator /= gcd;
    }
    return simplifiedFrac;
  }

  // check if any of these end up with negative denominators !!
  public Fraction add(Fraction f) {
      Fraction returnFrac = new Fraction(numerator, denominator);

      if (denominator == f.denominator) {
        returnFrac.numerator += f.numerator;
        
        returnFrac = returnFrac.simplify();
        return returnFrac;
      }

      // create temp values to not mess w/ original values
      // match denominators before adding
      int temp_d = denominator * f.denominator;
      int temp_n = denominator * f.numerator ; 
      returnFrac.numerator *= f.denominator;
      returnFrac.denominator *= f.denominator;

      returnFrac.numerator += temp_n;
      
      returnFrac = returnFrac.simplify();
      return returnFrac;
  }

  public Fraction subtract(Fraction f) {
      Fraction returnFrac = new Fraction(numerator, denominator);

      if (denominator == f.denominator) {
        returnFrac.numerator += f.numerator;

        returnFrac = returnFrac.simplify();
        return returnFrac;
      }

      // create temp values to not mess w/ original values
      // match denominators before subtracting
      int temp_d = f.denominator * denominator;
      int temp_n = f.numerator * denominator; 
      returnFrac.numerator *= f.denominator;
      returnFrac.denominator *= f.denominator;

      returnFrac.numerator -= temp_n;
      
      returnFrac = returnFrac.simplify();
      return returnFrac;
  }

  public Fraction multiply(Fraction f) {
    Fraction returnFrac = new Fraction(numerator, denominator);

    // multiply straight across!! fractions are fun!
    returnFrac.numerator *= f.numerator;
    returnFrac.denominator *= f.denominator;
    
    returnFrac = returnFrac.simplify();
    return returnFrac;
  }

  public Fraction divide(Fraction f) {
    if (f.numerator == 0) {
      Fraction returnFrac = new Fraction(0, 1);
      return returnFrac;
    }

    Fraction returnFrac = new Fraction(numerator, denominator);

    // multiplies num by f.den, den by f.num to emulate CFM 
    returnFrac.numerator *= f.denominator;
    returnFrac.denominator *= f.numerator;

    returnFrac = returnFrac.simplify();
    return returnFrac;
  }

  private int gcd(int a, int b) {
    // checks if neg, this function fails if a or b are negative 
    if (a < 0) {
      a *= -1;
    }
    if (b < 0) {
      b *= -1;
    }

    int gcd = 1;
    // iterates until i == a or b
    // assigns a gcd when cleanly divisible
    for(int i = 1; i <= a && i <= b; i++) {
      if (a % i == 0 && b % i == 0) {
        gcd = i;
      }
    }
    return gcd;
  }

  // sample test program
  public static void main(String[] args)
  {
    Fraction f1, f2;
    f1 = new Fraction();
    f2 = new Fraction(3, 5);

    System.out.print("\nFraction f1 = ");
    f1.show();
    System.out.print("\nFraction f2 = " + f2);	// uses toString

    System.out.println("\nCalling f1.set(11,14)");
    if (f1.set(11,14) == false)
	System.out.println("** set attempt failed");
    System.out.println("\nCalling f2.set(4,0)");
    if (!f2.set(4,0))
	System.out.println("** set attempt failed");

    System.out.print("\nFraction f1 = ");
    f1.show();
    System.out.print("\nFraction f2 = ");
    f2.show();

    System.out.println("\nDecimal value of f1 = " + f1.decimal());
    System.out.println("Decimal value of f2 = " + f2.decimal());
  }  

}