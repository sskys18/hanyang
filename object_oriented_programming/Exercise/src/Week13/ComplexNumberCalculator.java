package Week13;

public class ComplexNumberCalculator implements Calculator{

    @Override
    public ComplexNumber add(ComplexNumber c1, ComplexNumber c2){
        return new ComplexNumber(ComplexNumber.add(c1.getReal(),c2.getReal()), add(c1.getImaginary(),c2.getImaginary()));
    }
    @Override
    public ComplexNumber sub(ComplexNumber c1, ComplexNumber c2){
        return new ComplexNumber(ComplexNumber.sub(c1.getReal(),c2.getReal()), add(c1.getImaginary(),c2.getImaginary()));
    }
    @Override
    public ComplexNumber mul(ComplexNumber c1, ComplexNumber c2){
        return new ComplexNumber(ComplexNumber.mul(c1.getReal(),c2.getReal()), add(c1.getImaginary(),c2.getImaginary()));
    }

    @Override
    public ComplexNumber.RealNumber add(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2) {
        return null;
    }

    @Override
    public ComplexNumber.RealNumber sub(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2) {
        return null;
    }

    @Override
    public ComplexNumber.RealNumber mul(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2) {
        return null;
    }


}
