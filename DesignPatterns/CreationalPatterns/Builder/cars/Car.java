package DesignPatterns.CreationalPatterns.Builder.cars;

import DesignPatterns.CreationalPatterns.Builder.components.Engine;
import DesignPatterns.CreationalPatterns.Builder.components.GPSNavigator;
import DesignPatterns.CreationalPatterns.Builder.components.Transmission;
import DesignPatterns.CreationalPatterns.Builder.components.TripComputer;

/**
 * Car is a product class.
 */
public class Car {

    private CarType carType;
    private int seats;
    private Engine engine;
    private Transmission transmission;
    private TripComputer tripComputer;
    private GPSNavigator gpsNavigator;
    private double fuel = 0;

    public Car(
        CarType carType,
        int seats,
        Engine engine,
        Transmission transmission,
        TripComputer tripComputer,
        GPSNavigator gpsNavigator
    ) {
        this.carType = carType;
        this.seats = seats;
        this.engine = engine;
        this.transmission = transmission;
        this.tripComputer = tripComputer;
        if (this.tripComputer != null) {
            this.tripComputer.setCar(this);
        }
        this.gpsNavigator = gpsNavigator;
    }

    public CarType getCarType() {
        return carType;
    }

    public double getFuel() {
        return fuel;
    }

    public void setFuel(double fuel) {
        this.fuel = fuel;
    }

    public int getSeats() {
        return seats;
    }

    public Engine getEngine() {
        return engine;
    }

    public Transmission getTransmission() {
        return transmission;
    }

    public TripComputer getTripComputer() {
        return tripComputer;
    }

    public GPSNavigator getGpsNavigator() {
        return gpsNavigator;
    }
}
