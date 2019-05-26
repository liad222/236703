package tests.Dog;

import Solution.Given;
import Solution.Then;
import org.junit.Assert;

public class DogStoryTestNoWhenAnnotation {
	protected tests.Dog.Dog dog;

	@Given("a Dog of age &age")
	public void aDog(Integer age) {
		dog = new tests.Dog.Dog(age);
	}
	
	public void dogNotTakenForAWalk(Integer hours) {
		dog.notTakenForAWalk(hours);
	}
	
	@Then("the house condition is &condition")
	public void theHouseCondition(String condition) {
		Assert.assertEquals(condition, dog.houseCondition());
	}
}
