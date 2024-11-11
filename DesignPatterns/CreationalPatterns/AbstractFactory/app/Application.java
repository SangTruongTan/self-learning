package DesignPatterns.CreationalPatterns.AbstractFactory.app;

import DesignPatterns.CreationalPatterns.AbstractFactory.buttons.Button;
import DesignPatterns.CreationalPatterns.AbstractFactory.checkboxes.Checkbox;
import DesignPatterns.CreationalPatterns.AbstractFactory.factories.GUIFactory;

/**
 * Factory users don't care which concrete factory they use since they work with
 * factories and products through AbstractFactory interfaces.
 */
public class Application {

    private Button button;
    private Checkbox checkbox;

    public Application(GUIFactory factory) {
        button = factory.createButton();
        checkbox = factory.createCheckbox();
    }

    public void paint() {
        button.paint();
        checkbox.paint();
    }
}
