package tests;


import Provided.StoryTestException;
import Provided.StoryTester;
import Solution.StoryTesterImpl;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.Arrays;

/**
 * This is a minimal test. Write your own tests!
 * Please don't submit your tests!
 */
public class ClassroomTest {

    private StoryTester tester;
    private String simpleStory;
    private String derivedStory;
    private String nestedStory;
    private String thenStory;
    private Class<?> testClass;
    private Class<?> derivedTestClass;

    @Before
    public void setUp() throws Exception {

        simpleStory = "Given a classroom with a capacity of 75\n"
                + "When the number of students in the classroom is 60\n"
                + "Then the classroom is not-full\n"
                + "When the number of students in the classroom is 80\n"
                + "Then the classroom is full";

        derivedStory = "Given a classroom with a capacity of 50\n"
                + "When the number of students in the classroom is 40\n"
                + "When the number of broken chairs in the classroom is 10\n"
                + "Then the classroom is full";

        nestedStory = "Given a classroom that the number of seats in it is 1337\n"
                + "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n"
                + "Then the classroom is not-full";

        thenStory = "Given a classroom that the number of seats in it is 1337\n"
                + "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n"
                + "Then the classroom is not-full and quiet or the classroom is full and noisy";

        testClass = tests.ClassroomStoryTest.class;
        derivedTestClass = tests.ClassroomStoryDerivedTest.class;
        tester = new StoryTesterImpl();
    }

    @Test
    public void test1() throws Exception {
        try {
            tester.testOnInheritanceTree(simpleStory, testClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }

    @Test
    public void test2() throws Exception {
        try {
            tester.testOnNestedClasses(derivedStory, derivedTestClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }

    @Test
    public void test3() throws Exception {
        try {
            tester.testOnNestedClasses(nestedStory, derivedTestClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }
    @Test
    public void test4() throws Exception {
        try {
            tester.testOnNestedClasses(thenStory, derivedTestClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }

}
