package Week13;

public class RealNumberCalculator implements Calculator{
    @Override
    public ComplexNumber add(ComplexNumber c1, ComplexNumber c2) {
        return null;
    }

    @Override
    public ComplexNumber sub(ComplexNumber c1, ComplexNumber c2) {
        return null;
    }

    @Override
    public ComplexNumber mul(ComplexNumber c1, ComplexNumber c2) {
        return null;
    }

    @Override
    public ComplexNumber.RealNumber add(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2){
        return new ComplexNumber.RealNumber(r1.getDividend()+r2.getDividend(),r1.getDivisor()+ r2.getDivisor());
    }
    @Override
    public ComplexNumber.RealNumber sub(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2){
        return new ComplexNumber.RealNumber(r1.getDividend()-r2.getDividend(),r1.getDivisor()- r2.getDivisor());
    }
    @Override
    public ComplexNumber.RealNumber mul(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2){
        return new ComplexNumber.RealNumber(r1.getDividend()*r2.getDividend(),r1.getDivisor()* r2.getDivisor());
    }
}
