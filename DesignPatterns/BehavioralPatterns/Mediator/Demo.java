package DesignPatterns.BehavioralPatterns.Mediator;

import DesignPatterns.BehavioralPatterns.Mediator.components.*;
import DesignPatterns.BehavioralPatterns.Mediator.mediator.Editor;
import DesignPatterns.BehavioralPatterns.Mediator.mediator.Mediator;

import javax.swing.*;

/**
 * Demo class. Everything comes together here.
 */
public class Demo {
    public static void main(String[] args) {
        Mediator mediator = new Editor();

        mediator.registerComponent(new Title());
        mediator.registerComponent(new TextBox());
        mediator.registerComponent(new AddButton());
        mediator.registerComponent(new DeleteButton());
        mediator.registerComponent(new SaveButton());
        mediator.registerComponent(new List(new DefaultListModel()));
        mediator.registerComponent(new Filter());

        mediator.createGUI();
    }
}