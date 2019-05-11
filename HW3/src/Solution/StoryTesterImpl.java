package Solution;

import Provided.*;
import org.junit.ComparisonFailure;


import java.lang.reflect.*;
import java.util.*;
import java.util.stream.Collectors;


public class StoryTesterImpl implements StoryTester {

    //receives a story and breaks it down to a list of sentences.
    protected ArrayList<ArrayList> parser(String story){
        ArrayList<ArrayList> sentences = new ArrayList<>();
        String[] lines = story.split("\n");
        int counter = -1;
        for(String line: lines){
            String[] words = line.split(" ") ;
            counter++;
            ArrayList<String> new_sentence = new ArrayList<>();
            sentences.add(counter, new_sentence);
            ArrayList<String> sentence = sentences.get(counter);
            for(String word: words){
                sentence.add(word);
            }
        }
        return sentences;
    }


    //receives a sentence and a Given annotation, checks if the sentence and the annotation match.
    //if yes, returns a list of parameters otherwise returns an empty list.
    @SuppressWarnings("Duplicates")
    protected ArrayList<ArrayList> compareGiven(ArrayList<String> origSentence, Given g){
       String[] words = g.value().split(" ");
       ArrayList<ArrayList> params = new ArrayList<>();
       ArrayList<String> param_inst = new ArrayList<>();
       params.add(param_inst);
       ArrayList<String> sentence = new ArrayList<>(origSentence);
       sentence.remove(0);
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

    //receives a sentence and a When annotation, checks if the sentence and the annotation match.
    //if yes, returns a list of parameters otherwise returns an empty list.
    @SuppressWarnings("Duplicates")
    protected ArrayList<ArrayList> compareWhen(ArrayList<String> origSentence, When w){
        String[] words = w.value().split(" ");
        ArrayList<ArrayList> params = new ArrayList<>();
        ArrayList<String> param_inst = new ArrayList<>();
        params.add(param_inst);
        ArrayList<String> sentence = new ArrayList<>(origSentence);
        sentence.remove(0);
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

    //receives a sentence and a Then annotation, checks if the sentence and the annotation match.
    //if yes, returns a list of parameters otherwise returns an empty list.
    //In this function we deal with the word "OR" differently.
    protected ArrayList<ArrayList> compareThen(ArrayList<String> origSentence, Then t){
        String[] words = t.value().split(" ");
        ArrayList<ArrayList> params = new ArrayList<>();
        ArrayList<String> sentence = new ArrayList<>(origSentence);
        sentence.remove(0);
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

    //receives a sentence and a class and checks if the class has a matching annotation.
    //If yes, returns a singelton map from the name of the right method to the matching parameters,
    // otherwise an empty map.
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


        //receives a sentence and a class and checks recursively in the class inheritance tree if there is a matching method to the sentence.
        //this function uses the getMethod function.
    protected HashMap<String,ArrayList<ArrayList>> checkClassTree(ArrayList<String> sentence, Class<?> testClass){
        if(testClass == null){
            return new HashMap<String, ArrayList<ArrayList>>();
        }
        HashMap<String, ArrayList<ArrayList>> right_method = getMethod(sentence, testClass);
        if(!(right_method.isEmpty())){
            return right_method;
        }
        return checkClassTree(sentence, testClass.getSuperclass());
    }

    //receives a list of params and an array of classes with size equals to the number of params.
    //checks if each param is string or int, and inserting the the type of the param to the corresponding place in the array of classes.
    //eventually returns an array of Objects with String or Int types according to the checking above.
    protected Object[] convertParams(ArrayList<String> origins, Class[] types){
        int counter = 0;
        Object[] params = new Object[types.length];
        for(String origin: origins){
            try{
                int i = Integer.parseInt(origin);
                types[counter] = Integer.class;
                params[counter] = i;
                counter++;
            }catch(NumberFormatException e){
                types[counter] = String.class;
                params[counter] = origin;
                counter++;
            }
        }
        return params;
    }

    //receives an array of words and join them to a String.
    protected String joinSentence(ArrayList<String> sentence){
        String str = new String(sentence.get(0));
        for(String word: sentence){
            str = str.concat(" " + word);
        }
        return str;
    }


    protected Object[] doBackup(Field[] origin){
        Object[] backup = new Object[origin.length];
        int counter = 0;
        for(Field f:origin){
            try{
                Class<?> cl = f.getClass();
                Method c = f.getClass().getDeclaredMethod("clone");
                c.setAccessible(true);
                Object fNew = c.invoke(f);
                backup[counter] = fNew;
                counter++;
            }catch(Exception e){
                try{
                    Constructor<?> c = f.getClass().getDeclaredConstructor(f.getClass());
                    c.setAccessible(true);
                    Object fNew = c.newInstance(f);
                    backup[counter] = fNew;
                    counter++;
                }catch (Exception e1){
                    backup[counter] = f;
                    counter++;
                }
            }
        }
        return backup;
    }


    @Override
    public void testOnInheritanceTree(String story, Class<?> testClass) throws Exception {
        if(story == null || testClass == null){
            throw new IllegalArgumentException();
        }
        boolean already = false;
        Object[] backup = null;
        Object inst = testClass.newInstance();
        ArrayList<ArrayList> sentences = parser(story);
        StoryTestExceptionImpl excep = new StoryTestExceptionImpl();
        for(ArrayList<String> sentence: sentences){
            String firstWord = sentence.get(0);
            if(firstWord.equals("Given")){
                HashMap<String, ArrayList<ArrayList>> right_method = checkClassTree(sentence, testClass);
                if(right_method.isEmpty()){
                    throw new GivenNotFoundException();
                }
                List<String> methodNames = right_method.entrySet().stream().map(Map.Entry::getKey).collect(Collectors.toList());
                List<ArrayList<ArrayList>> methodParams = right_method.entrySet().stream().map(Map.Entry::getValue).collect(Collectors.toList());
                ArrayList<String> params = methodParams.get(0).get(0);
                Class[] c = new Class[params.size()];
                Object[] convertedParams = convertParams(params, c);
                Method m = testClass.getMethod((methodNames.get(0)), c);
                m.invoke(inst, convertedParams);
            }
            if(firstWord.equals("When")){
                HashMap<String, ArrayList<ArrayList>> right_method = checkClassTree(sentence, testClass);
                if(right_method.isEmpty()){
                    throw new WhenNotFoundException();
                }
                if(!already){
                    Field[] origin = testClass.getDeclaredFields();
                    backup = doBackup(origin);
                    already = true;
                }
                List<String> methodNames = right_method.entrySet().stream().map(Map.Entry::getKey).collect(Collectors.toList());
                List<ArrayList<ArrayList>> methodParams = right_method.entrySet().stream().map(Map.Entry::getValue).collect(Collectors.toList());
                ArrayList<String> params = methodParams.get(0).get(0);
                Class[] c = new Class[params.size()];
                Object[] convertedParams = convertParams(params, c);
                Method m = testClass.getMethod((methodNames.get(0)), c);
                m.invoke(inst, convertedParams);
            }
            if(firstWord.equals("Then")){
                HashMap<String, ArrayList<ArrayList>> right_method = checkClassTree(sentence, testClass);
                if(right_method.isEmpty()){
                    throw new ThenNotFoundException();
                }
                List<String> methodNames = right_method.entrySet().stream().map(Map.Entry::getKey).collect(Collectors.toList());
                List<ArrayList<ArrayList>> methodParams = right_method.entrySet().stream().map(Map.Entry::getValue).collect(Collectors.toList());
                ArrayList<ArrayList> runs = methodParams.get(0);
                ArrayList<String> expected = new ArrayList<>();
                ArrayList<String> actual = new ArrayList<>();
                boolean success = false;
                for(ArrayList<String> run: runs){
                    Class[] c = new Class[run.size()];
                    Object[] convertedParams = convertParams(run, c);
                    Method m = testClass.getMethod((methodNames.get(0)), c);
                    try{
                        m.invoke(inst, convertedParams);
                        success = true;
                        break;
                    }catch(ComparisonFailure e){
                        expected.add(e.getExpected());
                        actual.add(e.getActual());
                    }
                }
                if(!success){
                    excep.incNumFails();
                    if(excep.getNumFail() == 1){
                        excep.setSentence(joinSentence(sentence));
                        excep.setStoryExpected(expected);
                        excep.setStoryActual(actual);
                    }
                    Field[] fields = testClass.getDeclaredFields();
                    int counter = 0;
                    for (Field f : fields) {
                        f.setAccessible(true);
                        f.set(inst,backup[counter]);
                        counter++;
                    }
                }
            }
        }
        if(excep.getNumFail() > 0){
            throw excep;
        }
    }

    @Override
    public void testOnNestedClasses(String story, Class<?> testClass) throws Exception {
        if(story == null || testClass == null){
            throw new IllegalArgumentException();
        }
        boolean already = false;
        Object[] backup = null;
        Object inst = testClass.newInstance();
        ArrayList<ArrayList> sentences = parser(story);
        StoryTestExceptionImpl excep = new StoryTestExceptionImpl();
        for(ArrayList<String> sentence: sentences){
            String firstWord = sentence.get(0);
            if(firstWord.equals("Given")){
                HashMap<String, ArrayList<ArrayList>> right_method = checkClassTree(sentence, testClass);
                if(right_method.isEmpty()){
                    Class<?>[] nested = testClass.getDeclaredClasses();
                    for(Class<?> cla: nested){
                        try{
                            if(cla.isInterface()){
                                continue;
                            }
                            testOnNestedClasses(story,cla);
                            return;
                        }catch(StoryTestExceptionImpl | WhenNotFoundException | ThenNotFoundException e1){
                            throw e1;
                        }catch (GivenNotFoundException e2){
                            continue;
                        }
                    }
                    throw new GivenNotFoundException();
                }
                List<String> methodNames = right_method.entrySet().stream().map(Map.Entry::getKey).collect(Collectors.toList());
                List<ArrayList<ArrayList>> methodParams = right_method.entrySet().stream().map(Map.Entry::getValue).collect(Collectors.toList());
                ArrayList<String> params = methodParams.get(0).get(0);
                Class[] c = new Class[params.size()];
                Object[] convertedParams = convertParams(params, c);
                Method m = testClass.getMethod((methodNames.get(0)), c);
                m.invoke(inst, convertedParams);
            }
            if(firstWord.equals("When")){
                HashMap<String, ArrayList<ArrayList>> right_method = checkClassTree(sentence, testClass);
                if(right_method.isEmpty()){
                    throw new WhenNotFoundException();
                }
                if(!already){
                    Field[] origin = testClass.getDeclaredFields();
                    backup = doBackup(origin);
                    already = true;
                }
                List<String> methodNames = right_method.entrySet().stream().map(Map.Entry::getKey).collect(Collectors.toList());
                List<ArrayList<ArrayList>> methodParams = right_method.entrySet().stream().map(Map.Entry::getValue).collect(Collectors.toList());
                ArrayList<String> params = methodParams.get(0).get(0);
                Class[] c = new Class[params.size()];
                Object[] convertedParams = convertParams(params, c);
                Method m = testClass.getMethod((methodNames.get(0)), c);
                m.invoke(inst, convertedParams);
            }
            if(firstWord.equals("Then")){
                HashMap<String, ArrayList<ArrayList>> right_method = checkClassTree(sentence, testClass);
                if(right_method.isEmpty()){
                    throw new ThenNotFoundException();
                }
                List<String> methodNames = right_method.entrySet().stream().map(Map.Entry::getKey).collect(Collectors.toList());
                List<ArrayList<ArrayList>> methodParams = right_method.entrySet().stream().map(Map.Entry::getValue).collect(Collectors.toList());
                ArrayList<ArrayList> runs = methodParams.get(0);
                ArrayList<String> expected = new ArrayList<>();
                ArrayList<String> actual = new ArrayList<>();
                boolean success = false;
                for(ArrayList<String> run: runs){
                    Class[] c = new Class[run.size()];
                    Object[] convertedParams = convertParams(run, c);
                    Method m = testClass.getMethod((methodNames.get(0)), c);
                    try{
                        m.invoke(inst, convertedParams);
                        success = true;
                        break;
                    }catch(ComparisonFailure e){
                        expected.add(e.getExpected());
                        actual.add(e.getActual());
                    }
                }
                if(!success){
                    excep.incNumFails();
                    if(excep.getNumFail() == 1){
                        excep.setSentence(joinSentence(sentence));
                        excep.setStoryExpected(expected);
                        excep.setStoryActual(actual);
                    }
                    Field[] fields = testClass.getDeclaredFields();
                    int counter = 0;
                    for (Field f : fields) {
                        f.setAccessible(true);
                        f.set(inst,backup[counter]);
                        counter++;
                    }
                }
            }
        }
        if(excep.getNumFail() > 0){
            throw excep;
        }
    }
}
