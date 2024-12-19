package DesignPatterns.CreationalPatterns.AbstractFactory.factories;

import DesignPatterns.CreationalPatterns.AbstractFactory.buttons.Button;
import DesignPatterns.CreationalPatterns.AbstractFactory.buttons.MacOSButton;
import DesignPatterns.CreationalPatterns.AbstractFactory.checkboxes.Checkbox;
import DesignPatterns.CreationalPatterns.AbstractFactory.checkboxes.MacOSCheckbox;

/**
 * Each concrete factory extends basic factory and responsible for creating
 * products of a single variety.
 */
public class MacOSFactory implements GUIFactory {

    @Override
    public Button createButton() {
        return new MacOSButton();
    }

    @Override
    public Checkbox createCheckbox() {
        return new MacOSCheckbox();
    }
}
