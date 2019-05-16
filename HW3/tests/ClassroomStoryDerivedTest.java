package tests;

import Solution.Given;
import Solution.When;

public class ClassroomStoryDerivedTest extends tests.ClassroomStoryTest {
    @When("the number of broken chairs in the classroom is &broken")
    private void classroomIsWIthBrokenChairs(Integer broken) {
        classroom.brokenChairs(broken);
    }
    public class InnerClass extends tests.ClassroomStoryTest {
        @Given("a classroom that the number of seats in it is &seats")
        public void aClassroom(Integer seats) {
            classroom = new tests.Classroom(seats);
        }
        @When("the number of students in the classroom is &students and the " +
                "number among them that are standing is &standing")
                private void classroomIsWIthStandingStudents(Integer students, Integer standing){
            classroom.numberOfStudents(students - standing);
        }
    }

}
