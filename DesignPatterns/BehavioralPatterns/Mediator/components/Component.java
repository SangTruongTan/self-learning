package DesignPatterns.BehavioralPatterns.Mediator.components;

import DesignPatterns.BehavioralPatterns.Mediator.mediator.Mediator;

/**
 * Common component interface.
 */
public interface Component {
    void setMediator(Mediator mediator);
    String getName();
}
