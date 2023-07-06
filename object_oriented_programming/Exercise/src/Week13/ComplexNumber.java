package Week13;

public class ComplexNumber {
    public static class RealNumber {
        private int dividend;
        private int divisor;

        public RealNumber(int dividend, int divisor){
            this.dividend = dividend;
            this.divisor = divisor;
        }

        public int getDividend() {
            return dividend;
        }

        public int getDivisor() {
            return divisor;
        }

        @Override
        public String toString() {
            return "RealNumber{" + "dividend=" + dividend + ", divisor=" + divisor +'}';
        }
    }
    private RealNumber real;
    private RealNumber imaginary;

    public ComplexNumber(RealNumber real, RealNumber imaginary){
        this.real = real;
        this.imaginary = imaginary;
    }

    public static RealNumber add(RealNumber r1, RealNumber r2){
        return new RealNumber(r1.dividend+ r2.dividend,r1.divisor+r2.divisor);
    }
    public static RealNumber sub(RealNumber r1, RealNumber r2){
        return new RealNumber(r1.dividend- r2.dividend,r1.divisor-r2.divisor);
    }
    public static RealNumber mul(RealNumber r1, RealNumber r2){
        return new RealNumber(r1.dividend* r2.dividend,r1.divisor*r2.divisor);
    }
    public RealNumber getReal() {
        return real;
    }

    public RealNumber getImaginary() {
        return imaginary;
    }
}
