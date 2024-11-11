package DesignPatterns.CreationalPatterns.AbstractFactory.factories;

import DesignPatterns.CreationalPatterns.AbstractFactory.buttons.Button;
import DesignPatterns.CreationalPatterns.AbstractFactory.checkboxes.Checkbox;

/**
 * Abstract factory knows about all (abstract) product types.
 */
public interface GUIFactory {
    Button createButton();
    Checkbox createCheckbox();
}
