package DesignPatterns.BehavioralPatterns.Visitor.visitor;

import DesignPatterns.BehavioralPatterns.Visitor.shapes.Circle;
import DesignPatterns.BehavioralPatterns.Visitor.shapes.CompoundShape;
import DesignPatterns.BehavioralPatterns.Visitor.shapes.Dot;
import DesignPatterns.BehavioralPatterns.Visitor.shapes.Rectangle;

public interface Visitor {

    String visit(Dot dot);

    String visit(Circle circle);

    String visit(Rectangle rectangle);

    String visit(CompoundShape cg);
}
