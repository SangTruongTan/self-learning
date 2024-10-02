package DesignPatterns.CreationalPatterns.Builder.builders;

import DesignPatterns.CreationalPatterns.Builder.cars.CarType;
import DesignPatterns.CreationalPatterns.Builder.components.Engine;
import DesignPatterns.CreationalPatterns.Builder.components.GPSNavigator;
import DesignPatterns.CreationalPatterns.Builder.components.Transmission;
import DesignPatterns.CreationalPatterns.Builder.components.TripComputer;

/**
 * Builder interface defines all possible ways to configure a product.
 */
public interface Builder {
    void setCarType(CarType type);
    void setSeats(int seats);
    void setEngine(Engine engine);
    void setTransmission(Transmission transmission);
    void setTripComputer(TripComputer tripComputer);
    void setGPSNavigator(GPSNavigator gpsNavigator);
}
