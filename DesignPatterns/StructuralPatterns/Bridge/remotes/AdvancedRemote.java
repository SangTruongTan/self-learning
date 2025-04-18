package DesignPatterns.StructuralPatterns.Bridge.remotes;

import DesignPatterns.StructuralPatterns.Bridge.devices.Device;

public class AdvancedRemote extends BasicRemote {
    public AdvancedRemote(Device device) {
        super.device = device;
    }

    public void mute() {
        System.out.println("Remote: mute");
        device.setVolume(0);
    }
}
