package Week10;

public class DeluxeTaxi extends Taxi{
    private double farePerKilometer;
    private double baseDistance;
    private double baseFee;

    public DeluxeTaxi(int carNum ,double farePerKilometer){
        super(carNum);
        this.baseDistance = 3;
        this.baseFee = 5;
        if(farePerKilometer > 1){
            this.farePerKilometer = farePerKilometer;
        }
    }

    @Override
    public String toString() {
        return super.toString();
    }

    @Override
    public void getpaid(double distance) {
        super.setDistance(distance);
        if(distance < this.baseDistance){
            super.setIncome(this.baseFee);
        }
        else{
            super.setIncome((distance-this.baseDistance)*this.farePerKilometer);
        }
    }
}
