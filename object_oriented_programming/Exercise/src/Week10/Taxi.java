package Week10;

abstract class Taxi {
    private int carNum;
    private double distance;
    private double income;

    public Taxi(int carNum) {
        this.carNum = carNum;
        this.distance = 0;
        this.income = 0;
    }

    public String toString() {
        return "Taxi{" +
                "carNum=" + carNum +
                ", distance=" + distance +
                ", income=" + income +
                '}';
    }

    public abstract void getpaid(double distance);

    public void doDrive(double distance) {
        getpaid(distance);
    }

    public boolean earnMore(Taxi t) {
        return this.getIncome() > t.getIncome();
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }

    public void setIncome(double income) {
        this.income = income;
    }

    public double getIncome() {
        return income;
    }
}

