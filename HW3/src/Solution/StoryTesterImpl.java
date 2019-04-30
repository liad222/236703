package Solution;

import Provided.StoryTester;


import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;


public class StoryTesterImpl implements StoryTester {


    protected ArrayList<ArrayList> parser(String story){
        ArrayList<ArrayList> sentences = new ArrayList<>();
        String[] words = story.split(" ");
        int counter = -1;
        for(String word: words){
            if( word.equals("Given")  || word.equals("Then") || word.equals("When")){
                counter++;
                ArrayList<String> new_sentence = new ArrayList<>();
                sentences.add(counter, new_sentence);
            }
            ArrayList<String> sentence = sentences.get(counter);
            sentence.add(word);
        }
        return sentences;
    }

    @SuppressWarnings("Duplicates")
    protected ArrayList<ArrayList> compareGiven(ArrayList<String> sentence, Given g){
       String[] words = g.value().split(" ");
       ArrayList<ArrayList> params = new ArrayList<>();
       ArrayList<String> param_inst = new ArrayList<>();
       params.add(param_inst);
       if(words.length != sentence.size()){
           return params;
       }

       for(int counter = 0; counter < words.length; counter++ ){
           if(words[counter].charAt(0) == '&'){
               ArrayList<String> temp = params.get(0);
               temp.add(sentence.get(counter));
               continue;
           }
           if(words[counter] != sentence.get(counter)){
               params = new ArrayList<>();
               return params;
           }
       }
       return params;
    }

    @SuppressWarnings("Duplicates")
    protected ArrayList<ArrayList> compareWhen(ArrayList<String> sentence, When w){
        String[] words = w.value().split(" ");
        ArrayList<ArrayList> params = new ArrayList<>();
        ArrayList<String> param_inst = new ArrayList<>();
        params.add(param_inst);
        if(words.length != sentence.size()){
            return params;
        }

        for(int counter = 0; counter < words.length; counter++ ){
            if(words[counter].charAt(0) == '&'){
                ArrayList<String> temp = params.get(0);
                temp.add(sentence.get(counter));
                continue;
            }
            if(words[counter] != sentence.get(counter)){
                params = new ArrayList<>();
                return params;
            }
        }
        return params;
    }

    protected ArrayList<ArrayList> compareThen(ArrayList<String> sentence, Then t){
        String[] words = t.value().split(" ");
        ArrayList<ArrayList> params = new ArrayList<>();
        if(sentence.size() < words.length){
            return params;
        }
        int words_counter = 0;
        ArrayList<String> param_inst = new ArrayList<>();
        params.add(param_inst);
        for(int counter = 0; counter < sentence.size(); counter++){
            if(words[words_counter].charAt(0) == '&'){
                ArrayList<String> temp = params.get(params.size() - 1);
                temp.add(sentence.get(counter));
                words_counter++;
                continue;
            }
            if(sentence.get(counter).equals("or")){
                words_counter = 0;
                ArrayList<String> new_param_inst = new ArrayList<>();
                params.add(new_param_inst);
                continue;
            }
            if(words[words_counter] != sentence.get(counter)){
                params = new ArrayList<>();
                return params;
            }
            words_counter++;
        }
        return params;
    }

    @SuppressWarnings("Duplicates")
    protected HashMap<String,ArrayList<ArrayList>> getMethod(ArrayList<String> sentence, Class<?> testClass){
        String keyword = sentence.get(0);
        Method[] methods = testClass.getDeclaredMethods();
        List<Method> filtered = new ArrayList<>();
        HashMap<String, ArrayList<ArrayList>> right_method = new HashMap<>();
        if(keyword.equals("Given")) {
            filtered = Arrays.stream(methods).filter(m -> m.isAnnotationPresent(Given.class)).collect(Collectors.toList());
            for( Method m: filtered){
                ArrayList<ArrayList> temp_params = compareGiven(sentence, m.getAnnotation(Given.class));
                if(!(temp_params.isEmpty())){
                    right_method.put(m.getName(),temp_params);
                    break;
                }
            }
            return right_method;
        }
        else if(keyword.equals("When")) {
            filtered = Arrays.stream(methods).filter(m -> m.isAnnotationPresent(When.class)).collect(Collectors.toList());
            for( Method m: filtered){
                ArrayList<ArrayList> temp_params = compareWhen(sentence, m.getAnnotation(When.class));
                if(!(temp_params.isEmpty())){
                    right_method.put(m.getName(),temp_params);
                    break;
                }
            }
            return right_method;
        }
        else {
            filtered = Arrays.stream(methods).filter(m -> m.isAnnotationPresent(Then.class)).collect(Collectors.toList());
            for( Method m: filtered){
                ArrayList<ArrayList> temp_params = compareThen(sentence, m.getAnnotation(Then.class));
                if(!(temp_params.isEmpty())){
                    right_method.put(m.getName(),temp_params);
                    break;
                }
            }
            return right_method;
        }
    }



    @Override
    public void testOnInheritanceTree(String story, Class<?> testClass) throws Exception {
        if(story == null || testClass == null){
            throw new IllegalArgumentException();
        }
        Object inst = testClass.newInstance();

    }

    @Override
    public void testOnNestedClasses(String story, Class<?> testClass) throws Exception {
        if(story == null || testClass == null){
            throw new IllegalArgumentException();
        }

    }
}
