package tests;


import Provided.StoryTestException;
import Provided.StoryTester;
import Solution.StoryTesterImpl;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.Arrays;
import java.util.LinkedList;

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
    private String simpleBadStory;
    private String simpleBadStory2;
    private String simpleBadStory3;
    private String derivedBadStory;
    private String nestedBadStory;
    private String thenBadStory;
    private String thenBadStory2;
    private String thenBadStory3;
    private String thenBadStory4;
    private String thenStory2;
    private Class<?> testClass;
    private Class<?> derivedTestClass;
    private Class<?> nestedNestedTestClass;
    private String goodStory;
    private String badStory;
    private String badStory2;
    private String nestedStory1;
    private String nestedStory2;
    private String nestedStory3;
    private String nestedStory4;


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

        simpleBadStory = "Given a classroom with a capacity of 75\n"
                + "When the number of students in the classroom is 60\n"
                + "Then the classroom is full\n"
                + "When the number of students in the classroom is 80\n"
                + "Then the classroom is not-full";

        simpleBadStory2 = "Given a classroom with a capacity of 75\n"
                + "When the number of students in the classroom is 60\n"
                + "Then the classroom is not-full\n"
                + "When the number of students in the classroom is 80\n"
                + "Then the classroom is not-full";

        simpleBadStory3 = "Given a classroom with a capacity of 75\n"
                + "When the number of students in the classroom is 60\n"
                + "Then the classroom is full\n"
                + "When the number of students in the classroom is 80\n"
                + "Then the classroom is full";

        derivedBadStory = "Given a classroom with a capacity of 50\n"
                + "When the number of students in the classroom is 40\n"
                + "When the number of broken chairs in the classroom is 10\n"
                + "Then the classroom is not-full";

        nestedBadStory = "Given a classroom that the number of seats in it is 1337\n"
                + "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n"
                + "Then the classroom is full";

        thenBadStory = "Given a classroom that the number of seats in it is 1337\n"
                + "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n"
                + "Then the classroom is full and quiet or the classroom is full and noisy";

        thenBadStory2 = "Given a classroom that the number of seats in it is 1337\n"
                + "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n"
                + "Then the classroom is not-full and noisy or the classroom is full and noisy";

        thenBadStory3 = "Given a classroom that the number of seats in it is 1337\n"
                + "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n"
                + "Then the classroom is full and noisy or the classroom is full and noisy";

        thenBadStory4 = "Given a classroom that the number of seats in it is 1337\n"
                + "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n"
                + "Then the classroom is full and quiet or the classroom is not-full and noisy";

        thenStory2 = "Given a classroom that the number of seats in it is 1337\n"
                + "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n"
                + "Then the classroom is full and noisy or the classroom is not-full and quiet";

        //outside tests//
        goodStory = "Given a classroom with a capacity of 75\n"
                + "When the number of students in the classroom is 60\n"
                + "Then the classroom is not-full";

        badStory = "Given a classroom with a capacity of 50\n"
                + "When the number of students in the classroom is 40\n"
                + "When the number of broken chairs in the classroom is 10\n"
                + "Then the classroom is full\n"
                + "When the number of students in the classroom is 40\n"
                + "Then the classroom is not-full";

        badStory2 = "Given a classroom with a capacity of 50\n"
                + "When the number of students in the classroom is 60\n"
                + "Then the classroom is not-full\n"
                + "When the number of students in the classroom is 40\n"
                + "Then the classroom is not-full";

        nestedStory1 = "Given a classroom that the number of seats in it is 33\n"
                + "When the number of students in the classroom is 42 and the number among them that are standing is 6\n"
                + "Then the classroom is not-full and quiet or the classroom is what and quiet";

        nestedStory2 = "Given a classroom with a capacity of 50\n" +
                "When the number of students in the classroom is 40\n" +
                "When the number of broken chairs in the classroom is 10\n" +
                "Then the classroom is full";

        nestedStory3 = "Given a classroom that the number of seats in it is 1337\n" +
                "When the number of students in the classroom is 1378 and the number among them that are standing is 42\n" +
                "Then the classroom is not-full";

        nestedStory4 = "Given a classroom with a capacity of 200\n" +
                "When a dog is in the class, number of chairs he broke is 100\n" +
                "Then the classroom is not-full";

        testClass = tests.ClassroomStoryTest.class;
        derivedTestClass = tests.ClassroomStoryDerivedTest.class;
        nestedNestedTestClass = tests.DogStoryDerivedTest.class;
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

    @Test
    public void test5() throws Exception {
        try {
            tester.testOnInheritanceTree(simpleBadStory, testClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is full", e.getSentance());
            Assert.assertEquals(Arrays.asList("full"), e.getStoryExpected());
            Assert.assertEquals(Arrays.asList("not-full"), e.getTestResult());
            Assert.assertEquals(2, e.getNumFail());
        }
    }

    @Test
    public void test6() throws Exception {
        try {
            tester.testOnInheritanceTree(simpleBadStory2, testClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is not-full", e.getSentance());
            Assert.assertEquals(Arrays.asList("not-full"), e.getStoryExpected());
            Assert.assertEquals(Arrays.asList("full"), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }

    @Test
    public void test7() throws Exception {
        try {
            tester.testOnInheritanceTree(simpleBadStory3, testClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is full", e.getSentance());
            Assert.assertEquals(Arrays.asList("full"), e.getStoryExpected());
            Assert.assertEquals(Arrays.asList("not-full"), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }


    @Test
    public void test8() throws Exception {
        try {
            tester.testOnNestedClasses(derivedBadStory, derivedTestClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is not-full", e.getSentance());
            Assert.assertEquals(Arrays.asList("not-full"), e.getStoryExpected());
            Assert.assertEquals(Arrays.asList("full"), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }

    @Test
    public void test9() throws Exception {
        try {
            tester.testOnNestedClasses(nestedBadStory, derivedTestClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is full", e.getSentance());
            Assert.assertEquals(Arrays.asList("full"), e.getStoryExpected());
            Assert.assertEquals(Arrays.asList("not-full"), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }

    @Test
    public void test10() throws Exception {
        try {
            tester.testOnNestedClasses(thenBadStory, derivedTestClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is full and quiet or the classroom is full and noisy", e.getSentance());
            String expected[] = new String[] {"full", "full"};
            Assert.assertEquals(Arrays.asList(expected), e.getStoryExpected());
            String actual[] = new String[] {"not-full", "not-full"};
            Assert.assertEquals(Arrays.asList(actual), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }

    @Test
    public void test11() throws Exception {
        try {
            tester.testOnNestedClasses(thenBadStory2, derivedTestClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is not-full and noisy or the classroom is full and noisy", e.getSentance());
            String expected[] = new String[] {"noisy", "full"};
            Assert.assertEquals(Arrays.asList(expected), e.getStoryExpected());
            String actual[] = new String[] {"quiet", "not-full"};
            Assert.assertEquals(Arrays.asList(actual), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }

    @Test
    public void test12() throws Exception {
        try {
            tester.testOnNestedClasses(thenBadStory3, derivedTestClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is full and noisy or the classroom is full and noisy", e.getSentance());
            String expected[] = new String[] {"full", "full"};
            Assert.assertEquals(Arrays.asList(expected), e.getStoryExpected());
            String actual[] = new String[] {"not-full", "not-full"};
            Assert.assertEquals(Arrays.asList(actual), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }

    @Test
    public void test13() throws Exception {
        try {
            tester.testOnNestedClasses(thenBadStory4, derivedTestClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is full and quiet or the classroom is not-full and noisy", e.getSentance());
            String expected[] = new String[] {"full", "noisy"};
            Assert.assertEquals(Arrays.asList(expected), e.getStoryExpected());
            String actual[] = new String[] {"not-full", "quiet"};
            Assert.assertEquals(Arrays.asList(actual), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }

    @Test
    public void test14() throws Exception {
        try {
            tester.testOnNestedClasses(thenStory2, derivedTestClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }

    //outside tests//

    @Test
    public void test15() throws Exception {
        try {
            tester.testOnInheritanceTree(goodStory, testClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }

    @Test
    public void test16() throws Exception {
        try {
            tester.testOnNestedClasses(badStory, derivedTestClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is not-full", e.getSentance());
            Assert.assertEquals(Arrays.asList("not-full"), e.getStoryExpected());
            Assert.assertEquals(Arrays.asList("full"), e.getTestResult());
        }
    }

    @Test
    public void test17() throws Exception {
        try {
            tester.testOnNestedClasses(nestedStory1, derivedTestClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is not-full and quiet or the classroom is what and quiet", e.getSentance());
            LinkedList<String> expectedList = new LinkedList<String>();
            expectedList.addLast("not-full");
            expectedList.addLast("what");
            LinkedList<String> resultList = new LinkedList<String>();
            resultList.addLast("full");
            resultList.addLast("full");
            Assert.assertEquals(expectedList, e.getStoryExpected());
            Assert.assertEquals(resultList, e.getTestResult());
        }
    }
    @Test
    public void test18() throws Exception {
        try {
            tester.testOnNestedClasses(nestedStory2, derivedTestClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }

    @Test
    public void test19() throws Exception {
        try {
            tester.testOnNestedClasses(nestedStory3, derivedTestClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }

    @Test
    public void test20() throws Exception {
        try {
            tester.testOnNestedClasses(nestedStory4, nestedNestedTestClass);
            Assert.assertTrue(true);
        } catch (StoryTestException e) {
            Assert.assertTrue(false);
        }
    }

    @Test
    public void backUpTest() throws Exception {
        try {
            tester.testOnNestedClasses(badStory2, testClass);
            Assert.assertTrue(false);
        } catch (StoryTestException e) {
            Assert.assertTrue(true);
            Assert.assertEquals("Then the classroom is not-full", e.getSentance());
            Assert.assertEquals(Arrays.asList("not-full"), e.getStoryExpected());
            Assert.assertEquals(Arrays.asList("full"), e.getTestResult());
            Assert.assertEquals(1, e.getNumFail());
        }
    }

}

