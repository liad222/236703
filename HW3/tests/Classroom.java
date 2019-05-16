package tests;

public class Classroom {
    private Integer freeSpace;

    public Classroom(Integer capacity) {
        this.freeSpace = capacity;
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
        if(classroomCondition().equals("not-full")) {
            return "quiet";
        } else {
            return "noisy";
        }
    }
}
