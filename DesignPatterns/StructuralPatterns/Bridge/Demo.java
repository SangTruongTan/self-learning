package DesignPatterns.StructuralPatterns.Bridge;

import DesignPatterns.StructuralPatterns.Bridge.devices.Device;
import DesignPatterns.StructuralPatterns.Bridge.devices.Radio;
import DesignPatterns.StructuralPatterns.Bridge.devices.Tv;
import DesignPatterns.StructuralPatterns.Bridge.remotes.AdvancedRemote;
import DesignPatterns.StructuralPatterns.Bridge.remotes.BasicRemote;

public class Demo {
    public static void main(String[] args) {
        testDevice(new Tv());
        testDevice(new Radio());
    }

    public static void testDevice(Device device) {
        System.out.println("Tests with basic remote.");
        BasicRemote basicRemote = new BasicRemote(device);
        basicRemote.power();
        device.printStatus();

        System.out.println("\nTests with advanced remote.");
        AdvancedRemote advancedRemote = new AdvancedRemote(device);
        advancedRemote.power();
        advancedRemote.mute();
        device.printStatus();
    }
}
