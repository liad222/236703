package tests;

public class Classroom implements Cloneable{
    private Integer freeSpace;

    public Object clone()throws CloneNotSupportedException{
        return new Classroom(this.freeSpace);
    }
    public Classroom(Classroom c){
        this.freeSpace = c.getFreeSpace();
    }
    public Classroom(Integer capacity) {
        this.freeSpace = capacity;
    }
    public int getFreeSpace(){
        return this.freeSpace;
    }

    public void numberOfStudents(Integer numberOfStudents) {
        this.freeSpace -= numberOfStudents;
    }

    public void brokenChairs(Integer numberOfBrokenChairs) {
        this.freeSpace -= numberOfBrokenChairs;
    }

    public String classroomCondition() {
        return this.freeSpace > 0 ? "not-full" : "full";
    }

    public String classroomNoiseCondition() {
        return this.freeSpace > 0 ? "quiet" : "noisy";
    }
}
