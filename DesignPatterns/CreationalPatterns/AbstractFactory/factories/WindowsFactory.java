package AbstractFactory.factories;

import AbstractFactory.buttons.Button;
import AbstractFactory.buttons.WindowsButton;
import AbstractFactory.checkboxes.Checkbox;
import AbstractFactory.checkboxes.WindowsCheckbox;

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
