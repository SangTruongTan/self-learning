package DesignPatterns.CreationalPatterns.AbstractFactory.factories;

import DesignPatterns.CreationalPatterns.AbstractFactory.buttons.Button;
import DesignPatterns.CreationalPatterns.AbstractFactory.buttons.WindowsButton;
import DesignPatterns.CreationalPatterns.AbstractFactory.checkboxes.Checkbox;
import DesignPatterns.CreationalPatterns.AbstractFactory.checkboxes.WindowsCheckbox;

/**
 * Each concrete factory extends basic factory and responsible for creating
 * products of a single variety.
 */
public class WindowsFactory implements GUIFactory {

    @Override
    public Button createButton() {
        return new WindowsButton();
    }

    @Override
    public Checkbox createCheckbox() {
        return new WindowsCheckbox();
    }
}
