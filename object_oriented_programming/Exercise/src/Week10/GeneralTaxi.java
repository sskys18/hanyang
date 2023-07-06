package Week10;

public class GeneralTaxi extends Taxi{
    private double farePerKilometer;
    private double baseDistance;
    private double baseFee;

    public GeneralTaxi(int carNum ,double farePerKilometer){
        super(carNum);
        this.baseDistance = 3;
        this.baseFee = 3;
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
        if(distance < baseDistance){
            super.setIncome(baseFee);
        }
        else{
            super.setIncome((distance-baseDistance)*farePerKilometer);
        }
    }
}
