package AbstractFactory.factories;

import AbstractFactory.buttons.Button;
import AbstractFactory.buttons.MacOSButton;
import AbstractFactory.checkboxes.Checkbox;
import AbstractFactory.checkboxes.MacOSCheckbox;

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
