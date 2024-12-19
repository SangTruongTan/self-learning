package DesignPatterns.StructuralPatterns.Facade.some_complex_media_library;

import java.io.File;

public class AudioMixer {
    public File fix(VideoFile result) {
        System.out.println("AudiMixer: fixing audio...");
        return new File("tmp");
    }
}
