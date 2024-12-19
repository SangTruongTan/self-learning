package DesignPatterns.BehavioralPatterns.Iterator.social_networks;

import DesignPatterns.BehavioralPatterns.Iterator.iterators.ProfileIterator;

public interface SocialNetwork {
    ProfileIterator createFriendsIterator(String profileEmail);

    ProfileIterator createCoworkersIterator(String profileEmail);
}
