package Week13;

public interface Calculator {
    ComplexNumber add(ComplexNumber c1, ComplexNumber c2);
    ComplexNumber sub(ComplexNumber c1, ComplexNumber c2);
    ComplexNumber mul(ComplexNumber c1, ComplexNumber c2);
    ComplexNumber.RealNumber add(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2);
    ComplexNumber.RealNumber sub(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2);
    ComplexNumber.RealNumber mul(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2);

    default void printResult(ComplexNumber c){
        System.out.println("Real : "+c.getReal().toString()+" Imaginary : "+c.getImaginary().toString());
    }
    public static void main(String[] args) {
        Calculator calc = new Calculator();
        ComplexNumber c1 = new ComplexNumber(new ComplexNumber.RealNumber(4, 10), new ComplexNumber.RealNumber(3,2));
        ComplexNumber c2 = new ComplexNumber(new ComplexNumber.RealNumber(3, 10), new ComplexNumber.RealNumber(-4, 2));

        calc.printResult(calc.sub(c1, c2));
        }
}
