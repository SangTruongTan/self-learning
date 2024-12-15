package DesignPatterns.BehavioralPatterns.Observer;

import DesignPatterns.BehavioralPatterns.Observer.editor.Editor;
import DesignPatterns.BehavioralPatterns.Observer.listeners.EmailNotificationListener;
import DesignPatterns.BehavioralPatterns.Observer.listeners.LogOpenListener;

public class Demo {

    @SuppressWarnings("CallToPrintStackTrace")
    public static void main(String[] args) {
        Editor editor = new Editor();
        editor.events.subscribe("open", new LogOpenListener("file.txt"));
        editor.events.subscribe("save", new EmailNotificationListener("admin@example.com"));

        try {
            editor.openFile("file.txt");
            editor.saveFile();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
