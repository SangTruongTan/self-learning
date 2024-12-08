package DesignPatterns.BehavioralPatterns.Iterator.iterators;

import DesignPatterns.BehavioralPatterns.Iterator.profile.Profile;

public interface ProfileIterator {
    boolean hasNext();

    Profile getNext();

    void reset();
}
