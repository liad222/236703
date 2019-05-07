package Solution;

import Provided.StoryTestException;

import java.util.ArrayList;
import java.util.List;

public class StoryTestExceptionImpl extends StoryTestException {
    private String sentence;
    private int numFails;
    private List<String> expected;
    private List<String> actual;

    public StoryTestExceptionImpl(){
        sentence = null;
        numFails = 0;
        expected = new ArrayList<>();
        actual = new ArrayList<>();
    }
    @Override
    public String getSentance() {
        return sentence;
    }

    @Override
    public List<String> getStoryExpected() {
        return expected;
    }

    @Override
    public List<String> getTestResult() {
        return actual;
    }

    @Override
    public int getNumFail() {
        return numFails;
    }

    public StoryTestExceptionImpl setSentence(String str){
        sentence = new String(str);
        return this;
    }

    public StoryTestExceptionImpl setStoryExpected(ArrayList<String> list){
        expected = new ArrayList<>(list);
        return this;
    }

    public StoryTestExceptionImpl setStoryActual(ArrayList<String> list){
        actual = new ArrayList<>(list);
        return this;
    }

    public StoryTestExceptionImpl incNumFails(){
        numFails++;
        return this;
    }
}
