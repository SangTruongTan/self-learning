package DesignPatterns.BehavioralPatterns.Mediator.components;

import DesignPatterns.BehavioralPatterns.Mediator.mediator.Mediator;
import DesignPatterns.BehavioralPatterns.Mediator.mediator.Note;
import java.awt.event.ActionEvent;
import javax.swing.*;

/**
 * Concrete components don't talk with each other. They have only one
 * communication channel-sending requests to the mediator.class
 */
public class AddButton extends JButton implements Component {

    private Mediator mediator;

    public AddButton() {
        super("Add");
    }

    @Override
    public void setMediator(Mediator mediator) {
        this.mediator = mediator;
    }

    @Override
    protected void fireActionPerformed(ActionEvent actionEvent) {
        mediator.addNewNote(new Note());
    }

    @Override
    public String getName() {
        return "AddButton";
    }
}
