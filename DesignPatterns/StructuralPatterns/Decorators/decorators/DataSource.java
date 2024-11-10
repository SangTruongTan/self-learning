package DesignPatterns.StructuralPatterns.Decorators.decorators;

public interface DataSource {
    void writeData(String data);

    String readData();
}
