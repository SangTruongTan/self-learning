package DesignPatterns.CreationalPatterns.Builder.builders;

import DesignPatterns.CreationalPatterns.Builder.cars.Car;
import DesignPatterns.CreationalPatterns.Builder.cars.CarType;
import DesignPatterns.CreationalPatterns.Builder.components.Engine;
import DesignPatterns.CreationalPatterns.Builder.components.GPSNavigator;
import DesignPatterns.CreationalPatterns.Builder.components.Transmission;
import DesignPatterns.CreationalPatterns.Builder.components.TripComputer;

/**
 * Concrete builders implement steps defined in the common interface.
 */
public class CarBuilder implements Builder {

    private CarType type;
    private int seats;
    private Engine engine;
    private Transmission transmission;
    private TripComputer tripComputer;
    private GPSNavigator gpsNavigator;

    @Override
    public void setCarType(CarType type) {
        this.type = type;
    }

    @Override
    public void setSeats(int seats) {
        this.seats = seats;
    }

    @Override
    public void setEngine(Engine engine) {
        this.engine = engine;
    }

    @Override
    public void setTransmission(Transmission transmission) {
        this.transmission = transmission;
    }

    @Override
    public void setTripComputer(TripComputer tripComputer) {
        this.tripComputer = tripComputer;
    }

    @Override
    public void setGPSNavigator(GPSNavigator gpsNavigator) {
        this.gpsNavigator = gpsNavigator;
    }

    public Car getResult() {
        return new Car(
            type,
            seats,
            engine,
            transmission,
            tripComputer,
            gpsNavigator
        );
    }
}
