package DesignPatterns.BehavioralPatterns.Visitor.shapes;

import DesignPatterns.BehavioralPatterns.Visitor.visitor.Visitor;

public interface Shape {

    void move(int x, int y);

    void draw();

    String accept(Visitor visitor);
}
