package tests;


import Provided.*;
import Solution.StoryTesterImpl;
import org.junit.Before;
import org.junit.Test;

import java.util.Arrays;

import static java.util.Collections.singletonList;
import static org.junit.Assert.*;

/**
 * This is a minimal test. Write your own tests!
 * Please don't submit your tests!
 */
@SuppressWarnings("Duplicates")
public class DogTest {

    private StoryTester tester;
    private String goodStory;
    private String badStory;
    private String badStoryThenWithAnd;
    private String badStorySingle;
    private String badStoryMulti;
    private String derivedStory;
    private String nestedStory;
    private String badNestedStory;
    private String goodDerivedOrStory;
    private String bdaDerivedOrStory;
    private Class<?> testClass;
    private Class<?> derivedTestClass;

    @Before
    public void setUp() {
        // clean
        goodStory = "Given a Dog of age 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 5\n"
                + "Then the house condition is clean";

        // clean
        badStory = "Given a Dog of age 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 5\n"
                + "Then the house condition is smelly";

        // clean and age is 6;
        badStoryThenWithAnd = "Given a Dog of age 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 5\n"
                + "Then the house condition is clean and dog age is 60";

        // age is 6;
        badStorySingle = "Given a Dog of age 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 5\n"
                + "Then the house condition is clean\n"
                + "Then the house condition is clean and dog age is 60";

        // smelly and 6;
        badStoryMulti = "Given a Dog of age 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 5\n"
                + "Then the house condition is smelly\n"
                + "Then the house condition is clean and dog age is 60";

        derivedStory = "Given a Dog of age 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 15\n"
                + "When the house is cleaned, the number of hours is 11\n"
                + "Then the house condition is clean";

        nestedStory = "Given a Dog that his age is 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 5\n"
                + "Then the house condition is clean";

        badNestedStory = "Given a Dog 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 5\n"
                + "Then the house condition is clean";

        goodDerivedOrStory = "Given a Dog of age 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 15\n"
                + "When the house is cleaned, the number of hours is 11\n"
                + "Then the house condition is smelly or the house condition is clean or the house condition is smelly";

        bdaDerivedOrStory = "Given a Dog of age 6\n"
                + "When the dog is not taken out for a walk, the number of hours is 15\n"
                + "When the house is cleaned, the number of hours is 11\n"
                + "Then the house condition is smelly or the house condition is smelly or the house condition is smelly";


        testClass = tests.Dog.DogStoryTest.class;
        derivedTestClass = tests.Dog.DogStoryDerivedTest.class;
        tester = new StoryTesterImpl();
    }


    @Test
    public void testGoodStory() throws Exception {
        try {
            tester.testOnInheritanceTree(goodStory, testClass);
            assertTrue(true);
        } catch (StoryTestException e) {
            fail();
        }
    }

    @Test
    public void testNoAnnotationInTestClass() throws Exception {
        testClass = tests.Dog.DogStoryTestNoGivenAnnotation.class;
        try {
            tester.testOnInheritanceTree(goodStory, testClass);
            fail();
        } catch (GivenNotFoundException e) {
            assertTrue(true);
        }

        testClass = tests.Dog.DogStoryTestNoWhenAnnotation.class;
        try {
            tester.testOnInheritanceTree(goodStory, testClass);
            fail();
        } catch (WhenNotFoundException e) {
            assertTrue(true);
        }

        testClass = tests.Dog.DogStoryTestNoThenAnnotation.class;
        try {
            tester.testOnInheritanceTree(goodStory, testClass);
            fail();
        } catch (ThenNotFoundException e) {
            assertTrue(true);
        }
    }

    @Test
    public void testIllegalArgument() throws Exception {
        try {
            tester.testOnInheritanceTree(goodStory, null);
            fail();
        } catch (IllegalArgumentException e) {
            assertTrue(true);
        }

        try {
            tester.testOnInheritanceTree(null, testClass);
            fail();
        } catch (IllegalArgumentException e) {
            assertTrue(true);
        }

        try {
            tester.testOnInheritanceTree(null, null);
            fail();
        } catch (IllegalArgumentException e) {
            assertTrue(true);
        }
    }


    @SuppressWarnings("Duplicates")
    @Test
    public void testOnInheritanceTreeBadStory() throws Exception {
        try {
            tester.testOnInheritanceTree(badStory, testClass);
            fail();
        } catch (StoryTestException e) {
            assertEquals("Then the house condition is smelly", e.getSentance());
            assertEquals(singletonList("smelly"), e.getStoryExpected());
            assertEquals(singletonList("clean"), e.getTestResult());
            assertEquals(1, e.getNumFail());
        }

        try {
            tester.testOnInheritanceTree(badStoryThenWithAnd, testClass);
            fail();
        } catch (StoryTestException e) {
            assertEquals("Then the house condition is clean and dog age is 60", e.getSentance());
            assertEquals(singletonList("60"), e.getStoryExpected());
            assertEquals(singletonList("6"), e.getTestResult());
            assertEquals(1, e.getNumFail());
        }

        try {
            tester.testOnInheritanceTree(badStorySingle, testClass);
            fail();
        } catch (StoryTestException e) {
            assertEquals("Then the house condition is clean and dog age is 60", e.getSentance());
            assertEquals(singletonList("60"), e.getStoryExpected());
            assertEquals(singletonList("6"), e.getTestResult());
            assertEquals(1, e.getNumFail());
        }


        try {
            tester.testOnInheritanceTree(badStoryMulti, testClass);
            fail();
        } catch (StoryTestException e) {
            assertEquals("Then the house condition is smelly", e.getSentance());
            assertEquals(singletonList("smelly"), e.getStoryExpected());
            assertEquals(singletonList("clean"), e.getTestResult());
            assertEquals(2, e.getNumFail());
        }
    }

    @Test
    public void testDerived() throws Exception {
        try {
            tester.testOnInheritanceTree(derivedStory, derivedTestClass);
            assertTrue(true);
        } catch (StoryTestException e) {
            fail();
        }

        try {
            tester.testOnNestedClasses(derivedStory, derivedTestClass);
            assertTrue(true);
        } catch (StoryTestException e) {
            fail();
        }
    }

    @Test
    public void testBadStory() throws Exception {
        try {
            tester.testOnNestedClasses(badStory, testClass);
            fail();
        } catch (StoryTestException e) {
            assertEquals("Then the house condition is smelly", e.getSentance());
            assertEquals(singletonList("smelly"), e.getStoryExpected());
            assertEquals(singletonList("clean"), e.getTestResult());
        }
    }

    @Test
    public void testNestedStory() throws Exception {
        try {
            tester.testOnInheritanceTree(nestedStory, derivedTestClass);
            fail();
        } catch (GivenNotFoundException e) {
            assertTrue(true);
        }

        try {
            tester.testOnNestedClasses(nestedStory, derivedTestClass);
            assertTrue(true);
        } catch (StoryTestException e) {
            fail();
        }

        try {
            tester.testOnNestedClasses(badNestedStory, derivedTestClass);
            fail();
        } catch (GivenNotFoundException e) {
            assertTrue(true);
        }

        try {
            tester.testOnNestedClasses(goodDerivedOrStory, derivedTestClass);
            assertTrue(true);
        } catch (StoryTestException e) {
            fail();
        }

        try {
            tester.testOnNestedClasses(bdaDerivedOrStory, derivedTestClass);
            fail();
        } catch (StoryTestException e) {
            assertTrue(true);
            assertEquals("Then the house condition is smelly or the house condition is smelly or the house condition is smelly", e.getSentance());
            assertEquals(Arrays.asList("smelly", "smelly", "smelly"), e.getStoryExpected());
            assertEquals(Arrays.asList("clean", "clean", "clean"), e.getTestResult());
            assertEquals(1, e.getNumFail());
        }
    }

}
