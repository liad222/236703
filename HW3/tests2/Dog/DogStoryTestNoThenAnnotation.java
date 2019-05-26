package tests.Dog;

import Solution.Given;
import Solution.When;
import org.junit.Assert;

public class DogStoryTestNoThenAnnotation {
	protected tests.Dog.Dog dog;
	@Given("a Dog of age &age")
	public void aDog(Integer age) {
		dog = new tests.Dog.Dog(age);
	}
	
	@When("the dog is not taken out for a walk, the number of hours is &hours")
	public void dogNotTakenForAWalk(Integer hours) {
		dog.notTakenForAWalk(hours);
	}
	
	public void theHouseCondition(String condition) {
		Assert.assertEquals(condition, dog.houseCondition());
	}
}
